/* Copyright 2023 Mechlovin'
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
    AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;
   //JTAG-DP Disabled and SW-DP Enabled    
   AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}

void led_init_ports(void) {
  gpio_set_pin_output(B12);
  gpio_set_pin_output(A14);
  gpio_set_pin_output(A13);
  gpio_set_pin_output(A10);
  gpio_set_pin_output(A9);

}


layer_state_t layer_state_set_user(layer_state_t state)
{
  // if on layer 0, turn on B12 LED, otherwise off.
    if (get_highest_layer(state) == 0) {
        gpio_write_pin_high(B12);
    } else {
        gpio_write_pin_low(B12);
    }
  // if on layer 2, turn on A14 LED, otherwise off.
    if (get_highest_layer(state) == 1) {
        gpio_write_pin_high(A14);
    } else {
        gpio_write_pin_low(A14);
    }

  // if on layer 3, turn on A13 LED, otherwise off.
    if (get_highest_layer(state) == 2   ) {
        gpio_write_pin_high(A13);
    } else {
        gpio_write_pin_low(A13);
    }

  // if on layer 3, turn on A10 LED, otherwise off.
    if (get_highest_layer(state) == 3   ) {
        gpio_write_pin_high(A9);
    } else {
        gpio_write_pin_low(A9);
    }

  // if on layer 3, turn on A9 LED, otherwise off.
    if (get_highest_layer(state) == 4   ) {
        gpio_write_pin_high(A10);
    } else {
        gpio_write_pin_low(A10);
    }

    return state;
}
