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
#include "8xv2_add.h"
#include "rgblight.h"

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
}

const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {

    {0, C9_5,   C8_5,   C7_5}, //D155-A9-0
    {0, C9_6,   C8_6,   C7_6}, //D166-A11-1
    {0, C9_7,   C8_7,   C6_6}, //D178-A13-2
    {0, C9_8,   C7_7,   C6_7}, //D187-A15-3

    {0, C1_1,   C3_2,   C4_2}, //D115-A2-4-ok
    {0, C1_2,   C2_2,   C4_3}, //D126-A4-5-ok
    {0, C1_3,   C2_3,   C3_3}, //D138-A6-6-ok
    {0, C1_4,   C2_4,   C3_4}, //D149-A8-7-ok
    {0, C1_5,   C2_5,   C3_5}, //D160-A10-8-ok
    {0, C1_6,   C2_6,   C3_6}, //D173-A12-9-ok
    {0, C1_7,   C2_7,   C3_7}, //D183-A14-10-ok
    {0, C1_8,   C2_8,   C3_8}, //D190-A16-11-ok

    {0, C9_1,   C8_1,   C7_1}, //D108-A1-12
    {0, C9_2,   C8_2,   C7_2}, //D121-A3-13
    {0, C9_3,   C8_3,   C7_3}, //D132-A5-14
    {0, C9_4,   C8_4,   C7_4}, //D144-A7-15

    {0, C1_11,  C2_11,  C3_11}, //D90-B6-16-ok
    {0, C1_12,  C2_12,  C3_12}, //D82-B8-17-ok
    {0, C1_9,   C3_10,  C4_10}, //D89-B2-18-ok
    {0, C1_10,  C2_10,  C4_11}, //D94-B3-19-ok

    {1, C9_4,   C9_5,   C9_6}, //D102-A0-20
    {1, C9_7,   C9_8,   C1_10},  //D80-B0-21
    {1, C1_16,   C2_9,   C2_10},  //D84-B1-22
    {1, C2_16,  C3_9,  C3_16}, //D81-B4-23
    {1, C4_9,  C4_11,  C4_15}, //D85-B5-24
    {1, C4_16,  C5_9,  C5_11}, //D95-B7-25
    {1, C5_12,  C5_15,  C5_16}, //D86-B9-36

    {1, C6_9,  C6_11,  C6_12}, //D91-B10-27
    {1, C6_15,  C6_16,  C7_9}, //D96-B11-28
    {1, C7_11,  C7_12,  C7_15}, //D79-B12-29
    {1, C7_16,  C8_9,  C8_10}, //D83-B13-30
    {1, C8_11,  C8_12,  C8_13}, //D87-B14-31


    {1, C8_14,   C8_15,   C8_16}, //D102-C0-32
    {1, C9_9,   C9_10,   C9_11}, //D108-C1-33
    {1, C9_12,   C9_13,   C9_14}, //D115-C2-34
    {1, C9_15,   C9_16,   C8_6}, //D121-C3-35
    {1, C8_7,   C8_8,   C9_1}, //D126-C4-36
    {1, C9_2,   C9_3,   C9_4}, //D132-C5-37
    {1, C9_5,   C9_6,   C9_7}, //D138-C6-38
    {1, C9_8,   C1_9,   C1_10}, //D144-C7-39
    {1, C1_11,   C1_12,   C1_16}, //D149-C8-40
    {1, C2_9,   C2_10,   C2_11}, //D155-C9-41
    {1, C2_12,   C2_16,   C3_9}, //D160-C10-42
    {1, C3_10,   C3_16,   C4_9}, //D166-C11-43
    {1, C4_11,   C4_15,   C4_16}, //D173-C12-44
    {1, C5_9,   C5_10,   C5_11}, //D178-C13-45

    {1, C5_12,   C5_15,   C5_16},  //D80-D0-46
    {1, C6_9,   C6_10,  C6_11}, //D89-D2-47
    {1, C6_12,  C6_15,  C6_16}, //D94-D3-48
    {1, C7_9,  C7_11,  C7_12}, //D85-D5-49
    {1, C7_15,  C7_16,  C8_9}, //D90-D6-50
    {1, C8_10,  C8_11,  C8_12}, //D82-D8-51
    {1, C8_13,  C8_14,  C8_15}, //D91-D10-52
    {1, C8_16,  C9_9,  C9_10}, //D96-D11-53
    {1, C9_11,  C9_12,  C9_13}, //D87-D14-54
    {1, C9_14,  C9_15,  C9_16}, //D87-D14-55
    {1, C1_16,  C2_16,  C3_16}, //D87-D14-56
    {1, C4_16,  C5_16,  C6_16}, //D87-D14-57
    {1, C1_8,   C2_8,   C3_8},  //D84-D1-58
    {1, C4_8,   C5_8,   C6_8},  //D84-D1-59
    {1, C1_7,   C2_7,   C3_7},  //D84-D1-60
    {1, C1_10,  C2_10,  C4_11}, //D81-D4-61
    {1, C5_9,   C6_9,   C7_9},  //D95-D7-62
    {1, C5_12,  C6_12,  C7_12}, //D95-D7-63
    {1, C4_12,  C6_13,  C7_13}, //D86-D9-64
    {1, C1_14,  C2_14,  C3_14}, //D79-D12-65
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13,           14},
        {15,         16,          17,          18,          19,          20,          21,          22,          23,          24,           25,           26,           27,           28,           29},
        {30,         31,          32,          33,          34,          35,          36,          37,          38,          39,           40,           41,       NO_LED,           42,           43},
        {44,     NO_LED,          45,          46,          47,          48,          49,          50,          51,          52,           53,           54,           55,           56,           57},
        {58,         59,          60,      NO_LED,      NO_LED,      NO_LED,          61,      NO_LED,      NO_LED,      NO_LED,       NO_LED,           62,           63,           64,           65},
    }, {
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},                    {208,  0},     {224,  0},
        {0, 0},              {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0, 0},  {16, 0},    {32, 0},                                           {96,  0},                                                             {176,  0},     {192,  0},     {208,  0},     {224,  0},
    }, {
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,                            1,             1,
       1,                    1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,                                                  1,                                                                     1,             1,             1,             1,
    }
};

