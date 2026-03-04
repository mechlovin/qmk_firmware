/*
Copyright 2026 Mechlovin'

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

#ifdef RGBLIGHT_ENABLE

#define BLOCKER_LED_COUNT 4
#define UG_LED_COUNT RGBLIGHT_LED_COUNT - BLOCKER_LED_COUNT

#define WS2812_SPI_DRIVER SPID2 // default: SPID1
#define WS2812_SPI_USE_CIRCULAR_BUFFER
#endif

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_SDA

#define RGB_MATRIX_DISABLE_SHARED_KEYCODES
#    define I2C1_SCL_PIN      B8
#    define I2C1_SDA_PIN      B9
#    define I2C1_CLOCK_SPEED  400000
#    define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

// Fixed LED index for indicators
#define CAPS_LED_INDEX 30   // ví dụ Caps Lock
#define BLOCKER_LED_INDEX 14   // ví dụ Scroll Lock

// EECONFIG data size: each indicator takes 5 bytes; there are four possible indicators.
#define EECONFIG_KB_DATA_SIZE (5*6)

#define WEAR_LEVELING_LOGICAL_SIZE 2048
#define WEAR_LEVELING_BACKING_SIZE 4096	