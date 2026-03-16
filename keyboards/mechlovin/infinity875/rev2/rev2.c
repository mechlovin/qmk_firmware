// Copyright 2024 Mechlovin'
// SPDX-License-Identifier: GPL-2.0-or-later
//
// IF875 Rev.2 — External LED Module  (RGBLIGHT approach)
//
// ┌─────────────────────────────────────────────────────────────────────────────┐
// │  WS2812 chain (SPI2, pin B15 MOSI):                                        │
// │                                                                             │
// │  LED  0 – 23  │ Underglow PCB (24 bóng, theo keyboard.json led_count=44)   │
// │  LED 24 – 43  │ Ext module (tối đa 20 bóng, hàn dây từ DOUT LED 23)       │
// │                                                                             │
// │  rgblight effect_range = [0, 24)  →  animation engine CHỈ đụng LED 0-23   │
// │  LED 24-43 được ext_led_task() quản lý độc lập qua rgblight_sethsv_range() │
// │                                                                             │
// │  SYNC mode: effect_range mở rộng = [0, 24+n) để animation "tràn" sang     │
// │  module một cách tự nhiên, không cần code riêng.                           │
// │                                                                             │
// │  Hardware indicators riêng (không phải WS2812):                            │
// │    CapsLock  = B10   (hardware LED, controlled by QMK indicator feature)   │
// │    ScrollLock = B5   (hardware LED)                                        │
// └─────────────────────────────────────────────────────────────────────────────┘

#include "rev2.h"      // kéo vào quantum.h, via.h, eeprom.h + tất cả declarations
#include "rgblight.h"  // rgblight API (rgblight_set_effect_range, etc.)
#include "eeprom.h"    // eeprom_read_block / eeprom_write_block
#include <string.h>     // memset

// Forward declaration (định nghĩa ở cuối file, dùng trước khai báo)
static void update_effect_range(void);

// ── Shared memory cho các effect cần per-LED state (union → tiết kiệm RAM) ──
static union {
    uint8_t  rd_hue[EXT_LED_MAX_COUNT];            // RAINDROPS
    struct {
        uint8_t hue[EXT_LED_MAX_COUNT];
        uint8_t sat[EXT_LED_MAX_COUNT];
    } jb;                                           // JELLYBEAN
    struct {
        uint8_t val[EXT_LED_MAX_COUNT];
        uint8_t hue[EXT_LED_MAX_COUNT];
    } tw;                                           // TWINKLE
} eff_mem;
static uint8_t reactive_brightness = 0;            // REACTIVE_FLASH
static uint8_t eff_prev             = 0xFF;         // detect effect change → reset eff_mem

