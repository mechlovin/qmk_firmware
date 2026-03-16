// Copyright 2024 Mechlovin'
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "quantum.h"
#include "via.h"    // ← phải include trước để lấy VIA_EEPROM_CUSTOM_CONFIG_ADDR

// ── VIA_EEPROM_CUSTOM_CONFIG_ADDR fallback ────────────────────────────────────
// quantum/via.h trong QMK hiện đại define sẵn macro này.
// Nếu fork cũ không có, dùng hardcoded offset 41:
//   ARM STM32/APM32: EECONFIG block ~32 bytes
//   VIA header: magic(2) + version(1) + keyboard_id(2) + layout_options(4) = 9 bytes
//   → VIA custom config bắt đầu từ byte 32+9 = 41
// KHÔNG dùng (EECONFIG_SIZE + N) vì EECONFIG_SIZE là sizeof() — không phải
// preprocessor constant, sẽ lỗi "undeclared" khi macro expand trong function body.
#ifndef VIA_EEPROM_CUSTOM_CONFIG_ADDR
#    define VIA_EEPROM_CUSTOM_CONFIG_ADDR 41
#endif

// ═══════════════════════════════════════════════════════════════════════════════
//  Custom keycodes
// ═══════════════════════════════════════════════════════════════════════════════
enum infinity875_keycodes {
    KBC_UG_TOG  = QK_KB_0,   // Toggle underglow (LED 0–23) on/off độc lập
    KBC_EXT_TOG = QK_KB_1,   // Toggle ext module (LED 24–43) on/off độc lập
};

// ═══════════════════════════════════════════════════════════════════════════════
//  Module type  (dropdown trong VIA)
// ═══════════════════════════════════════════════════════════════════════════════
#define EXT_MODULE_NONE    0   // Không cắm gì          → 0 LED
#define EXT_MODULE_SINGLE  1   // 1 bóng LED đơn        → 1 LED
#define EXT_MODULE_STRIP20 2   // Strip 20 LED thẳng    → 20 LED
#define EXT_MODULE_RING20  3   // Ring 16 ngoài + 4 trong → 20 LED

// ═══════════════════════════════════════════════════════════════════════════════
//  Effect  (dropdown trong VIA — 3 nhóm)
// ═══════════════════════════════════════════════════════════════════════════════

// ── Nhóm Classic (0-5) ────────────────────────────────────────────────────────
#define EXT_EFFECT_SYNC         0   // Mirror hiệu ứng underglow
#define EXT_EFFECT_SOLID        1   // Màu đơn sắc tĩnh
#define EXT_EFFECT_BREATHE      2   // Thở (triangle wave)
#define EXT_EFFECT_RAINBOW      3   // Cầu vồng xoay
#define EXT_EFFECT_CHASE        4   // Chấm chạy (strip thẳng / ring tròn)
#define EXT_EFFECT_INDICATOR    5   // Trạng thái Lock / Layer

// ── Nhóm RGB Matrix-style (6-28) ──────────────────────────────────────────────
#define EXT_EFFECT_BAND_SAT          6   // Dải fade saturation cuộn trái→phải
#define EXT_EFFECT_BAND_VAL          7   // Dải fade brightness cuộn trái→phải
#define EXT_EFFECT_BAND_PW_SAT       8   // 3 dải đều (pinwheel) fade saturation xoay
#define EXT_EFFECT_BAND_PW_VAL       9   // 3 dải đều (pinwheel) fade brightness xoay
#define EXT_EFFECT_BAND_SP_SAT       10  // Sóng saturation (spiral) cuộn
#define EXT_EFFECT_BAND_SP_VAL       11  // Sóng brightness (spiral) cuộn
#define EXT_EFFECT_CYCLE_ALL         12  // Toàn dải đổi hue liên tục (solid cycling)
#define EXT_EFFECT_CYCLE_LR          13  // Rainbow gradient cuộn trái→phải
#define EXT_EFFECT_CYCLE_UD          14  // Rainbow gradient cuộn phải→trái
#define EXT_EFFECT_CYCLE_OUT_IN      15  // Rainbow từ ngoài vào giữa
#define EXT_EFFECT_CYCLE_OUT_IN_DUAL 16  // Hai gradient từ 2 đầu gặp giữa
#define EXT_EFFECT_CHEVRON           17  // Dải V-shape cuộn
#define EXT_EFFECT_CYCLE_PINWHEEL    18  // 3 hue bands xoay (pinwheel)
#define EXT_EFFECT_CYCLE_SPIRAL      19  // Gradient xoắn tăng tốc (spiral)
#define EXT_EFFECT_DUAL_BEACON       20  // 2 điểm sáng đối nhau quét vòng
#define EXT_EFFECT_RAINBOW_BEACON    21  // Rainbow xoáy từ tâm
#define EXT_EFFECT_RAINBOW_PINWHEELS 22  // 2 nửa rainbow xoay ngược chiều
#define EXT_EFFECT_FLOWER_BLOOMING   23  // Nở hoa: 2 nửa gặp nhau ở tâm
#define EXT_EFFECT_RAINDROPS         24  // Random từng LED đổi hue
#define EXT_EFFECT_JELLYBEAN         25  // Random từng LED đổi hue+saturation
#define EXT_EFFECT_HUE_BREATHING     26  // Hue dao động nhẹ đồng thời
#define EXT_EFFECT_HUE_PENDULUM      27  // Hue dao động thành sóng trái-phải
#define EXT_EFFECT_HUE_WAVE          28  // Sóng hue liên tục cuộn

