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

#include "quantum.h"
#include "rev1.h"
#include "rgblight.h"
#include "rgb_fade.h"

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
}

const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0,   CS37_SW7, CS39_SW7,   CS38_SW7}, //0
    {0,   CS37_SW8, CS39_SW8,   CS38_SW8}, //1
    {0,   CS34_SW7, CS36_SW7,   CS35_SW7}, //2
    {0,   CS34_SW8, CS36_SW8,   CS35_SW8}, //3
    {0,   CS31_SW7, CS33_SW7,   CS32_SW7}, //4
    {0,   CS31_SW8, CS33_SW8,   CS32_SW8}, //5
    {0,   CS28_SW7, CS30_SW7,   CS29_SW7}, //6
    {0,   CS28_SW8, CS30_SW8,   CS29_SW8}, //7
    {0,    CS7_SW7, CS9_SW7,    CS8_SW7},  //8
    {0,    CS7_SW8, CS9_SW8,    CS8_SW8},  //9
    {0,   CS13_SW7, CS15_SW7,   CS14_SW7}, //10
    {0,   CS13_SW8, CS15_SW8,   CS14_SW8}, //11
    {0,   CS16_SW7, CS18_SW7,   CS17_SW7}, //12
    {0,   CS16_SW8, CS18_SW8,   CS17_SW8}, //13
    {0,   CS19_SW8, CS21_SW8,   CS20_SW8}, //14

    {0,   CS37_SW5, CS39_SW5,   CS38_SW5}, //15
    {0,   CS37_SW6, CS39_SW6,   CS38_SW6}, //16
    {0,   CS34_SW5, CS36_SW5,   CS35_SW5}, //17
    {0,   CS34_SW6, CS36_SW6,   CS35_SW6}, //18
    {0,   CS31_SW5, CS33_SW5,   CS32_SW5}, //19
    {0,   CS31_SW6, CS33_SW6,   CS32_SW6}, //20
    {0,   CS28_SW5, CS30_SW5,   CS29_SW5}, //21
    {0,   CS28_SW6, CS30_SW6,   CS29_SW6}, //22
    {0,    CS7_SW5, CS9_SW5,    CS8_SW5},  //23
    {0,    CS7_SW6, CS9_SW6,    CS8_SW6},  //24
    {0,   CS13_SW5, CS15_SW5,   CS14_SW5}, //25
    {0,   CS13_SW6, CS15_SW6,   CS14_SW6}, //26
    {0,   CS16_SW5, CS18_SW5,   CS17_SW5}, //27
    {0,   CS16_SW6, CS18_SW6,   CS17_SW6}, //28
    {0,   CS19_SW6, CS21_SW6,   CS20_SW6}, //29

    {0,   CS37_SW3, CS39_SW3,   CS38_SW3}, //30
    {0,   CS37_SW4, CS39_SW4,   CS38_SW4}, //31
    {0,   CS34_SW3, CS36_SW3,   CS35_SW3}, //32
    {0,   CS34_SW4, CS36_SW4,   CS35_SW4}, //33
    {0,   CS31_SW3, CS33_SW3,   CS32_SW3}, //34
    {0,   CS31_SW4, CS33_SW4,   CS32_SW4}, //35
    {0,   CS28_SW3, CS30_SW3,   CS29_SW3}, //36
    {0,   CS28_SW4, CS30_SW4,   CS29_SW4}, //37
    {0,    CS7_SW3, CS9_SW3,    CS8_SW3},  //38
    {0,    CS7_SW4, CS9_SW4,    CS8_SW4},  //39
    {0,   CS13_SW3, CS15_SW3,   CS14_SW3}, //40
    {0,   CS13_SW4, CS15_SW4,   CS14_SW4}, //41
    {0,   CS16_SW3, CS18_SW3,   CS17_SW3}, //42
    {0,   CS19_SW3, CS21_SW3,   CS20_SW3}, //43

    {0,   CS37_SW1, CS39_SW1,   CS38_SW1}, //44
    {0,   CS34_SW1, CS36_SW1,   CS35_SW1}, //45
    {0,   CS34_SW2, CS36_SW2,   CS35_SW2}, //46
    {0,   CS31_SW1, CS33_SW1,   CS32_SW1}, //47
    {0,   CS31_SW2, CS33_SW2,   CS32_SW2}, //48
    {0,   CS28_SW1, CS30_SW1,   CS29_SW1}, //49
    {0,   CS28_SW2, CS30_SW2,   CS29_SW2}, //50
    {0,    CS7_SW1, CS9_SW1,    CS8_SW1},  //51
    {0,    CS7_SW2, CS9_SW2,    CS8_SW2},  //52
    {0,   CS13_SW1, CS15_SW1,   CS14_SW1}, //53
    {0,   CS13_SW2, CS15_SW2,   CS14_SW2}, //54
    {0,   CS16_SW1, CS18_SW1,   CS17_SW1}, //55
    {0,   CS16_SW2, CS18_SW2,   CS17_SW2}, //56
    {0,   CS19_SW2, CS21_SW2,   CS20_SW2}, //57

    {0,   CS37_SW9, CS39_SW9,   CS38_SW9}, //58
    {0,   CS37_SW2, CS39_SW2,   CS38_SW2}, //59
    {0,   CS34_SW9, CS36_SW9,   CS35_SW9}, //60
    {0,   CS28_SW9, CS30_SW9,   CS29_SW9}, //61
    {0,   CS13_SW9, CS15_SW9,   CS14_SW9}, //62
    {0,   CS16_SW9, CS18_SW9,   CS17_SW9}, //63
    {0,   CS16_SW4, CS18_SW4,   CS17_SW4}, //64
    {0,   CS19_SW4, CS21_SW4,   CS20_SW4}, //65
};

