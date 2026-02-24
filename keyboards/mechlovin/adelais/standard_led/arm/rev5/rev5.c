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

 
#include "rev5.h"
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

static bool g_config_loaded = false;

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
    rgblight_enable_noeeprom();

    switch (state) {
        case RGB_STATE_OFF:
            rgblight_disable_noeeprom();
            return;

        case RGB_UG_ONLY:
            rgblight_reload_from_eeprom();
            rgblight_sethsv_range(0, 0, 0, UG_LED_COUNT, RGBLIGHT_LED_COUNT);
            rgblight_set_effect_range(0, UG_LED_COUNT);
            break;

        case RGB_LOGO_ONLY_NO_IND:
            rgblight_reload_from_eeprom();
            rgblight_sethsv_range(0, 0, 0, 0, UG_LED_COUNT);
            rgblight_set_effect_range(UG_LED_COUNT, BLOCKER_LED_COUNT);
            break;

        case RGB_LOGO_ONLY_WITH_IND:
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_sethsv_range(0, 0, 0, 0, UG_LED_COUNT);
            indicator_apply();
            break;

        case RGB_UG_LOGO_NO_IND:
            rgblight_reload_from_eeprom();
            rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
            break;

        case RGB_UG_LOGO_WITH_IND:
            rgblight_reload_from_eeprom();
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

        // color type: data[3] = H, data[4] = S (2 byte cùng lúc)
        case id_indicator_caps_h:
            g_indicator.caps_h = data[3];
            g_indicator.caps_s = data[4];
            break;
        case id_indicator_num_h:
            g_indicator.num_h = data[3];
            g_indicator.num_s = data[4];
            break;
        case id_indicator_scroll_h:
            g_indicator.scroll_h = data[3];
            g_indicator.scroll_s = data[4];
            break;

        // brightness vẫn là range, 1 byte bình thường
        case id_indicator_caps_v:     g_indicator.caps_v   = data[3]; break;
        case id_indicator_num_v:      g_indicator.num_v    = data[3]; break;
        case id_indicator_scroll_v:   g_indicator.scroll_v = data[3]; break;
    }
    rgblight_config_save();
    update_rgblight();
}

void rgblight_config_get_value(uint8_t *data) {
    switch (data[2]) {
        case id_rgblight_logo_toggle: data[3] = g_custom_rgblight_config.logo_enabled; break;
        case id_rgblight_ug_toggle:   data[3] = g_custom_rgblight_config.ug_enabled;   break;
        case id_indicator_enable:     data[3] = g_indicator.enabled; break;

        // trả về cả H và S
        case id_indicator_caps_h:
            data[3] = g_indicator.caps_h;
            data[4] = g_indicator.caps_s;
            break;
        case id_indicator_num_h:
            data[3] = g_indicator.num_h;
            data[4] = g_indicator.num_s;
            break;
        case id_indicator_scroll_h:
            data[3] = g_indicator.scroll_h;
            data[4] = g_indicator.scroll_s;
            break;

        case id_indicator_caps_v:     data[3] = g_indicator.caps_v;   break;
        case id_indicator_num_v:      data[3] = g_indicator.num_v;    break;
        case id_indicator_scroll_v:   data[3] = g_indicator.scroll_v; break;
    }
}

/* ================================
 * EEPROM
 * ================================ */
void rgblight_config_save(void) {
    user_config_t cfg = {
        .rgb       = g_custom_rgblight_config,
        .indicator = g_indicator,
    };
    eeconfig_update_user_datablock(&cfg, 0, sizeof(user_config_t));
}

void rgblight_config_load(void) {
    user_config_t cfg;
    eeconfig_read_user_datablock(&cfg, 0, sizeof(user_config_t));
    g_custom_rgblight_config = cfg.rgb;
    g_indicator              = cfg.indicator;
    g_config_loaded          = true;
}

/* ================================
 * EEPROM DEFAULT (gọi khi reset EEPROM)
 * ================================ */
void eeconfig_init_user(void) {
    g_custom_rgblight_config.logo_enabled = true;
    g_custom_rgblight_config.ug_enabled   = true;

    g_indicator.enabled  = false;
    g_indicator.caps_h   = 255; g_indicator.caps_s   = 255; g_indicator.caps_v   = 255;
    g_indicator.num_h    = 255; g_indicator.num_s    = 255; g_indicator.num_v    = 255;
    g_indicator.scroll_h = 255; g_indicator.scroll_s = 255; g_indicator.scroll_v = 255;

    rgblight_config_save();
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
    rgblight_config_load();
    if (!rgblight_is_enabled()) {
        g_custom_rgblight_config.logo_enabled = 0;
        g_custom_rgblight_config.ug_enabled   = 0;
        rgblight_config_save();
        rgblight_disable_noeeprom();
        return;
    }
    wait_ms(10); 
    update_rgblight();
}