int indi_index;
int data_index;

keyboard_indicators indicators;
uint8_t* pIndicators = (uint8_t*)&indicators;

int indicator_number =
    sizeof(keyboard_indicators) / sizeof(indicator_config);

_Static_assert(sizeof(keyboard_indicators) == EECONFIG_KB_DATA_SIZE,
               "Mismatch in keyboard indicators stored data");

custom_rgblight_config_t g_custom_rgblight_config;

/* ============================================================
 * INDICATOR CORE
 * ============================================================ */

indicator_config* get_indicator_p(int index) {
    return (indicator_config*)(pIndicators + sizeof(indicator_config) * index);
}

static bool indicator_active(indicator_config ind) {
    switch (ind.func) {
        case 0: return host_keyboard_led_state().num_lock;
        case 1: return host_keyboard_led_state().scroll_lock;
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            return IS_LAYER_ON(ind.func - 2);
        default:
            return false;
    }
}

static HSV indicator_hsv(indicator_config ind) {
    return (HSV){ ind.h, ind.s, ind.v };
}

/* ============================================================
 * RGB MATRIX INDICATOR CALLBACK
 * ============================================================ */

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    for (int i = 0; i < indicator_number; i++) {
        indicator_config* ind = get_indicator_p(i);

        if (!ind->enabled) {
            continue;
        }

        if (i == 0) { // ind0
            RGB rgb = hsv_to_rgb((HSV){ ind->h, ind->s, ind->v });
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(ind->index, rgb.r, rgb.g, rgb.b);
            }
            continue;
        }
        /* ===== IND5: MANUAL, NO FUNC ===== */
        if (i == 4) { // ind5
            RGB rgb = hsv_to_rgb((HSV){ ind->h, ind->s, ind->v });
            rgb_matrix_set_color(ind->index, rgb.r, rgb.g, rgb.b);
            continue;
        }

        /* ===== IND1–IND4: NORMAL APOLLO ===== */
        if (indicator_active(*ind)) {
            RGB rgb = hsv_to_rgb(indicator_hsv(*ind));
            rgb_matrix_set_color(ind->index, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(ind->index, 0, 0, 0);
        }
    }
    return true;
}

/* ============================================================
 * EEPROM INIT (KB)
 * ============================================================ */