led_config_t g_led_config = { {
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,          10,          11,          12,          13,          14},
        {15,         16,          17,          18,          19,          20,          21,          22,          23,          24,          25,          26,          27,          28,          29},
        {30,         31,          32,          33,          34,          35,          36,          37,          38,          39,          40,          41,      NO_LED,          42,          43},
        {44,     NO_LED,          45,          46,          47,          48,          49,          50,          51,          52,          53,          54,          55,          56,          57},
        {58,         59,          60,      NO_LED,      NO_LED,      NO_LED,          61,      NO_LED,      NO_LED,      NO_LED,      NO_LED,          62,          63,          64,          65},
    }, {
        {0,   0}, {16,  0}, {32,  0}, {48,  0}, {64,  0}, {80,  0}, {96,  0}, {112, 0}, {128, 0}, {144, 0}, {160, 0}, {176, 0}, {192, 0}, {208, 0}, {224, 0},
        {0,  16}, {16, 16}, {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112,16}, {128,16}, {144,16}, {160,16}, {176,16}, {192,16}, {208,16}, {224,16},
        {0,  32}, {16, 32}, {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112,32}, {128,32}, {144,32}, {160,32}, {176,32},           {208,32}, {224,32},
        {0,  48},           {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112,48}, {128,48}, {144,48}, {160,48}, {176,48}, {192,48}, {208,48}, {224,48},
        {0,  64}, {16, 64}, {32, 64},                               {96, 64},                                           {176,64}, {192,64}, {208,64}, {224,64},
    }, {
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1,
       1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
       1, 1, 1,          1,          1, 1, 1, 1,
    }
};

/* ============================================================
 * GLOBALS
 * ============================================================ */

int indi_index;
int data_index;

keyboard_indicators indicators;
uint8_t* pIndicators = (uint8_t*)&indicators;

int indicator_number = sizeof(keyboard_indicators) / sizeof(indicator_config);

_Static_assert(sizeof(keyboard_indicators) == EECONFIG_KB_DATA_SIZE,
               "keyboard_indicators size mismatch with EECONFIG_KB_DATA_SIZE");

custom_rgblight_config_t g_custom_rgblight_config;

