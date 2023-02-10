/*
Copyright 2022 Mechlovin'

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "wearhaus66.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {9,          8,     NO_LED,           7,     NO_LED,          6,     NO_LED,          5,     NO_LED,          4,      NO_LED,         3,            2,          1,         0},
  {10,    NO_LED,     NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,       23},
  {11,    NO_LED,     NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,       22},
  {12,        13,     NO_LED,          14,     NO_LED,         15,     NO_LED,         16,     NO_LED,         17,      NO_LED,         18,          19,          20,       21},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,   NO_LED}
}, {
  //LED Index to Physical Positon
  {0,0},  {14,0},    {28,0},      {42,0},     {56,0},     {67,0},     {70,0},     {84,0},     {98,0},    {112,0},    {126,0},     {140,0},     {154,0},     {168,0},     {182,0},     {196,0},    {210,0},     {224,0},
  {224,13},          {196,13},                {182,13},               {154,13},               {112,13},                           {84,13}
}, {
      1,       1,         1,           1,          1,          1,          1,          1,          1,          1,           1,          1,           1,           1,           1,           1,          1,           1,
      1,                  1,                       1,                      1,                      1,                                   1,
} };
#endif

void keyboard_post_init_kb(void) {
  setPinOutput(B7);
  setPinOutput(B4);

  writePin(B7, 0);
  writePin(B4, 0);
}