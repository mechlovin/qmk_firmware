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

#include "infinity87.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
// left CA
    {0,  CS34_SW1,  CS35_SW1,  CS36_SW1}, /* RGB1 - D92 - K00*/
    {0,  CS37_SW1,  CS38_SW1,  CS39_SW1}, /* RGB2 - D94 - K01*/
    {0,  CS31_SW1,  CS32_SW1,  CS33_SW1}, /* RGB3 - D96 - K02*/
    {0,  CS28_SW1,  CS29_SW1,  CS30_SW1}, /* RGB4 - D98 - K03*/
    {0,  CS25_SW1,  CS26_SW1,  CS27_SW1}, /* RGB5 - D100 - K04*/
    {0,  CS22_SW1,  CS23_SW1,  CS24_SW1}, /* RGB6 - D102 - K05*/
    {0,  CS19_SW1,  CS20_SW1,  CS21_SW1}, /* RGB7 - D104 - K06*/
    {0,  CS18_SW1,  CS17_SW1,  CS16_SW1}, /* RGB8 - D106 - K07*/
    {0,  CS15_SW1,  CS14_SW1,  CS13_SW1}, /* RGB9 - D108 - K08*/
    {0,  CS12_SW1,  CS11_SW1,  CS10_SW1}, /* RGB10 - D110 - K09*/
    {0,  CS9_SW1,   CS8_SW1,   CS7_SW1}, /* RGB11 - D112 - K0A*/
    {0,  CS6_SW1,  CS5_SW1,  CS4_SW1}, /* RGB12 - D114 - K0B*/
    {0,  CS3_SW1,  CS2_SW1,  CS1_SW1}, /* RGB13 - D116 - K0C*/
    {0,  CS15_SW7, CS14_SW7, CS13_SW7}, /* D46-30-8 */
    {0, C4_4,   C6_5,   C7_5}, //D61-31-9
    {0, C1_5,   C2_5,   C3_5}, //D73-32-10
    {0, C4_5,   C5_5,   C7_6}, //D78-33-11
    {0, C1_6,   C2_6,   C3_6}, //D126-44-12
    {0, C4_6,   C5_6,   C6_6}, //D51-45-13
    {0, C1_7,   C2_7,   C3_7}, //D63-46-14
    {0, C4_7,   C5_7,   C6_7}, //D74-47-15
    {0, C1_8,   C2_8,   C3_8}, //D56-60-16
    {0, C4_8,   C5_8,   C6_8}, //D67-61-17

// left CB
    {0, C2_9,   C3_9,   C4_9},  //D80-4-18
    {0, C5_9,   C6_9,   C7_9},  //D84-5-19
    {0, C1_9,   C3_10,  C4_10}, //D89-6-20
    {0, C5_10,  C6_10,  C7_10}, //D94-7-21
    {0, C1_10,  C2_10,  C4_11}, //D81-19-22
    {0, C5_11,  C6_11,  C7_11}, //D85-20-23
    {0, C1_11,  C2_11,  C3_11}, //D90-21-24
    {0, C5_12,  C6_12,  C7_12}, //D95-22-25
    {0, C1_12,  C2_12,  C3_12}, //D82-34-26
    {0, C4_12,  C6_13,  C7_13}, //D86-35-27
    {0, C1_13,  C2_13,  C3_13}, //D91-36-28
    {0, C4_13,  C5_13,  C7_14}, //D96-37-29
    {0, C1_14,  C2_14,  C3_14}, //D79-48-30
    {0, C4_14,  C5_14,  C6_14}, //D83-49-31
    {0, C1_15,  C2_15,  C3_15}, //D87-50-32
    {0, C4_15,  C5_15,  C6_15}, //D92-51-33
    {0, C1_16,  C2_16,  C3_16}, //D75-62-34
    {0, C4_16,  C5_16,  C6_16}, //D93-63-35

