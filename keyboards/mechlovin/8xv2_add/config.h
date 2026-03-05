/*
Copyright 2026 Mechlovin'
SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

/* ── IS31FL3731 (I2C) ───────────────────────────────────────────────────── */
#define IS31FL3731_I2C_ADDRESS_1    IS31FL3731_I2C_ADDRESS_GND
#define I2C1_SCL_PIN                B8
#define I2C1_SDA_PIN                B9
#define I2C1_CLOCK_SPEED            400000
#define I2C1_DUTY_CYCLE             FAST_DUTY_CYCLE_2

/* ── WS2812 (SPI) ───────────────────────────────────────────────────────── */
#define WS2812_SPI_DRIVER           SPID2
#define WS2812_SPI_USE_CIRCULAR_BUFFER

#define IS31FL3731_LED_COUNT        20
#define WS2812_LED_COUNT            20

/* ── Misc ───────────────────────────────────────────────────────────────── */
#define RGB_MATRIX_DISABLE_SHARED_KEYCODES
#define EECONFIG_KB_DATA_SIZE       12

#define WEAR_LEVELING_LOGICAL_SIZE  2048
#define WEAR_LEVELING_BACKING_SIZE  4096