static inline uint8_t step_toward(uint8_t cur, uint8_t tgt, uint8_t step) {
    if (cur < tgt) return (tgt - cur > step) ? (uint8_t)(cur + step) : tgt;
    if (cur > tgt) return (cur - tgt > step) ? (uint8_t)(cur - step) : tgt;
    return cur;
}

static inline RGB scale_rgb(RGB c, uint8_t s) {
    if (s == 255) return c;
    if (s == 0)   return (RGB){0, 0, 0};
    return (RGB){
        (uint8_t)((uint16_t)c.r * s / 255),
        (uint8_t)((uint16_t)c.g * s / 255),
        (uint8_t)((uint16_t)c.b * s / 255),
    };
}

/* ── Per-indicator scale ─────────────────────────────────────── */
static uint8_t ind_scale[5]     = {255,   0,   0,   0, 255};
static uint8_t ind_scale_tgt[5] = {255,   0,   0,   0, 255};

/* ============================================================
 * matrix_scan_kb  —  state machine ticks
 * ============================================================ */
void matrix_scan_kb(void) {
    rgb_fade_tick();

    /* ── Per-indicator scale ── */
    static uint32_t ind_last = 0;
    if (timer_elapsed32(ind_last) >= RGB_FADE_TICK_MS) {
        ind_last = timer_read32();
        for (int i = 0; i < 5; i++) {
            ind_scale[i] = step_toward(ind_scale[i], ind_scale_tgt[i], RGB_FADE_POWER_STEP);
        }
    }

    matrix_scan_user();
}


void housekeeping_task_kb(void) {
    housekeeping_task_user();
}

/* ============================================================
 * PUBLIC FADE API — delegated to rgb_fade.h
 * ============================================================ */

void matrix_fade_in(void)    { rgb_fade_matrix_in();    }
void matrix_fade_out(void)   { rgb_fade_matrix_out();   }
void rgblight_fade_in(void)  { rgb_fade_rgblight_in();  }
void rgblight_fade_out(void) { rgb_fade_rgblight_out(); }

/* ============================================================
 * INDICATOR HELPERS
 * ============================================================ */

indicator_config* get_indicator_p(int index) {
    return (indicator_config*)(pIndicators + sizeof(indicator_config) * index);
}

static bool indicator_active(indicator_config ind) {
    switch (ind.func) {
        case 0: return host_keyboard_led_state().num_lock;
        case 1: return host_keyboard_led_state().scroll_lock;
        case 2: case 3: case 4: case 5: case 6:
            return IS_LAYER_ON(ind.func - 2);
        default: return false;
    }
}

/* ============================================================
 * RGB MATRIX INDICATORS
 *
 * During MX_XFADE_IN: dim every LED by mx_dim_scale so new
 * effect fades in smoothly. During MX_IDLE with dim==255: pass
 * through unchanged. Indicator LEDs always rendered last.
 * ============================================================ */
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) return false;

    /* Indicator overrides — always applied on top.
     * No manual dimming needed: engine scales via hsv.v. */
    for (int i = 0; i < indicator_number; i++) {
        indicator_config* ind = get_indicator_p(i);
        uint8_t sc = ind_scale[i];

        if (i == 0) {
            if (host_keyboard_led_state().caps_lock && sc > 0) {
                RGB rgb = scale_rgb(hsv_to_rgb((HSV){ind->h, ind->s, ind->v}), sc);
                rgb_matrix_set_color(CAPS_LED_INDEX, rgb.r, rgb.g, rgb.b);
            } else {
                rgb_matrix_set_color(CAPS_LED_INDEX, 0, 0, 0);
            }
            continue;
        }

        if (i == 4) {
            RGB rgb = scale_rgb(hsv_to_rgb((HSV){ind->h, ind->s, ind->v}), sc);
            rgb_matrix_set_color(BLOCKER_LED_INDEX, rgb.r, rgb.g, rgb.b);
            continue;
        }

        if (sc == 0) {
            rgb_matrix_set_color(ind->index, 0, 0, 0);
            continue;
        }
        if (indicator_active(*ind)) {
            RGB rgb = scale_rgb(hsv_to_rgb((HSV){ind->h, ind->s, ind->v}), sc);
            rgb_matrix_set_color(ind->index, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(ind->index, 0, 0, 0);
        }
    }
    return true;
}

