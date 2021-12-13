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
#include QMK_KEYBOARD_H
#ifdef WPM_ENABLE
#include <stdio.h>
char wpm_str[10];
# define WPM_LOWER 20 // above this wpm value typing animation to trigger
#endif 

// OLED animation
#include "lib/wave.c"
#include "lib/logo.c"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
     KC_SPC, KC_ESC,  KC_1, KC_2,    KC_3, KC_4,   KC_5, KC_6,            KC_7, KC_8,   KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
     KC_SPC, KC_TAB,  KC_Q, KC_W,    KC_E, KC_R,   KC_T,                  KC_Y, KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_SLSH,
     KC_SPC, KC_CAPS, KC_A, KC_S,    KC_D, KC_F,   KC_G,                  KC_H, KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
             KC_LSFT,       KC_Z,    KC_X, KC_C,   KC_V, KC_B,            KC_N, KC_M,   KC_COMM, KC_DOT,  KC_BSLS, MO(1),   KC_RSFT, KC_UP,
             KC_LCTL,       KC_LALT,       KC_SPC,       MO(2),                 KC_SPC,          KC_RALT,                            KC_RCTL ),
    [1] = LAYOUT_all(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                  KC_TRNS,          KC_TRNS,                            KC_TRNS ),
    [2] = LAYOUT_all(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                  KC_TRNS,          KC_TRNS,                            KC_TRNS ),
    [3] = LAYOUT_all(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
              KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,                  KC_TRNS,          KC_TRNS,                            KC_TRNS ),

};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_LEFT);
        } else {
            tap_code(KC_RGHT);
        }
    }
    else if (index == 2) {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
    return true;
}

  #endif


#ifdef OLED_ENABLE
    uint16_t startup_timer; 

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        startup_timer = timer_read();
        wave_timer = timer_read();

        return rotation;
    }

            
    static void render_rgb_effect(void) {
        switch (rgblight_get_mode()) {
            case 0:
                oled_write_ln(PSTR("OFF"), false);
                break;
            case 1:
                oled_write_ln(PSTR("SOLID"), false);
                break;
            case 2:
                oled_write_ln(PSTR("BRT1"), false);
                break;
            case 3:
                oled_write_ln(PSTR("BRT2"), false);
                break;
            case 4:
                oled_write_ln(PSTR("BRT3"), false);
                break;
            case 5:
                oled_write_ln(PSTR("BRT4"), false);
                break;
            case 6:
                oled_write_ln(PSTR("Mood1"), false);
                break;
            case 7:
                oled_write_ln(PSTR("Mood2"), false);
                break;
            case 8:
                oled_write_ln(PSTR("Mood3"), false);
                break;
            case 9:
                oled_write_ln(PSTR("Swirl1"), false);
                break;
            case 10:
                oled_write_ln(PSTR("Swirl2"), false);
                break;
            case 11:
                oled_write_ln(PSTR("Swirl3"), false);
                break;
            case 12:
                oled_write_ln(PSTR("Swirl4"), false);
                break;
            case 13:
                oled_write_ln(PSTR("Swirl5"), false);
                break;
            case 14:
                oled_write_ln(PSTR("Swirl6"), false);
                break;
            case 15:
                oled_write_ln(PSTR("SNAKE1"), false);
                break;
            case 16:
                oled_write_ln(PSTR("SNAKE2"), false);
                break;
            case 17:
                oled_write_ln(PSTR("SNAKE3"), false);
                break;
            case 18:
                oled_write_ln(PSTR("SNAKE4"), false);
                break;
            case 19:
                oled_write_ln(PSTR("SNAKE5"), false);
                break;
            case 20:
                oled_write_ln(PSTR("SNAKE6"), false);
                break;
            case 21:
                oled_write_ln(PSTR("Knight1"), false);
                break;
            case 22:
                oled_write_ln(PSTR("Knight2"), false);
                break;
            case 23:
                oled_write_ln(PSTR("Knight3"), false);
                break;
            case 24:
                oled_write_ln(PSTR("Xmas"), false);
                break;
            case 25:
                oled_write_ln(PSTR("Gradient1"), false);
                break;
            case 26:
                oled_write_ln(PSTR("Gradient2"), false);
                break;
            case 27:
                oled_write_ln(PSTR("Gradient3"), false);
                break;
            case 28:
                oled_write_ln(PSTR("Gradient4"), false);
                break;
            case 29:
                oled_write_ln(PSTR("Gradient5"), false);
                break;
            case 30:
                oled_write_ln(PSTR("Gradient6"), false);
                break;
            case 31:
                oled_write_ln(PSTR("Gradient7"), false);
                break;
            case 32:
                oled_write_ln(PSTR("Gradient8"), false);
                break;
            case 33:
                oled_write_ln(PSTR("Gradient9"), false);
                break;
            case 34:
                oled_write_ln(PSTR("Gradient10"), false);
                break;
            case 35:
                oled_write_ln(PSTR("TEST"), false);
                break;
            case 36:
                oled_write_ln(PSTR("Alternate"), false);
                break;
            default:
                oled_write_ln(PSTR("X"), false);
        }
    }

    static void render_layer_number(void) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("0"), false);
                break;
            case 1:
                oled_write_P(PSTR("1"), false);
                break;
            case 2:
                oled_write_P(PSTR("2"), false);
                break;
            case 3:
                oled_write_P(PSTR("3"), false);
                break;
            case 4:
                oled_write_P(PSTR("4"), false);
                break;
            case 5:
                oled_write_P(PSTR("5"), false);
                break;
            case 6:
                oled_write_P(PSTR("6"), false);
                break;
            case 7:
                oled_write_P(PSTR("7"), false);
                break;
            default:
                oled_write_P(PSTR("X"), false);
        }
    }

    bool oled_task_user(void) {
        static bool finished_logo = false;

        if ((timer_elapsed(startup_timer) < 2000) && !finished_logo) {
            render_logo();
        } else {
            finished_logo = true;
            led_t led_usb_state = host_keyboard_led_state();
            oled_set_cursor(0, 0);
            oled_write_P(PSTR("____ADELAIS REV.4____"), false);

            // sleep if it has been long enough since we last got a char
            //if (timer_elapsed32(wave_sleep) > OLED_TIMEOUT) {
            //    oled_off();
            //} else {
            //    oled_on();
            //}
            // time for the next frame?
            if (timer_elapsed(wave_timer) > FRAME_TIMEOUT) {
                wave_timer = timer_read();
                render_frame();
            }

            oled_set_cursor(0, 2);
            oled_write_P(PSTR("Layer:"), false);
            render_layer_number();

        #ifdef WPM_ENABLE
            oled_write_P(PSTR(" WPM:"), false);
            oled_write(get_u8_str(get_current_wpm(), '0'), false);

        #endif

            oled_set_cursor(0, 3);
            oled_write_P(led_usb_state.caps_lock ? PSTR("C ") : PSTR(""), false);
            oled_write_P(led_usb_state.scroll_lock ? PSTR("S ") : PSTR(""), false);
            oled_write_P(led_usb_state.num_lock ? PSTR("N ") : PSTR(""), false);
        
//            oled_set_cursor(0, 3);
            oled_write_P(PSTR("RGB:"), false);
            render_rgb_effect();


        }

        return true;
    }
#endif