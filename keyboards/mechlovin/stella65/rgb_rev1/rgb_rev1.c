/* Copyright 2021 Mechlovin' Studio
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

#include "rgb_rev1.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    {0, CS3_SW1,    CS2_SW1,    CS1_SW1}, //D93-K00-0
    {0, CS6_SW1,    CS5_SW1,    CS4_SW1}, //D95-K01-1
    {0, CS9_SW1,    CS8_SW1,    CS7_SW1}, //D97-K02-2
    {0, CS12_SW1,   CS11_SW1,   CS10_SW1}, //D99-K03-3
    {0, CS15_SW1,   CS14_SW1,   CS13_SW1}, //D101-K04-4
    {0, CS18_SW1,   CS17_SW1,   CS16_SW1}, //D103-K05-5
    {0, CS27_SW1,   CS26_SW1,   CS25_SW1}, //D105-K06-6
    {0, CS24_SW1,   CS23_SW1,   CS22_SW1}, //D107-K07-7
    {0, CS30_SW1,   CS29_SW1,   CS28_SW1}, //D109-K08-8
    {0, CS33_SW1,   CS32_SW1,   CS31_SW1}, //D111-K09-9
    {0, CS36_SW1,   CS35_SW1,   CS34_SW1},  //D113-K0A-10
    {0, CS39_SW1,   CS38_SW1,   CS37_SW1},  //D115-K0B-11
    {0, CS21_SW1,   CS20_SW1,   CS19_SW1},  //D117-K0C-12
    {0, CS21_SW6,   CS20_SW6,   CS19_SW6}, //D86-K0D-13
    {0, CS21_SW7,   CS20_SW7,   CS19_SW7}, //D119-K0E-14
    {0, CS3_SW2,    CS2_SW2,    CS1_SW2}, //D124-K10-15
    {0, CS6_SW2,    CS5_SW2,    CS4_SW2}, //D127-K11-16
    {0, CS9_SW2,    CS8_SW2,    CS7_SW2}, //D130-K12-17
    {0, CS12_SW2,   CS11_SW2,   CS10_SW2}, //D133-K13-18
    {0, CS15_SW2,   CS14_SW2,   CS13_SW2}, //D135-K14-19
    {0, CS18_SW2,   CS17_SW2,   CS16_SW2}, //D137-K15-20
    {0, CS27_SW2,   CS26_SW2,   CS25_SW2}, //D139-K16-21
    {0, CS24_SW2,   CS23_SW2,   CS22_SW2}, //D142-K17-22
    {0, CS30_SW2,   CS29_SW2,   CS28_SW2}, //D144-K18-23
    {0, CS33_SW2,   CS32_SW2,   CS31_SW2}, //D146-K19-24
    {0, CS36_SW2,   CS35_SW2,   CS34_SW2},  //D148-K1A-25
    {0, CS39_SW2,   CS38_SW2,   CS37_SW2},  //D151-K1B-26
    {0, CS21_SW2,   CS20_SW2,   CS19_SW2},  //D154-K1C-27
    {0, CS3_SW6,    CS2_SW6,    CS1_SW6}, //D159-K1D-28
    {0, CS9_SW7,    CS8_SW7,    CS7_SW7}, //D180-K1E-29
    {0, CS3_SW3,    CS2_SW3,    CS1_SW3}, //D166-K20-30
    {0, CS6_SW3,    CS5_SW3,    CS4_SW3}, //D167-K21-31
    {0, CS9_SW3,    CS8_SW3,    CS7_SW3}, //D168-K22-32
    {0, CS12_SW3,   CS11_SW3,   CS10_SW3}, //D169-K23-33
    {0, CS15_SW3,   CS14_SW3,   CS13_SW3}, //D170-K24-34
    {0, CS18_SW3,   CS17_SW3,   CS16_SW3}, //D171-K25-35
    {0, CS27_SW3,   CS26_SW3,   CS25_SW3}, //D172-K26-36
    {0, CS24_SW3,   CS23_SW3,   CS22_SW3}, //D173-K27-37
    {0, CS30_SW3,   CS29_SW3,   CS28_SW3}, //D174-K28-38
    {0, CS33_SW3,   CS32_SW3,   CS31_SW3}, //D175-K29-39
    {0, CS36_SW3,   CS35_SW3,   CS34_SW3},  //D176-K2A-40
    {0, CS39_SW3,   CS38_SW3,   CS37_SW3},  //D177-K2B-41
    {0, CS21_SW3,   CS20_SW3,   CS19_SW3},  //D87-K2C-42
    {0, CS6_SW6,    CS5_SW6,    CS4_SW6}, //D179-K2D-43
    {0, CS18_SW7,   CS17_SW7,   CS16_SW7}, //D42-K2E-44
    {0, CS3_SW4,    CS2_SW4,    CS1_SW4}, //D186-K30-45
    {0, CS6_SW4,    CS5_SW4,    CS4_SW4}, //D128-K31-46
    {0, CS9_SW4,    CS8_SW4,    CS7_SW4}, //D131-K32-47
    {0, CS12_SW4,   CS11_SW4,   CS10_SW4}, //D134-K33-48
    {0, CS15_SW4,   CS14_SW4,   CS13_SW4}, //D136-K34-49
    {0, CS18_SW4,   CS17_SW4,   CS16_SW4}, //D138-K35-50
    {0, CS27_SW4,   CS26_SW4,   CS25_SW4}, //D140-K36-51
    {0, CS24_SW4,   CS23_SW4,   CS22_SW4}, //D143-K37-52
    {0, CS30_SW4,   CS29_SW4,   CS28_SW4}, //D145-K38-53
    {0, CS33_SW4,   CS32_SW4,   CS31_SW4}, //D147-K39-54
    {0, CS36_SW4,   CS35_SW4,   CS34_SW4},  //D49-K3A-55
    {0, CS39_SW4,   CS38_SW4,   CS37_SW4},  //D152-K3B-56
    {0, CS21_SW4,   CS20_SW4,   CS19_SW4},  //D155-K3C-57
    {0, CS12_SW6,   CS11_SW6,   CS10_SW6}, //D160-K3D-58
    {0, CS12_SW7,   CS11_SW7,   CS10_SW7}, //D47-K3E-59
    {0, CS3_SW5,    CS2_SW5,    CS1_SW5}, //D126-K40-60
    {0, CS6_SW5,    CS5_SW5,    CS4_SW5}, //D129-K41-61
    {0, CS9_SW5,    CS8_SW5,    CS7_SW5}, //D132-K42-62
    {0, CS15_SW5,   CS14_SW5,   CS13_SW5}, //D28-K44-63
    {0, CS27_SW5,   CS26_SW5,   CS25_SW5}, //D188-K46-64
    {0, CS30_SW5,   CS29_SW5,   CS28_SW5}, //D37-K48-65
    {0, CS36_SW5,   CS35_SW5,   CS34_SW5},  //D150-K4A-66
    {0, CS39_SW5,   CS38_SW5,   CS37_SW5},  //D153-K4B-67
    {0, CS21_SW5,   CS20_SW5,   CS19_SW5},  //D156-K4C-68
    {0, CS15_SW6,   CS14_SW6,   CS13_SW6}, //D161-K4D-69
    {0, CS15_SW7,   CS14_SW7,   CS13_SW7}, //D162-K5E-70
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,           1,           2,           3,           4,           5,           6,           7,           8,           9,           10,           11,           12,           13,           14},
        {15,         16,          17,          18,          19,          20,          21,          22,          23,          24,           25,           26,           27,           28,           29},
        {30,         31,          32,          33,          34,          35,          36,          37,          38,          39,           40,           41,           42,           43,           44},
        {43,         46,          47,          48,          49,          50,          51,          52,          53,          54,           55,           56,           57,           58,           59},
        {60,         61,          62,                       63,                       64,                       65,                        66,           67,           68,           69,           70}      
    }, {
  //LED Index to Physical Positon

  {  0,  0},  { 16,  0},  { 32, 0 },  { 48, 0 },  { 64, 0},   { 80, 0},   { 96, 0},   { 112, 0},  { 128, 0},  { 144, 0},  { 160, 0},  { 176, 0},    {192,  0},   {208,  0},   {208, 16},   {224, 0},
  {  0, 16},  { 16, 16},  { 32,16 },  { 48,16 },  { 64,16},   { 80,16},   { 96,16},   { 112,16},  { 128,16},  { 144,16},  { 160,16},  { 176,16},    {192, 16},   {192, 32},   {224,16},
  {  0, 32},  { 16, 32},  { 32,32 },  { 48,32 },  { 64,32},   { 80,32},   { 96,32},   { 112,32},  { 128,32},  { 144,32},  { 160,32},  { 176,32},    {208, 32},   {224,32},
  {  0, 48},  { 16, 48},  { 32,48 },  { 48,48 },  { 64,48},   { 80,48},   { 96,48},   { 112,48},  { 128,48},  { 144,48},  { 160,48},  { 176,48},    {192, 48},   {208, 48},   {224,48},
  {  0, 64},  { 16, 64},  { 32,64 },              { 64,64},               { 96,64},               { 128,64},              { 160,64},  { 176,64},    {192, 64},   {208, 64},   {224,64},
}, {
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,                      1,                      1,                      1,                      1,          1,            1,           1,           1,          
} };



__attribute__((weak))
void rgb_matrix_indicators_user(void) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(51, 255, 255, 255);
        }
        if (host_keyboard_led_state().scroll_lock) {
            rgb_matrix_set_color(30, 255, 255, 255);
        }
}


void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif

