/*
Copyright 2025 Mechlovin'

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

#include "rev1.h"
#include "rgblight.h"

/* =========================================================
 * GLOBAL CONFIG
 * ========================================================= */
custom_rgblight_config_t g_custom_rgblight_config = {
    .logo_enabled = true,
    .ug_enabled   = true,
};

indicator_config_t g_indicator = {
    .enabled  = false,

    .caps_h = 255,    .caps_s = 255, .caps_v = 255,
    .num_h  = 255,   .num_s  = 255, .num_v  = 255,
    .scroll_h = 255,.scroll_s = 255,.scroll_v = 255,
};

/* =========================================================
 * RGB STATE MACHINE
 * ========================================================= */
typedef enum {
    RGB_STATE_OFF = 0,
    RGB_UG_ONLY,
    RGB_LOGO_ONLY_NO_IND,
    RGB_LOGO_ONLY_WITH_IND,
    RGB_UG_LOGO_NO_IND,
    RGB_UG_LOGO_WITH_IND,
} rgb_state_t;

/* =========================================================
 * HELPERS
 * ========================================================= */
static inline bool indicator_active(void) {
    return g_indicator.enabled;
}

static inline void indicator_set(uint8_t idx, uint8_t h, uint8_t s, uint8_t v) {
    rgblight_sethsv_at(h, s, v, idx);
}

static inline void indicator_clear(uint8_t idx) {
    rgblight_sethsv_at(0, 0, 0, idx);
}

/* =========================================================
 * INDICATOR OVERLAY (KHÔNG ĐỤNG EFFECT)
 * ========================================================= */
static void indicator_apply(void) {
    if (!rgblight_is_enabled()) return;
    if (!g_custom_rgblight_config.logo_enabled) return;
    if (!g_indicator.enabled) return;

    led_t led = host_keyboard_led_state();

    led.caps_lock
        ? indicator_set(INDICATOR_CAPS_LED_INDEX,
                        g_indicator.caps_h,
                        g_indicator.caps_s,
                        g_indicator.caps_v)
        : indicator_clear(INDICATOR_CAPS_LED_INDEX);

    led.num_lock
        ? indicator_set(INDICATOR_NUM_LED_INDEX,
                        g_indicator.num_h,
                        g_indicator.num_s,
                        g_indicator.num_v)
        : indicator_clear(INDICATOR_NUM_LED_INDEX);

    led.scroll_lock
        ? indicator_set(INDICATOR_SCROLL_LED_INDEX,
                        g_indicator.scroll_h,
                        g_indicator.scroll_s,
                        g_indicator.scroll_v)
        : indicator_clear(INDICATOR_SCROLL_LED_INDEX);
}

/* =========================================================
 * RESOLVE RGB STATE
 * ========================================================= */
static rgb_state_t resolve_rgb_state(void) {
    bool logo = g_custom_rgblight_config.logo_enabled;
    bool ug   = g_custom_rgblight_config.ug_enabled;
    bool ind  = indicator_active();

    if (!logo && !ug) return RGB_STATE_OFF;
    if (ug && !logo)  return RGB_UG_ONLY;
    if (logo && !ug)  return ind ? RGB_LOGO_ONLY_WITH_IND
                                 : RGB_LOGO_ONLY_NO_IND;
    return ind ? RGB_UG_LOGO_WITH_IND
               : RGB_UG_LOGO_NO_IND;
}

/* =========================================================
 * UPDATE RGBLIGHT (SWITCH–CASE)
 * ========================================================= */
void update_rgblight(void) {
    rgb_state_t state = resolve_rgb_state();

    switch (state) {
        case RGB_STATE_OFF:
            rgblight_disable_noeeprom();
            break;

        case RGB_UG_ONLY:
            rgblight_enable_noeeprom();
            rgblight_set_effect_range(0, UG_LED_COUNT);
            rgblight_sethsv_range(0,0,0, UG_LED_COUNT, RGBLIGHT_LED_COUNT);
            break;

        case RGB_LOGO_ONLY_NO_IND:
            rgblight_enable_noeeprom();
            rgblight_sethsv_range(0, 0, 0, 0, UG_LED_COUNT);
            rgblight_set_effect_range(UG_LED_COUNT,
                                      RGBLIGHT_LED_COUNT);
            break;

        case RGB_LOGO_ONLY_WITH_IND:
            rgblight_enable_noeeprom();
            rgblight_set_effect_range(UG_LED_COUNT, INDICATOR_START_INDEX);
            rgblight_sethsv_range(0,0,0, 0, UG_LED_COUNT + BLOCKER_LED_COUNT - INDICATOR_COUNT);
            indicator_apply();
            break;

        case RGB_UG_LOGO_NO_IND:
            rgblight_enable_noeeprom();
            rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
            break;

        case RGB_UG_LOGO_WITH_IND:
            rgblight_enable_noeeprom();
            rgblight_set_effect_range(0, UG_LED_COUNT + BLOCKER_LED_COUNT - INDICATOR_COUNT);
            indicator_apply();
            break;
    }
}

