/*
Copyright 2020 Team Mechlovin

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
#define VENDOR_ID    0x4D4C
#define PRODUCT_ID   0x6500
#define DEVICE_VER   0x0001
#define MANUFACTURER Team Mechlovin
#define PRODUCT      Hannah65

#define MATRIX_ROWS 5
#define MATRIX_COLS 15

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
#define MATRIX_ROW_PINS { A4, A5, A3, A2, A1 }
#define MATRIX_COL_PINS { B11, B10, B2, B1, B0, A7, A6, A0, C15, B4, B5, B3, C13, C14, A13 }

#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN B8
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 3

#define BACKLIGHT_LEVELS 3
