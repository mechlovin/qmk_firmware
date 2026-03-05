/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#pragma once

#include "quantum.h"
#include "via.h"
#include "eeconfig.h"

/* ── Zone layout (rgb_matrix indices) ──────────────────────────────────────
 *
 *  IS31FL3731   0–15  : ring  (16 LEDs, clockwise from 12:00)
 *  IS31FL3731  16–19  : center (4 LEDs — TL / TR / BR / BL)
 *  WS2812      20–35  : ring  (same angular positions as IS31 ring)
 *  WS2812      36–39  : center (same corner positions as IS31 center)
 *
 *  WS physical index = rgb_matrix_index - IS31FL3731_LED_COUNT (20)
 * ─────────────────────────────────────────────────────────────────────────── */
#define IS31_RING_START     0
#define IS31_RING_COUNT     16
#define IS31_CENTER_START   16
#define IS31_CENTER_COUNT   4

#define WS_RING_START       20
#define WS_RING_COUNT       16
#define WS_CENTER_START     36
#define WS_CENTER_COUNT     4

/* ── Center zone modes ──────────────────────────────────────────────────── */
#define CENTER_MODE_SYNC    0   /* follow rgb_matrix effect (position-based) */
#define CENTER_MODE_STATIC  1   /* fixed HSV color                           */
#define CENTER_MODE_CAPS    2   /* Caps Lock indicator                       */
#define CENTER_MODE_NUM     3   /* Num Lock indicator                        */
#define CENTER_MODE_SCROLL  4   /* Scroll Lock indicator                     */

/* ── Center zone config (5 bytes) ──────────────────────────────────────── */
typedef struct {
    bool    enabled;
    uint8_t mode;
    uint8_t h;
    uint8_t s;
    uint8_t v;
} center_cfg_t;

/* ── EEPROM KB block  12 bytes = EECONFIG_KB_DATA_SIZE ─────────────────── */
typedef struct {
    bool         is31_ring_enabled;   /*  1 */
    center_cfg_t is31_center;         /*  5 */
    bool         ws_ring_enabled;     /*  1 */
    center_cfg_t ws_center;           /*  5 */
} kb_eeprom_t;                        /* 12 */

/* ── VIA custom channel / IDs ───────────────────────────────────────────── */
#define VIA_KB_CHANNEL  0

enum via_kb_id {
    id_is31_ring_enabled      = 1,
    id_is31_center_enabled    = 2,
    id_is31_center_mode       = 3,
    id_is31_center_brightness = 4,
    id_is31_center_color      = 5,   /* H + S, 2 bytes */
    id_ws_ring_enabled        = 6,
    id_ws_center_enabled      = 7,
    id_ws_center_mode         = 8,
    id_ws_center_brightness   = 9,
    id_ws_center_color        = 10,  /* H + S, 2 bytes */
};

/* ── Globals ────────────────────────────────────────────────────────────── */
extern kb_eeprom_t g_kb_config;

/* ── Prototypes ─────────────────────────────────────────────────────────── */
void kb_config_set_value(uint8_t *data);
void kb_config_get_value(uint8_t *data);
void kb_config_save(void);