/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#define HAL_USE_ADC TRUE

#ifdef RGB_MATRIX_ENABLE
#    define HAL_USE_I2C TRUE
#endif

#include_next <halconf.h>