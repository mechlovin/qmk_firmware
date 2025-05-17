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

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           |           LED Number in schematic
 *   |  |           |           |           |    Key Number in schematic
 *   |  |           |           |           |    |   LED Index  
 *   |  |           |           |           |    |   |*/
    {0,   CS21_SW5, CS23_SW5,   CS20_SW5}, //D71-SW2-0
    {0,   CS25_SW5, CS29_SW5,   CS27_SW5}, //D79-SW7-1
    {0,   CS28_SW5, CS32_SW5,   CS30_SW5}, //D84-SW13-2
    {0,   CS31_SW5, CS35_SW5,   CS33_SW5}, //D90-SW19-3
    {0,   CS34_SW5, CS38_SW5,   CS36_SW5}, //D95-SW24-4
    {0,   CS37_SW5, CS2_SW5,    CS39_SW5}, //D106-SW29-5
    {0,   CS1_SW5,  CS5_SW5,    CS3_SW5}, //D112-SW33-6
    {0,   CS4_SW5,  CS8_SW5,    CS6_SW5}, //D117-SW39-7
    {0,    CS7_SW5, CS11_SW5,   CS9_SW5}, //D1123-SW44-8
    {0,   CS10_SW5, CS14_SW5,   CS12_SW5},  //D129-SW49-9
    {0,   CS13_SW5, CS17_SW5,   CS15_SW5}, //D137-SW54-10
    {0,   CS16_SW5, CS19_SW5,   CS18_SW5}, //D144-SW54-11
    {0,   CS1_SW7,  CS5_SW7,   CS3_SW7}, //D149-SW66-12
    {0,   CS4_SW7,  CS8_SW7,   CS6_SW7}, //D155-SW66-13
    
    {0,   CS21_SW4, CS23_SW4,   CS20_SW4}, //D69-SW2-14
    {0,   CS24_SW4, CS26_SW4,   CS22_SW4}, //D80-SW2-15
    {0,   CS25_SW4, CS29_SW4,   CS27_SW4}, //D85-SW7-16
    {0,   CS28_SW4, CS32_SW4,   CS30_SW4}, //D91-SW13-17
    {0,   CS31_SW4, CS35_SW4,   CS33_SW4}, //D96-SW19-18
    {0,   CS34_SW4, CS38_SW4,   CS36_SW4}, //D101-SW24-19
    {0,   CS37_SW4, CS2_SW4,    CS39_SW4}, //D107-SW29-20
    {0,   CS1_SW4,  CS5_SW4,    CS3_SW4}, //D113-SW33-21
    {0,   CS4_SW4,  CS8_SW4,    CS6_SW4}, //D118-SW39-22
    {0,    CS7_SW4, CS11_SW4,   CS9_SW4}, //D124-SW44-23
    {0,   CS10_SW4, CS14_SW4,   CS12_SW4},  //D130-SW49-24
    {0,   CS13_SW4, CS17_SW4,   CS15_SW4}, //D138-SW54-25
    {0,   CS16_SW4, CS19_SW4,   CS18_SW4}, //D145-SW54-26
    {0,   CS1_SW6,  CS5_SW6,   CS3_SW6}, //D150-SW66-27
    {0,   CS4_SW8,  CS8_SW8,   CS6_SW8}, //D172-SW66-28
    {0,   CS4_SW6,  CS8_SW6,   CS6_SW6}, //D156-SW66-29
    
    {0,   CS21_SW3, CS23_SW3,   CS20_SW3}, //D75-SW2-30
    {0,   CS24_SW3, CS26_SW3,   CS22_SW3}, //D81-SW2-31
    {0,   CS25_SW3, CS29_SW3,   CS27_SW3}, //D86-SW7-32
    {0,   CS28_SW3, CS32_SW3,   CS30_SW3}, //D92-SW13-33
    {0,   CS31_SW3, CS35_SW3,   CS33_SW3}, //D97-SW19-34
    {0,   CS34_SW3, CS38_SW3,   CS36_SW3}, //D102-SW24-35
    {0,   CS37_SW3, CS2_SW3,    CS39_SW3}, //D108-SW29-36
    {0,   CS1_SW3,  CS5_SW3,    CS3_SW3}, //D114-SW33-37
    {0,   CS4_SW3,  CS8_SW3,    CS6_SW3}, //D119-SW39-38
    {0,    CS7_SW3, CS11_SW3,   CS9_SW3}, //D125-SW34-39
    {0,   CS10_SW3, CS14_SW3,   CS12_SW3},  //D131-SW39-40
    {0,   CS13_SW3, CS17_SW3,   CS15_SW3}, //D139-SW54-41
    {0,   CS16_SW3, CS19_SW3,   CS18_SW3}, //D146-SW54-42
    {0,   CS16_SW6, CS19_SW6,   CS18_SW6}, //D151-SW54-43
    {0,   CS7_SW6,  CS11_SW6,   CS9_SW6}, //D157-SW66-44
    
    {0,   CS21_SW2, CS23_SW2,   CS20_SW2}, //D76-SW2-45
    {0,   CS24_SW2, CS26_SW2,   CS22_SW2}, //D82-SW2-46
    {0,   CS25_SW2, CS29_SW2,   CS27_SW2}, //D87-SW7-47
    {0,   CS28_SW2, CS32_SW2,   CS30_SW2}, //D93-SW13-48
    {0,   CS31_SW2, CS35_SW2,   CS33_SW2}, //D98-SW19-49
    {0,   CS34_SW2, CS38_SW2,   CS36_SW2}, //D103-SW24-50
    {0,   CS37_SW2, CS2_SW2,    CS39_SW2}, //D109-SW29-51
    {0,   CS1_SW2,  CS5_SW2,    CS3_SW2}, //D115-SW33-52
    {0,   CS4_SW2,  CS8_SW2,    CS6_SW2}, //D120-SW39-53
    {0,    CS7_SW2, CS11_SW2,   CS9_SW2}, //D126-SW34-54
    {0,   CS10_SW2, CS14_SW2,   CS12_SW2},  //D133-SW39-55
    {0,   CS13_SW2, CS17_SW2,   CS15_SW2}, //D140-SW54-56
    {0,   CS16_SW2, CS19_SW2,   CS18_SW2}, //D152-SW54-57
    {0,   CS10_SW6,  CS14_SW6,   CS12_SW6}, //D158-SW66-58
        
    {0,   CS21_SW1, CS23_SW1,   CS20_SW1}, //D77-SW1-59
    {0,   CS24_SW1, CS26_SW1,   CS22_SW1}, //D167-SW2-60
    {0,   CS25_SW1, CS29_SW1,   CS27_SW1}, //D88-SW7-61
    {0,   CS28_SW1, CS32_SW1,   CS30_SW1}, //D94-SW13-62
    {0,   CS31_SW1, CS35_SW1,   CS33_SW1}, //D99-SW19-63
    {0,   CS34_SW1, CS38_SW1,   CS36_SW1}, //D105-SW24-64
    {0,   CS37_SW1, CS2_SW1,    CS39_SW1}, //D110-SW29-65
    {0,   CS1_SW1,  CS5_SW1,    CS3_SW1}, //D116-SW33-66
    {0,   CS4_SW1,  CS8_SW1,    CS6_SW1}, //D121-SW39-67
    {0,    CS7_SW1, CS11_SW1,   CS9_SW1}, //D127-SW24-68
    {0,   CS10_SW1, CS14_SW1,   CS12_SW1},  //D134-SW29-69
    {0,   CS13_SW1, CS17_SW1,   CS15_SW1}, //D142-SW54-70
    {0,   CS16_SW1, CS19_SW1,   CS18_SW1}, //D147-SW54-71
    {0,   CS16_SW7, CS19_SW7,   CS18_SW7}, //D153-SW54-72
    {0,   CS13_SW6, CS17_SW6,   CS15_SW6}, //D159-SW54-73

    {0,   CS21_SW8, CS23_SW8,   CS20_SW8}, //D78-SW2-74
    {0,   CS24_SW8, CS26_SW8,   CS22_SW8}, //D83-SW2-75
    {0,   CS25_SW8, CS29_SW8,   CS27_SW8}, //D89-SW7-76
    {0,   CS37_SW8, CS2_SW8,    CS39_SW8}, //D111-SW29-77
    {0,   CS10_SW8, CS14_SW8,   CS12_SW8},  //D136-SW39-78
    {0,   CS13_SW8, CS17_SW8,   CS15_SW8}, //D143-SW54-79
    {0,   CS16_SW8, CS19_SW8,   CS18_SW8}, //D148-SW54-80
    {0,   CS10_SW7, CS14_SW7,   CS12_SW7}, //D154-SW54-81
    {0,   CS13_SW7,  CS17_SW7,   CS15_SW7}, //D162-SW66-82
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    { 0,        NO_LED,             1,             2,             3,             4,             5,             6,             7,             8,             9,            10,            11,            12,            13},
    {14,            15,            16,            17,            18,            19,            20,            21,            22,            23,            24,            25,            26,            27,            28,            29},
    {30,            31,            32,            33,            34,            35,            36,            37,            38,            39,            40,            41,            42,            43,            44},
    {45,            46,            47,            48,            49,            50,            51,            52,            53,            54,            55,            56,            57,            58},
    {59,            60,            61,            62,            63,            64,            65,            66,            67,            68,            69,            70,            71,            72,            73},
    {74,            75,            76,        NO_LED,        NO_LED,        NO_LED,            77,        NO_LED,        NO_LED,        NO_LED,            78,            79,            80,            81,            82},
}, {
        //LED Index to Physical Positon
  {0, 0},                    {32,  0},      {48,  0},      {64,  0},      {80,  0},      {96,  0},      {112, 0},      {128, 0},      {144, 0},      {160, 0},      {176, 0},      {192, 0},      {208, 0},      {224, 0},
  {0,13},     {16, 13},      {32, 13},      {48, 13},      {64, 13},      {80, 13},      {96, 13},      {112,13},      {128,13},      {144,13},      {160,13},      {176,13},      {192,13},      {208,13},      {214,13},      {224,13},
  {0,25},     {16, 25},      {32, 25},      {48, 25},      {64, 25},      {80, 25},      {96, 25},      {112,25},      {128,25},      {144,25},      {160,25},      {176,25},      {192,25},      {208,25},      {224,25},
  {0,38},     {16, 38},      {32, 38},      {48, 38},      {64, 38},      {80, 38},      {96, 38},      {112,38},      {128,38},      {144,38},      {160,38},      {176,38},                     {208,38},      {224,38},
  {0,51},     {16, 51},      {32, 51},      {48, 51},      {64, 51},      {80, 51},      {96, 51},      {112,51},      {128,51},      {144,51},      {160,51},      {176,51},      {192,51},      {208,51},      {224,51},
  {0,64},     {16, 13},      {32, 13},                                                   {96, 64},                                                   {160,64},      {176,64},      {192,64},      {208,64},      {224,64},
    }, {
       4,                           4,             4,             4,             4,             4,             4,             4,             4,             4,             4,             4,             4,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,            1,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,                            1,            4,
       4,            1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,             1,            4,
       4,            1,             1,                                                          1,                                                          1,             1,             1,             1,            4,
    } 
};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(45, 255, 255, 255);
    }
    return true;
}

#endif