// ── Nhóm Creative (29-35) ─────────────────────────────────────────────────────
#define EXT_EFFECT_COMET        29  // Sao chổi với đuôi màu chuyển
#define EXT_EFFECT_TWINKLE      30  // LED nhấp nháy random độc lập (twinkle)
#define EXT_EFFECT_RIPPLE       31  // Sóng giao thoa từ tâm
#define EXT_EFFECT_GRAD_STATIC  32  // Rainbow tĩnh theo vị trí
#define EXT_EFFECT_GRAD_CYCLE   33  // Rainbow cuộn + offset hue người dùng
#define EXT_EFFECT_REACTIVE     34  // Flash khi nhấn phím, rồi fade
#define EXT_EFFECT_BAND_SCAN    35  // Dải sáng quét qua lại (bounce)

#define EXT_EFFECT_MAX          35  // Giá trị lớn nhất hợp lệ

// ═══════════════════════════════════════════════════════════════════════════════
//  Indicator mode  (dropdown trong VIA)
// ═══════════════════════════════════════════════════════════════════════════════
#define EXT_IND_LAYER 0   // Tất cả LED = màu theo layer hiện tại
#define EXT_IND_CAPS  1   // CapsLock on → đỏ, off → tắt
#define EXT_IND_NUM   2   // NumLock  on → xanh lá, off → tắt
#define EXT_IND_ALL   3   // Đồng thời: layer + CapsLock + NumLock + ScrollLock

// ═══════════════════════════════════════════════════════════════════════════════
//  VIA channel / Value IDs
//  Channel 0 = ext LED module (custom)
//  Channel 3 = rgblight underglow (built-in QMK VIA handler)
// ═══════════════════════════════════════════════════════════════════════════════
#define EXT_LED_VIA_CHANNEL  0

#define VID_UG_ENABLED      1   // bool   — underglow on/off
#define VID_EXT_ENABLED     2   // bool   — module on/off
#define VID_MODULE_TYPE     3   // uint8  — dropdown EXT_MODULE_*
#define VID_EFFECT          4   // uint8  — dropdown EXT_EFFECT_*
#define VID_COLOR           5   // hue+sat (2 bytes)
#define VID_VAL             6   // uint8  — brightness 0-255
#define VID_SPEED           7   // uint8  — speed 0-255
#define VID_INDICATOR_MODE  8   // uint8  — dropdown EXT_IND_*

// ═══════════════════════════════════════════════════════════════════════════════
//  EEPROM state struct — 9 bytes (= VIA_EEPROM_CUSTOM_CONFIG_SIZE)
// ═══════════════════════════════════════════════════════════════════════════════
typedef struct {
    bool    ug_enabled;        // default: true
    bool    ext_enabled;       // default: false
    uint8_t module_type;       // default: EXT_MODULE_NONE
    uint8_t effect;            // default: EXT_EFFECT_SYNC
    uint8_t hue;               // default: 0
    uint8_t sat;               // default: 255
    uint8_t val;               // default: 180
    uint8_t speed;             // default: 128
    uint8_t indicator_mode;    // default: EXT_IND_LAYER
} __attribute__((packed)) ext_led_state_t;

// ─── Extern ───────────────────────────────────────────────────────────────────
extern ext_led_state_t ext_led_state;

// ─── Helper: số LED active theo module_type ──────────────────────────────────
static inline uint8_t ext_led_count(void) {
    switch (ext_led_state.module_type) {
        case EXT_MODULE_SINGLE: return 1;
        case EXT_MODULE_STRIP20:
        case EXT_MODULE_RING20: return EXT_LED_MAX_COUNT;  // 20
        default:                return 0;
    }
}

// ─── Prototypes ───────────────────────────────────────────────────────────────
void ext_led_config_load(void);
void ext_led_config_save(void);
void ext_led_set_defaults(void);
void ext_led_task(void);