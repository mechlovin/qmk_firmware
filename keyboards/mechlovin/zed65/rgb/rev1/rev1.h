/*
Copyright 2026 Mechlovin' Studio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"
#include "rgblight.h"
#include "via.h"
#include "eeconfig.h"

#define INDICATOR_PROPERTY_NUMBER 5

/* ================= VIA IDs ================= */

enum via_rgblight_value {
    id_rgblight_logo_toggle = 1,
    id_rgblight_ug_toggle   = 2,
};

enum via_indicator_color {
    id_ind1_brightness = 4,
    id_ind1_color      = 5,
    id_ind1_func       = 6,
    id_ind1_index      = 7,

    id_ind2_enabled    = 8,
    id_ind2_brightness = 9,
    id_ind2_color      = 10,
    id_ind2_func       = 11,
    id_ind2_index      = 12,

    id_ind3_enabled    = 13,
    id_ind3_brightness = 14,
    id_ind3_color      = 15,
    id_ind3_func       = 16,
    id_ind3_index      = 17,

    id_ind4_enabled    = 18,
    id_ind4_brightness = 19,
    id_ind4_color      = 20,
    id_ind4_func       = 21,
    id_ind4_index      = 22,

    id_ind5_enabled    = 23,
    id_ind5_brightness = 24,
    id_ind5_color      = 25,
};

/* ================= STRUCTS ================= */

typedef struct {
    uint8_t h;
    uint8_t s;
    uint8_t v;
    uint8_t func;
    uint8_t index;
    bool    enabled;
} indicator_config;  // 6 bytes

typedef struct {
    indicator_config ind1;
    indicator_config ind2;
    indicator_config ind3;
    indicator_config ind4;
    indicator_config ind5;
} keyboard_indicators;  // 30 bytes == EECONFIG_KB_DATA_SIZE

typedef struct {
    bool logo_enabled;
    bool ug_enabled;
} custom_rgblight_config_t;

/* ================= EXTERN ================= */

extern int indi_index;
extern int data_index;
extern int indicator_number;

extern keyboard_indicators indicators;
extern uint8_t* pIndicators;

extern custom_rgblight_config_t g_custom_rgblight_config;

/* ================= FUNCTION PROTOTYPES ================= */

indicator_config* get_indicator_p(int index);

void rgblight_config_set_value(uint8_t *data);
void rgblight_config_get_value(uint8_t *data);
void rgblight_config_save(void);
void rgblight_config_load(void);
void indicator_config_set_value(uint8_t *data);
void indicator_config_get_value(uint8_t *data);
void indicator_config_save(void);
void update_rgblight(bool logo_was, bool ug_was);

/* Fade engine – called from keymap.c for keycode handlers */
void matrix_fade_in(void);
void matrix_fade_out(void);
void rgblight_fade_in(void);
void rgblight_fade_out(void);