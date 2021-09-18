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
#define VENDOR_ID    0x4D4C // "ML"
#define DEVICE_VER   0x0001
#define MANUFACTURER Team.Mechlovin
#define PRODUCT_ID   0xAD03
#define PRODUCT      Adelais

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B1, A0, C13, A1, A2}
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B11, B10, B8, B4, B5, B3, C14, A15 }
#define UNUSED_PINS

#define BACKLIGHT_PIN B0
#define BACKLIGHT_BREATHING
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL 3

#define RGB_DI_PIN A7
#define RGBLED_NUM 23
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_ANIMATIONS


/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define LED_NUM_LOCK_PIN C15
#define LED_CAPS_LOCK_PIN B2
#define LED_SCROLL_LOCK_PIN B9

#define ENCODERS_PAD_A { A6, A4, B7 }
#define ENCODERS_PAD_B { A5, A3, B6 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 10