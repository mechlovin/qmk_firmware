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
#define PRODUCT      Stella65 Rev1

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
#define RGB_MATRIX_DISABLE_KEYCODES
#define RGB_DI_PIN B3
    #define RGBLED_NUM 9
#define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#define RGBLIGHT_EFFECT_BREATHE_MAX	150
#define RGBLIGHT_RAINBOW_SWIRL_RANGE    150
#define RGBLIGHT_LIMIT_VAL 150
/*== all animations enable ==*/
//     #define RGBLIGHT_ANIMATIONS
// /*== or choose animations ==*/
//     #define RGBLIGHT_EFFECT_BREATHING
//     #define RGBLIGHT_EFFECT_RAINBOW_MOOD
     #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//     #define RGBLIGHT_EFFECT_SNAKE
//     #define RGBLIGHT_EFFECT_KNIGHT
//     #define RGBLIGHT_EFFECT_CHRISTMAS
//     #define RGBLIGHT_EFFECT_STATIC_GRADIENT
     #define RGBLIGHT_EFFECT_RGB_TEST
//     #define RGBLIGHT_EFFECT_ALTERNATING
//     #define RGBLIGHT_EFFECT_TWINKLE
     #define RGBLIGHT_EFFECT_STATIC_GRADIENT

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
#define RGB_MAXIMUM_BRIGHTNESS 160 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
//#define DISABLE_RGB_MATRIX_SOLID_COLOR
//#define DISABLE_RGB_MATRIX_ALPHAS_MODS	
//#define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
//#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
//#define DISABLE_RGB_MATRIX_BREATHING	
#define DISABLE_RGB_MATRIX_BAND_SAT	
#define DISABLE_RGB_MATRIX_BAND_VAL	
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT	
#define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL	
//#define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT	
//#define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL	
//#define DISABLE_RGB_MATRIX_CYCLE_ALL
//#define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
//#define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN	
//#define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
//#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN		
//#define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
//#define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL	
#define DISABLE_RGB_MATRIX_CYCLE_SPIRAL	
//#define DISABLE_RGB_MATRIX_DUAL_BEACON	
//#define DISABLE_RGB_MATRIX_RAINBOW_BEACON
//#define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS	
#define DISABLE_RGB_MATRIX_RAINDROPS	
#define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS	
//#define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#define DISABLE_RGB_MATRIX_DIGITAL_RAIN		
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE		
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE	
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS	
//#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS	
//#define DISABLE_RGB_MATRIX_SPLASH	
//#define DISABLE_RGB_MATRIX_MULTISPLASH	
//#define DISABLE_RGB_MATRIX_SOLID_SPLASH	
//#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH	
//#define DISABLE_RGB_MATRIX_SPLASH
//#define DISABLE_RGB_MATRIX_MULTISPLASH
//#define DISABLE_RGB_MATRIX_SOLID_SPLASH	
//#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH

#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL


//#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define DRIVER_ADDR_1 0b0110010
#define DRIVER_ADDR_2 0b0110010
#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 71
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#endif