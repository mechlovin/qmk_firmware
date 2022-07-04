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

#include "neon_box.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {5,         4,         3,           2,          1,          0},
  {6,         7,         8,           9,         10,         11},
  {17,        16,        15,          14,        13,         12},
  {18,        19,        20,          21,        22,         23}
}, {
  //LED Index to Physical Positon
  {224,  0},  {179,  0},  {134, 0 },  {  89, 0 },  {  45, 0},   { 0, 0},
  {  0, 21},  { 45, 21},  { 89, 21},  { 134, 21},  { 179,21},   { 224,21},
  {224, 42},  {179, 42},  {134,42 },  {  89,42 },  {  45,42},   { 0,42},
  {  0, 64},  { 45, 64},  { 89, 64},  { 134, 64},  { 179,64},   { 224,64},            
}, {
  4,          4,          4,          4,          4,          4,
  4,          1,          1,          1,          1,          4,  
  4,          1,          1,          1,          1,          4,  
  4,          4,          4,          4,          4,          4, 
} };

void rgb_matrix_indicators_user(void) {
}
#endif