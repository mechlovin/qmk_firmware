/* Copyright 2026 Mechlovin' Studio
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include "rgblight.h"
#include "via.h"
#include "eeconfig.h"


/* ================= VIA IDS ================= */
enum custom_via_ids {
    id_rgblight_logo_toggle = 1,
    id_rgblight_ug_toggle   = 2,

    id_indicator_enable     = 10,

    id_indicator_caps_h     = 20,
    id_indicator_caps_s     = 21,
    id_indicator_caps_v     = 22,

    id_indicator_num_h      = 23,
    id_indicator_num_s      = 24,
    id_indicator_num_v      = 25,

    id_indicator_scroll_h  = 26,
    id_indicator_scroll_s  = 27,
    id_indicator_scroll_v  = 28,
};

/* ================= CONFIG STRUCT ================= */
typedef struct {
    bool logo_enabled;
    bool ug_enabled;
} custom_rgblight_config_t;

typedef struct {
    bool enabled;

    uint8_t caps_h, caps_s, caps_v;
    uint8_t num_h,  num_s,  num_v;
    uint8_t scroll_h, scroll_s, scroll_v;
} indicator_config_t;

/* ================= EXTERN ================= */
extern custom_rgblight_config_t g_custom_rgblight_config;
extern indicator_config_t g_indicator;

/* ================= API ================= */
void update_rgblight(void);
void rgblight_config_set_value(uint8_t *data);
void rgblight_config_get_value(uint8_t *data);
void rgblight_config_save(void);
void rgblight_config_load(void);