// right CA
    {1, C2_1,   C3_1,   C4_1},  //D98-8-36
    {1, C5_1,   C6_1,   C7_1},  //D102-9-37
    {1, C1_1,   C3_2,   C4_2},  //D106-10-38
    {1, C5_2,   C6_2,   C7_2},  //D111-11-39
    {1, C2_9,   C3_9,   C4_9},  //D116-12-40
    {1, C5_9,   C6_9,   C7_9},  //D130-13-41
    {1, C1_13,  C2_13,  C3_13}, //D121-14-42
    {1, C1_2,   C2_2,   C4_3},  //D99-23-43
    {1, C5_3,   C6_3,   C7_3},  //D103-24-44
    {1, C1_3,   C2_3,   C3_3},  //D107-25-45
    {1, C5_4,   C6_4,   C7_4},  //D112-26-46
    {1, C1_9,   C3_10,  C4_10}, //D117-27-47
    {1, C5_10,  C6_10,  C7_10}, //D129-28-48
    {1, C4_13,  C5_13,  C7_14}, //D122-29-49
    {1, C1_4,   C2_4,   C3_4},  //D100-38-50
    {1, C4_4,   C6_5,   C7_5},  //D104-39-51
    {1, C1_5,   C2_5,   C3_5},  //D108-40-52
    {1, C4_5,   C5_5,   C7_6},  //D113-41-53
// right CB
    {1, C1_10,  C2_10,  C4_11}, //D118-42-54
    {1, C5_11,  C6_11,  C7_11}, //D123-43-55
    {1, C1_6,   C2_6,   C3_6},  //D97-52-56
    {1, C4_6,   C5_6,   C6_6},  //D101-53-57
    {1, C1_7,   C2_7,   C3_7},  //D105-54-58
    {1, C4_7,   C5_7,   C6_7},  //D109-55-59
    {1, C1_11,  C2_11,  C3_11}, //D114-56-60
    {1, C5_12,  C6_12,  C7_12}, //D128-57-61
    {1, C1_14,  C2_14,  C3_14}, //D119-58-62
    {1, C4_14,  C5_14,  C6_14}, //D124-59-63
    {1, C1_8,   C2_8,   C3_8}, //D127-64-64
    {1, C4_8,   C5_8,   C6_8}, //D110-65-65
    {1, C1_12,  C2_12,  C3_12}, //D115-66-66
    {1, C4_12,  C6_13,  C7_13}, //D120-67-67
    {1, C1_15,  C2_15,  C3_15}, //D125-68-68
    {1, C4_15,  C5_15,  C6_15}, //D140-69-69
    {0, C8_7,   C7_7,   C7_8}, //INDICATOR LED-70
    {0, C8_8,   C8_1,   C8_2}, //INDICATOR LED-71
    {0, C9_7,   C8_6,   C9_6}, //INDICATOR LED-72
    {0, C9_8,   C8_4,   C8_5},//INDICATOR LED-73
    {0, C8_15,  C9_1,   C9_2},//INDICATOR LED-74
    {0, C8_16,  C8_3,   C9_3},//INDICATOR LED-75
    {0, C9_15,  C9_9,   C9_10},//INDICATOR LED-76
    {0, C9_16,  C9_11,  C7_12},//INDICATOR LED-77
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {0,          1,          2,          3,          18,          19,        20,         21,         36,         37,          38,        39,          40,           41},
  {4,           5,         6,           7,         22,          23,        24,         25,         43,         44,          45,        46,          47,           69},
  {8,           9,         10,         11,         26,          27,        28,         29,         50,         51,          52,        53,          54,           55},
  {13,         14,         15,         30,         31,          32,        33,         56,         57,         58,          59,        60,          62,           63},
  {16,         17,         34,         NO_LED,     NO_LED,      NO_LED,    35,         NO_LED,     NO_LED,     NO_LED,      65,        66,          67,           68},
    },
    {
  //LED Index to Physical Positon
  {  0,  0},  { 16,  0},  { 32, 0 },  { 48,  0}, //9-59-68-76
  {  0, 16},  { 16, 16},  { 32, 16},  { 48, 16}, //10-60-72-77
  {  0, 32},  { 16, 32},  { 32, 32},  { 48, 32}, //46-61-73-78
  {  0, 48},  {  0, 48},  { 12, 48},  { 16, 48}, //126-51-63-74  
  {  0, 64},  { 16, 64}, //56-67  
  { 64,  0},  { 80,  0},   { 96, 0},  { 112, 0}, //80-84-89-94
  { 64, 16},  { 80, 16},   { 96,16},  { 112,16}, //81-85-90-95
  { 64, 32},  { 80, 32},   { 96,32},  { 112,32}, //82-86-91-96
  { 32, 48},  { 48, 48},   { 64,48},  {  80,48}, //79-83-87-92
  { 32, 64},  { 80, 64}, //75-93
  { 128, 0},  { 144, 0},  { 160, 0},  { 176, 0},    {192,  0},   {220,  0},   {210, 0}, //98-102-106-111-116-121-130
  { 128,16},   {144,16},   {160,16},  {176, 16},    {192, 16},   {220, 16},   {220,16}, //99-103-107-112-117-129-122
  { 128,32},  { 144,32},  { 160,32},  { 176,32},    {192, 32},   {220, 32}, //100-104-108-113-118-123
  {  96,48},   {112,48},  {128, 48},  {144, 48},    {160, 48},   {200, 48},   {220,48},   {220,48}, //97-101-105-109-114-119-128-124 
  {  96,64},   {144,64},   {160,64},   {176,64},    {220, 64}, //127-110-115-120-125
  { 220, 0},   //140                  
}, {
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1, 
} };

