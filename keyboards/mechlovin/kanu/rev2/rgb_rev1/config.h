/* Copyright 2021 Mechlovin' Studio

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
#define PRODUCT_ID   0x434E
#define DEVICE_VER   0x0001
#define MANUFACTURER Mechlovin Studio
#define PRODUCT      Kanu Rev. 2

/* key matrix size */
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
#define MATRIX_ROW_PINS { C4, C5, C6, C7, B2 }
#define MATRIX_COL_PINS { B4, C3, C2, D7, D6, D5, D4, A0, A1, A2, A3, A4, A5, A6, A7 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#ifdef RGB_MATRIX_ENABLE
//rgb matrix setting
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b0110000 AD <-> GND
// 0b0110011 AD <-> VCC
// 0b0110001 AD <-> SCL
// 0b0110010 AD <-> SDA
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MAXIMUM_BRIGHTNESS 255 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#define DRIVER_ADDR_1 0b0110010
#define DRIVER_ADDR_2 0b0110010
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 79
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
  #define USB_MAX_POWER_CONSUMPTION 500
#endif