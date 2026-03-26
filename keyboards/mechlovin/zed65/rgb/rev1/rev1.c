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
       4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1,
       4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    4, 1,
       4,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1,
       4, 4, 4,          4,          4, 4, 4, 1,
    }
};

/* ============================================================
 * GLOBALS
 * ============================================================ */

keyboard_indicators indicators;

/* Per-LED colour overrides — RAM only (reset on power cycle) */
static perled_config perled_overrides[PERLED_COUNT];
static uint8_t       selected_led = 0;

#define INDICATOR_COUNT  (sizeof(keyboard_indicators) / sizeof(indicator_config))
_Static_assert(sizeof(keyboard_indicators)    == 30,  "keyboard_indicators size changed");
_Static_assert(sizeof(perled_config)          == 4,   "perled_config size changed");
_Static_assert(sizeof(keyboard_eeprom_data_t) == EECONFIG_KB_DATA_SIZE,
               "keyboard_eeprom_data_t size mismatch with EECONFIG_KB_DATA_SIZE");

custom_rgblight_config_t g_custom_rgblight_config;

/* ============================================================
 * INDICATOR HELPERS
 * ============================================================ */

indicator_config* get_indicator_p(int index) {
    return ((indicator_config*)&indicators) + index;
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
 * ind1 (Caps): follows matrix effect. Caps ON → override colour/brightness.
 * ind5 (Blocker): follows matrix effect. VIA enabled=true → override.
 * ind2–ind4: follows matrix effect. enabled + trigger active → override.
 * ============================================================ */

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) return false;

    /* ind1: Caps Lock – fixed at CAPS_LED_INDEX */
    {
        indicator_config* ind = get_indicator_p(0);
        if (host_keyboard_led_state().caps_lock) {
            RGB rgb = hsv_to_rgb((HSV){ind->h, ind->s, ind->v});
            rgb_matrix_set_color(CAPS_LED_INDEX, rgb.r, rgb.g, rgb.b);
        }
    }

    /* ind5: Blocker – fixed at BLOCKER_LED_INDEX */
    {
        indicator_config* ind = get_indicator_p(4);
        if (ind->enabled) {
            RGB rgb = hsv_to_rgb((HSV){ind->h, ind->s, ind->v});
            rgb_matrix_set_color(BLOCKER_LED_INDEX, rgb.r, rgb.g, rgb.b);
        }
    }

    /* ind2–ind4: user-configurable position and trigger */
    for (int i = 1; i <= 3; i++) {
        indicator_config* ind = get_indicator_p(i);
        if (!ind->enabled) continue;
        if (indicator_active(*ind)) {
            RGB rgb = hsv_to_rgb((HSV){ind->h, ind->s, ind->v});
            rgb_matrix_set_color(ind->index, rgb.r, rgb.g, rgb.b);
        }
    }

    /* Per-LED colour overrides */
    for (int i = 0; i < PERLED_COUNT; i++) {
        if (perled_overrides[i].enabled) {
            RGB rgb = hsv_to_rgb((HSV){ perled_overrides[i].h,
                                        perled_overrides[i].s,
                                        perled_overrides[i].v });
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }

    return true;
}

/* ============================================================
 * PER-LED VIA HANDLERS
 * ============================================================ */

void perled_config_set_value(uint8_t *data) {
    uint8_t id  = data[0];
    uint8_t *v  = &data[1];
    switch (id) {
        case id_perled_index:
            selected_led = (v[0] < PERLED_COUNT) ? v[0] : 0;
            break;
        case id_perled_enable:
            perled_overrides[selected_led].enabled = v[0];
            /* Per-LED overrides need the matrix task running to be rendered.
             * If the matrix is currently off, turn it on (no-EEPROM so the
             * user's persistent "off" preference is not changed). */
            if (v[0] && !rgb_matrix_is_enabled()) {
                rgb_matrix_enable_noeeprom();
            }
            break;
        case id_perled_brightness:
            perled_overrides[selected_led].v = v[0];
            break;
        case id_perled_color:
            perled_overrides[selected_led].h = v[0];
            perled_overrides[selected_led].s = v[1];
            break;
    }
}

