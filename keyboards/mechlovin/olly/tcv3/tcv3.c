/* Copyright 2023 Mechlovin'
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

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_kb(void) {
  // Call the post init code.
  rgblight_sethsv_at(255, 255, 255, 0);	
    keyboard_post_init_user();
}
#endif

const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *    driver
 *    |  LED address
 *    |  | */
    { 0, C1_1  },  { 0, C2_1 },  { 0, C3_1  },                { 0, C4_1  },  { 0, C5_1 },  { 0, C6_1  },  { 0, C7_1 },  { 0, C8_1  },  { 0, C1_9  },  { 0, C2_9   },  { 0, C3_9  },  { 0, C4_9   },  { 0, C5_9  },  { 0, C6_9   },  { 0, C7_9  },  { 0, C8_9 },  { 0, C9_9  },
    { 0, C1_2  },  { 0, C2_2 },  { 0, C3_2  }, { 0, C4_2  },  { 0, C5_2  },  { 0, C6_2 },  { 0, C7_2  },  { 0, C8_2 },  { 0, C9_2  },  { 0, C1_10 },  { 0, C2_10  },  { 0, C3_10 },  { 0, C4_10  },  { 0, C5_10 },  { 0, C6_10  },  { 0, C7_10 },  { 0, C9_13 }, { 0, C8_10 },
    { 0, C1_3  },  { 0, C2_3 },  { 0, C3_3  }, { 0, C4_3  },  { 0, C5_3  },  { 0, C6_3 },  { 0, C7_3  },  { 0, C8_3 },  { 0, C9_3  },  { 0, C1_11 },  { 0, C2_11  },  { 0, C3_11 },  { 0, C4_11  },  { 0, C5_11 },  { 0, C6_11  },  { 0, C7_11 },  { 0, C8_11},  { 0, C9_11 },
    { 0, C1_4  },  { 0, C2_4 },  { 0, C3_4  }, { 0, C4_4  },  { 0, C5_4  },  { 0, C6_4 },  { 0, C7_4  },  { 0, C8_4 },  { 0, C9_4  },  { 0, C1_12 },  { 0, C2_12  },  { 0, C3_12 },  { 0, C4_12  },  { 0, C5_12 },  { 0, C6_12  },  { 0, C7_12 },  { 0, C8_12},  { 0, C9_12 },
    { 0, C1_5  },  { 0, C2_5 },  { 0, C3_5  }, { 0, C4_5  },  { 0, C5_5  },  { 0, C6_5 },  { 0, C7_5  },  { 0, C8_5 },  { 0, C9_5  },  { 0, C1_13 },  { 0, C2_13  },  { 0, C3_13 },  { 0, C4_13  },  { 0, C5_13 },  { 0, C6_13  },  { 0, C7_13 },  { 0, C8_13},  { 0, C9_10 },
    { 0, C1_6  },  { 0, C2_6 },  { 0, C3_6  }, { 0, C4_6  },  { 0, C5_6  },                                             { 0, C5_8  },                                                { 0, C4_14  },  { 0, C5_14 },  { 0, C6_14  },  { 0, C7_14 },  { 0, C8_14},  { 0, C9_14 },
    
    { 0, C6_6 },  { 0, C8_6 }, { 0, C7_6 },  // Lock Indicator
    { 0, C5_15 }, { 0, C4_15 }, { 0, C4_16 }, { 0, C6_15 }, { 0, C6_16 }, { 0, C5_16 }, // Layer Indicator
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    { 0,             1,             2,        NO_LED,             3,             4,             5,             6,             7,             8,             9,            10,            11,            12,            13,             14,             15,             16},
    {17,            18,            19,            20,            21,            22,            23,            24,            25,            26,            27,            28,            29,            30,            31,             32,             33,             34},
    {35,            36,            37,            38,            39,            40,            41,            42,            43,            44,            45,            46,            47,            48,            49,             50,             51,             52},
    {53,            54,            55,            56,            57,            58,            59,            60,            61,            62,            63,            64,            65,            66,            67,             68,             69,             70},
    {71,            72,            73,            74,            75,            76,            77,            78,            79,            80,            81,            82,            83,            84,            85,             86,             86,             87},
    {88,            89,            90,            91,            92,        NO_LED,        NO_LED,        NO_LED,            93,        NO_LED,        NO_LED,        NO_LED,            94,            95,            96,             97,             98,             86},
}, {
        //LED Index to Physical Positon
  {0, 0},     {13,  0},      {26,  0},                     {52,  0},      {66,  0},      {79,  0},      {92, 0},       {105, 0},      {118, 0},      {131, 0},      {145, 0},      {158, 0},      {171, 0},      {184, 0},      {197, 0},      {211, 0},      {224, 0},
  {0,13},     {13, 13},      {26, 13},      {39, 13},      {52, 13},      {66, 13},      {79, 13},      {92,13},       {105,13},      {118,13},      {131,13},      {145,13},      {158,13},      {171,13},      {184,13},      {197,13},      {211,13},      {224,13},
  {0,25},     {13, 25},      {26, 25},      {39, 25},      {52, 25},      {66, 25},      {79, 25},      {92,25},       {105,25},      {118,25},      {131,25},      {145,25},      {158,25},      {171,25},      {184,25},      {197,25},      {211,25},      {224,25},
  {0,38},     {13, 38},      {26, 38},      {39, 38},      {52, 38},      {66, 38},      {79, 38},      {92,38},       {105,38},      {118,38},      {131,38},      {145,38},      {158,38},      {171,38},      {184,38},      {197,38},      {211,38},      {224,38},
  {0,51},     {13, 51},      {26, 51},      {39, 51},      {52, 51},      {66, 51},      {79, 51},      {92,51},       {105,51},      {118,51},      {131,51},      {145,51},      {158,51},      {171,51},      {184,51},      {197,51},      {211,51},      {197,13},
  {0,64},     {13, 64},      {26, 64},      {39, 64},      {52, 64},                                                    {105,64},                                                   {158,64},      {171,64},      {184,64},      {197,64},      {211,64},      {224,64},
    }, {
       1,            1,             1,                            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,
       1,            1,             1,             1,             1,                                                          1,                                                          1,             1,             1,             1,             1,             1,
    } 
};


