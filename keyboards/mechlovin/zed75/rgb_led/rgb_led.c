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

 #include "quantum.h"
 
#ifdef RGB_MATRIX_ENABLE
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           |           LED Number in schematic
 *   |  |           |           |           |    Key Number in schematic
 *   |  |           |           |           |    |   LED Index  
 *   |  |           |           |           |    |   |*/
    {0,   SW5_CS21, SW5_CS23,   SW5_CS20}, //D71-SW2-0
    {0,   SW5_CS25, SW5_CS29,   SW5_CS27}, //D79-SW7-1
    {0,   SW5_CS28, SW5_CS32,   SW5_CS30}, //D84-SW13-2
    {0,   SW5_CS31, SW5_CS35,   SW5_CS33}, //D90-SW19-3
    {0,   SW5_CS34, SW5_CS38,   SW5_CS36}, //D95-SW24-4
    {0,   SW5_CS37, SW5_CS2,    SW5_CS39}, //D106-SW29-5
    {0,   SW5_CS1,  SW5_CS5,    SW5_CS3}, //D112-SW33-6
    {0,   SW5_CS4,  SW5_CS8,    SW5_CS6}, //D117-SW39-7
    {0,    SW5_CS7, SW5_CS11,   SW5_CS9}, //D1123-SW44-8
    {0,   SW5_CS10, SW5_CS14,   SW5_CS12},  //D129-SW49-9
    {0,   SW5_CS13, SW5_CS17,   SW5_CS15}, //D137-SW54-10
    {0,   SW5_CS16, SW5_CS19,   SW5_CS18}, //D144-SW54-11
    {0,   SW7_CS1,  SW7_CS5,   SW7_CS3}, //D149-SW66-12
    {0,   SW7_CS4,  SW7_CS8,   SW7_CS6}, //D155-SW66-13
    
    {0,   SW4_CS21, SW4_CS23,   SW4_CS20}, //D69-SW2-14
    {0,   SW4_CS24, SW4_CS26,   SW4_CS22}, //D80-SW2-15
    {0,   SW4_CS25, SW4_CS29,   SW4_CS27}, //D85-SW7-16
    {0,   SW4_CS28, SW4_CS32,   SW4_CS30}, //D91-SW13-17
    {0,   SW4_CS31, SW4_CS35,   SW4_CS33}, //D96-SW19-18
    {0,   SW4_CS34, SW4_CS38,   SW4_CS36}, //D101-SW24-19
    {0,   SW4_CS37, SW4_CS2,    SW4_CS39}, //D107-SW29-20
    {0,   SW4_CS1,  SW4_CS5,    SW4_CS3}, //D113-SW33-21
    {0,   SW4_CS4,  SW4_CS8,    SW4_CS6}, //D118-SW39-22
    {0,    SW4_CS7, SW4_CS11,   SW4_CS9}, //D124-SW44-23
    {0,   SW4_CS10, SW4_CS14,   SW4_CS12},  //D130-SW49-24
    {0,   SW4_CS13, SW4_CS17,   SW4_CS15}, //D138-SW54-25
    {0,   SW4_CS16, SW4_CS19,   SW4_CS18}, //D145-SW54-26
    {0,   SW6_CS1,  SW6_CS5,   SW6_CS3}, //D150-SW66-27
    {0,   SW8_CS4,  SW8_CS8,   SW8_CS6}, //D172-SW66-28
    {0,   SW6_CS4,  SW6_CS8,   SW6_CS6}, //D156-SW66-29
    
    {0,   SW3_CS21, SW3_CS23,   SW3_CS20}, //D75-SW2-30
    {0,   SW3_CS24, SW3_CS26,   SW3_CS22}, //D81-SW2-31
    {0,   SW3_CS25, SW3_CS29,   SW3_CS27}, //D86-SW7-32
    {0,   SW3_CS28, SW3_CS32,   SW3_CS30}, //D92-SW13-33
    {0,   SW3_CS31, SW3_CS35,   SW3_CS33}, //D97-SW19-34
    {0,   SW3_CS34, SW3_CS38,   SW3_CS36}, //D102-SW24-35
    {0,   SW3_CS37, SW3_CS2,    SW3_CS39}, //D108-SW29-36
    {0,   SW3_CS1,  SW3_CS5,    SW3_CS3}, //D114-SW33-37
    {0,   SW3_CS4,  SW3_CS8,    SW3_CS6}, //D119-SW39-38
    {0,    SW3_CS7, SW3_CS11,   SW3_CS9}, //D125-SW34-39
    {0,   SW3_CS10, SW3_CS14,   SW3_CS12},  //D131-SW39-40
    {0,   SW3_CS13, SW3_CS17,   SW3_CS15}, //D139-SW54-41
    {0,   SW3_CS16, SW3_CS19,   SW3_CS18}, //D146-SW54-42
    {0,   SW6_CS16, SW6_CS19,   SW6_CS18}, //D151-SW54-43
    {0,   SW6_CS7,  SW6_CS11,   SW6_CS9}, //D157-SW66-44
    
    {0,   SW2_CS21, SW2_CS23,   SW2_CS20}, //D76-SW2-45
    {0,   SW2_CS24, SW2_CS26,   SW2_CS22}, //D82-SW2-46
    {0,   SW2_CS25, SW2_CS29,   SW2_CS27}, //D87-SW7-47
    {0,   SW2_CS28, SW2_CS32,   SW2_CS30}, //D93-SW13-48
    {0,   SW2_CS31, SW2_CS35,   SW2_CS33}, //D98-SW19-49
    {0,   SW2_CS34, SW2_CS38,   SW2_CS36}, //D103-SW24-50
    {0,   SW2_CS37, SW2_CS2,    SW2_CS39}, //D109-SW29-51
    {0,   SW2_CS1,  SW2_CS5,    SW2_CS3}, //D115-SW33-52
    {0,   SW2_CS4,  SW2_CS8,    SW2_CS6}, //D120-SW39-53
    {0,    SW2_CS7, SW2_CS11,   SW2_CS9}, //D126-SW34-54
    {0,   SW2_CS10, SW2_CS14,   SW2_CS12},  //D133-SW39-55
    {0,   SW2_CS13, SW2_CS17,   SW2_CS15}, //D140-SW54-56
    {0,   SW2_CS16, SW2_CS19,   SW2_CS18}, //D152-SW54-57
    {0,   SW6_CS10,  SW6_CS14,   SW6_CS12}, //D158-SW66-58
        
    {0,   SW1_CS21, SW1_CS23,   SW1_CS20}, //D77-SW1-59
    {0,   SW1_CS24, SW1_CS26,   SW1_CS22}, //D167-SW2-60
    {0,   SW1_CS25, SW1_CS29,   SW1_CS27}, //D88-SW7-61
    {0,   SW1_CS28, SW1_CS32,   SW1_CS30}, //D94-SW13-62
    {0,   SW1_CS31, SW1_CS35,   SW1_CS33}, //D99-SW19-63
    {0,   SW1_CS34, SW1_CS38,   SW1_CS36}, //D105-SW24-64
    {0,   SW1_CS37, SW1_CS2,    SW1_CS39}, //D110-SW29-65
    {0,   SW1_CS1,  SW1_CS5,    SW1_CS3}, //D116-SW33-66
    {0,   SW1_CS4,  SW1_CS8,    SW1_CS6}, //D121-SW39-67
    {0,    SW1_CS7, SW1_CS11,   SW1_CS9}, //D127-SW24-68
    {0,   SW1_CS10, SW1_CS14,   SW1_CS12},  //D134-SW29-69
    {0,   SW1_CS13, SW1_CS17,   SW1_CS15}, //D142-SW54-70
    {0,   SW1_CS16, SW1_CS19,   SW1_CS18}, //D147-SW54-71
    {0,   SW7_CS16, SW7_CS19,   SW7_CS18}, //D153-SW54-72
    {0,   SW6_CS13, SW6_CS17,   SW6_CS15}, //D159-SW54-73

    {0,   SW8_CS21, SW8_CS23,   SW8_CS20}, //D78-SW2-74
    {0,   SW8_CS24, SW8_CS26,   SW8_CS22}, //D83-SW2-75
    {0,   SW8_CS25, SW8_CS29,   SW8_CS27}, //D89-SW7-76
    {0,   SW8_CS37, SW8_CS2,    SW8_CS39}, //D111-SW29-77
    {0,   SW8_CS10, SW8_CS14,   SW8_CS12},  //D136-SW39-78
    {0,   SW8_CS13, SW8_CS17,   SW8_CS15}, //D143-SW54-79
    {0,   SW8_CS16, SW8_CS19,   SW8_CS18}, //D148-SW54-80
    {0,   SW7_CS10, SW7_CS14,   SW7_CS12}, //D154-SW54-81
    {0,   SW7_CS13,  SW7_CS17,   SW7_CS15}, //D162-SW66-82
};

