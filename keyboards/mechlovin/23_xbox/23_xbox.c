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

#include "23_xbox.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {0,         1,         2,           3,          4,          5},
  {11,        10,        9,           8,          7,          6},
  {12,        13,        14,          15,         16,         17},
  {23,        22,        21,          20,         19,         18}
}, {
  //LED Index to Physical Positon
  {  0,  0},  { 45,  0},  { 89, 0 },  { 134, 0 },  { 179, 0},   { 224, 0},
  {224, 21},  { 179,21},  { 134,21},  { 89, 21 },  { 45, 21},   { 0,  21},
  {  0, 42},  { 45, 42},  { 89,42 },  { 134,42 },  { 179,42},   { 224,42},
  {224, 64},  { 179,64},  { 134,64},  { 89, 64 },  { 45, 64},   { 0,  64},                
}, {
  1,          1,          1,          1,          1,          1,
  1,          1,          1,          1,          1,          1,  
  1,          1,          1,          1,          1,          1,  
  1,          1,          1,          1,          1,          1, 
} };

void rgb_matrix_indicators_user(void) {
}
#endif