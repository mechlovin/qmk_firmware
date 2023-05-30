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

#pragma once

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 14

/* Custom matrix pins and port select array */
#define MATRIX_ROW_PINS \
    { A15, B3, B4, B5, B1 }
#define MATRIX_COL_CHANNELS \
    { 2, 1, 0, 3, 5, 7, 6, 4}
#define MUX_SEL_PINS \
    { A0, A1, A2 }

/* Hardware peripherals pins */
#define APLEX_EN_PIN_0 A3
#define APLEX_EN_PIN_1 A6
#define DISCHARGE_PIN  A5
#define ANALOG_PORT A4

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
//#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define DEFAULT_ACTUATION_LEVEL 450
#define DEFAULT_RELEASE_LEVEL 350

#define DISCHARGE_TIME 10

//#define LED_NUM_LOCK_PIN B0
#define LED_CAPS_LOCK_PIN  A8
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4