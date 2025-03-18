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
#include QMK_KEYBOARD_H

enum custom_keycodes {
    PWM_UP = SAFE_RANGE,
    PWM_DOWN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_3,  PWM_UP,    PWM_DOWN,    KC_3
    ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t pwm_duty = 128;  // Giá trị ban đầu (0 - 255)

    if (record->event.pressed) {
        switch (keycode) {
            case PWM_UP:
                if (pwm_duty < 255) pwm_duty += 25;
                OCR3A = pwm_duty;
                uprintf("PWM tăng: %d\n", pwm_duty);
                return false;

            case PWM_DOWN:
                if (pwm_duty > 0) pwm_duty -= 25;
                OCR3A = pwm_duty;
                uprintf("PWM giảm: %d\n", pwm_duty);
                return false;
        }
    }
    return true;
}