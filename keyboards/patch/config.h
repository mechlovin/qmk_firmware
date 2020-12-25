/*
Copyright 2020 Mechlovin

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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0x4C4D
#define PRODUCT_ID   0x0108
#define DEVICE_VER   0x0001
#define MANUFACTURER Mechlovin
#define PRODUCT      Patch

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B12, B13, B14, B15, A8, A9 }
#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A5, A4, A3, A1, A2, B7, B6, B5, B4, B3, A15, A14 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

//#define LED_NUM_LOCK_PIN B0
#define LED_CAPS_LOCK_PIN C13
//#define LED_SCROLL_LOCK_PIN B2
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

#define BACKLIGHT_PIN B8
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_PWM_CHANNEL 3

#define BACKLIGHT_LEVELS 5
