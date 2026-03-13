/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * 8xv2_add.c — Matrix 8XV2 Add keyboard glue
 *
 * Responsibilities:
 *   · IS31FL3731 / WS2812 custom rgb_matrix driver
 *   · Boot-time and hot-swap module detection (STM32F1 IDR trick)
 *   · Mirror LED buffer → enables SYNC brightness scaling
 *   · EEPROM init / read
 *   · VIA custom channel
 *   · QMK callbacks: rgb_matrix_indicators_kb, housekeeping_task_kb
 *
 * Animation logic: lib/module_effects.c
 */
#include "quantum.h"
#include "8xv2_add.h"
#include "i2c_master.h"
#include "is31fl3731.h"
#include "ws2812.h"
#include "hal.h"

#if defined(RGB_MATRIX_ENABLE) && defined(RGBLIGHT_ENABLE)
#    error "Disable RGBLIGHT_ENABLE when RGB_MATRIX_ENABLE is set"
#endif

void board_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

/* ════════════════════════════════════════════════════════════════
 * IS31FL3731 LED MAP  (indices 0–19)
 * ════════════════════════════════════════════════════════════════ */
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    {0, C9_5,  C8_5,  C7_5},  //  0 ring
    {0, C9_6,  C8_6,  C7_6},  //  1
    {0, C9_7,  C8_7,  C6_6},  //  2
    {0, C9_8,  C7_7,  C6_7},  //  3
    {0, C1_1,  C3_2,  C4_2},  //  4
    {0, C1_2,  C2_2,  C4_3},  //  5
    {0, C1_3,  C2_3,  C3_3},  //  6
    {0, C1_4,  C2_4,  C3_4},  //  7
    {0, C1_5,  C2_5,  C3_5},  //  8
    {0, C1_6,  C2_6,  C3_6},  //  9
    {0, C1_7,  C2_7,  C3_7},  // 10
    {0, C1_8,  C2_8,  C3_8},  // 11
    {0, C9_1,  C8_1,  C7_1},  // 12
    {0, C9_2,  C8_2,  C7_2},  // 13
    {0, C9_3,  C8_3,  C7_3},  // 14
    {0, C9_4,  C8_4,  C7_4},  // 15
    {0, C1_11, C2_11, C3_11}, // 16 TL
    {0, C1_12, C2_12, C3_12}, // 17 TR
    {0, C1_9,  C3_10, C4_10}, // 18 BR
    {0, C1_10, C2_10, C4_11}, // 19 BL
};

/* ════════════════════════════════════════════════════════════════
 * GLOBALS
 * ════════════════════════════════════════════════════════════════ */
kb_eeprom_t     g_kb_config;
module_active_t g_active_module = MODULE_ACTIVE_IS31;

/* ════════════════════════════════════════════════════════════════
 * MIRROR LED BUFFER
 *
 * Every _set_color call writes here AND to the hardware driver.
 * _get_color reads from here.
 *
 * Purpose: SYNC mode reads back what QMK's effect just rendered,
 * scales by cfg->v, and writes back — giving per-zone brightness
 * control over the active QMK effect.
 *
 * Flow:
 *   1. rgb_matrix_task runs effect → calls _set_color for all LEDs
 *      → values land in s_led_buf AND hardware driver buffer
 *   2. rgb_matrix_indicators_kb is called
 *   3. In SYNC mode: module_effects reads s_led_buf via _get_color,
 *      scales, writes scaled values back
 *   4. flush() sends hardware buffer to LEDs
 * ════════════════════════════════════════════════════════════════ */
static RGB s_led_buf[IS31FL3731_LED_COUNT];

static void _set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index >= 0 && index < IS31FL3731_LED_COUNT)
        s_led_buf[index] = (RGB){r, g, b};
    if (g_active_module == MODULE_ACTIVE_IS31)
        is31fl3731_set_color(index, r, g, b);
    else
        ws2812_set_color(index, r, g, b);
}

static RGB _get_color(int index) {
    if (index >= 0 && index < IS31FL3731_LED_COUNT)
        return s_led_buf[index];
    return (RGB){0, 0, 0};
}

/* ════════════════════════════════════════════════════════════════
 * BOOT-TIME DETECTION
 * PB7 as input: IS31 pull-up (4.7kΩ) → HIGH; WS2812 GND → LOW.
 * Majority vote of 3 readings after 50ms settle.
 * ════════════════════════════════════════════════════════════════ */
