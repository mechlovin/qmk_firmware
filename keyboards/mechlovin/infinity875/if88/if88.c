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

#include "infinity875.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {0,          1,         2,           3,          4,          6,          7,          8,          9,         10,         11,          12,          13,          14,          15,         16,         17},
  {26,    NO_LED,        25,      NO_LED,         24,     NO_LED,         23,     NO_LED,         22,     NO_LED,      NO_LED,         21,      NO_LED,          20,          19,     NO_LED,         18},
  {27,    NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,         41},
  {28,    NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,         40},
  {29,    NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,         39},
  {30,    NO_LED,        31,      NO_LED,         32,     NO_LED,     NO_LED,         33,     NO_LED,         34,      NO_LED,         35,          36,      NO_LED,          37,     NO_LED,         38}
}, {
  //LED Index to Physical Positon
  {0,0},  {14,0},    {28,0},      {42,0},     {56,0},     {65,0},     {70,0},     {84,0},     {98,0},    {112,0},    {126,0},     {140,0},     {154,0},     {168,0},     {182,0},     {196,0},    {210,0},     {224,0},
  {0,1},             {28,1},                  {56,1},                 {84,1},                {112,1},                             {154,1},                  {182,1},     {196,1},                 {224,1},
  {0,2},                                                                                                                                                                                          {224,2},
  {0,3},                                                                                                                                                                                          {224,3},
  {0,4},                                                                                                                                                                                          {224,4},
  {0,5},             {28,5},                  {56,5},                             {84,5},                {112,5},                 {154,5},     {182,5},                  {196,5},                 {224,5},
}, {
      1,       1,         1,           1,          1,          1,          1,          1,          1,          1,           1,          1,           1,           1,           1,           1,          1,           1,
      1,                  1,                       1,                      1,                      1,                                   1,                        1,           1,                       1,
      1,                                                                                                                                                                                                1,
      1,                                                                                                                                                                                                1,
      1,                                                                                                                                                                                                1,
      1,                  1,                       1,                                  1,                      1,                       1,           1,                        1,                       1,
} };
#endif

