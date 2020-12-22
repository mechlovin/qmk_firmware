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
    {0, C5_1},
    {0, C5_2},
    {0, C5_3},
    {0, C5_7},
    {0, C5_12},
    {0, C5_13},
    {0, C5_14},
}
;

void led_matrix_indicators_kb(void) {
        if (host_keyboard_led_state().caps_lock) {
            led_matrix_set_index_value(4, 255);
        }
}

#endif