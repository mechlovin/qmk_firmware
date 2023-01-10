/* Copyright 2022 Team Mechlovin
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

#include "rgb_led.h"

void bootloader_jump(void) {
    // This board doesn't use the standard DFU bootloader, and no information is available regarding how to enter bootloader mode. All we can do here is reset.
    NVIC_SystemReset();
}


#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    {0, E_1, D_1, F_1}, //0
    {0, E_14, D_14, F_14}, 
    {0, E_13, D_13, F_13}, 
    {0, E_12, D_12, F_12}, 
    {0, E_11, D_11, F_11}, 
    {0, E_10, D_10, F_10}, //5
    {0, E_9, D_9, F_9}, 
    {0, E_8, D_8, F_8}, 
    {0, E_7, D_7, F_7}, 
    {0, E_6, D_6, F_6}, 
    {0, E_5, D_5, F_5}, //10
    {0, E_4, D_4, F_4}, 
    {0, E_3, D_3, F_3}, 
    {0, E_2, D_2, F_2}, //13

    {0, B_1, A_1, C_1}, //14
    {0, B_15, A_15, C_15}, //15
    {0, B_14, A_14, C_14},
    {0, B_13, A_13, C_13},
    {0, B_12, A_12, C_12},
    {0, B_11, A_11, C_11},
    {0, B_10, A_10, C_10}, //20
    {0, B_9, A_9, C_9},
    {0, B_8, A_8, C_8},
    {0, B_7, A_7, C_7},
    {0, B_6, A_6, C_6},
    {0, B_5, A_5, C_5}, //25
    {0, B_4, A_4, C_4},
    {0, B_3, A_3, C_3},
    {0, B_2, A_2, C_2}, //28

    {0, K_1, J_1, L_1}, //29
    {0, K_15, J_15, L_15}, //30
    {0, K_14, J_14, L_14},
    {0, K_13, J_13, L_13},
    {0, K_12, J_12, L_12},
    {0, K_11, J_11, L_11},
    {0, K_10, J_10, L_10}, //35
    {0, K_9, J_9, L_9},
    {0, K_8, J_8, L_8},
    {0, K_7, J_7, L_7},
    {0, K_6, J_6, L_6},
    {0, K_5, J_5, L_5}, //40
    {0, K_4, J_4, L_4},
    {0, K_3, J_3, L_3},
    {0, K_2, J_2, L_2}, //43
    
    {1, B_16, A_16, C_16}, //44
    {1, B_15, A_15, C_15}, //45
    {1, B_14, A_14, C_14},
    {1, B_12, A_12, C_12},
    {1, B_11, A_11, C_11},
    {1, B_10, A_10, C_10}, 
    {1, B_9, A_9, C_9}, //50
    {1, B_8, A_8, C_8},
    {1, B_7, A_7, C_7},
    {1, B_6, A_6, C_6},
    {1, B_5, A_5, C_5}, 
    {1, B_1, A_1, C_1}, //55
    {1, B_3, A_3, C_3},
    {1, B_4, A_4, C_4}, //57

    {1, E_16, D_16, F_16}, //58
    {1, E_14, D_14, F_14}, 
    {1, E_12, D_12, F_12}, //60
    {1, E_11, D_11, F_11}, 
    {1, E_10, D_10, F_10}, 
    {1, E_9, D_9, F_9}, 
    {1, E_8, D_8, F_8}, 
    {1, E_7, D_7, F_7}, //65
    {1, E_6, D_6, F_6}, 
    {1, E_5, D_5, F_5}, 
    {1, E_1, D_1, F_1}, 
    {1, E_2, D_2, F_2}, 
    {1, E_3, D_3, F_3}, //70
    {1, E_4, D_4, F_4}, //71
    
    {1, H_16, G_16, I_16}, //72
    {1, H_15, G_15, I_15},
    {1, H_14, G_14, I_14}, 
    {1, H_9, G_9, I_9}, //75
    {1, H_5, G_5, I_5},
    {1, H_1, G_1, I_1},
    {1, H_2, G_2, I_2},
    {1, H_3, G_3, I_3}, 
    {1, H_4, G_4, I_4}, //80
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    { 0,        NO_LED,             1,             2,             3,             4,             5,             6,             7,             8,             9,            10,            11,            12,            13},
    {14,            15,            16,            17,            18,            19,            20,            21,            22,            23,            24,            25,            26,            27,            28},
    {29,            30,            31,            32,            33,            34,            35,            36,            37,            38,            39,            40,            41,            42,            43},
    {44,            45,            46,            47,            48,            49,            50,            51,            52,            53,            54,            55,        NO_LED,            56,            57},
    {58,        NO_LED,            59,            60,            61,            62,            63,            64,            65,            66,            67,            68,            69,            70,            71},
    {72,            73,            74,        NO_LED,        NO_LED,        NO_LED,            75,        NO_LED,        NO_LED,        NO_LED,            76,            77,            78,            79,            80},
}, {
        //LED Index to Physical Positon
  {0, 0},                    {32,  0},      {48,  0},      {64,  0},      {80,  0},      {96,  0},      {112, 0},      {128, 0},      {144, 0},      {160, 0},      {176, 0},      {192, 0},      {208, 0},      {224, 0},
  {0,13},     {16, 13},      {32, 13},      {48, 13},      {64, 13},      {80, 13},      {96, 13},      {112,13},      {128,13},      {144,13},      {160,13},      {176,13},      {192,13},      {208,13},      {224,13},
  {0,25},     {16, 25},      {32, 25},      {48, 25},      {64, 25},      {80, 25},      {96, 25},      {112,25},      {128,25},      {144,25},      {160,25},      {176,25},      {192,25},      {208,25},      {224,25},
  {0,38},     {16, 38},      {32, 38},      {48, 38},      {64, 38},      {80, 38},      {96, 38},      {112,38},      {128,38},      {144,38},      {160,38},      {176,38},                     {208,38},      {224,38},
  {0,51},                    {32, 51},      {48, 51},      {64, 51},      {80, 51},      {96, 51},      {112,51},      {128,51},      {144,51},      {160,51},      {176,51},      {192,51},      {208,51},      {224,51},
  {0,64},     {16, 13},      {32, 13},                                                   {96, 64},                                                   {160,64},      {176,64},      {192,64},      {208,64},      {224,64},
    }, {
       4,                           4,             4,             4,             4,             4,             4,             4,             4,             4,             4,             4,             4,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,            4,
       4,                           1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,            4,
       4,            1,             1,                                                          1,                                                          1,             1,             1,             1,            4,
    } 
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(44, 255, 255, 255);
    }
    return true;
}

#endif