void eeconfig_init_kb(void) {
    indicators.ind1 = (indicator_config){ .h=0, .s=0, .v=255, .func=0xFF, .index=CAPS_LED_INDEX, .enabled=true  };
    indicators.ind2 = (indicator_config){ .h=0, .s=0, .v=255, .func=3, .index=1, .enabled=false };
    indicators.ind3 = (indicator_config){ .h=0, .s=0, .v=255, .func=4, .index=2,  .enabled=false };
    indicators.ind4 = (indicator_config){ .h=0, .s=0, .v=255, .func=5, .index=3,  .enabled=false };
    indicators.ind5 = (indicator_config){ .h=0, .s=0, .v=255, .func=0xFF, .index=BLOCKER_LED_INDEX, .enabled=true  };

    eeconfig_update_kb_datablock(&indicators);
}

/* ============================================================
 * RGB MATRIX STARTUP
 * ============================================================ */

static void rgb_matrix_startup(void) {
    rgb_matrix_disable_noeeprom();
    wait_ms(20);
    rgb_matrix_reload_from_eeprom();
    rgb_matrix_enable_noeeprom();
}

/* ============================================================
 * RGBLIGHT VIA HANDLER
 * ============================================================ */

void rgblight_config_set_value(uint8_t *data) {
    switch (data[0]) {
        case id_rgblight_logo_toggle:
            g_custom_rgblight_config.logo_enabled = data[1];
            break;
        case id_rgblight_ug_toggle:
            g_custom_rgblight_config.ug_enabled = data[1];
            break;
    }
    rgblight_config_save();
    update_rgblight();
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

void update_rgblight(void) {
    if (g_custom_rgblight_config.logo_enabled || g_custom_rgblight_config.ug_enabled) {
        rgblight_enable_noeeprom();

        if (g_custom_rgblight_config.logo_enabled && g_custom_rgblight_config.ug_enabled) {
            rgblight_set_effect_range(0, RGBLIGHT_LED_COUNT);
        } else {
            if (g_custom_rgblight_config.logo_enabled) {
                rgblight_set_effect_range(UG_LED_COUNT, BLOCKER_LED_COUNT);
            } else {
                rgblight_sethsv_range(0,0,0,UG_LED_COUNT,RGBLIGHT_LED_COUNT);
            }

            if (g_custom_rgblight_config.ug_enabled) {
                rgblight_set_effect_range(0, UG_LED_COUNT);
            } else {
                rgblight_sethsv_range(0,0,0,0,UG_LED_COUNT);
            }
        }
        rgblight_mode_noeeprom(rgblight_get_mode());
    } else {
        rgblight_enable_noeeprom();
    }
}

/* ============================================================
 * VIA CUSTOM VALUE HANDLER (SINGLE – APOLLO STYLE)
 * ============================================================ */

void indicator_config_set_value(uint8_t *data) {
    uint8_t id = data[0];
    uint8_t *v = &data[1];

    indi_index = (id - 3) / INDICATOR_PROPERTY_NUMBER;
    data_index = (id - 3) % INDICATOR_PROPERTY_NUMBER;

    indicator_config* ind = get_indicator_p(indi_index);
    
    if (indi_index == 0 && data_index == 4) {
        return;
    }

    if (indi_index == 0 && data_index == 0) {ind->enabled = true;
        return;
    }
    
    if (indi_index == 4) { // ind5
    switch (data_index) {
        case 0: ind->enabled = v[0]; break;
        case 1: ind->v       = v[0]; break;
        case 2: ind->h = v[0]; ind->s = v[1]; break;
        default: return; // ❌ ignore func / index
        }
    } else {
    switch (data_index) {
        case 0: ind->enabled = v[0]; break;
        case 1: ind->v       = v[0]; break;
        case 2: ind->h = v[0]; ind->s = v[1]; break;
        case 3: ind->func    = v[0]; break;
        case 4: ind->index   = v[0]; break;
    }
    }
    rgb_matrix_indicators_kb();
}

void indicator_config_get_value(uint8_t *data) {
    uint8_t id = data[0];
    uint8_t *v = &data[1];

    indi_index = (id - 3) / INDICATOR_PROPERTY_NUMBER;
    data_index = (id - 3) % INDICATOR_PROPERTY_NUMBER;

    indicator_config* ind = get_indicator_p(indi_index);
    if (indi_index == 4) { // ind5
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

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *cmd = &data[0];
    uint8_t *ch  = &data[1];
    uint8_t *vd  = &data[2];

    if (*ch != id_custom_channel) {
        *cmd = id_unhandled;
        return;
    }

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
    wait_ms(10); 
    update_rgblight();

    rgb_matrix_startup();
    eeconfig_read_kb_datablock(&indicators);
    rgb_matrix_indicators_kb();
}