void perled_config_get_value(uint8_t *data) {
    uint8_t id  = data[0];
    uint8_t *v  = &data[1];
    switch (id) {
        case id_perled_index:      v[0] = selected_led;                                break;
        case id_perled_enable:     v[0] = perled_overrides[selected_led].enabled;      break;
        case id_perled_brightness: v[0] = perled_overrides[selected_led].v;            break;
        case id_perled_color:
            v[0] = perled_overrides[selected_led].h;
            v[1] = perled_overrides[selected_led].s;
            break;
    }
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

    memset(perled_overrides, 0, sizeof(perled_overrides));

    keyboard_eeprom_data_t block;
    block.ind = indicators;
    memcpy(block.perled, perled_overrides, sizeof(perled_overrides));
    eeconfig_update_kb_datablock(&block);
}

/* ============================================================
 * RGBLIGHT ZONE MANAGEMENT
 * ============================================================ */

/* Apply effect_range and blackout for the inactive zone.
 * Must be called whenever zone state changes. */
static void apply_rgblight_zones(void) {
    bool logo = g_custom_rgblight_config.logo_enabled;
    bool ug   = g_custom_rgblight_config.ug_enabled;

    if (!logo && !ug) {
        rgblight_disable_noeeprom();
        return;
    }

    rgblight_enable_noeeprom();

    if (logo && ug) {
        rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
    } else if (logo) {
        rgblight_set_effect_range(UG_LED_COUNT, BLOCKER_LED_COUNT);
        rgblight_sethsv_range(0, 0, 0, 0, UG_LED_COUNT);
    } else {
        rgblight_set_effect_range(0, UG_LED_COUNT);
        rgblight_sethsv_range(0, 0, 0, UG_LED_COUNT, RGBLIGHT_LED_COUNT);
    }
}

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
    /* Bits 0–1 default to 0 on a fresh/cleared EEPROM.
     * Treat 0b00 as "never written" and default both zones ON. */
    if ((raw & 0x3) == 0) {
        g_custom_rgblight_config.logo_enabled = true;
        g_custom_rgblight_config.ug_enabled   = true;
        rgblight_config_save();
    } else {
        g_custom_rgblight_config.logo_enabled = raw & 0x1;
        g_custom_rgblight_config.ug_enabled   = (raw >> 1) & 0x1;
    }
}

void update_rgblight(bool logo_was, bool ug_was) {
    (void)logo_was;
    (void)ug_was;
    apply_rgblight_zones();
}

/* ============================================================
 * VIA INDICATOR HANDLERS
 * ============================================================ */

void indicator_config_set_value(uint8_t *data) {
    uint8_t id = data[0];
    uint8_t *v = &data[1];
    int indi_index = (id - 3) / INDICATOR_PROPERTY_NUMBER;
    int data_index = (id - 3) % INDICATOR_PROPERTY_NUMBER;

    indicator_config* ind = get_indicator_p(indi_index);

    if (indi_index == 0) {
        /* ind1: Caps – always enabled, no func/index change needed */
        switch (data_index) {
            case 0: ind->enabled = true;                       break;
            case 1: ind->v       = v[0];                       break;
            case 2: ind->h = v[0]; ind->s = v[1];             break;
            case 3: ind->func    = v[0];                       break;
            case 4: ind->index   = v[0];                       break;
        }
        return;
    }

    if (indi_index == 4) {
        /* ind5: Blocker – no func/index in VIA UI */
        switch (data_index) {
            case 0: ind->enabled = v[0];                       break;
            case 1: ind->v       = v[0];                       break;
            case 2: ind->h = v[0]; ind->s = v[1];             break;
            default: return;
        }
        return;
    }

    /* ind2–ind4 */
    switch (data_index) {
        case 0: ind->enabled = v[0];                           break;
        case 1: ind->v       = v[0];                           break;
        case 2: ind->h = v[0]; ind->s = v[1];                 break;
        case 3: ind->func    = v[0];                           break;
        case 4: ind->index   = v[0];                           break;
    }
}

