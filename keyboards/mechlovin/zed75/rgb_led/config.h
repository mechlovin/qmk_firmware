/*
Copyright 2022 Team Mechlovin

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

#ifdef RGB_MATRIX_ENABLE
#    define IS31FL3741_I2C_ADDRESS_1 IS31FL3741_I2C_ADDRESS_SDA
#    define RGB_MATRIX_DISABLE_KEYCODES
#    define I2C_DRIVER I2CD2
#    define I2C1_SCL_PIN B10
#    define I2C1_SDA_PIN B11
#    define I2C1_CLOCK_SPEED  400000
#    define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#endif

#ifdef RGBLIGHT_ENABLE
#    define WS2812_PWM_DRIVER PWMD3  // default: PWMD2
#    define WS2812_PWM_CHANNEL 2  // default: 2
#    define WS2812_PWM_PAL_MODE 2  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
//#    define WS2812_PWM_COMPLEMENTARY_OUTPUT // Define for a complementary timer output (TIMx_CHyN); omit for a normal timer output (TIMx_CHy).
#define WS2812_PWM_DMA_STREAM  STM32_DMA1_STREAM3
#define WS2812_PWM_DMA_CHANNEL 3
#endif
