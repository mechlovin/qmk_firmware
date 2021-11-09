/*
Copyright 2020 Evy Dekkers

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

RGB_MATRIX_EFFECT(artisan_esc)
RGB_MATRIX_EFFECT(artisan_f13)
RGB_MATRIX_EFFECT(artisan_nav)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool artisan_esc(effect_params_t* params) {
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min ; i < 42; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }
    for (uint8_t i = 18 ; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool artisan_f13(effect_params_t* params) {
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min ; i < 42; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }
    for (uint8_t i = 18 ; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color(14, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

static bool artisan_nav(effect_params_t* params) {
    HSV hsv = rgb_matrix_config.hsv;
    RGB rgb = hsv_to_rgb(hsv);
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min ; i < 42; i++) {
        rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
    }
    for (uint8_t i = 18 ; i < led_max; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    for (uint8_t i = 15 ; i < 18; i++) {
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
