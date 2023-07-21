/* Copyright 2020 Team Mechlovin'
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

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
}

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
    {0,   CS33_SW3, CS32_SW3,   CS31_SW3}, //D93-SW2-0
    {0,   CS27_SW2, CS26_SW2,   CS25_SW2}, //D95-SW7-1
    {0,   CS33_SW4, CS32_SW4,   CS31_SW4}, //D97-SW13-2
    {0,   CS27_SW5, CS26_SW5,   CS25_SW5}, //D99-SW19-3
    {0,   CS33_SW7, CS32_SW7,   CS31_SW7}, //D101-SW24-4
    {0,   CS27_SW6, CS26_SW6,   CS25_SW6}, //D103-SW29-5
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
        {0,         1},
        {2,         3},
        {4,         5},
    }, {
        {0,  0},  {224, 0},
        {0, 32},  {224, 32},  
        {0, 64},  {224, 64},
    }, {
       1,        1,          1,           1,           1,           1,
    }
};

#endif
