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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {NO_LED,            NO_LED,      NO_LED,     NO_LED,    NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,    NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,    NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,    NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,                   NO_LED,                                    },
  {NO_LED,            NO_LED,      NO_LED,     NO_LED,    NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,                   NO_LED,                  NO_LED,           },
  {NO_LED, NO_LED,    NO_LED,                                         NO_LED,                                          NO_LED,     NO_LED,      NO_LED,                   NO_LED,     NO_LED,     NO_LED}
}, {
        {224,  0},    {196,  0},     {168,  0},     {140,  0},     {112,  0},     {84,  0},     {56,  0},     {28,  0},      {0,  0}, {28, 0},    {56, 0},    {84,  0},    {112,  0},    {140,  0},    {168,  0},    {196,  0},  {224,  0}   

}, {1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1 
      
} };
#endif