__attribute__((weak)) void rgb_matrix_indicators_user(void) {
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

__attribute__((weak))
layer_state_t layer_state_set_user(layer_state_t state) {
  // if on layer 1, turn on L1 LED, otherwise off.
    if (get_highest_layer(state) == 0) {
        rgb_matrix_set_color(73, 255, 0, 0);
    } else {
        rgb_matrix_set_color(73, 0, 0, 0);
    }
  // if on layer 2, turn on L2 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        rgb_matrix_set_color(74, 255, 0, 0);
    } else {
        rgb_matrix_set_color(74, 0, 0, 0);
    }

  // if on layer 3, turn on L3 LED, otherwise off.
    if (get_highest_layer(state) == 2) {
        rgb_matrix_set_color(75, 255, 0, 0);
    } else {
        rgb_matrix_set_color(75, 0, 0, 0);
    }

  // if on layer 4, turn on L4 LED, otherwise off.
    if (get_highest_layer(state) == 3) {
        rgb_matrix_set_color(76, 255, 0, 0);
    } else {
        rgb_matrix_set_color(76, 0, 0, 0);
    }

  // if on layer 5, turn on L5 LED, otherwise off.
    if (get_highest_layer(state) == 4) {
        rgb_matrix_set_color(77, 255, 0, 0);
    } else {
        rgb_matrix_set_color(77, 0, 0, 0);
    }

    return state;
}

#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch(keycode) {
    #ifdef RGB_MATRIX_DISABLE_KEYCODES
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
        default:
        break;
    }
  }
  return true;
}