led_config_t g_led_config = {
{
        // Key Matrix to LED Index
    { 0,        NO_LED,             1,             2,             3,             4,             5,             6,             7,             8,             9,            10,            11,            12,            13},
    {14,            15,            16,            17,            18,            19,            20,            21,            22,            23,            24,            25,            26,            27,            29},
    {30,            31,            32,            33,            34,            35,            36,            37,            38,            39,            40,            41,            42,            43,            44},
    {45,            46,            47,            48,            49,            50,            51,            52,            53,            54,            55,            56,            28,            57,            58},
    {59,            60,            61,            62,            63,            64,            65,            66,            67,            68,            69,            70,            71,            72,            73},
    {74,            75,            76,        NO_LED,        NO_LED,        NO_LED,            77,        NO_LED,        NO_LED,        NO_LED,            78,            79,            80,            81,            82},
}, {
        //LED Index to Physical Positon
  {0, 0},                    {32,  0},      {48,  0},      {64,  0},      {80,  0},      {96,  0},      {112, 0},      {128, 0},      {144, 0},      {160, 0},      {176, 0},      {192, 0},      {208, 0},      {224, 0},
  {0,13},     {16, 13},      {32, 13},      {48, 13},      {64, 13},      {80, 13},      {96, 13},      {112,13},      {128,13},      {144,13},      {160,13},      {176,13},      {192,13},      {208,13},      {214,13},      {224,13},
  {0,25},     {16, 25},      {32, 25},      {48, 25},      {64, 25},      {80, 25},      {96, 25},      {112,25},      {128,25},      {144,25},      {160,25},      {176,25},      {192,25},      {208,25},      {224,25},
  {0,38},     {16, 38},      {32, 38},      {48, 38},      {64, 38},      {80, 38},      {96, 38},      {112,38},      {128,38},      {144,38},      {160,38},      {176,38},                     {208,38},      {224,38},
  {0,51},     {16, 51},      {32, 51},      {48, 51},      {64, 51},      {80, 51},      {96, 51},      {112,51},      {128,51},      {144,51},      {160,51},      {176,51},      {192,51},      {208,51},      {224,51},
  {0,64},     {16, 64},      {32, 64},                                                   {105, 64},                                                   {160,64},      {176,64},      {192,64},      {208,64},      {224,64},
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
