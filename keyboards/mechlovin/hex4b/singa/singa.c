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

#include "hex4b.h"
#define XX NO_LED

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  { 0,  1,  2, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX},
  {XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX},
  {XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX},
  {XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX},
  {XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX},
  {XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX, XX}
}, {
  //LED Index to Physical Positon
  {0,0},  {14,0},    {28,0}
}, {
      1,       1,         1,
} };

__attribute__((weak)) void rgb_matrix_indicators_user(void) {
        if (host_keyboard_led_state().caps_lock) {
            rgb_matrix_set_color(2, 255, 255, 255);
        }
        if (host_keyboard_led_state().num_lock) {
            rgb_matrix_set_color(1, 255, 255, 255);
        }
        if (host_keyboard_led_state().scroll_lock) {
            rgb_matrix_set_color(0, 255, 255, 255);
        }
}

#endif


#ifdef RGBLIGHT_ENABLE
// RGB LED Indicators
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_WHITE}     // Light 1 LED, starting with LED 0
);
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_numlock_layer,
    my_scroll_lock_layer
);

void keyboard_post_init_kb(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_kb(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    rgblight_set_layer_state(1, led_state.num_lock);
    rgblight_set_layer_state(2, led_state.scroll_lock);
    return true;
}
#endif