void indicator_config_get_value(uint8_t *data) {
    uint8_t id = data[0];
    uint8_t *v = &data[1];
    int indi_index = (id - 3) / INDICATOR_PROPERTY_NUMBER;
    int data_index = (id - 3) % INDICATOR_PROPERTY_NUMBER;

    indicator_config* ind = get_indicator_p(indi_index);

    if (indi_index == 4) {
        switch (data_index) {
            case 0: v[0] = ind->enabled;                       break;
            case 1: v[0] = ind->v;                             break;
            case 2: v[0] = ind->h; v[1] = ind->s;             break;
            default: v[0] = 0;
        }
        return;
    }

    switch (data_index) {
        case 0: v[0] = ind->enabled;                           break;
        case 1: v[0] = ind->v;                                 break;
        case 2: v[0] = ind->h; v[1] = ind->s;                 break;
        case 3: v[0] = ind->func;                              break;
        case 4: v[0] = ind->index;                             break;
    }
}

void indicator_config_save(void) {
    keyboard_eeprom_data_t block;
    eeconfig_read_kb_datablock(&block);
    block.ind = indicators;
    eeconfig_update_kb_datablock(&block);
}

void perled_config_save(void) {
    keyboard_eeprom_data_t block;
    eeconfig_read_kb_datablock(&block);
    memcpy(block.perled, perled_overrides, sizeof(perled_overrides));
    eeconfig_update_kb_datablock(&block);
}

void perled_config_load(void) {
    keyboard_eeprom_data_t block;
    eeconfig_read_kb_datablock(&block);
    indicators = block.ind;
    memcpy(perled_overrides, block.perled, sizeof(perled_overrides));
}

/* ============================================================
 * VIA DISPATCH
 * ============================================================ */

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *cmd = &data[0];
    uint8_t *ch  = &data[1];
    uint8_t *vd  = &data[2];

    /* Channel 0x0F: bootloader jump and EEPROM reset (formerly in keymap.c) */
    if (*ch == 0x0F) {
        if (*cmd == id_custom_set_value) {
            if      (vd[0] == 0x01) reset_keyboard();
            else if (vd[0] == 0x02) eeconfig_init();
        }
        return;
    }

    if (*ch != id_custom_channel) { *cmd = id_unhandled; return; }

    switch (*cmd) {
        case id_custom_set_value:
            if      (vd[0] <= id_rgblight_ug_toggle) rgblight_config_set_value(vd);
            else if (vd[0] <= id_ind5_color)          indicator_config_set_value(vd);
            else                                       perled_config_set_value(vd);
            break;
        case id_custom_get_value:
            if      (vd[0] <= id_rgblight_ug_toggle) rgblight_config_get_value(vd);
            else if (vd[0] <= id_ind5_color)          indicator_config_get_value(vd);
            else                                       perled_config_get_value(vd);
            break;
        case id_custom_save:
            rgblight_config_save();
            indicator_config_save();
            perled_config_save();
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
    perled_config_load();

    /* Enforce fixed state for structurally-fixed indicators */
    indicators.ind1.enabled = true;
    indicators.ind1.v       = 255;

    apply_rgblight_zones();

    rgb_matrix_reload_from_eeprom();

    /* If any per-LED override was loaded, ensure the matrix is enabled so
     * rgb_matrix_indicators_kb() actually runs and renders them. */
    for (int i = 0; i < PERLED_COUNT; i++) {
        if (perled_overrides[i].enabled) {
            if (!rgb_matrix_is_enabled()) rgb_matrix_enable_noeeprom();
            break;
        }
    }

    rgb_matrix_indicators_kb();
}