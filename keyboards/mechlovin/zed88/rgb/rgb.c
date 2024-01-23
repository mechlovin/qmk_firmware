// Copyright 2024 mechlovin (@mechlovin)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
}

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_kb(void) {
  // Call the post init code.
  rgblight_sethsv_at(255, 255, 255, 0);	
    keyboard_post_init_user();
}
#endif

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
    {0,   CS9_SW1,  CS7_SW1,    CS8_SW1}, //D92-SW1-0
    {0,  CS12_SW1, CS10_SW1,   CS11_SW1}, //D94-SW12-1
    {0,  CS15_SW1, CS13_SW1,   CS14_SW1}, //D96-SW18-2
    {0,  CS18_SW1, CS16_SW1,   CS17_SW1}, //D98-SW23-3
    {0,  CS21_SW1, CS19_SW1,   CS20_SW1}, //D100-SW28-4
    {0,  CS24_SW1, CS22_SW1,   CS23_SW1}, //D102-SW37-5
    {0,  CS27_SW1, CS25_SW1,   CS26_SW1}, //D104-SW42-6
    {0,  CS30_SW1, CS28_SW1,   CS29_SW1}, //D106-SW47-7
    {0,  CS33_SW1, CS31_SW1,   CS32_SW1}, //D108-SW52-8
    {0,  CS36_SW1, CS34_SW1,   CS35_SW1}, //D110-SW59-9
    {0,  CS39_SW1, CS37_SW1,   CS38_SW1}, //D112-SW65-10
    {0,   CS3_SW1,  CS1_SW1,    CS2_SW1}, //D114-SW71-11
    {0,   CS4_SW1,  CS6_SW1,    CS5_SW1}, //D116-SW77-12
    {0,   CS4_SW7,  CS6_SW7,    CS5_SW7}, //D57-SW3-13
    {0,  CS39_SW7, CS37_SW7,   CS38_SW7}, //D118-SW79-14
    {0,  CS36_SW7, CS34_SW7,   CS35_SW7}, //D120-SW83-15
    {0,  CS33_SW7, CS31_SW7,   CS32_SW7}, //D122-SW88-16
    
    {0,   CS9_SW2,  CS7_SW2,    CS8_SW2}, //D93-SW93-17
    {0,  CS12_SW2, CS10_SW2,   CS11_SW2}, //D95-SW95-18
    {0,  CS15_SW2, CS13_SW2,   CS14_SW2}, //D97-SW97-19
    {0,  CS18_SW2, CS16_SW2,   CS17_SW2}, //D99-SW99-20
    {0,  CS21_SW2, CS19_SW2,   CS20_SW2}, //D101-SW101-21
    {0,  CS24_SW2, CS22_SW2,   CS23_SW2}, //D103-SW103-22
    {0,  CS27_SW2, CS25_SW2,   CS26_SW2}, //D105-SW105-23
    {0,  CS30_SW2, CS28_SW2,   CS29_SW2}, //D107-SW107-24
    {0,  CS33_SW2, CS31_SW2,   CS32_SW2}, //D109-SW109-25
    {0,  CS36_SW2, CS34_SW2,   CS35_SW2}, //D111-SW111-26
    {0,  CS39_SW2, CS37_SW2,   CS38_SW2}, //D113-SW113-27
    {0,   CS3_SW2,  CS1_SW2,    CS2_SW2}, //D115-SW115-28
    {0,   CS4_SW2,  CS6_SW2,    CS5_SW2}, //D117-SW117-29
    {0,   CS4_SW8,  CS6_SW8,    CS5_SW8}, //D183-SW183-30
    {0,  CS39_SW8, CS37_SW8,   CS38_SW8}, //D119-SW19-31
    {0,  CS36_SW8, CS34_SW8,   CS35_SW8}, //D121-SW121-32
    {0,  CS33_SW8, CS31_SW8,   CS32_SW8}, //D123-SW123-33
    
    {0,   CS9_SW3,  CS7_SW3,    CS8_SW3}, //D124-SW3-34
    {0,  CS12_SW3, CS10_SW3,   CS11_SW3}, //D127-SW3-35
    {0,  CS15_SW3, CS13_SW3,   CS14_SW3}, //D130-SW3-36
    {0,  CS18_SW3, CS16_SW3,   CS17_SW3}, //D133-SW3-37
    {0,  CS21_SW3, CS19_SW3,   CS20_SW3}, //D135-SW3-38
    {0,  CS24_SW3, CS22_SW3,   CS23_SW3}, //D137-SW3-39
    {0,  CS27_SW3, CS25_SW3,   CS26_SW3}, //D139-SW3-40
    {0,  CS30_SW3, CS28_SW3,   CS29_SW3}, //D142-SW3-41
    {0,  CS33_SW3, CS31_SW3,   CS32_SW3}, //D144-SW3-42
    {0,  CS36_SW3, CS34_SW3,   CS35_SW3}, //D146-SW3-43
    {0,  CS39_SW3, CS37_SW3,   CS38_SW3}, //D148-SW3-44
    {0,   CS3_SW3,  CS1_SW3,    CS2_SW3}, //D151-SW1-45
    {0,   CS4_SW3,  CS6_SW3,    CS5_SW3}, //D154-SW1-46
    {0,   CS4_SW6,  CS6_SW6,    CS5_SW6}, //D159-SW1-47
    {0,  CS39_SW6, CS37_SW6,   CS38_SW6}, //D180-SW1-48
    {0,  CS36_SW6, CS34_SW6,   CS35_SW6}, //D181-SW1-49
    {0,  CS33_SW6, CS31_SW6,   CS32_SW6}, //D182-SW1-50
    
    {0,   CS9_SW4,  CS7_SW4,    CS8_SW4}, //D166-SW4-51
    {0,  CS12_SW4, CS10_SW4,   CS11_SW4}, //D167-SW4-52
    {0,  CS15_SW4, CS13_SW4,   CS14_SW4}, //D168-SW4-53
    {0,  CS18_SW4, CS16_SW4,   CS17_SW4}, //D169-SW4-54
    {0,  CS21_SW4, CS19_SW4,   CS20_SW4}, //D170-SW4-55
    {0,  CS24_SW4, CS22_SW4,   CS23_SW4}, //D171-SW4-56
    {0,  CS27_SW4, CS25_SW4,   CS26_SW4}, //D172-SW4-57
    {0,  CS30_SW4, CS28_SW4,   CS29_SW4}, //D173-SW4-58
    {0,  CS33_SW4, CS31_SW4,   CS32_SW4}, //D174-SW4-59
    {0,  CS36_SW4, CS34_SW4,   CS35_SW4}, //D175-SW4-60
    {0,  CS39_SW4, CS37_SW4,   CS38_SW4}, //D176-SW4-61
    {0,   CS3_SW4,  CS1_SW4,    CS2_SW4}, //D177-SW1-62
    {0,   CS4_SW4,  CS6_SW4,    CS5_SW4}, //D179-SW1-63
    
    {0,   CS9_SW5,  CS7_SW5,    CS8_SW5}, //D125-SW5-64
    {0,  CS15_SW5, CS13_SW5,   CS14_SW5}, //D131-SW5-65
    {0,  CS18_SW5, CS16_SW5,   CS17_SW5}, //D134-SW5-66
    {0,  CS21_SW5, CS19_SW5,   CS20_SW5}, //D136-SW5-67
    {0,  CS24_SW5, CS22_SW5,   CS23_SW5}, //D138-SW5-68
    {0,  CS27_SW5, CS25_SW5,   CS26_SW5}, //D140-SW5-69
    {0,  CS30_SW5, CS28_SW5,   CS29_SW5}, //D143-SW5-70
    {0,  CS33_SW5, CS31_SW5,   CS32_SW5}, //D145-SW5-71
    {0,  CS36_SW5, CS34_SW5,   CS35_SW5}, //D147-SW5-72
    {0,  CS39_SW5, CS37_SW5,   CS38_SW5}, //D149-SW5-73
    {0,   CS3_SW5,  CS1_SW5,    CS2_SW5}, //D152-SW1-74
    {0,   CS4_SW5,  CS6_SW5,    CS5_SW5}, //D160-SW1-75
    {0,   CS3_SW6,  CS1_SW6,    CS2_SW6}, //D163-SW1-76
    
    {0,   CS9_SW9,  CS7_SW9,    CS8_SW9}, //D126-SW9-77
    {0,  CS12_SW9, CS10_SW9,   CS11_SW9}, //D129-SW3-78
    {0,  CS15_SW9, CS13_SW9,   CS14_SW9}, //D132-SW5-79
    {0,  CS30_SW9, CS28_SW9,   CS29_SW9}, //D188-SW9-80
    {0,   CS3_SW9,  CS1_SW9,    CS2_SW9}, //D153-SW1-81
    {0,   CS4_SW9,  CS6_SW9,    CS5_SW9}, //D156-SW1-82
    {0,   CS3_SW7,  CS1_SW7,    CS2_SW7}, //D161-SW1-83
    {0,  CS39_SW9, CS37_SW9,   CS38_SW9}, //D162-SW1-84
    {0,  CS36_SW9, CS34_SW9,   CS35_SW9}, //D164-SW1-85
    {0,  CS33_SW9, CS31_SW9,   CS32_SW9}, //D165-SW1-86
    
    
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13,           14,           15,           16},
        {17,         18,          19,          20,          21,          22,          23,          24,          25,          26,           27,           28,           29,           30,           31,           32,           33},
        {34,         35,          36,          37,          38,          39,          40,          41,          42,          43,           44,           45,           46,           47,           48,           49,           50},
        {51,         52,          53,          54,          55,          56,          57,          58,          59,          60,           61,           62,       NO_LED,           63,       NO_LED,       NO_LED,       NO_LED},
        {64,     NO_LED,          65,          66,          67,          68,          69,          70,          71,          72,           73,           74,       NO_LED,           75,       NO_LED,           76,       NO_LED},
        {77,         78,          79,      NO_LED,      NO_LED,      NO_LED,          80,      NO_LED,      NO_LED,      NO_LED,       NO_LED,           81,           82,           83,           84,           85,           86}
    }, {
        {0, 0},  {14, 0},    {28, 0},    {42,  0},    {56,  0},    {70,  0},    {84,  0},    {98,  0},    {112,  0},    {126,  0},     {140,  0},     {154,  0},     {168,  0},     {182,  0},     {196,  0},     {210,  0},      {224,  0},
        {0,16},  {14,16},    {28,16},    {42, 16},    {56, 16},    {70, 16},    {84, 16},    {98, 16},    {112, 16},    {126, 16},     {140, 16},     {154, 16},     {168, 16},     {182, 16},     {196, 16},     {210, 16},      {224, 16},
        {0,32},  {14,32},    {28,32},    {42, 32},    {56, 32},    {70, 32},    {84, 32},    {98, 32},    {112, 32},    {126, 32},     {140, 32},     {154, 32},     {168, 32},     {182, 32},     {196, 32},     {210, 32},      {224, 32},
        {0,48},  {14,48},    {28,48},    {42, 48},    {56, 48},    {70, 48},    {84, 48},    {98, 48},    {112, 48},    {126, 48},     {140, 48},     {154, 48},                    {182, 48},
        {0,64},              {28,64},    {42, 64},    {56, 64},    {70, 64},    {84, 64},    {98, 64},    {112, 64},    {126, 64},     {140, 64},     {154, 64},                    {182, 64},                    {210, 64},
        {0,80},  {14,80},    {28,80},                                           {84, 80},                                                             {154, 80},     {168, 80},     {182, 80},     {196, 80},     {210, 80},      {224, 80}
    }, {
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,             1,             1,             1,             1,             1,
       1,        1,          1,           1,           1,           1,           1,           1,            1,            1,             1,             1,                            1,
       1,                    1,           1,           1,           1,           1,           1,            1,            1,             1,             1,                            1,                            1,
       1,        1,          1,                                                  1,                                                                     1,             1,             1,             1,             1,             1
    } };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(51, 255, 255, 255);
    }
    if (host_keyboard_led_state().scroll_lock) {
        rgb_matrix_set_color(15, 255, 255, 255);
    }
    return true;
}

#endif