static bool read_pin_boot(void) {
    palSetPadMode(GPIOB, 6, PAL_MODE_INPUT_PULLDOWN);
    palSetPadMode(GPIOB, 7, PAL_MODE_INPUT_PULLDOWN);
    wait_ms(50);
    uint8_t high = 0;
    for (uint8_t i = 0; i < 3; i++) {
        if (palReadPad(GPIOB, 7) == PAL_HIGH) high++;
        wait_ms(10);
    }
    bool det = (high >= 2);
    if (det) {
        palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
        palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    }
    return det;
}

/* ════════════════════════════════════════════════════════════════
 * HOT-SWAP DETECTION — NON-BLOCKING
 * STM32F1 RM §9.1.4: IDR readable even when pin is in AF mode.
 * Case A (IS31 active): read IDR[7] directly — I2C unaffected.
 * Case B (WS active):   tristate PB7 for 2µs inside WS2812 reset.
 * ════════════════════════════════════════════════════════════════ */
#define HOTSWAP_CHECK_INTERVAL_MS 200
#define HOTSWAP_CONFIRM_COUNT     5

static uint32_t hotswap_timer = 0;
static uint8_t  confirm_is31  = 0;
static uint8_t  confirm_ws    = 0;

static bool read_pin_nonblocking(void) {
    if (g_active_module == MODULE_ACTIVE_IS31) {
        return (GPIOB->IDR & (1U << 7)) != 0;
    } else {
        GPIOB->CRL = (GPIOB->CRL & ~(0xFU << 28)) | (0x8U << 28);
        wait_us(2);
        bool high = (GPIOB->IDR & (1U << 7)) != 0;
        GPIOB->CRL = (GPIOB->CRL & ~(0xFU << 28)) | (0x3U << 28);
        return high;
    }
}

/* ════════════════════════════════════════════════════════════════
 * DRIVER START / STOP
 * ════════════════════════════════════════════════════════════════ */
static void start_is31(void) {
    palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
    i2c_init();
    is31fl3731_init(0);
    for (uint8_t i = 0; i < IS31FL3731_LED_COUNT; i++)
        is31fl3731_set_led_control_register(i, true, true, true);
    is31fl3731_update_led_control_registers(0);
    g_active_module = MODULE_ACTIVE_IS31;
    confirm_is31 = confirm_ws = 0;
}
static void stop_is31(void) {
    is31fl3731_set_color_all(0, 0, 0);
    is31fl3731_update_pwm_buffers(0);
    i2cStop(&I2CD1);
}
static void start_ws2812(void) {
    palSetPadMode(GPIOB, 7, PAL_MODE_OUTPUT_PUSHPULL);
    palWritePad(GPIOB, 7, 0);
    ws2812_init();
    g_active_module = MODULE_ACTIVE_WS;
    confirm_is31 = confirm_ws = 0;
}
static void stop_ws2812(void) {
    ws2812_set_color_all(0, 0, 0);
    ws2812_flush();
}

/* ════════════════════════════════════════════════════════════════
 * CUSTOM RGB MATRIX DRIVER
 * ════════════════════════════════════════════════════════════════ */
static void rgb_matrix_driver_init(void) {
    eeconfig_read_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));
    if (g_kb_config.module_sel > MODULE_SEL_WS) g_kb_config.module_sel = MODULE_SEL_AUTO;

    bool use_is31;
    if      ((module_sel_t)g_kb_config.module_sel == MODULE_SEL_IS31) use_is31 = true;
    else if ((module_sel_t)g_kb_config.module_sel == MODULE_SEL_WS)   use_is31 = false;
    else                                                               use_is31 = read_pin_boot();

    if (use_is31) start_is31(); else start_ws2812();
}
static void rgb_matrix_driver_flush(void) {
    if (g_active_module == MODULE_ACTIVE_IS31) is31fl3731_update_pwm_buffers(0);
    else                                       ws2812_flush();
}
static void rgb_matrix_driver_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    if (g_active_module == MODULE_ACTIVE_IS31) is31fl3731_set_color_all(r, g, b);
    else                                       ws2812_set_color_all(r, g, b);
    for (uint8_t i = 0; i < IS31FL3731_LED_COUNT; i++)
        s_led_buf[i] = (RGB){r, g, b};
}

// clang-format off
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = rgb_matrix_driver_init,
    .flush         = rgb_matrix_driver_flush,
    .set_color     = _set_color,
    .set_color_all = rgb_matrix_driver_set_color_all,
};
// clang-format on

/* ════════════════════════════════════════════════════════════════
 * HOT-SWAP TASK
 * ════════════════════════════════════════════════════════════════ */
static void hotswap_check(void) {
    if ((module_sel_t)g_kb_config.module_sel != MODULE_SEL_AUTO) return;
    bool now_is31 = read_pin_nonblocking();
    if (now_is31) { confirm_ws = 0;    if (confirm_is31 < HOTSWAP_CONFIRM_COUNT) confirm_is31++; }
    else          { confirm_is31 = 0;  if (confirm_ws   < HOTSWAP_CONFIRM_COUNT) confirm_ws++;   }
    if (confirm_is31 >= HOTSWAP_CONFIRM_COUNT && g_active_module != MODULE_ACTIVE_IS31) {
        stop_ws2812(); start_is31();
    } else if (confirm_ws >= HOTSWAP_CONFIRM_COUNT && g_active_module != MODULE_ACTIVE_WS) {
        stop_is31(); start_ws2812();
    }
}

/* ════════════════════════════════════════════════════════════════
 * CENTER — INDICATOR LOGIC  (keyboard-specific modes above library max)
 *
 * Modes CENTER_IND_CAPS / NUM / SCROLL are not animations — they
 * light all 4 LEDs solid when the matching lock is active.
 * Returns true if handled here; false = let the library render.
 * ════════════════════════════════════════════════════════════════ */
static void blank_zone(uint8_t start, uint8_t count) {
    for (uint8_t i = start; i < start + count; i++) _set_color(i, 0, 0, 0);
}

static bool center_indicator_render(void) {
    uint8_t mode = g_kb_config.center.mode;
    if (mode < CENTER_IND_CAPS || mode > CENTER_IND_SCROLL) return false;

    bool active = false;
    switch (mode) {
        case CENTER_IND_CAPS:   active = host_keyboard_led_state().caps_lock;   break;
        case CENTER_IND_NUM:    active = host_keyboard_led_state().num_lock;    break;
        case CENTER_IND_SCROLL: active = host_keyboard_led_state().scroll_lock; break;
    }
    if (active) {
        RGB rgb = hsv_to_rgb((HSV){g_kb_config.center.h,
                                   g_kb_config.center.s,
                                   g_kb_config.center.v});
        for (uint8_t i = CENTER_START; i < CENTER_START + CENTER_COUNT; i++)
            _set_color(i, rgb.r, rgb.g, rgb.b);
    } else {
        blank_zone(CENTER_START, CENTER_COUNT);
    }
    return true;
}

/* ════════════════════════════════════════════════════════════════
 * QMK CALLBACKS
 * ════════════════════════════════════════════════════════════════ */
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) return false;

    /* ── Ring ─────────────────────────────────────────────────── */
    if (g_kb_config.ring_enabled)
        ring_fx_render(&g_kb_config.ring, RING_START);
    else
        blank_zone(RING_START, RING_COUNT);

    /* ── Center ───────────────────────────────────────────────── */
    if (!g_kb_config.center_enabled) {
        blank_zone(CENTER_START, CENTER_COUNT);
    } else if (!center_indicator_render()) {
        center_fx_render(&g_kb_config.center, CENTER_START);
    }
    return true;
}

void housekeeping_task_kb(void) {
    static uint32_t ring_timer   = 0;
    static uint32_t center_timer = 0;

    /* ── Ring tick ────────────────────────────────────────────── */
    if (g_kb_config.ring_enabled) {
        uint32_t e = timer_elapsed32(ring_timer);
        if (e > 0) { ring_timer = timer_read32(); ring_fx_tick(e, &g_kb_config.ring); }
    }

    /* ── Center tick — only for library-managed animated modes ── */
    if (g_kb_config.center_enabled &&
        g_kb_config.center.mode <= CENTER_FX_MAX) {
        uint32_t e = timer_elapsed32(center_timer);
        if (e > 0) { center_timer = timer_read32(); center_fx_tick(e, &g_kb_config.center); }
    }

    /* ── Hot-swap ─────────────────────────────────────────────── */
    if (timer_elapsed32(hotswap_timer) >= HOTSWAP_CHECK_INTERVAL_MS) {
        hotswap_timer = timer_read32();
        hotswap_check();
    }
}

/* ════════════════════════════════════════════════════════════════
 * EEPROM
 * ════════════════════════════════════════════════════════════════ */