/* ================================
 * VIA HANDLER
 * ================================ */
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    if (data[1] != id_custom_channel) return;

    switch (data[0]) {
        case id_custom_set_value:
            rgblight_config_set_value(data);
            break;
        case id_custom_get_value:
            rgblight_config_get_value(data);
            break;
        case id_custom_save:
            rgblight_config_save();
            break;
    }
}

/* ================================
 * VIA SET / GET
 * ================================ */
void rgblight_config_set_value(uint8_t *data) {
    switch (data[2]) {
        case id_rgblight_logo_toggle: g_custom_rgblight_config.logo_enabled = data[3]; break;
        case id_rgblight_ug_toggle:   g_custom_rgblight_config.ug_enabled   = data[3]; break;

        case id_indicator_enable:     g_indicator.enabled = data[3]; break;

        case id_indicator_caps_h:     g_indicator.caps_h = data[3]; break;
        case id_indicator_caps_s:     g_indicator.caps_s = data[3]; break;
        case id_indicator_caps_v:     g_indicator.caps_v = data[3]; break;

        case id_indicator_num_h:      g_indicator.num_h = data[3]; break;
        case id_indicator_num_s:      g_indicator.num_s = data[3]; break;
        case id_indicator_num_v:      g_indicator.num_v = data[3]; break;

        case id_indicator_scroll_h:   g_indicator.scroll_h = data[3]; break;
        case id_indicator_scroll_s:   g_indicator.scroll_s = data[3]; break;
        case id_indicator_scroll_v:   g_indicator.scroll_v = data[3]; break;
    }

    rgblight_config_save();
    update_rgblight();
}

void rgblight_config_get_value(uint8_t *data) {
    switch (data[2]) {
        case id_rgblight_logo_toggle: data[3] = g_custom_rgblight_config.logo_enabled; break;
        case id_rgblight_ug_toggle:   data[3] = g_custom_rgblight_config.ug_enabled; break;

        case id_indicator_enable:     data[3] = g_indicator.enabled; break;

        case id_indicator_caps_h:     data[3] = g_indicator.caps_h; break;
        case id_indicator_caps_s:     data[3] = g_indicator.caps_s; break;
        case id_indicator_caps_v:     data[3] = g_indicator.caps_v; break;

        case id_indicator_num_h:      data[3] = g_indicator.num_h; break;
        case id_indicator_num_s:      data[3] = g_indicator.num_s; break;
        case id_indicator_num_v:      data[3] = g_indicator.num_v; break;

        case id_indicator_scroll_h:   data[3] = g_indicator.scroll_h; break;
        case id_indicator_scroll_s:   data[3] = g_indicator.scroll_s; break;
        case id_indicator_scroll_v:   data[3] = g_indicator.scroll_v; break;
    }
}

/* ================================
 * EEPROM
 * ================================ */
void rgblight_config_save(void) {
    uint32_t d = 0;
    d |= (g_custom_rgblight_config.logo_enabled ? 1 : 0) << 0;
    d |= (g_custom_rgblight_config.ug_enabled   ? 1 : 0) << 1;
    eeconfig_update_user(d);
}

void rgblight_config_load(void) {
    uint32_t d = eeconfig_read_user();
    g_custom_rgblight_config.logo_enabled = (d >> 0) & 1;
    g_custom_rgblight_config.ug_enabled   = (d >> 1) & 1;
}


/* =========================================================
 * LOCK UPDATE HOOK
 * ========================================================= */
bool led_update_user(led_t led_state) {
    indicator_apply();
    return true;
}

/* =========================================================
 * INIT
 * ========================================================= */
void keyboard_post_init_user(void) {
    if (!rgblight_is_enabled()) {
        g_custom_rgblight_config.logo_enabled = 0;
        g_custom_rgblight_config.ug_enabled   = 0;
        rgblight_config_save();
        rgblight_disable_noeeprom();
        return;
    }
    rgblight_config_load();
    wait_ms(10); 
    update_rgblight();
}