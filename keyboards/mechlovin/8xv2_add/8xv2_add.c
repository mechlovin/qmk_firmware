/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "quantum.h"
#include "8xv2_add.h"
#include "i2c_master.h"
#include "is31fl3731.h"
#include "ws2812.h"

#if defined(RGB_MATRIX_ENABLE) && defined(RGBLIGHT_ENABLE)
#    error "RGBLIGHT_ENABLE must be disabled — WS2812 is driven by the custom RGB Matrix driver"
#endif

/* ════════════════════════════════════════════════════════════════
 * BOARD INIT
 *
 * STM32F103: AFIO APB2 clock must be enabled before writing
 * AFIO->MAPR, otherwise the I2C1_REMAP bit is ignored and I2C1
 * defaults to PB6/PB7 instead of PB8/PB9 → all transactions
 * time out → IS31 stays dark and VIA loads slowly.
 * ════════════════════════════════════════════════════════════════ */

void board_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->MAPR   |= AFIO_MAPR_I2C1_REMAP;
}

/* ════════════════════════════════════════════════════════════════
 * IS31FL3731 LED MAP  (IS31FL3731_LED_COUNT = 20)
 *
 * Ring  0–15 : clockwise from 12:00
 *   0  = 12:00   4  = 3:00   8  = 6:00   12 = 9:00
 *
 * Center 16–19 : inner square corners
 *   16 = top-left   17 = top-right
 *   18 = bot-right  19 = bot-left
 * ════════════════════════════════════════════════════════════════ */

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
    /* ring */
    {0, C9_5,  C8_5,  C7_5},  //  0  12:00
    {0, C9_6,  C8_6,  C7_6},  //  1
    {0, C9_7,  C8_7,  C6_6},  //  2
    {0, C9_8,  C7_7,  C6_7},  //  3
    {0, C1_1,  C3_2,  C4_2},  //  4   3:00
    {0, C1_2,  C2_2,  C4_3},  //  5
    {0, C1_3,  C2_3,  C3_3},  //  6
    {0, C1_4,  C2_4,  C3_4},  //  7
    {0, C1_5,  C2_5,  C3_5},  //  8   6:00
    {0, C1_6,  C2_6,  C3_6},  //  9
    {0, C1_7,  C2_7,  C3_7},  // 10
    {0, C1_8,  C2_8,  C3_8},  // 11
    {0, C9_1,  C8_1,  C7_1},  // 12   9:00
    {0, C9_2,  C8_2,  C7_2},  // 13
    {0, C9_3,  C8_3,  C7_3},  // 14
    {0, C9_4,  C8_4,  C7_4},  // 15
    /* center corners */
    {0, C1_11, C2_11, C3_11}, // 16  top-left
    {0, C1_12, C2_12, C3_12}, // 17  top-right
    {0, C1_9,  C3_10, C4_10}, // 18  bot-right
    {0, C1_10, C2_10, C4_11}, // 19  bot-left
};

/* ════════════════════════════════════════════════════════════════
 * GLOBAL CONFIG
 * ════════════════════════════════════════════════════════════════ */

kb_eeprom_t g_kb_config;

/* ════════════════════════════════════════════════════════════════
 * CUSTOM RGB MATRIX DRIVER
 *
 * rgb_matrix indices:
 *   0–19  → IS31FL3731  (physical index = rgb_matrix index)
 *  20–39  → WS2812      (physical index = rgb_matrix index − 20)
 *
 * set_color() buffers colors in the IS31 and WS2812 internal
 * buffers; flush() pushes both to hardware in one frame.
 * ════════════════════════════════════════════════════════════════ */

static void rgb_matrix_driver_init(void) {
    i2c_init();
    is31fl3731_init(0);
    ws2812_init();
    for (uint8_t i = 0; i < IS31FL3731_LED_COUNT; i++)
        is31fl3731_set_led_control_register(i, true, true, true);
    is31fl3731_update_led_control_registers(0);
}

static void rgb_matrix_driver_flush(void) {
    is31fl3731_update_pwm_buffers(0);
    ws2812_flush();
}

static void rgb_matrix_driver_set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index < IS31FL3731_LED_COUNT) {
        is31fl3731_set_color(index, r, g, b);
    } else {
        ws2812_set_color(index - IS31FL3731_LED_COUNT, r, g, b);
    }
}

