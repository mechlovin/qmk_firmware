/* Copyright 2020 Team Mechlovin
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

#include "rouge60.h"

#ifdef LED_MATRIX_ENABLE
#include "is31fl3731-simple.h"

const is31_led g_is31_leds[LED_DRIVER_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, C1_1},
    {0, C1_2},
    {0, C1_3},
    {0, C1_4},
    {0, C1_5},
    {0, C1_6},
    {0, C1_7},
    {0, C1_8},
    {0, C1_9},
    {0, C1_10},
    {0, C1_11},
    {0, C1_12},
    {0, C1_13},
    {0, C1_14},
    {0, C2_1},
    {0, C2_2},
    {0, C2_3},
    {0, C2_4},
    {0, C2_5},
    {0, C2_6},
    {0, C2_7},
    {0, C2_8},
    {0, C2_9},
    {0, C2_10},
    {0, C2_11},
    {0, C2_12},
    {0, C2_13},
    {0, C2_14},
    {0, C2_1},
    {0, C3_2},
    {0, C3_3},
    {0, C3_4},
    {0, C3_5},
    {0, C3_6},
    {0, C3_7},
    {0, C3_8},
    {0, C3_9},
    {0, C3_10},
    {0, C3_11},
    {0, C3_12},
    {0, C3_13},
    {0, C3_14},
    {0, C4_1},
    {0, C4_2},
    {0, C4_3},
    {0, C4_4},
    {0, C4_5},
    {0, C4_6},
    {0, C4_7},
    {0, C4_8},
    {0, C4_9},
    {0, C4_10},
    {0, C4_11},
    {0, C4_12},
    {0, C4_13},
    {0, C4_14},
    {0, C5_1},
    {0, C5_2},
    {0, C5_3},
    {0, C5_7},
    {0, C5_12},
    {0, C5_13},
    {0, C5_14},
};

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {0,          1,          2,          3,           4,           5,         6,          7,          8,          9,          10,        11,          12,           13},
  {14,        15,         16,          17,         18,          19,        20,         21,         22,         23,          24,        25,          26,           27},
  {28,        29,         30,          31,         32,          33,        34,         35,         36,         37,          38,        39,          40,           41},
  {42,        43,         44,          45,         46,          47,        48,         49,         50,         51,          52,        53,          54,           55},
  {56,        57,         58,         NO_LED,     NO_LED,      NO_LED,     59,         NO_LED,     NO_LED,     NO_LED,  NO_LED,        60,          61,           62},
}, {
  //LED Index to Physical Positon
  {  0,  0},  { 16,  0},  { 32, 0 },  { 48, 0 },  { 64, 0},   { 80, 0},   { 96, 0},   { 112, 0},  { 128, 0},  { 144, 0},  { 160, 0},  { 176, 0},    {192,  0},   {208,  0},   {216, 0},
  {220, 0},   {211, 16},  {200,16 },  {176,16 },  {160,16},   {144,16},   {128,16},   { 112,16},  { 96,16},   { 80,16},   { 64,16},   { 48,16},     {32, 16},    {16, 16},    {0,16}, 
  {  0, 32},  { 16, 32},  { 32,32 },  { 48,32 },  { 64,32},   { 80,32},   { 96,32},   { 112,32},  { 128,32},  { 144,32},  { 160,32},  { 176,32},    {192, 32},   {208, 32},   {224,48}, 
  {208, 48},  {192, 48},  {160,48 },  {144,48 },  {128,48},   {112,48},   {96,48},    { 80,48},   { 64,48},   { 48,48},   { 32,48},   { 16,48},     {8, 48},     {0, 48},     {0,48}, 
  {  0, 64},  { 16, 64},  { 32,64 },  { 48,64 },  { 64,64},   { 80,64},   { 96,64},   { 112,64},  { 144,64},  { 160,64},  { 192,64},  { 224,64},                         
}, {
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1, 
} };


void led_matrix_indicators_kb(void) {
        if (host_keyboard_led_state().caps_lock) {
            led_matrix_set_index_value(4, 255);
        }
}

#endif