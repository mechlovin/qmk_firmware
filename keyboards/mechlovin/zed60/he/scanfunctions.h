/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once
#include "analogkeys.h"
#include <stdint.h>
#include "quantum.h"

void get_sensor_offsets(void);

/* All thresholds below are in the 0..255 "value" scale (already converted from
 * the per-key % settings by matrix_scan_custom). */
void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t actuation, uint8_t press_sens, uint8_t release_sens);

void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t actuation, uint8_t press_sens, uint8_t release_sens);

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t actuation, uint8_t release_hysteresis);