#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    {0,  CS34_SW1,  CS35_SW1,  CS36_SW1}, /* RGB1 */
    {0,  CS37_SW1,  CS38_SW1,  CS39_SW1}, /* RGB2 */
    {0,  CS31_SW1,  CS32_SW1,  CS33_SW1}, /* RGB3 */
    {0,  CS28_SW1,  CS29_SW1,  CS30_SW1}, /* RGB4 */
    {0,  CS25_SW1,  CS26_SW1,  CS27_SW1}, /* RGB5 */
    {0,  CS22_SW1,  CS23_SW1,  CS24_SW1}, /* RGB6 */
    {0,  CS19_SW1,  CS20_SW1,  CS21_SW1}, /* RGB7 */
    {0,  CS18_SW1,  CS17_SW1,  CS16_SW1}, /* RGB8 */
    {0,  CS15_SW1,  CS14_SW1,  CS13_SW1}, /* RGB9 */
    {0,  CS12_SW1,  CS11_SW1,  CS10_SW1}, /* RGB10 */
    {0,  CS9_SW1,   CS8_SW1,   CS7_SW1}, /* RGB11 */
    {0,  CS6_SW1,  CS5_SW1,  CS4_SW1}, /* RGB12 */
    {0,  CS3_SW1,  CS2_SW1,  CS1_SW1}, /* RGB13 */
    {0,  CS9_SW5,  CS8_SW5,  CS7_SW5}, /* RGB14 */
    {0,  CS9_SW6,  CS8_SW6,  CS7_SW6}, /* RGB15 */
    {0,  CS9_SW7,  CS8_SW7,  CS7_SW7}, /* RGB16 */
    {0,  CS9_SW8,  CS8_SW8,  CS7_SW8}, /* RGB17 */
    {0,  CS9_SW9,  CS8_SW9,  CS7_SW9}, /* RGB18 */
    {0, CS12_SW1, CS11_SW1, CS10_SW1}, /* RGB19 */
    {0, CS12_SW2, CS11_SW2, CS10_SW2}, /* RGB20 */
    {0, CS12_SW3, CS11_SW3, CS10_SW3}, /* RGB21 */
    {0, CS12_SW4, CS11_SW4, CS10_SW4}, /* RGB22 */
    {0, CS12_SW5, CS11_SW5, CS10_SW5}, /* RGB23 */
    {0, CS12_SW6, CS11_SW6, CS10_SW6}, /* RGB24 */
    {0, CS12_SW7, CS11_SW7, CS10_SW7}, /* RGB25 */
    {0, CS12_SW8, CS11_SW8, CS10_SW8}, /* RGB26 */
    {0, CS12_SW9, CS11_SW9, CS10_SW9}, /* RGB27 */
    {0, CS15_SW1, CS14_SW1, CS13_SW1}, /* RGB28 */
    {0, CS15_SW2, CS14_SW2, CS13_SW2}, /* RGB29 */
    {0, CS15_SW3, CS14_SW3, CS13_SW3}, /* RGB30 */
    {0, CS15_SW4, CS14_SW4, CS13_SW4}, /* RGB31 */
    {0, CS15_SW5, CS14_SW5, CS13_SW5}, /* RGB32 */
    {0, CS15_SW6, CS14_SW6, CS13_SW6}, /* RGB33 */
    {0, CS15_SW7, CS14_SW7, CS13_SW7}, /* RGB34 */
    {0, CS15_SW8, CS14_SW8, CS13_SW8}, /* RGB35 */
    {0, CS15_SW9, CS14_SW9, CS13_SW9}, /* RGB36 */
    {0, CS18_SW1, CS17_SW1, CS16_SW1}, /* RGB37 */
    {0, CS18_SW2, CS17_SW2, CS16_SW2}, /* RGB38 */
    {0, CS18_SW3, CS17_SW3, CS16_SW3}, /* RGB39 */
    {0, CS18_SW4, CS17_SW4, CS16_SW4}, /* RGB40 */
    {0, CS18_SW5, CS17_SW5, CS16_SW5}, /* RGB41 */
    {0, CS18_SW6, CS17_SW6, CS16_SW6}, /* RGB42 */
    {0, CS18_SW7, CS17_SW7, CS16_SW7}, /* RGB43 */
    {0, CS18_SW8, CS17_SW8, CS16_SW8}, /* RGB44 */
    {0, CS18_SW9, CS17_SW9, CS16_SW9}, /* RGB45 */
    {0, CS21_SW1, CS20_SW1, CS19_SW1}, /* RGB46 */
	{0, CS21_SW2, CS20_SW2, CS19_SW2}, /* RGB47 */
    {0, CS21_SW3, CS20_SW3, CS19_SW3}, /* RGB48 */
	{0, CS21_SW4, CS20_SW4, CS19_SW4}, /* RGB49 */
	{0, CS21_SW5, CS20_SW5, CS19_SW5}, /* RGB50 */
    {0, CS21_SW6, CS20_SW6, CS19_SW6}, /* RGB51 */
    {0, CS21_SW7, CS20_SW7, CS19_SW7}, /* RGB52 */
    {0, CS21_SW8, CS20_SW8, CS19_SW8}, /* RGB53 */
    {0, CS21_SW9, CS20_SW9, CS19_SW9}, /* RGB54 */
    {0, CS24_SW1, CS23_SW1, CS22_SW1}, /* RGB55 */
    {0, CS24_SW2, CS23_SW2, CS22_SW2}, /* RGB56 */
	{0, CS24_SW3, CS23_SW3, CS22_SW3}, /* RGB57 */
    {0, CS24_SW4, CS23_SW4, CS22_SW4}, /* RGB58 */
    {0, CS24_SW5, CS23_SW5, CS22_SW5}, /* RGB59 */
    {0, CS24_SW6, CS23_SW6, CS22_SW6}, /* RGB60 */
    {0, CS24_SW7, CS23_SW7, CS22_SW7}, /* RGB61 */
    {0, CS24_SW8, CS23_SW8, CS22_SW8}, /* RGB62 */
    {0, CS24_SW9, CS23_SW9, CS22_SW9}, /* RGB63 */
    {0, CS27_SW1, CS26_SW1, CS25_SW1}, /* RGB64 */
    {0, CS27_SW2, CS26_SW2, CS25_SW2}, /* RGB65 */
	{0, CS27_SW3, CS26_SW3, CS25_SW3}, /* RGB66 */
    {0, CS27_SW4, CS26_SW4, CS25_SW4}, /* RGB67 */
    {0, CS27_SW5, CS26_SW5, CS25_SW5}, /* RGB68 */
    {0, CS27_SW6, CS26_SW6, CS25_SW6}, /* RGB69 */
    {0, CS27_SW7, CS26_SW7, CS25_SW7}, /* RGB70 */
    {0, CS27_SW8, CS26_SW8, CS25_SW8}, /* RGB71 */
    {0, CS27_SW9, CS26_SW9, CS25_SW9}, /* RGB72 */
    {0, CS30_SW2, CS29_SW2, CS28_SW2}, /* RGB73 */
    {0, CS30_SW3, CS29_SW3, CS28_SW3}, /* RGB74 */
    {0, CS30_SW4, CS29_SW4, CS28_SW4}, /* RGB75 */
    {0, CS30_SW5, CS29_SW5, CS28_SW5}, /* RGB76 */
    {0, CS30_SW6, CS29_SW6, CS28_SW6}, /* RGB77 */
    {0, CS30_SW7, CS29_SW7, CS28_SW7}, /* RGB78 */
    {0, CS30_SW8, CS29_SW8, CS28_SW8}, /* RGB79 */
    {0, CS30_SW9, CS29_SW9, CS28_SW9}, /* RGB80 */
    {0, CS36_SW1, CS35_SW1, CS34_SW1}, /* RGB81 */
    {0, CS36_SW2, CS35_SW2, CS34_SW2}, /* RGB82 */
    {0, CS36_SW4, CS35_SW4, CS34_SW4}, /* RGB83 */
    {0, CS36_SW3, CS35_SW3, CS34_SW3}, /* RGB84 */
    {0, CS36_SW6, CS35_SW6, CS34_SW6}, /* RGB85 */
    {0, CS30_SW1, CS29_SW1, CS28_SW1}, /* RGB86 */
    {0, CS39_SW2, CS38_SW2, CS37_SW2}, /* RGB87 */
    {0, CS39_SW3, CS38_SW3, CS37_SW3}, /* RGB89 */
    {0, CS39_SW4, CS38_SW4, CS37_SW4}, /* RGB88 */
    {0, CS39_SW6, CS38_SW6, CS37_SW6}, /* RGB90 */
    {0, CS39_SW1, CS38_SW1, CS37_SW1}, /* RGB91 */
};