static void rgb_matrix_driver_set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    is31fl3731_set_color_all(r, g, b);
    ws2812_set_color_all(r, g, b);
}

// clang-format off
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = rgb_matrix_driver_init,
    .flush         = rgb_matrix_driver_flush,
    .set_color     = rgb_matrix_driver_set_color,
    .set_color_all = rgb_matrix_driver_set_color_all,
};
// clang-format on

/* ════════════════════════════════════════════════════════════════
 * ZONE HELPERS
 *
 * Called from rgb_matrix_indicators_kb() — after the effect
 * engine has written all 40 slots, before driver_flush().
 * ════════════════════════════════════════════════════════════════ */

/* Zero-out a contiguous block of IS31 LEDs */
static void blank_is31(uint8_t start, uint8_t count) {
    for (uint8_t i = start; i < start + count; i++)
        is31fl3731_set_color(i, 0, 0, 0);
}

/* Zero-out a contiguous block of WS2812 LEDs
 * start / count use rgb_matrix indices (20–39);
 * we subtract IS31FL3731_LED_COUNT to get the physical WS index. */
static void blank_ws(uint8_t start, uint8_t count) {
    for (uint8_t i = start; i < start + count; i++)
        ws2812_set_color(i - IS31FL3731_LED_COUNT, 0, 0, 0);
}

/* Apply a solid color to IS31 center (rgb_matrix 16–19) */
static void fill_is31_center(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = IS31_CENTER_START; i < IS31_CENTER_START + IS31_CENTER_COUNT; i++)
        is31fl3731_set_color(i, r, g, b);
}

/* Apply a solid color to WS2812 center (physical 16–19) */
static void fill_ws_center(uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = WS_CENTER_START; i < WS_CENTER_START + WS_CENTER_COUNT; i++)
        ws2812_set_color(i - IS31FL3731_LED_COUNT, r, g, b);
}

/* Evaluate a center config and call fill_xxx_center() or leave
 * the effect-engine color intact (SYNC mode). Returns false when
 * no override is needed (SYNC).                                   */
static bool center_override(const center_cfg_t *c, bool *show_out, RGB *rgb_out) {
    bool show = false;
    switch (c->mode) {
        case CENTER_MODE_SYNC:   return false;          /* let effect engine handle */
        case CENTER_MODE_STATIC: show = true;           break;
        case CENTER_MODE_CAPS:   show = host_keyboard_led_state().caps_lock;   break;
        case CENTER_MODE_NUM:    show = host_keyboard_led_state().num_lock;    break;
        case CENTER_MODE_SCROLL: show = host_keyboard_led_state().scroll_lock; break;
        default:                 return false;
    }
    *show_out = show;
    if (show) *rgb_out = hsv_to_rgb((HSV){c->h, c->s, c->v});
    else       rgb_out->r = rgb_out->g = rgb_out->b = 0;
    return true;
}

/* ════════════════════════════════════════════════════════════════
 * RGB MATRIX INDICATORS CALLBACK
 *
 * Called every frame after the effect engine sets all 40 LEDs,
 * before driver_flush() pushes data to hardware.
 *
 * Overrides:
 *   • Disabled ring → black
 *   • Disabled center → black
 *   • Non-SYNC center → indicator / static color
 *   • SYNC center → effect engine color is already correct
 *     (the (x,y) coords in keyboard.json place the center LEDs
 *      inside the ring at their proper angular positions, so
 *      radial/gradient effects automatically assign the right hue)
 * ════════════════════════════════════════════════════════════════ */

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) return false;

    /* ── IS31 ring ─────────────────────────────────────────── */
    if (!g_kb_config.is31_ring_enabled)
        blank_is31(IS31_RING_START, IS31_RING_COUNT);

    /* ── IS31 center ───────────────────────────────────────── */
    if (!g_kb_config.is31_center.enabled) {
        blank_is31(IS31_CENTER_START, IS31_CENTER_COUNT);
    } else {
        RGB rgb = {0, 0, 0};
        bool show = false;
        if (center_override(&g_kb_config.is31_center, &show, &rgb))
            fill_is31_center(rgb.r, rgb.g, rgb.b);
        /* else: SYNC — effect engine color already written */
    }

    /* ── WS ring ───────────────────────────────────────────── */
    if (!g_kb_config.ws_ring_enabled)
        blank_ws(WS_RING_START, WS_RING_COUNT);

    /* ── WS center ─────────────────────────────────────────── */
    if (!g_kb_config.ws_center.enabled) {
        blank_ws(WS_CENTER_START, WS_CENTER_COUNT);
    } else {
        RGB rgb = {0, 0, 0};
        bool show = false;
        if (center_override(&g_kb_config.ws_center, &show, &rgb))
            fill_ws_center(rgb.r, rgb.g, rgb.b);
        /* else: SYNC */
    }

    return true;
}

