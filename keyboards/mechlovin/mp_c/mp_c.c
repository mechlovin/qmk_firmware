/* Copyright 2020 Team Mechlovin'
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
 
 //#ifndef RGB_BACKLIGHT_MPC
 //#error RGB_BACKLIGHT_MPC not defined, recheck config.h
 //#endif

#include "mp_c.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {

    {0, C2_1,   C3_1,   C4_1}, //D102-A0-0
    {0, C5_1,   C6_1,   C7_1}, //D108-A1-1
    {0, C1_1,   C3_2,   C4_2}, //D115-A2-2
    {0, C5_2,   C6_2,   C7_2}, //D121-A3-3
    {0, C1_2,   C2_2,   C4_3}, //D126-A4-4
    {0, C5_3,   C6_3,   C7_3}, //D132-A5-5
    {0, C1_3,   C2_3,   C3_3}, //D138-A6-6
    {0, C5_4,   C6_4,   C7_4}, //D144-A7-7
    {0, C1_4,   C2_4,   C3_4}, //D149-A8-8
    {0, C4_4,   C6_5,   C7_5}, //D155-A9-9
    {0, C1_5,   C2_5,   C3_5}, //D160-A10-10
    {0, C4_5,   C5_5,   C7_6}, //D166-A11-11
    {0, C1_6,   C2_6,   C3_6}, //D173-A12-12
    {0, C4_6,   C5_6,   C6_6}, //D178-A13-13
    {0, C1_7,   C2_7,   C3_7}, //D183-A14-14
    {0, C4_7,   C5_7,   C6_7}, //D187-A15-15
    {0, C1_8,   C2_8,   C3_8}, //D190-A16-16


    {0, C2_9,   C3_9,   C4_9},  //D80-B0-17
    {0, C5_9,   C6_9,   C7_9},  //D84-B1-18
    {0, C1_9,   C3_10,  C4_10}, //D89-B2-19
    {0, C5_10,  C6_10,  C7_10}, //D94-B3-20
    {0, C1_10,  C2_10,  C4_11}, //D81-B4-21
    {0, C5_11,  C6_11,  C7_11}, //D85-B5-22
    {0, C1_11,  C2_11,  C3_11}, //D90-B6-23
    {0, C5_12,  C6_12,  C7_12}, //D95-B7-24
    {0, C1_12,  C2_12,  C3_12}, //D82-B8-25
    {0, C4_12,  C6_13,  C7_13}, //D86-B9-26
    {0, C1_13,  C2_13,  C3_13}, //D91-B10-27
    {0, C4_13,  C5_13,  C7_14}, //D96-B11-28
    {0, C1_14,  C2_14,  C3_14}, //D79-B12-29
    {0, C4_14,  C5_14,  C6_14}, //D83-B13-30
    {0, C1_15,  C2_15,  C3_15}, //D87-B14-31
    {0, C4_15,  C5_15,  C6_15}, //D92-B15-32
    {0, C1_16,  C2_16,  C3_16}, //D75-B16-33
    {0, C4_16,  C5_16,  C6_16}, //D93-B17-34


    {1, C2_1,   C3_1,   C4_1}, //D102-C0-35
    {1, C5_1,   C6_1,   C7_1}, //D108-C1-36
    {1, C1_1,   C3_2,   C4_2}, //D115-C2-37
    {1, C5_2,   C6_2,   C7_2}, //D121-C3-38
    {1, C1_2,   C2_2,   C4_3}, //D126-C4-39
    {1, C5_3,   C6_3,   C7_3}, //D132-C5-40
    {1, C1_3,   C2_3,   C3_3}, //D138-C6-41
    {1, C5_4,   C6_4,   C7_4}, //D144-C7-42
    {1, C1_4,   C2_4,   C3_4}, //D149-C8-43
    {1, C4_4,   C6_5,   C7_5}, //D155-C9-44
    {1, C1_5,   C2_5,   C3_5}, //D160-C10-45
    {1, C4_5,   C5_5,   C7_6}, //D166-C11-46
    {1, C1_6,   C2_6,   C3_6}, //D173-C12-47
    {1, C4_6,   C5_6,   C6_6}, //D178-C13-48
    {1, C1_7,   C2_7,   C3_7}, //D183-C14-49
    {1, C4_7,   C5_7,   C6_7}, //D187-C15-50
    {1, C1_8,   C2_8,   C3_8}, //D190-C16-51
    

    {1, C2_9,   C3_9,   C4_9},  //D80-D0-52
    {1, C5_9,   C6_9,   C7_9},  //D84-D1-53
    {1, C1_9,   C3_10,  C4_10}, //D89-D2-54
    {1, C5_10,  C6_10,  C7_10}, //D94-D3-55
    {1, C1_10,  C2_10,  C4_11}, //D81-D4-56
    {1, C5_11,  C6_11,  C7_11}, //D85-D5-57
    {1, C1_11,  C2_11,  C3_11}, //D90-D6-58
    {1, C5_12,  C6_12,  C7_12}, //D95-D7-59
    {1, C1_12,  C2_12,  C3_12}, //D82-D8-60
    {1, C4_12,  C6_13,  C7_13}, //D86-D9-61
    {1, C1_13,  C2_13,  C3_13}, //D91-D10-62
    {1, C4_13,  C5_13,  C7_14}, //D96-D11-63
    {1, C1_14,  C2_14,  C3_14}, //D79-D12-64
    {1, C4_14,  C5_14,  C6_14}, //D83-D13-65
    {1, C1_15,  C2_15,  C3_15}, //D87-D14-66

    {2, C2_1,   C3_1,   C4_1}, //D102-E0-67
    {2, C5_1,   C6_1,   C7_1}, //D108-E1-68
    {2, C1_1,   C3_2,   C4_2}, //D115-E2-69
    {2, C5_2,   C6_2,   C7_2}, //D121-E3-70
    {2, C1_2,   C2_2,   C4_3}, //D126-E4-71
    {2, C5_3,   C6_3,   C7_3}, //D132-E5-72
    {2, C1_3,   C2_3,   C3_3}, //D138-E6-73
    {2, C5_4,   C6_4,   C7_4}, //D144-E7-74
    {2, C1_4,   C2_4,   C3_4}, //D149-E8-75
    {2, C4_4,   C6_5,   C7_5}, //D155-E9-76
    {2, C1_5,   C2_5,   C3_5}, //D160-E10-77
    {2, C4_5,   C5_5,   C7_6}, //D166-E11-78
    {2, C1_6,   C2_6,   C3_6}, //D173-E12-79
    {2, C4_6,   C5_6,   C6_6}, //D178-E13-80
    {2, C1_7,   C2_7,   C3_7}, //D183-E14-81
    {2, C4_7,   C5_7,   C6_7}, //D187-E15-82
    {2, C1_8,   C2_8,   C3_8}, //D190-E16-83
    

    {2, C2_9,   C3_9,   C4_9},  //D80-F0-84
    {2, C5_9,   C6_9,   C7_9},  //D84-F1-85
    {2, C1_9,   C3_10,  C4_10}, //D89-F2-86
    {2, C1_10,  C2_10,  C4_11}, //D81-F3-87
    {2, C5_11,  C6_11,  C7_11}, //D85-F4-88
    {2, C1_11,  C2_11,  C3_11}, //D90-F5-89
    {2, C5_12,  C6_12,  C7_12}, //D95-F6-90
    {2, C1_12,  C2_12,  C3_12}, //D82-F7-91
    {2, C4_12,  C6_13,  C7_13}, //D86-F8-92
    {2, C1_13,  C2_13,  C3_13}, //D91-F9-93
    {2, C4_13,  C5_13,  C7_14}, //D96-F10-94
    {2, C1_14,  C2_14,  C3_14} //D79-F11-95

};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13,           14,           15,           16},
  {17,         18,          19,          20,          21,          22,          23,          24,          25,          26,           27,           28,           29,           30,           32,           33,           34},
  {35,         36,          37,          38,          39,          40,          41,          42,          43,          44,           45,           46,           47,           48,           49,           50,           51},
  {52,         53,          54,          55,          56,          57,          58,          59,          60,          61,           62,           63,           64,           65,       NO_LED,       NO_LED,       NO_LED},
  {67,         69,          70,          71,          72,          73,          74,          75,          76,          77,           78,           79,           80,           82,       NO_LED,           83,       NO_LED},
  {84,         85,          86,      NO_LED,      NO_LED,      NO_LED,          87,      NO_LED,      NO_LED,      NO_LED,           89,           90,           91,           92,           93,           94,           95}
    },
    {
  //LED Index to Physical Positon
  {0, 0},  {14, 0},    {28, 0},    {42,  0},    {56,  0},    {70,  0},    {84,  0},    {98,  0},    {112,  0},    {126,  0},     {140,  0},     {154,  0},     {168,  0},     {182,  0},     {196,  0},     {210,  0},      {224,  0},        
  {0, 1},  {14, 1},    {28, 1},    {42,  1},    {56,  1},    {70,  1},    {84,  1},    {98,  1},    {112,  1},    {126,  1},     {140,  1},     {154,  1},     {168,  1},     {182,  1},     {196,  1},     {210,  1},      {224,  1},        
  {0, 2},  {14, 2},    {28, 2},    {42,  2},    {56,  2},    {70,  2},    {84,  2},    {98,  2},    {112,  2},    {126,  2},     {140,  2},     {154,  2},     {168,  2},     {182,  2},     {196,  2},     {210,  2},      {224,  2},        
  {0, 3},  {14, 3},    {28, 3},    {42,  3},    {56,  3},    {70,  3},    {84,  3},    {98,  3},    {112,  3},    {126,  3},     {140,  3},     {154,  3},     {168,  3},     {182,  3},
  {0, 4},  {14, 4},    {28, 4},    {42,  4},    {56,  4},    {70,  4},    {84,  4},    {98,  4},    {112,  4},    {126,  4},     {140,  4},     {154,  4},     {168,  4},     {182,  4},     {210,  4},
  {0, 5},  {14, 5},    {28, 5},                                           {84,  5},                                              {140,  5},     {154,  5},     {168,  5},     {182,  5},     {196,  5},     {210,  5},      {224,  5}
}, {
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,                                                  1,                                                      1,             1,             1,             1,             1,             1,             1
} };

void rgb_matrix_indicators_user(void) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(8, 255, 255, 255);
            rgb_matrix_set_color(70, 255, 0, 0);
        } else {
            rgb_matrix_set_color(70, 0, 0, 0);
        }
        if (host_keyboard_led_state().num_lock) {
            rgb_matrix_set_color(71, 255, 0, 0);
        } else {
            rgb_matrix_set_color(71, 0, 0, 0);
        }
        if (host_keyboard_led_state().scroll_lock) {
            rgb_matrix_set_color(72, 255, 0, 0);
        } else {
            rgb_matrix_set_color(72, 0, 0, 0);
        }
}

#ifndef RAW_ENABLE
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#else
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#endif
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGBLIGHT_ENABLE
        #ifdef RGB_MATRIX_ENABLE
        case KC_F13: // toggle rgb matrix
            rgb_matrix_toggle();
            return false;
        case KC_F14:
            rgb_matrix_step();
            return false;
        case KC_F15:
            rgb_matrix_increase_speed();
            return false;
        case KC_F16:
            rgb_matrix_decrease_speed();
            return false;
        case KC_F17:
            rgb_matrix_increase_hue();
            return false;
        case KC_F18:
            rgb_matrix_decrease_hue();
            return false;
        case KC_F19:
            rgb_matrix_increase_sat();
            return false;
        case KC_F20:
            rgb_matrix_decrease_sat();
            return false;
        case KC_F21:
            rgb_matrix_increase_val();
            return false;
        case KC_F22:
            rgb_matrix_decrease_val();
            return false;
        #endif
    #endif
        default:
        break;
    }
  }
  return true;
}
