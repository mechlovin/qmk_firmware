/*
Copyright 2026 Mechlovin'
SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#define IS31FL3731_I2C_ADDRESS_1    IS31FL3731_I2C_ADDRESS_GND
#define I2C1_SCL_PIN                B6
#define I2C1_SDA_PIN                B7
#define I2C1_CLOCK_SPEED            400000
#define I2C1_DUTY_CYCLE             FAST_DUTY_CYCLE_2

/* ── WS2812 (TIM4_CH1 PWM on B6) ───────────────────────────────────────── */
#define WS2812_PWM_DRIVER           PWMD4        /* TIM4                    */
#define WS2812_PWM_CHANNEL          1            /* TIM4_CH1 → PB6          */
#define WS2812_PWM_PAL_MODE         2            /* AF push-pull (STM32F1)  */
#define WS2812_DMA_STREAM           STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL          1

#define IS31FL3731_LED_COUNT        20
#define WS2812_LED_COUNT            20

/* ── Misc ───────────────────────────────────────────────────────────────── */
#define RGB_MATRIX_DISABLE_SHARED_KEYCODES
#define EECONFIG_KB_DATA_SIZE       13

#define WEAR_LEVELING_LOGICAL_SIZE  2048
#define WEAR_LEVELING_BACKING_SIZE  4096