// 16-bit Xorshift LFSR — fast_rand(), không cần stdlib, ~8 bytes Flash
static uint16_t lfsr = 0xACE1u;
static inline uint8_t fast_rand(void) {
    lfsr ^= lfsr << 7;
    lfsr ^= lfsr >> 9;
    lfsr ^= lfsr << 8;
    return (uint8_t)(lfsr & 0xFFu);
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Global state
// ═══════════════════════════════════════════════════════════════════════════════
ext_led_state_t ext_led_state;

// ═══════════════════════════════════════════════════════════════════════════════
//  EEPROM helpers
// ═══════════════════════════════════════════════════════════════════════════════
void ext_led_set_defaults(void) {
    ext_led_state.ug_enabled     = true;
    ext_led_state.ext_enabled    = false;
    ext_led_state.module_type    = EXT_MODULE_NONE;
    ext_led_state.effect         = EXT_EFFECT_SYNC;
    ext_led_state.hue            = 0;
    ext_led_state.sat            = 255;
    ext_led_state.val            = 180;
    ext_led_state.speed          = 128;
    ext_led_state.indicator_mode = EXT_IND_LAYER;
}

void ext_led_config_save(void) {
    eeprom_write_block(&ext_led_state,
                       (void *)VIA_EEPROM_CUSTOM_CONFIG_ADDR,
                       sizeof(ext_led_state_t));
}

void ext_led_config_load(void) {
    eeprom_read_block(&ext_led_state,
                      (const void *)VIA_EEPROM_CUSTOM_CONFIG_ADDR,
                      sizeof(ext_led_state_t));
    // Sanity check (EEPROM trắng = 0xFF sau khi flash lần đầu)
    if (ext_led_state.module_type    > EXT_MODULE_RING20    ||
        ext_led_state.effect         > EXT_EFFECT_MAX    ||
        ext_led_state.indicator_mode > EXT_IND_ALL) {
        ext_led_set_defaults();
        ext_led_config_save();
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  QMK keyboard lifecycle hooks
// ═══════════════════════════════════════════════════════════════════════════════

// Gọi khi eeconfig bị xóa (QMK_RESET hoặc flash lần đầu)
void eeconfig_init_kb(void) {
    ext_led_set_defaults();
    ext_led_config_save();
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    ext_led_config_load();

    // Thiết lập effect_range dựa theo trạng thái load từ EEPROM.
    // Hàm này xử lý cả ug_enabled=false (range bắt đầu từ UNDERGLOW_LED_COUNT)
    // lẫn SYNC mode (range mở rộng sang module LEDs).
    update_effect_range();

    keyboard_post_init_user();
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Custom keycodes
// ═══════════════════════════════════════════════════════════════════════════════
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) return false;

    // Reactive: set brightness khi bất kỳ phím nào được nhấn
    if (record->event.pressed &&
        ext_led_state.ext_enabled &&
        ext_led_state.effect == EXT_EFFECT_REACTIVE) {
        reactive_brightness = 255;
    }

    if (!record->event.pressed) return true;

    switch (keycode) {
        case KBC_UG_TOG:
            ext_led_state.ug_enabled = !ext_led_state.ug_enabled;
            update_effect_range();
            ext_led_config_save();
            return false;

        case KBC_EXT_TOG:
            ext_led_state.ext_enabled = !ext_led_state.ext_enabled;
            update_effect_range();
            ext_led_config_save();
            return false;
    }
    return true;
}

// ═══════════════════════════════════════════════════════════════════════════════
//  VIA custom channel 0 — ext LED module
// ═══════════════════════════════════════════════════════════════════════════════
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t  cmd     = data[0];
    uint8_t  channel = data[1];
    uint8_t  vid     = data[2];
    uint8_t *val     = &data[3];

    // ─── Channel 3 = QMK RGBLIGHT built-in ───────────────────────────────────
    // Mechlovin fork gọi via_custom_value_command_kb cho TẤT CẢ channels,
    // không tự route channel 3 đến handler built-in. Phải tự xử lý ở đây.
    //
    // VIA RGBLIGHT value IDs (chuẩn QMK):
    //   1 = brightness (val)
    //   2 = effect (mode)
    //   3 = speed
    //   4 = color (hue byte + sat byte)
    if (channel == 3) {
        if (cmd == id_custom_get_value) {
            switch (vid) {
                case 1: val[0] = rgblight_get_val();   break;
                case 2: val[0] = rgblight_get_mode();  break;
                case 3: val[0] = rgblight_get_speed(); break;
                case 4:
                    val[0] = rgblight_get_hue();
                    val[1] = rgblight_get_sat();
                    break;
                default: data[0] = id_unhandled; break;
            }
        } else if (cmd == id_custom_set_value) {
            switch (vid) {
                case 1: rgblight_sethsv_noeeprom(rgblight_get_hue(),
                                                 rgblight_get_sat(),
                                                 val[0]); break;
                case 2: rgblight_mode_noeeprom(val[0]); break;
                case 3: rgblight_set_speed_noeeprom(val[0]); break;
                case 4: rgblight_sethsv_noeeprom(val[0], val[1],
                                                 rgblight_get_val()); break;
                default: data[0] = id_unhandled; break;
            }
        } else if (cmd == id_custom_save) {
            // Persist vào EEPROM qua rgblight API chuẩn
            eeconfig_update_rgblight_current();
        } else {
            data[0] = id_unhandled;
        }
        return;
    }

    // ─── Channel 0 = Ext LED module custom ───────────────────────────────────
    if (channel != EXT_LED_VIA_CHANNEL) {
        // Channel khác (1=backlight, 2=rgb_matrix, ...): không phải của ta,
        // trả id_unhandled để VIA biết không handle được.
        data[0] = id_unhandled;
        return;
    }

    if (cmd == id_custom_get_value) {
        switch (vid) {
            case VID_UG_ENABLED:     val[0] = ext_led_state.ug_enabled;     break;
            case VID_EXT_ENABLED:    val[0] = ext_led_state.ext_enabled;    break;
            case VID_MODULE_TYPE:    val[0] = ext_led_state.module_type;    break;
            case VID_EFFECT:         val[0] = ext_led_state.effect;         break;
            case VID_COLOR:
                val[0] = ext_led_state.hue;
                val[1] = ext_led_state.sat;
                break;
            case VID_VAL:            val[0] = ext_led_state.val;            break;
            case VID_SPEED:          val[0] = ext_led_state.speed;          break;
            case VID_INDICATOR_MODE: val[0] = ext_led_state.indicator_mode; break;
            default: data[0] = id_unhandled; break;
        }

    } else if (cmd == id_custom_set_value) {
        switch (vid) {
            case VID_UG_ENABLED:
                ext_led_state.ug_enabled = val[0];
                update_effect_range();
                break;

            case VID_EXT_ENABLED:
                ext_led_state.ext_enabled = val[0];
                update_effect_range();
                break;

            case VID_MODULE_TYPE:
                ext_led_state.module_type = val[0];
                update_effect_range();
                break;

            case VID_EFFECT:
                ext_led_state.effect = val[0];
                update_effect_range();
                break;

            case VID_COLOR:
                ext_led_state.hue = val[0];
                ext_led_state.sat = val[1];
                break;
            case VID_VAL:            ext_led_state.val            = val[0]; break;
            case VID_SPEED:          ext_led_state.speed          = val[0]; break;
            case VID_INDICATOR_MODE: ext_led_state.indicator_mode = val[0]; break;
            default: data[0] = id_unhandled; break;
        }

    } else if (cmd == id_custom_save) {
        ext_led_config_save();
    } else {
        data[0] = id_unhandled;
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  Ext-module animation engine
// ═══════════════════════════════════════════════════════════════════════════════

// ── Position & geometry helpers (integer math only) ──────────────────────────

// Vị trí dọc theo strip: LED i trong n LEDs → 0 (trái) .. 255 (phải)
static inline uint8_t pos_x(uint8_t i, uint8_t n) {
    if (n <= 1) return 128u;
    return (uint8_t)((uint16_t)i * 255u / (uint8_t)(n - 1u));
}

// Khoảng cách từ tâm: 0 = giữa, 255 = cạnh ngoài
static inline uint8_t dist_center(uint8_t i, uint8_t n) {
    if (n <= 1) return 0u;
    uint8_t  c  = (uint8_t)(n - 1u);      // 2 * center (scaled)
    uint16_t d2 = (i * 2u >= c) ? (uint16_t)(i * 2u - c)
                                : (uint16_t)(c  - i * 2u);
    return (uint8_t)(d2 * 255u / c);
}

// Góc đều cho ring: LED i trong n LED → 0..255
static inline uint8_t ring_angle(uint8_t i, uint8_t n) {
    if (n == 0) return 0u;
    return (uint8_t)((uint16_t)i * 256u / n);
}

// Triangle wave: phase 0→127 = tăng 0→254, phase 128→255 = giảm 254→0
static inline uint8_t tri_wave(uint8_t phase) {
    return (phase < 128) ? (phase << 1) : (uint8_t)(510u - (phase << 1));
}

// Fill một dải LED ext module [start_offset, start_offset+count) với HSV
// Offset tính từ EXT_LED_START (không phải từ 0)
static void ext_fill(uint8_t offset, uint8_t count, uint8_t h, uint8_t s, uint8_t v) {
    rgblight_sethsv_range(h, s, v,
                          EXT_LED_START + offset,
                          EXT_LED_START + offset + count);
}

// Tắt một dải LED ext module
static void ext_clear(uint8_t offset, uint8_t count) {
    rgblight_setrgb_range(0, 0, 0,
                          EXT_LED_START + offset,
                          EXT_LED_START + offset + count);
}

// Set 1 LED ext module tại index (offset từ EXT_LED_START)
static void ext_set_one(uint8_t i, uint8_t h, uint8_t s, uint8_t v) {
    rgblight_sethsv_range(h, s, v,
                          EXT_LED_START + i,
                          EXT_LED_START + i + 1);
}

// ─── Cập nhật RGBLIGHT effect_range dựa trên trạng thái hiện tại ─────────────
//
// Đây là cách duy nhất để tránh flicker underglow:
//   • ug_enabled=true  → range bắt đầu từ 0 (animation đụng LED 0-23)
//   • ug_enabled=false → range bắt đầu từ UNDERGLOW_LED_COUNT (animation
//     KHÔNG BAO GIỜ ghi vào LED 0-23; underglow bị blank một lần và giữ nguyên)
//
//   Nếu SYNC mode và ext module đang bật: mở rộng range sang module LEDs.
static void update_effect_range(void) {
    uint8_t start, count;

    if (ext_led_state.ug_enabled) {
        // Underglow bật: animation bắt đầu từ LED 0
        start = 0;
        if (ext_led_state.ext_enabled &&
            ext_led_state.effect == EXT_EFFECT_SYNC) {
            count = UNDERGLOW_LED_COUNT + ext_led_count();  // tràn sang module
        } else {
            count = UNDERGLOW_LED_COUNT;
        }
    } else {
        // Underglow tắt: animation KHÔNG chạm LED 0-23
        // Blank underglow buffer một lần (persistent cho đến khi bật lại)
        rgblight_setrgb_range(0, 0, 0, 0, UNDERGLOW_LED_COUNT);
        start = UNDERGLOW_LED_COUNT;
        if (ext_led_state.ext_enabled &&
            ext_led_state.effect == EXT_EFFECT_SYNC) {
            count = ext_led_count();  // SYNC chỉ chạy trên module
        } else {
            count = 0;  // ext task tự quản lý, engine không cần range
        }
    }

    rgblight_set_effect_range(start, count);
}

// ─── Main task — gọi từ matrix_scan_kb() ─────────────────────────────────────
void ext_led_task(void) {
    static uint32_t last_tick = 0;
    static uint8_t  frame     = 0;

    // Tốc độ: speed=255 → 4ms/tick (nhanh), speed=0 → 132ms/tick (chậm)
    uint32_t interval = 4u + (uint32_t)((255u - ext_led_state.speed) >> 1);

    if (timer_elapsed32(last_tick) >= interval) {
        last_tick = timer_read32();
        frame++;  // uint8 tự wrap 0→255
    }

    // ── Module tắt hoặc không cắm ────────────────────────────────────────────
    uint8_t n = ext_led_count();
    if (!ext_led_state.ext_enabled || n == 0) {
        ext_clear(0, EXT_LED_MAX_COUNT);  // tắt toàn bộ slot ext
        return;
    }

    // ── SYNC: animation engine tự xử lý, chỉ cần tắt slot dư ────────────────
    if (ext_led_state.effect == EXT_EFFECT_SYNC) {
        if (n < EXT_LED_MAX_COUNT) {
            ext_clear(n, EXT_LED_MAX_COUNT - n);
        }
        return;
    }

    // ── Custom effects ────────────────────────────────────────────────────────
    uint8_t h = ext_led_state.hue;
    uint8_t s = ext_led_state.sat;
    uint8_t v = ext_led_state.val;

    switch (ext_led_state.effect) {

        // ── SOLID ─────────────────────────────────────────────────────────────
        case EXT_EFFECT_SOLID:
            ext_fill(0, n, h, s, v);
            break;

        // ── BREATHE ───────────────────────────────────────────────────────────
        case EXT_EFFECT_BREATHE: {
            uint8_t bv = (uint8_t)((uint16_t)tri_wave(frame) * v >> 8);
            ext_fill(0, n, h, s, bv);
            break;
        }

        // ── RAINBOW ───────────────────────────────────────────────────────────
        case EXT_EFFECT_RAINBOW: {
            uint8_t step = (n > 1) ? (uint8_t)(256u / n) : 0;
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, (uint8_t)(frame + i * step), s, v);
            }
            break;
        }

        // ── CHASE ─────────────────────────────────────────────────────────────
        case EXT_EFFECT_CHASE: {
            if (ext_led_state.module_type == EXT_MODULE_RING20) {
                // Outer 16: chấm chạy vòng tròn với đuôi 3 LED
                const uint8_t OUTER = 16;
                const uint8_t INNER = 4;
                const uint8_t TAIL  = 3;
                uint8_t pos = frame % OUTER;

                for (uint8_t i = 0; i < OUTER; i++) {
                    uint8_t dist = (uint8_t)((OUTER + pos - i) % OUTER);
                    uint8_t lv = (dist == 0)     ? v :
                                 (dist <= TAIL)  ? (uint8_t)(v / (dist + 1u)) : 0;
                    ext_set_one(i, h, s, lv);
                }
                // Inner 4: breathe chậm ở nửa brightness
                uint8_t ibv = (uint8_t)((uint16_t)tri_wave((uint8_t)(frame >> 1)) * (v >> 1) >> 8);
                ext_fill(OUTER, INNER, h, s, ibv);
            } else {
                // Linear chase (STRIP20 hoặc SINGLE)
                const uint8_t TAIL = 3;
                uint8_t pos = (n > 0) ? (frame % n) : 0;
                for (uint8_t i = 0; i < n; i++) {
                    uint8_t dist = (uint8_t)((n + pos - i) % n);
                    uint8_t lv = (dist == 0)     ? v :
                                 (dist <= TAIL)  ? (uint8_t)(v / (dist + 1u)) : 0;
                    ext_set_one(i, h, s, lv);
                }
            }
            break;
        }

        // ── INDICATOR ─────────────────────────────────────────────────────────
        // Chú ý: hardware LEDs B10 (CapsLock) và B5 (ScrollLock) được QMK
        // điều khiển tự động qua indicators trong keyboard.json.
        // Ở đây chỉ dùng WS2812 module để hiển thị thêm trạng thái bằng màu.
        case EXT_EFFECT_INDICATOR: {
            led_t   locks     = host_keyboard_led_state();
            uint8_t layer     = get_highest_layer(layer_state);
            uint8_t layer_hue = (uint8_t)((uint16_t)layer * 42u);
            bool    caps      = locks.caps_lock;
            bool    num       = locks.num_lock;
            bool    scrl      = locks.scroll_lock;

            switch (ext_led_state.indicator_mode) {

                case EXT_IND_LAYER:
                    ext_fill(0, n, layer_hue, 255, v);
                    break;

                case EXT_IND_CAPS:
                    ext_fill(0, n, 0, 255, caps ? v : 0);
                    break;

                case EXT_IND_NUM:
                    ext_fill(0, n, 85, 255, num ? v : 0);
                    break;

                case EXT_IND_ALL: {
                    if (ext_led_state.module_type == EXT_MODULE_RING20) {
                        // Outer 16: cầu vồng breathing theo layer
                        uint8_t bv = (uint8_t)((uint16_t)tri_wave(frame) * v >> 8);
                        for (uint8_t i = 0; i < 16; i++) {
                            ext_set_one(i, (uint8_t)(layer_hue + i * 16u), 200, bv);
                        }
                        // Inner 4: [24]=Caps(đỏ), [25]=Num(xanh), [26]=Scroll(vàng), [27]=Layer(hue)
                        const uint8_t ih[4]  = {0, 85, 43, 0};
                        const bool    ion[4] = {caps, num, scrl, true};
                        uint8_t ihd[4] = {ih[0], ih[1], ih[2], layer_hue};
                        for (uint8_t k = 0; k < 4; k++) {
                            ext_set_one(16 + k, ihd[k], 255, ion[k] ? v : (v >> 3));
                        }
                    } else {
                        // Strip: chia 4 phân đoạn bằng nhau
                        uint8_t seg = (n >= 4) ? (n >> 2) : 1;
                        const uint8_t sh[4]  = {0, 85, 43, 0};
                        const bool    son[4] = {caps, num, scrl, true};
                        uint8_t shd[4] = {sh[0], sh[1], sh[2], layer_hue};
                        for (uint8_t k = 0; k < 4; k++) {
                            uint8_t from = k * seg;
                            uint8_t to   = (k == 3) ? n : (from + seg);
                            if (from >= n) break;
                            ext_fill(from, to - from, shd[k], 255, son[k] ? v : (v >> 3));
                        }
                    }
                    break;
                }
            }
            break;
        }


        // ═══ RGB MATRIX-STYLE EFFECTS ═══════════════════════════════════════════

        // ── BAND_SAT: dải fade saturation cuộn ───────────────────────────────
        case EXT_EFFECT_BAND_SAT: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px = pos_x(i, n);
                uint8_t d  = (px >= frame) ? (uint8_t)(px - frame)
                                           : (uint8_t)(frame - px);
                uint8_t wd = (d < 128u) ? d : (uint8_t)(256u - d);
                uint8_t ls = (wd < 128u) ? (uint8_t)(255u - (uint16_t)wd * 2u) : 0u;
                ext_set_one(i, h, ls, v);
            }
            break;
        }

        // ── BAND_VAL: dải fade brightness cuộn ───────────────────────────────
        case EXT_EFFECT_BAND_VAL: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px = pos_x(i, n);
                uint8_t d  = (px >= frame) ? (uint8_t)(px - frame)
                                           : (uint8_t)(frame - px);
                uint8_t wd = (d < 128u) ? d : (uint8_t)(256u - d);
                uint8_t lv2 = (wd < 128u)
                    ? (uint8_t)((uint16_t)(255u - (uint16_t)wd * 2u) * v >> 8u)
                    : 0u;
                ext_set_one(i, h, s, lv2);
            }
            break;
        }

        // ── BAND_PINWHEEL_SAT: 3 dải đều fade saturation xoay ────────────────
        case EXT_EFFECT_BAND_PW_SAT: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px = pos_x(i, n);
                uint8_t md = 255u;
                for (uint8_t b = 0; b < 3u; b++) {
                    uint8_t bp = (uint8_t)(frame + (uint8_t)(b * 85u));
                    uint8_t d  = (px >= bp) ? (uint8_t)(px - bp)
                                            : (uint8_t)(bp - px);
                    uint8_t wd = (d < 128u) ? d : (uint8_t)(256u - d);
                    if (wd < md) md = wd;
                }
                uint8_t ls = (md < 64u) ? (uint8_t)(255u - (uint16_t)md * 4u) : 0u;
                ext_set_one(i, h, ls, v);
            }
            break;
        }

        // ── BAND_PINWHEEL_VAL: 3 dải đều fade brightness xoay ────────────────
        case EXT_EFFECT_BAND_PW_VAL: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px = pos_x(i, n);
                uint8_t md = 255u;
                for (uint8_t b = 0; b < 3u; b++) {
                    uint8_t bp = (uint8_t)(frame + (uint8_t)(b * 85u));
                    uint8_t d  = (px >= bp) ? (uint8_t)(px - bp)
                                            : (uint8_t)(bp - px);
                    uint8_t wd = (d < 128u) ? d : (uint8_t)(256u - d);
                    if (wd < md) md = wd;
                }
                uint8_t lv2 = (md < 64u)
                    ? (uint8_t)((uint16_t)(255u - (uint16_t)md * 4u) * v >> 8u)
                    : 0u;
                ext_set_one(i, h, s, lv2);
            }
            break;
        }

        // ── BAND_SPIRAL_SAT: sóng saturation cuộn dọc strip ──────────────────
        case EXT_EFFECT_BAND_SP_SAT: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t phase = (uint8_t)(frame + pos_x(i, n));
                ext_set_one(i, h, tri_wave(phase), v);
            }
            break;
        }

        // ── BAND_SPIRAL_VAL: sóng brightness cuộn dọc strip ──────────────────
        case EXT_EFFECT_BAND_SP_VAL: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t phase = (uint8_t)(frame + pos_x(i, n));
                uint8_t lv2   = (uint8_t)((uint16_t)tri_wave(phase) * v >> 8u);
                ext_set_one(i, h, s, lv2);
            }
            break;
        }

        // ── CYCLE_ALL: solid hue cycling ─────────────────────────────────────
        case EXT_EFFECT_CYCLE_ALL:
            ext_fill(0, n, frame, s, v);
            break;

        // ── CYCLE_LR: rainbow gradient trái→phải ─────────────────────────────
        case EXT_EFFECT_CYCLE_LR: {
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, (uint8_t)(frame + pos_x(i, n)), s, v);
            }
            break;
        }

        // ── CYCLE_UD: rainbow gradient phải→trái (ngược chiều LR) ────────────
        case EXT_EFFECT_CYCLE_UD: {
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, (uint8_t)(frame - pos_x(i, n)), s, v);
            }
            break;
        }

        // ── CYCLE_OUT_IN: gradient từ 2 đầu vào giữa ─────────────────────────
        case EXT_EFFECT_CYCLE_OUT_IN: {
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, (uint8_t)(frame + dist_center(i, n)), s, v);
            }
            break;
        }

        // ── CYCLE_OUT_IN_DUAL: 2 gradient gặp nhau ở tâm ─────────────────────
        case EXT_EFFECT_CYCLE_OUT_IN_DUAL: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px = pos_x(i, n);
                uint8_t m  = (px < 128u) ? px : (uint8_t)(255u - px);
                ext_set_one(i, (uint8_t)(frame + m), s, v);
            }
            break;
        }

        // ── CHEVRON: V-shape rainbow di chuyển về phía tâm ───────────────────
        case EXT_EFFECT_CHEVRON: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t dc = dist_center(i, n);
                ext_set_one(i, (uint8_t)(frame - dc), s, v);
            }
            break;
        }

        // ── CYCLE_PINWHEEL: 3 hue bands xoay đều ─────────────────────────────
        case EXT_EFFECT_CYCLE_PINWHEEL: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t a = ring_angle(i, n);
                ext_set_one(i, (uint8_t)((uint16_t)frame * 3u + (uint16_t)a * 3u), s, v);
            }
            break;
        }

        // ── CYCLE_SPIRAL: gradient xoắn tăng tốc ────────────────────────────
        case EXT_EFFECT_CYCLE_SPIRAL: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t a = ring_angle(i, n);
                ext_set_one(i, (uint8_t)(frame * 2u + a + (frame >> 2u)), s, v);
            }
            break;
        }

        // ── DUAL_BEACON: 2 điểm sáng đối nhau quét vòng ─────────────────────
        case EXT_EFFECT_DUAL_BEACON: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t a  = ring_angle(i, n);
                uint8_t d1 = (uint8_t)(a >= frame ? a - frame : frame - a);
                d1 = (d1 < 128u) ? d1 : (uint8_t)(256u - d1);
                uint8_t f2 = (uint8_t)(frame + 128u);
                uint8_t d2 = (uint8_t)(a >= f2 ? a - f2 : f2 - a);
                d2 = (d2 < 128u) ? d2 : (uint8_t)(256u - d2);
                uint8_t dm = (d1 < d2) ? d1 : d2;
                uint8_t lv2 = (dm < 64u)
                    ? (uint8_t)((uint16_t)(63u - dm) * v / 64u)
                    : 0u;
                ext_set_one(i, (uint8_t)(frame + a), s, lv2);
            }
            break;
        }

        // ── RAINBOW_BEACON: rainbow xoáy từ tâm ─────────────────────────────
        case EXT_EFFECT_RAINBOW_BEACON: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t a   = ring_angle(i, n);
                uint8_t lh2 = (uint8_t)(a * 2u + frame * 2u);
                uint8_t lv2 = (uint8_t)((uint16_t)tri_wave((uint8_t)(a + frame)) * v >> 8u);
                ext_set_one(i, lh2, s, lv2);
            }
            break;
        }

        // ── RAINBOW_PINWHEELS: 2 nửa rainbow xoay ngược chiều ────────────────
        case EXT_EFFECT_RAINBOW_PINWHEELS: {
            uint8_t half = n / 2u;
            uint8_t d    = (half > 1u) ? (uint8_t)(half - 1u) : 1u;
            for (uint8_t i = 0; i < n; i++) {
                if (i < half) {
                    uint8_t a = (uint8_t)((uint16_t)i * 255u / d);
                    ext_set_one(i, (uint8_t)(a + frame), s, v);
                } else {
                    uint8_t j = (uint8_t)(n - 1u - i);
                    uint8_t a = (j < half) ? (uint8_t)((uint16_t)j * 255u / d) : 255u;
                    ext_set_one(i, (uint8_t)(a - frame), s, v);
                }
            }
            break;
        }

        // ── FLOWER_BLOOMING: 2 nửa gặp nhau ở tâm ───────────────────────────
        case EXT_EFFECT_FLOWER_BLOOMING: {
            uint8_t half = n / 2u;
            uint8_t d    = (half > 1u) ? (uint8_t)(half - 1u) : 1u;
            for (uint8_t i = 0; i < n; i++) {
                if (i < half) {
                    uint8_t a = (uint8_t)((uint16_t)i * 255u / d);
                    ext_set_one(i, (uint8_t)(a + frame), s, v);
                } else {
                    uint8_t j = (uint8_t)(n - 1u - i);
                    uint8_t a = (j < half) ? (uint8_t)((uint16_t)j * 255u / d) : 255u;
                    ext_set_one(i, (uint8_t)(a + frame), s, v);
                }
            }
            break;
        }

        // ── RAINDROPS: random từng LED đổi hue ───────────────────────────────
        case EXT_EFFECT_RAINDROPS: {
            if (eff_prev != EXT_EFFECT_RAINDROPS) {
                memset(&eff_mem, 0, sizeof(eff_mem));
            }
            uint8_t pick = fast_rand() % n;
            eff_mem.rd_hue[pick] = fast_rand();
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, eff_mem.rd_hue[i], s, v);
            }
            break;
        }

        // ── JELLYBEAN_RAINDROPS: random hue+saturation ───────────────────────
        case EXT_EFFECT_JELLYBEAN: {
            if (eff_prev != EXT_EFFECT_JELLYBEAN) {
                memset(&eff_mem, 0, sizeof(eff_mem));
                for (uint8_t i = 0; i < EXT_LED_MAX_COUNT; i++) {
                    eff_mem.jb.sat[i] = 200u;
                }
            }
            uint8_t pick = fast_rand() % n;
            eff_mem.jb.hue[pick] = fast_rand();
            eff_mem.jb.sat[pick] = (uint8_t)(128u + (fast_rand() & 0x7Fu));
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, eff_mem.jb.hue[i], eff_mem.jb.sat[i], v);
            }
            break;
        }

        // ── HUE_BREATHING: hue dao động nhẹ đồng thời (±16) ─────────────────
        case EXT_EFFECT_HUE_BREATHING: {
            int8_t  shift = (int8_t)((int16_t)(tri_wave(frame) >> 3u) - 16);
            uint8_t lh    = (uint8_t)((int16_t)h + shift);
            ext_fill(0, n, lh, s, v);
            break;
        }

        // ── HUE_PENDULUM: sóng hue đong đưa trái-phải ────────────────────────
        case EXT_EFFECT_HUE_PENDULUM: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px    = pos_x(i, n);
                uint8_t phase = (uint8_t)(frame + (px >> 2u));
                int8_t  shift = (int8_t)((int16_t)(tri_wave(phase) >> 3u) - 16);
                ext_set_one(i, (uint8_t)((int16_t)h + shift), s, v);
            }
            break;
        }

        // ── HUE_WAVE: sóng hue liên tục cuộn ────────────────────────────────
        case EXT_EFFECT_HUE_WAVE: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px    = pos_x(i, n);
                uint8_t phase = (uint8_t)(frame + (px >> 1u));
                int8_t  shift = (int8_t)((int16_t)(tri_wave(phase) >> 3u) - 16);
                ext_set_one(i, (uint8_t)((int16_t)h + shift), s, v);
            }
            break;
        }

        // ═══ CREATIVE EFFECTS ════════════════════════════════════════════════

        // ── COMET: sao chổi đuôi rainbow ─────────────────────────────────────
        case EXT_EFFECT_COMET: {
            uint8_t pos  = (n > 0u) ? (uint8_t)(frame % n) : 0u;
            const uint8_t TAIL = 5u;
            for (uint8_t i = 0; i < n; i++) {
                uint8_t dist = (uint8_t)((uint8_t)(n + pos - i) % n);
                if (dist == 0u) {
                    ext_set_one(i, h, s, v);
                } else if (dist <= TAIL) {
                    uint8_t th = (uint8_t)(h + dist * 16u);
                    uint8_t tv = (uint8_t)((uint16_t)v / (uint16_t)(dist + 1u));
                    ext_set_one(i, th, s, tv);
                } else {
                    ext_set_one(i, h, s, 0u);
                }
            }
            break;
        }

        // ── TWINKLE: LED nhấp nháy random độc lập ────────────────────────────
        case EXT_EFFECT_TWINKLE: {
            if (eff_prev != EXT_EFFECT_TWINKLE) {
                memset(&eff_mem, 0, sizeof(eff_mem));
            }
            // Random light up ~1 LED mỗi vài tick
            if ((fast_rand() & 0x03u) == 0u) {
                uint8_t pick = fast_rand() % n;
                eff_mem.tw.val[pick] = v;
                eff_mem.tw.hue[pick] = (uint8_t)(h + (fast_rand() & 0x3Fu) - 32u);
            }
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, eff_mem.tw.hue[i], s, eff_mem.tw.val[i]);
                if (eff_mem.tw.val[i] >= 8u) eff_mem.tw.val[i] -= 8u;
                else                          eff_mem.tw.val[i]  = 0u;
            }
            break;
        }

        // ── RIPPLE: sóng giao thoa cuộn ─────────────────────────────────────
        case EXT_EFFECT_RIPPLE: {
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px   = pos_x(i, n);
                uint8_t phase = (uint8_t)(frame * 2u - px);
                uint8_t lv2  = (uint8_t)((uint16_t)tri_wave(phase) * v >> 8u);
                ext_set_one(i, h, s, lv2);
            }
            break;
        }

        // ── GRAD_STATIC: rainbow tĩnh theo vị trí ────────────────────────────
        case EXT_EFFECT_GRAD_STATIC: {
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, (uint8_t)(h + pos_x(i, n)), s, v);
            }
            break;
        }

        // ── GRAD_CYCLE: rainbow cuộn + offset hue người dùng ─────────────────
        case EXT_EFFECT_GRAD_CYCLE: {
            for (uint8_t i = 0; i < n; i++) {
                ext_set_one(i, (uint8_t)(h + pos_x(i, n) + frame), s, v);
            }
            break;
        }

        // ── REACTIVE: flash khi nhấn phím, fade dần ──────────────────────────
        case EXT_EFFECT_REACTIVE: {
            uint8_t lv2 = (uint8_t)((uint16_t)reactive_brightness * v >> 8u);
            ext_fill(0, n, h, s, lv2);
            if (reactive_brightness >= 8u) reactive_brightness -= 8u;
            else                           reactive_brightness  = 0u;
            break;
        }

        // ── BAND_SCAN: dải sáng quét qua lại (bounce) ────────────────────────
        case EXT_EFFECT_BAND_SCAN: {
            uint8_t bp = tri_wave(frame);   // 0-254, bounce tự động
            for (uint8_t i = 0; i < n; i++) {
                uint8_t px = pos_x(i, n);
                uint8_t d  = (px >= bp) ? (uint8_t)(px - bp)
                                        : (uint8_t)(bp - px);
                uint8_t lv2 = (d < 32u)
                    ? (uint8_t)((uint16_t)(31u - d) * v / 32u)
                    : 0u;
                ext_set_one(i, h, s, lv2);
            }
            break;
        }

    } // effect switch

    // Cập nhật eff_prev sau khi render (để detect effect change ở lần sau)
    eff_prev = ext_led_state.effect;

    // Tắt slot LED dư (khi module_type < 20 LED)
    if (n < EXT_LED_MAX_COUNT) {
        ext_clear(n, EXT_LED_MAX_COUNT - n);
    }
}

// ═══════════════════════════════════════════════════════════════════════════════
//  matrix_scan_kb — gọi ext_led_task mỗi scan (~1ms)
// ═══════════════════════════════════════════════════════════════════════════════
void matrix_scan_kb(void) {
    ext_led_task();
    matrix_scan_user();
}