led_config_t g_led_config = {
	{
		/* C0     C1         C2        C3        C4        C5        C6        C7        C8          C9        C10         C11        C12        C13        C14        C15        C16  */
		{  0,      1,         2,        3,        4,        5,        6,        7,        8,         9,         10,         11,       12,        13,        14,        15,        16 }, /* R0 */
		{ 17,     18,        19,       20,       21,       22,       23,       24,       25,         26,        27,         28,       29,        30,        31,        32,        33 }, /* R1 */
		{ 34,     35,        36,       37,       38,       39,       40,       41,       42,         43,        44,         45,       46,        47,        48,/*?*/   49,/*?*/   50 }, /* R2 */
		{ 51,     52,        53,       54,       55,       56,       57,       58,       59,         60,        61,         62,       63,        64,    NO_LED,    NO_LED,    NO_LED }, /* R3 */
		{ 65,     66,        67,       68,       69,       70,       71,       72,       73,         74,        75,         76,       77,        78,    NO_LED,        79,    NO_LED }, /* R4 */
		{ 80,     81,        82,   NO_LED,   NO_LED,       NO_LED,   83,   NO_LED,       NO_LED,   NO_LED,      84,         85,       86,        87,        88,        89,        90 }, /* R5 */ 
    }, {
        {0,  0},   {16, 0},   {32, 0},  {48, 0},  {64, 0},  {80, 0},  {96, 0},  {112, 0},  {128, 0},  {144, 0},  {160, 0},  {176, 0},  {192, 0},  {208, 0},   {224, 0},  {240, 0},
		{0, 16},  {16, 16},  {32, 16}, {48, 16}, {64, 16}, {80, 16}, {96, 16}, {112, 16}, {128, 16}, {144, 16}, {160, 16}, {176, 16}, {192, 16}, {208, 16},  {224, 16}, {240, 16},
		{0, 32},  {16, 32},  {32, 32}, {48, 32}, {64, 32}, {80, 32}, {96, 32}, {112, 32}, {128, 32}, {144, 32}, {160, 32}, {176, 32}, {192, 32}, {208, 32},  {224, 32}, {240, 32},
		{0, 48},  {16, 48},  {32, 48}, {48, 48}, {64, 48}, {80, 48}, {96, 48}, {112, 48}, {128, 48}, {144, 48}, {160, 48}, {176, 48}, {192, 48}, {208, 48},  {224, 48}, {240, 48},
		{0, 64},  {16, 64},  {32, 64}, {48, 64}, {64, 64}, {80, 64}, {96, 64}, {112, 64}, {128, 64}, {144, 64}, {160, 64}, {176, 64}, {192, 64}, {208, 64},  {224, 64}, {240, 64},
		{0, 80},  {16, 80},  {32, 80}, {48, 80}, {64, 80},                     {80, 80},                        {96, 80},  {112, 80}, {128, 80}, {144, 80}, {160, 80}, 
	}, {
	       4,       4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,          4,         4,
	       4,       4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,          4,         4,
	       4,       4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,          4,         4,
	       4,       4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,          4,         4,
		   4,       4,         4,        4,        4,        4,        4,        4,         4,         4,         4,          4,        4,        4,          4,         4,
		   4,       4,         4,        4,        4,                            4,                               4,          4,        4,        4,          4, 
	}
};


void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

void keyboard_pre_init_kb(void) {
    setPinOutput(A2);
    writePinHigh(A2);
    keyboard_pre_init_user();
}

#endif