/* ============================================================
 * EEPROM
 * ============================================================ */

void eeconfig_init_kb(void) {
    indicators.ind1 = (indicator_config){ .h=0, .s=0,   .v=255, .func=0xFF, .index=CAPS_LED_INDEX,    .enabled=true  };
    indicators.ind2 = (indicator_config){ .h=0, .s=255, .v=255, .func=0,    .index=1,                 .enabled=false };
    indicators.ind3 = (indicator_config){ .h=0, .s=255, .v=255, .func=1,    .index=2,                 .enabled=false };
    indicators.ind4 = (indicator_config){ .h=0, .s=255, .v=255, .func=2,    .index=3,                 .enabled=false };
    indicators.ind5 = (indicator_config){ .h=0, .s=0,   .v=255, .func=0xFF, .index=BLOCKER_LED_INDEX, .enabled=true  };

    eeconfig_update_kb_datablock(&indicators);
    eeconfig_init_kb_datablock();
}

/* ============================================================
 * RGB MATRIX STARTUP
 * ============================================================ */

static void rgb_matrix_startup(void) {
    rgb_matrix_reload_from_eeprom();
}

/* ============================================================
 * RGBLIGHT CONFIG
 * ============================================================ */

void rgblight_config_set_value(uint8_t *data) {
    bool logo_was = g_custom_rgblight_config.logo_enabled;
    bool ug_was   = g_custom_rgblight_config.ug_enabled;

    switch (data[0]) {
        case id_rgblight_logo_toggle: g_custom_rgblight_config.logo_enabled = data[1]; break;
        case id_rgblight_ug_toggle:   g_custom_rgblight_config.ug_enabled   = data[1]; break;
    }

    rgblight_config_save();
    update_rgblight(logo_was, ug_was);
}

void rgblight_config_get_value(uint8_t *data) {
    data[1] = (data[0] == id_rgblight_logo_toggle)
                ? g_custom_rgblight_config.logo_enabled
                : g_custom_rgblight_config.ug_enabled;
}

void rgblight_config_save(void) {
    uint32_t raw = eeconfig_read_user();
    raw &= ~0x3;
    raw |= (uint32_t)g_custom_rgblight_config.logo_enabled;
    raw |= (uint32_t)g_custom_rgblight_config.ug_enabled << 1;
    eeconfig_update_user(raw);
}

void rgblight_config_load(void) {
    uint32_t raw = eeconfig_read_user();
    g_custom_rgblight_config.logo_enabled = raw & 0x1;
    g_custom_rgblight_config.ug_enabled   = (raw >> 1) & 0x1;
}

void update_rgblight(bool logo_was, bool ug_was) {
    bool logo    = g_custom_rgblight_config.logo_enabled;
    bool ug      = g_custom_rgblight_config.ug_enabled;
    bool was_any = logo_was || ug_was;
    bool is_any  = logo     || ug;

    if (!was_any && !is_any) return;

    if (!was_any && is_any) {
        rgblight_fade_in();
    } else if (was_any && !is_any) {
        rgblight_fade_out();
    } else {
        /* Zone swap: fade out current, apply zone at midpoint, fade in */
        rgb_fade_rgblight_out();
        rgb_fade_rgblight_in();
    }
}

/* ============================================================
 * VIA INDICATOR HANDLERS
 * ============================================================ */