bool led_matrix_indicators_kb(void) {
    if (!led_matrix_indicators_user()) { return false; }
    if (host_keyboard_led_state().caps_lock) {
        led_matrix_set_value(37, 0xFF);
        led_matrix_set_value(101, 0xFF);
    } else {
        led_matrix_set_value(101, 0x00);
    }
    if (host_keyboard_led_state().num_lock) {
        led_matrix_set_value(102, 0xFF);
    } else {
        led_matrix_set_value(102, 0x00);
    }
    if (host_keyboard_led_state().scroll_lock) {
        led_matrix_set_value(103, 0xFF);
    } else {
        led_matrix_set_value(103, 0x00);
    }
    return true;
}


layer_state_t layer_state_set_kb(layer_state_t state) {
  // if on layer 1, turn on L1 LED, otherwise off.
    if (get_highest_layer(state) == 0) {
        led_matrix_set_value(104, 0xFF);
    } else {
        led_matrix_set_value(104, 0x00);
    }
  // if on layer 2, turn on L2 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        led_matrix_set_value(105, 0xFF);
    } else {
        led_matrix_set_value(105, 0x00);
    }

  // if on layer 3, turn on L3 LED, otherwise off.
    if (get_highest_layer(state) == 2) {
        led_matrix_set_value(106, 0xFF);
    } else {
        led_matrix_set_value(106, 0x00);
    }

  // if on layer 4, turn on L4 LED, otherwise off.
    if (get_highest_layer(state) == 3) {
        led_matrix_set_value(107, 0xFF);
    } else {
        led_matrix_set_value(107, 0x00);
    }
    return layer_state_set_user(state);
}