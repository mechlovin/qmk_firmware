/* Copyright 2022 Mechlovin'
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

#define LT1_CAP     LT(1, KC_CAPS)

/* LAYOUT_all — every connected cell gets a keycode ("full connection"), so the
 * configurator can offer all physical layouts and grey out the keys not in the
 * selected one (VIA layout-options style). Overlapping variant cells:
 *   Backspace : KC_BSPC[0,9]=2u   vs  KC_BSPC[0,10]+KC_DEL[0,8]=split
 *   RightShift: KC_RSFT[3,9]=full vs  KC_RSFT[3,10]+TO(1)[3,8]=split
 *   Space     : KC_SPC[4,3]=6.25u vs  KC_SPC[4,4]=7u
 *   RightMods : [4,12]=RAlt(6.25u only); [4,13]/[4,14] are remapped per layout in
 *               he.c (via_set_layout_options_kb): 6.25u=RGui/Menu, 7u=RAlt/RGui. */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        LT1_CAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_NO, KC_RSFT, TO(1),   KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI, KC_APP,  KC_RCTL
    ),
    [1] = LAYOUT_all(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PENT,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

};
