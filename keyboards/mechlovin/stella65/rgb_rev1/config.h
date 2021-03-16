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
#define VENDOR_ID    0x4D4C // ML
#define PRODUCT_ID   0xC601 // Commissions 60v1
#define DEVICE_VER   0x0001
#define MANUFACTURER Mechlovin Studio
#define PRODUCT      Setlla65 Rev1

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

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B3
    #define RGBLED_NUM 9
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
    #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
// /*== or choose animations ==*/
     #define RGBLIGHT_EFFECT_BREATHING
     #define RGBLIGHT_EFFECT_RAINBOW_MOOD
     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
     #define RGBLIGHT_EFFECT_SNAKE
//     #define RGBLIGHT_EFFECT_KNIGHT
     #define RGBLIGHT_EFFECT_CHRISTMAS
//     #define RGBLIGHT_EFFECT_STATIC_GRADIENT
     #define RGBLIGHT_EFFECT_RGB_TEST
     #define RGBLIGHT_EFFECT_ALTERNATING
#endif

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
#define DISABLE_RGB_MATRIX_KEYPRESSES
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DRIVER_ADDR_1 0b0110010
#define DRIVER_ADDR_2 0b0110010
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 71
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#endif