/* ════════════════════════════════════════════════════════════════
 * EEPROM
 * ════════════════════════════════════════════════════════════════ */

void eeconfig_init_kb(void) {
    g_kb_config = (kb_eeprom_t){
        .is31_ring_enabled = true,
        .is31_center       = {true, CENTER_MODE_SYNC, 0, 255, 200},
        .ws_ring_enabled   = true,
        .ws_center         = {true, CENTER_MODE_SYNC, 0, 255, 200},
    };
    eeconfig_update_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));
}

void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));
    keyboard_post_init_user();
}

/* ════════════════════════════════════════════════════════════════
 * VIA SET / GET / SAVE
 * ════════════════════════════════════════════════════════════════ */

void kb_config_set_value(uint8_t *data) {
    uint8_t  id = data[0];
    uint8_t *v  = &data[1];
    switch ((enum via_kb_id)id) {
        case id_is31_ring_enabled:      g_kb_config.is31_ring_enabled     = v[0]; break;
        case id_is31_center_enabled:    g_kb_config.is31_center.enabled   = v[0]; break;
        case id_is31_center_mode:       g_kb_config.is31_center.mode      = v[0]; break;
        case id_is31_center_brightness: g_kb_config.is31_center.v         = v[0]; break;
        case id_is31_center_color:      g_kb_config.is31_center.h         = v[0];
                                        g_kb_config.is31_center.s         = v[1]; break;
        case id_ws_ring_enabled:        g_kb_config.ws_ring_enabled       = v[0]; break;
        case id_ws_center_enabled:      g_kb_config.ws_center.enabled     = v[0]; break;
        case id_ws_center_mode:         g_kb_config.ws_center.mode        = v[0]; break;
        case id_ws_center_brightness:   g_kb_config.ws_center.v           = v[0]; break;
        case id_ws_center_color:        g_kb_config.ws_center.h           = v[0];
                                        g_kb_config.ws_center.s           = v[1]; break;
    }
}

void kb_config_get_value(uint8_t *data) {
    uint8_t  id = data[0];
    uint8_t *v  = &data[1];
    switch ((enum via_kb_id)id) {
        case id_is31_ring_enabled:      v[0] = g_kb_config.is31_ring_enabled;   break;
        case id_is31_center_enabled:    v[0] = g_kb_config.is31_center.enabled; break;
        case id_is31_center_mode:       v[0] = g_kb_config.is31_center.mode;    break;
        case id_is31_center_brightness: v[0] = g_kb_config.is31_center.v;       break;
        case id_is31_center_color:      v[0] = g_kb_config.is31_center.h;
                                        v[1] = g_kb_config.is31_center.s;       break;
        case id_ws_ring_enabled:        v[0] = g_kb_config.ws_ring_enabled;     break;
        case id_ws_center_enabled:      v[0] = g_kb_config.ws_center.enabled;   break;
        case id_ws_center_mode:         v[0] = g_kb_config.ws_center.mode;      break;
        case id_ws_center_brightness:   v[0] = g_kb_config.ws_center.v;         break;
        case id_ws_center_color:        v[0] = g_kb_config.ws_center.h;
                                        v[1] = g_kb_config.ws_center.s;         break;
        default:                        v[0] = 0;                               break;
    }
}

void kb_config_save(void) {
    eeconfig_update_kb_datablock(&g_kb_config, 0, sizeof(g_kb_config));
}

/* ════════════════════════════════════════════════════════════════
 * VIA ENTRY POINT
 * ════════════════════════════════════════════════════════════════ */

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *cmd = &data[0];
    uint8_t *ch  = &data[1];
    uint8_t *vd  = &data[2];
    if (*ch != VIA_KB_CHANNEL) { *cmd = id_unhandled; return; }
    switch (*cmd) {
        case id_custom_set_value: kb_config_set_value(vd); break;
        case id_custom_get_value: kb_config_get_value(vd); break;
        case id_custom_save:      kb_config_save();         break;
        default:                  *cmd = id_unhandled;      break;
    }
}