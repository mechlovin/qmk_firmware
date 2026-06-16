/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include_next <mcuconf.h>

/* COM pins A4/A5/A6/A7/B2 are all ADC2 inputs on the STM32G431 */
#undef STM32_ADC_USE_ADC2
#define STM32_ADC_USE_ADC2 TRUE

/* IS31FL3741 RGB driver sits on I2C1 (SCL A15 / SDA B7) */
#ifdef RGB_MATRIX_ENABLE
#    undef STM32_I2C_USE_I2C1
#    define STM32_I2C_USE_I2C1 TRUE
#endif