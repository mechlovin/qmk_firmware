/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MUXES 5
//#define MUX_PINS { C2, C3, A0, A1, A2, A3 }
#define MUX_PINS { A0, A1, A2, A3, B0 }
#define MUX_SELECTOR_BITS 4
#define MUX_SELECTOR_PINS { A4, A5, A6, A7 }

#define MUX_CHANNELS ( 1 << MUX_SELECTOR_BITS )

#define EECONFIG_KB_DATA_SIZE 6

//#define DEBUG_ENABLE
#define DEBUG_MATRIX_SCAN_RATE


#define ADC_RESOLUTION 12

#define CALIBRATION_RANGE 255