void indicator_config_set_value(uint8_t *data) {
    uint8_t id = data[0];
    uint8_t *v = &data[1];

    indi_index = (id - 3) / INDICATOR_PROPERTY_NUMBER;
    data_index = (id - 3) % INDICATOR_PROPERTY_NUMBER;

    indicator_config* ind = get_indicator_p(indi_index);

    if (indi_index == 0) {
        switch (data_index) {
            case 0: ind->enabled = true; break;
            case 1: ind->v       = v[0]; break;
            case 2: ind->h = v[0]; ind->s = v[1]; break;
            case 3: ind->func    = v[0]; break;
            case 4: ind->index   = v[0]; break;
        }
        return;
    }

    if (indi_index == 4) {
        switch (data_index) {
            case 0:
                ind->enabled = v[0];
                ind_scale_tgt[4] = v[0] ? 255 : 0;
                break;
            case 1: ind->v = v[0]; break;
            case 2: ind->h = v[0]; ind->s = v[1]; break;
            default: return;
        }
        return;
    }

    switch (data_index) {
        case 0:
            ind->enabled = v[0];
            ind_scale_tgt[indi_index] = v[0] ? 255 : 0;
            break;
        case 1: ind->v       = v[0]; break;
        case 2: ind->h = v[0]; ind->s = v[1]; break;
        case 3: ind->func    = v[0]; break;
        case 4: ind->index   = v[0]; break;
    }
}

void indicator_config_get_value(uint8_t *data) {
    uint8_t id = data[0];
    uint8_t *v = &data[1];

    indi_index = (id - 3) / INDICATOR_PROPERTY_NUMBER;
    data_index = (id - 3) % INDICATOR_PROPERTY_NUMBER;

    indicator_config* ind = get_indicator_p(indi_index);

    if (indi_index == 4) {
        switch (data_index) {
            case 0: v[0] = ind->enabled; break;
            case 1: v[0] = ind->v; break;
            case 2: v[0] = ind->h; v[1] = ind->s; break;
            default: v[0] = 0;
        }
        return;
    }

    switch (data_index) {
        case 0: v[0] = ind->enabled; break;
        case 1: v[0] = ind->v; break;
        case 2: v[0] = ind->h; v[1] = ind->s; break;
        case 3: v[0] = ind->func; break;
        case 4: v[0] = ind->index; break;
    }
}

void indicator_config_save(void) {
    eeconfig_update_kb_datablock(&indicators);
}

/* ============================================================
 * VIA DISPATCH
 * ============================================================ */

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *cmd = &data[0];
    uint8_t *ch  = &data[1];
    uint8_t *vd  = &data[2];

    if (*ch != id_custom_channel) { *cmd = id_unhandled; return; }

    switch (*cmd) {
        case id_custom_set_value:
            if (vd[0] <= id_rgblight_ug_toggle)
                rgblight_config_set_value(vd);
            else
                indicator_config_set_value(vd);
            break;
        case id_custom_get_value:
            if (vd[0] <= id_rgblight_ug_toggle)
                rgblight_config_get_value(vd);
            else
                indicator_config_get_value(vd);
            break;
        case id_custom_save:
            rgblight_config_save();
            indicator_config_save();
            break;
        default:
            *cmd = id_unhandled;
    }
}

/* ============================================================
 * POST INIT
 * ============================================================ */

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;

    rgblight_config_load();
    eeconfig_read_kb_datablock(&indicators);

    indicators.ind1.index   = CAPS_LED_INDEX;
    indicators.ind1.enabled = true;
    indicators.ind5.index   = BLOCKER_LED_INDEX;

    ind_scale[0] = 255; ind_scale_tgt[0] = 255;
    for (int i = 1; i <= 3; i++) {
        uint8_t s = get_indicator_p(i)->enabled ? 255 : 0;
        ind_scale[i] = s; ind_scale_tgt[i] = s;
    }
    ind_scale[4] = indicators.ind5.enabled ? 255 : 0;
    ind_scale_tgt[4] = ind_scale[4];

    wait_ms(10);

    rgb_matrix_startup();

    if (g_custom_rgblight_config.logo_enabled || g_custom_rgblight_config.ug_enabled) {
        rgblight_fade_in();
    } else {
        rgblight_enable_noeeprom();
    }

    rgb_fade_init();
    rgb_matrix_indicators_kb();
}