/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include "scanfunctions.h"
#include "analog.h"
#include "multiplexer.h"

/* Record the resting ADC level of every connected key (called with all keys
 * released). Averages several passes so a single noisy reading can't leave a
 * key with a wrong rest (which would make it read as always-pressed / unable to
 * press). matrix_scan_custom then measures travel as the distance from it. */
#define SENSOR_REST_PASSES 8
void         get_sensor_offsets(void) {
    static uint32_t acc[MATRIX_ROWS][MATRIX_COLS];
    memset(acc, 0, sizeof(acc));

    for (uint8_t pass = 0; pass < SENSOR_REST_PASSES; pass++) {
        for (uint8_t channel = 0; channel < MUX_CHANNELS; channel++) {
            uint8_t channel_greycoded = (channel >> 1) ^ channel;
            select_mux(channel_greycoded);
            for (uint8_t mux = 0; mux < MUXES; mux++) {
                uint8_t current_row = mux_index[mux][channel_greycoded].row;
                uint8_t current_col = mux_index[mux][channel_greycoded].col;
                if (current_row == 255 || current_col == 255) continue;
                acc[current_row][current_col] += analogReadPin(mux_pins[mux]);
            }
        }
    }

    for (uint8_t row = 0; row < MATRIX_ROWS; row++)
        for (uint8_t col = 0; col < MATRIX_COLS; col++)
            keys[row][col].rest = acc[row][col] / SENSOR_REST_PASSES;
}

static void update_extremum(analog_key_t *key)               { key->extremum = key->value; }
static void register_key(matrix_row_t *row, uint8_t col)     { *row |=  (1 << col); }
static void deregister_key(matrix_row_t *row, uint8_t col)   { *row &= ~(1 << col); }

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t actuation, uint8_t release_hysteresis) {
    if (*current_row & (1 << current_col)) {
        if (key->value < (actuation > release_hysteresis ? actuation - release_hysteresis : 0)) {
            deregister_key(current_row, current_col);
        }
    } else {
        if (key->value > actuation) {
            register_key(current_row, current_col);
        }
    }
}

/* Rapid-trigger core shared by the dynamic and continuous-dynamic modes.
 * `extremum` is the travel reversal point: while held it tracks the deepest
 * point and releases after a `release_sens` upstroke; while released it tracks
 * the shallowest point and presses after a `press_sens` downstroke. (Polarity-
 * agnostic — value is already |raw - rest|, so it rises on every press.) */
static void rapid_trigger_track(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t press_sens, uint8_t release_sens) {
    if (*current_row & (1 << current_col)) {
        if (key->value > key->extremum) {
            update_extremum(key);
        } else if (key->value < key->extremum - release_sens) {
            deregister_key(current_row, current_col);
            update_extremum(key);
        }
    } else {
        if (key->value < key->extremum) {
            update_extremum(key);
        } else if (key->value > key->extremum + press_sens) {
            register_key(current_row, current_col);
            update_extremum(key);
        }
    }
}

/* Dynamic actuation: the FIRST downstroke registers right AT the actuation point;
 * rapid trigger (press_sens / release_sens) then governs release + re-press only
 * WITHIN the actuated zone. Bug fixed: the initial press used to also require
 * extremum + press_sens, so you had to push ~press_sens DEEPER than the actuation
 * point before it typed. Below the point the key is forced released and extremum is
 * pinned to the live (sub-actuation) level — extremum <= actuation then marks "just
 * crossed up from rest" so the next upstroke re-arms the at-actuation press. */
void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t actuation, uint8_t press_sens, uint8_t release_sens) {
    if (key->value > actuation) {
        if (!(*current_row & (1 << current_col)) && key->extremum <= actuation) {
            register_key(current_row, current_col);
            update_extremum(key);
        } else {
            rapid_trigger_track(current_row, current_col, key, press_sens, release_sens);
        }
    } else {
        deregister_key(current_row, current_col);
        update_extremum(key);
    }
}

/* Continuous rapid trigger: once the actuation point is first crossed, tracking
 * stays armed through the whole stroke until the key returns fully to rest. */
void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key, uint8_t actuation, uint8_t press_sens, uint8_t release_sens) {
    if (key->continuous_dynamic_actuation) {
        rapid_trigger_track(current_row, current_col, key, press_sens, release_sens);
        if (key->value == 0) {
            deregister_key(current_row, current_col);
            update_extremum(key);
            key->continuous_dynamic_actuation = false;
        }
    } else if (key->value > actuation) {
        register_key(current_row, current_col);
        update_extremum(key);
        key->continuous_dynamic_actuation = true;
    }
}