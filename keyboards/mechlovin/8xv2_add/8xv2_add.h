/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 */
#pragma once

#include "quantum.h"
#include "via.h"
#include "eeconfig.h"

/* ── Zone layout (rgb_matrix indices 0–19) ─────────────────────────────
 *  Ring   0–15 : 16 LEDs clockwise from 12:00
 *  Center 16–19: 4 corner LEDs (TL / TR / BR / BL)
 *  Both IS31FL3731 and WS2812 use the same 20 indices.
 * ─────────────────────────────────────────────────────────────────────── */
#define RING_START    0
#define RING_COUNT    16
#define CENTER_START  16
#define CENTER_COUNT  4

/* ── Center mode ────────────────────────────────────────────────────── */
#define CENTER_MODE_SYNC    0   /* follow rgb_matrix effect */
#define CENTER_MODE_STATIC  1   /* fixed HSV color          */
#define CENTER_MODE_CAPS    2   /* Caps Lock indicator      */
#define CENTER_MODE_NUM     3   /* Num Lock indicator       */
#define CENTER_MODE_SCROLL  4   /* Scroll Lock indicator    */

/* ── Module selection ───────────────────────────────────────────────── */
typedef enum { MODULE_SEL_AUTO=0, MODULE_SEL_IS31=1, MODULE_SEL_WS=2 } module_sel_t;
typedef enum { MODULE_ACTIVE_IS31=0, MODULE_ACTIVE_WS=1 }              module_active_t;

typedef struct { bool enabled; uint8_t mode, h, s, v; } center_cfg_t;

typedef struct {
    bool         ring_enabled;
    center_cfg_t center;
    uint8_t      module_sel;
} kb_eeprom_t;

/* ── VIA ─────────────────────────────────────────────────────────────── */
#define VIA_KB_CHANNEL 0

enum via_kb_id {
    id_ring_enabled      = 1,
    id_center_enabled    = 2,
    id_center_mode       = 3,
    id_center_brightness = 4,
    id_center_color      = 5,
    id_module_sel        = 6,
};

/* ── Globals ─────────────────────────────────────────────────────────── */
extern kb_eeprom_t     g_kb_config;
extern module_active_t g_active_module;

void kb_config_set_value(uint8_t *data);
void kb_config_get_value(uint8_t *data);
void kb_config_save(void);