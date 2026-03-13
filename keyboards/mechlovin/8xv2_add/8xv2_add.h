/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * 8xv2_add.h — keyboard config for Matrix 8XV2 Add
 * Animation logic lives in lib/module_effects.h / module_effects.c
 */
#pragma once
#include "quantum.h"
#include "via.h"
#include "eeconfig.h"
#include "module_effects.h"

/* ── Zone layout ────────────────────────────────────────────────────────
 *  Ring   0–15 : 16 LEDs, clockwise from 12:00
 *  Center 16–19: TL(16) TR(17) BR(18) BL(19)
 * ─────────────────────────────────────────────────────────────────────── */
#define RING_START    0
#define RING_COUNT    16
#define CENTER_START  16
#define CENTER_COUNT  4

/* ── Module selection ───────────────────────────────────────────────── */
typedef enum { MODULE_SEL_AUTO=0, MODULE_SEL_IS31=1, MODULE_SEL_WS=2 } module_sel_t;
typedef enum { MODULE_ACTIVE_IS31=0, MODULE_ACTIVE_WS=1 }              module_active_t;

/* ── Center indicator modes (keyboard-specific, above CENTER_FX_MAX) ──
 * These are handled in 8xv2_add.c, not in the library.
 * Values must be > CENTER_FX_MAX (=9).                              */
#define CENTER_IND_CAPS    10
#define CENTER_IND_NUM     11
#define CENTER_IND_SCROLL  12
#define CENTER_MODE_MAX    CENTER_IND_SCROLL

/* ── EEPROM layout — 13 bytes ───────────────────────────────────────────
 *
 *   Field              Bytes   Notes
 *   ring_enabled         1     bool
 *   ring                 5     led_zone_cfg_t {mode, h, s, v, speed}
 *   center_enabled       1     bool
 *   center               5     led_zone_cfg_t {mode, h, s, v, speed}
 *   module_sel           1
 *   ─────────────────────────────────────────────────────────────────
 *   Total               13
 *
 *   config.h must have:  #define EECONFIG_KB_DATA_SIZE 13
 *   First flash: hold ESC during USB plug to clear EEPROM.
 * ─────────────────────────────────────────────────────────────────────── */
typedef struct {
    bool           ring_enabled;
    led_zone_cfg_t ring;           /* mode h s v speed  (5 bytes) */
    bool           center_enabled;
    led_zone_cfg_t center;         /* mode h s v speed  (5 bytes) */
    uint8_t        module_sel;
} kb_eeprom_t;

/* ── VIA channel & IDs ──────────────────────────────────────────────── */
#define VIA_KB_CHANNEL 0

enum via_kb_id {
    id_ring_enabled      = 1,
    id_center_enabled    = 2,
    id_center_mode       = 3,
    id_center_brightness = 4,
    id_center_color      = 5,   /* 2 bytes: H, S */
    id_module_sel        = 6,
    id_ring_mode         = 7,
    id_ring_color        = 8,   /* 2 bytes: H, S */
    id_ring_brightness   = 9,
    id_ring_speed        = 10,
    id_center_speed      = 11,
};

/* ── Globals ─────────────────────────────────────────────────────────── */
extern kb_eeprom_t     g_kb_config;
extern module_active_t g_active_module;

void kb_config_set_value(uint8_t *data);
void kb_config_get_value(uint8_t *data);
void kb_config_save(void);