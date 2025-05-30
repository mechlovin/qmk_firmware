/* Copyright 2024 Mechlovin'
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
    {0,   SW1_CS39, SW1_CS38,   SW1_CS37}, //D93-SW2-0
    {0,   SW1_CS36, SW1_CS35,   SW1_CS34}, //D95-SW7-1
    {0,   SW1_CS33, SW1_CS32,   SW1_CS31}, //D97-SW13-2
    {0,   SW1_CS30, SW1_CS29,   SW1_CS28}, //D99-SW19-3
    {0,   SW1_CS21, SW1_CS20,   SW1_CS19}, //D101-SW24-4
    {0,   SW1_CS18, SW1_CS17,   SW1_CS16}, //D103-SW29-5
    {0,   SW1_CS15, SW1_CS14,   SW1_CS13}, //D105-SW33-6
    {0,   SW1_CS12, SW1_CS11,   SW1_CS10}, //D107-SW39-7
    {0,   SW1_CS27, SW1_CS26,   SW1_CS25},  //D109-SW44-8
    {0,   SW1_CS24, SW1_CS23,   SW1_CS22},  //D111-SW49-9
    {0,    SW1_CS6,  SW1_CS5,    SW1_CS4}, //D113-SW54-10
    {0,    SW1_CS3,  SW1_CS2,    SW1_CS1}, //D115-SW60-11
    {0,    SW1_CS9,  SW1_CS8,    SW1_CS7}, //D117-SW66-12
    {0,    SW4_CS9,  SW4_CS8,    SW4_CS7}, //D86-SW72-13
    {0,    SW5_CS9,  SW5_CS8,    SW5_CS7}, //D180-SW80-14

    {0,   SW2_CS39, SW2_CS38,   SW2_CS37}, //D124-SW5-15
    {0,   SW2_CS36, SW2_CS35,   SW2_CS34}, //D127-SW9-16
    {0,   SW2_CS33, SW2_CS32,   SW2_CS31}, //D130-SW14-17
    {0,   SW2_CS30, SW2_CS29,   SW2_CS28}, //D133-SW20-18
    {0,   SW2_CS21, SW2_CS20,   SW2_CS19}, //D135-SW25-19
    {0,   SW2_CS18, SW2_CS17,   SW2_CS16}, //D137-SW30-20
    {0,   SW2_CS15, SW2_CS14,   SW2_CS13}, //D139-SW34-21
    {0,   SW2_CS12, SW2_CS11,   SW2_CS10}, //D142-SW40-22
    {0,   SW2_CS27, SW2_CS26,   SW2_CS25}, //D144-SW45-23
    {0,   SW2_CS24, SW2_CS23,   SW2_CS22}, //D146-SW50-24
    {0,    SW2_CS6,  SW2_CS5,    SW2_CS4}, //D148-SW55-25
    {0,    SW2_CS3,  SW2_CS2,    SW2_CS1}, //D151-SW61-26
    {0,    SW2_CS9,  SW2_CS8,    SW2_CS7}, //D154-SW67-27
    {0,    SW6_CS9,  SW6_CS8,    SW6_CS7}, //D179-SW73-28
    
    {0,   SW3_CS39, SW3_CS38,   SW3_CS37}, //D165-SW93-29
    {0,   SW3_CS36, SW3_CS35,   SW3_CS34}, //D167-SW11-30
    {0,   SW3_CS33, SW3_CS32,   SW3_CS31}, //D168-SW16-31
    {0,   SW3_CS30, SW3_CS29,   SW3_CS28}, //D169-SW22-32
    {0,   SW3_CS21, SW3_CS20,   SW3_CS19}, //D170-SW27-33
    {0,   SW3_CS18, SW3_CS17,   SW3_CS16}, //D171-SW32-34
    {0,   SW3_CS15, SW3_CS14,   SW3_CS13}, //D172-SW38-35
    {0,   SW3_CS12, SW3_CS11,   SW3_CS10}, //D173-SW43-36
    {0,   SW3_CS27, SW3_CS26,   SW3_CS25},  //D174-SW48-37
    {0,   SW3_CS24, SW3_CS23,   SW3_CS22},  //D175-SW53-38
    {0,    SW3_CS6,  SW3_CS5,    SW3_CS4}, //D176-SW58-39
    {0,    SW3_CS3,  SW3_CS2,    SW3_CS1}, //D177-SW64-40
    {0,    SW3_CS9,  SW3_CS8,    SW3_CS7}, //D87-SW94-41
    
    {0,   SW7_CS39, SW7_CS38,   SW7_CS37}, //D125-SW3-42
    {0,   SW7_CS36, SW7_CS35,   SW7_CS34}, //D131-SW15-43
    {0,   SW7_CS33, SW7_CS32,   SW7_CS31}, //D134-SW21-44
    {0,   SW7_CS30, SW7_CS29,   SW7_CS28}, //D136-SW26-45
    {0,   SW7_CS21, SW7_CS20,   SW7_CS19}, //D138-SW31-46
    {0,   SW7_CS18, SW7_CS17,   SW7_CS16}, //D140-SW35-47
    {0,   SW7_CS15, SW7_CS14,   SW7_CS13}, //D143-SW41-48
    {0,   SW7_CS12, SW7_CS11,   SW7_CS10},  //D145-SW46-49
    {0,   SW7_CS27, SW7_CS26,   SW7_CS25},  //D147-SW51-50
    {0,   SW7_CS24, SW7_CS23,   SW7_CS22}, //D149-SW56-51
    {0,    SW7_CS6,  SW7_CS5,    SW7_CS4}, //D152-SW62-52
    {0,    SW7_CS9,  SW7_CS8,    SW7_CS7}, //D160-SW74-53
    {0,    SW7_CS3,  SW7_CS2,    SW7_CS1}, //D155-SW68-54
    
    {0,   SW9_CS39, SW9_CS38,   SW9_CS37}, //D124-SW104-58
    {0,   SW9_CS36, SW9_CS35,   SW9_CS34}, //D127-SW106-59
    {0,   SW9_CS33, SW9_CS32,   SW9_CS31}, //D130-SW17-60
    {0,   SW9_CS18, SW9_CS17,   SW9_CS16}, //D140-SW35-47
    {0,   SW9_CS24, SW9_CS23,   SW9_CS22}, //D149-SW56-51
    {0,    SW9_CS6,  SW9_CS5,    SW9_CS4}, //D152-SW62-52
    {0,    SW9_CS9,  SW9_CS8,    SW9_CS7}, //D160-SW74-53
    {0,    SW9_CS3,  SW9_CS2,    SW9_CS1}, //D155-SW68-54
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13},
        {15,         16,          17,          18,          19,          20,          21,          22,          23,           24,          25,           26,           27,           28},
        {29,         30,          31,          32,          33,          34,          35,          36,          37,           38,          39,           40,           14,           41},
        {42,         NO_LED,      43,          44,          45,          46,          47,          48,          49,           50,          51,           52,           53,           54},
        {55,         56,          57,      NO_LED,      NO_LED,      NO_LED,          58,      NO_LED,      NO_LED,      NO_LED,           59,           60,           61,           62},
    }, {
        {0, 0},  {16, 0},    {32, 0},    {48,  0},    {64,  0},    {80,  0},    {96,  0},    {112, 0},    {128,  0},    {144,  0},     {160,  0},     {176,  0},     {192,  0},     {208,  0},     {224,  0},
        {0,16},  {16,16},    {32,16},    {48, 16},    {64, 16},    {80, 16},    {96, 16},    {112,16},    {128, 16},    {144, 16},     {160, 16},     {176, 16},     {192, 16},     {208, 16},     {224, 16},
        {0,32},  {16,32},    {32,32},    {48, 32},    {64, 32},    {80, 32},    {96, 32},    {112,32},    {128, 32},    {144, 32},     {160, 32},     {176, 32},                    {208, 32},     {224, 32},
        {0,48},              {32,48},    {48, 48},    {64, 48},    {80, 48},    {96, 48},    {112,48},    {128, 48},    {144, 48},     {160, 48},     {176, 48},     {192, 48},     {208, 48},     {224, 48},
        {0,64},  {16,64},    {32,64},                                           {96, 64},                                              {160, 64},     {176, 64},     {192, 64},     {208, 64},     {224, 64},
    }, {
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,                            1,             1,
       1,                    1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,
       1,        1,          1,                                                  1,                                                      1,             1,             1,             1,             1,
    }
};

#endif