void eeconfig_init_kb(void) {
    g_kb_config = (kb_eeprom_t){
        .ring_enabled   = true,
        .ring           = { .mode=RING_FX_CHASE,     .h=0, .s=255, .v=200, .speed=128 },
        .center_enabled = true,
        .center         = { .mode=CENTER_FX_BREATHE, .h=0, .s=255, .v=200, .speed=128 },
        .module_sel     = MODULE_SEL_AUTO,
    };
    eeconfig_update_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));
}

void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));

    if (g_kb_config.ring.mode    > RING_FX_MAX)      g_kb_config.ring.mode    = RING_FX_CHASE;
    if (g_kb_config.ring.speed   == 0)               g_kb_config.ring.speed   = 128;
    if (g_kb_config.center.mode  > CENTER_MODE_MAX)  g_kb_config.center.mode  = CENTER_FX_BREATHE;
    if (g_kb_config.center.speed == 0)               g_kb_config.center.speed = 128;

    hotswap_timer = timer_read32();

    /* Pass both callbacks — _get_color enables SYNC brightness scaling */
    ring_fx_init(RING_COUNT, _set_color, _get_color);
    center_fx_init(_set_color, _get_color);

    keyboard_post_init_user();
}

/* ════════════════════════════════════════════════════════════════
 * VIA
 * ════════════════════════════════════════════════════════════════ */
void kb_config_set_value(uint8_t *data) {
    uint8_t  id = data[0];
    uint8_t *v  = &data[1];
    switch ((enum via_kb_id)id) {
        case id_ring_enabled:
            g_kb_config.ring_enabled = v[0]; break;
        case id_ring_mode:
            g_kb_config.ring.mode = (v[0] > RING_FX_MAX) ? RING_FX_CHASE : v[0];
            ring_fx_reset(); break;
        case id_ring_color:
            g_kb_config.ring.h = v[0]; g_kb_config.ring.s = v[1]; break;
        case id_ring_brightness:
            g_kb_config.ring.v = v[0]; break;
        case id_ring_speed:
            g_kb_config.ring.speed = v[0] ? v[0] : 1; break;

        case id_center_enabled:
            g_kb_config.center_enabled = v[0]; break;
        case id_center_mode:
            g_kb_config.center.mode = (v[0] > CENTER_MODE_MAX) ? CENTER_FX_BREATHE : v[0];
            center_fx_reset(); break;
        case id_center_color:
            g_kb_config.center.h = v[0]; g_kb_config.center.s = v[1]; break;
        case id_center_brightness:
            g_kb_config.center.v = v[0]; break;
        case id_center_speed:
            g_kb_config.center.speed = v[0] ? v[0] : 1; break;

        case id_module_sel:
            g_kb_config.module_sel = v[0];
            kb_config_save();
            soft_reset_keyboard();
            break;
        default: break;
    }
}

void kb_config_get_value(uint8_t *data) {
    uint8_t  id = data[0];
    uint8_t *v  = &data[1];
    switch ((enum via_kb_id)id) {
        case id_ring_enabled:      v[0] = g_kb_config.ring_enabled;   break;
        case id_ring_mode:         v[0] = g_kb_config.ring.mode;      break;
        case id_ring_color:        v[0] = g_kb_config.ring.h; v[1] = g_kb_config.ring.s; break;
        case id_ring_brightness:   v[0] = g_kb_config.ring.v;         break;
        case id_ring_speed:        v[0] = g_kb_config.ring.speed;     break;
        case id_center_enabled:    v[0] = g_kb_config.center_enabled; break;
        case id_center_mode:       v[0] = g_kb_config.center.mode;    break;
        case id_center_color:      v[0] = g_kb_config.center.h; v[1] = g_kb_config.center.s; break;
        case id_center_brightness: v[0] = g_kb_config.center.v;       break;
        case id_center_speed:      v[0] = g_kb_config.center.speed;   break;
        case id_module_sel:        v[0] = g_kb_config.module_sel;     break;
        default:                   v[0] = 0; break;
    }
}

void kb_config_save(void) {
    eeconfig_update_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *cmd = &data[0], *ch = &data[1], *vd = &data[2];
    if (*ch != VIA_KB_CHANNEL) { *cmd = id_unhandled; return; }
    switch (*cmd) {
        case id_custom_set_value: kb_config_set_value(vd); break;
        case id_custom_get_value: kb_config_get_value(vd); break;
        case id_custom_save:      kb_config_save();         break;
        default:                  *cmd = id_unhandled;      break;
    }
}