/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include "scanfunctions.h"
#include "analog.h"
#include "multiplexer.h"
#include "lut.h"

void         get_sensor_offsets(void) {
    uint16_t rest_adc_value = distance_to_adc(0);
    for (uint8_t channel = 0; channel < MUX_CHANNELS; channel++) {
        uint8_t channel_greycoded = (channel >> 1) ^ channel;
        select_mux(channel_greycoded);
        for (uint8_t mux = 0; mux < MUXES; mux++) {
            uint8_t current_row = mux_index[mux][channel_greycoded].row;
            uint8_t current_col = mux_index[mux][channel_greycoded].col;

            pin_t pin = mux_pins[mux];

            keys[current_row][current_col].offset = rest_adc_value - analogReadPin(pin);
        }
    }
}

void update_extremum(analog_key_t *key) {
    key->extremum = key->value;
}

void register_key(matrix_row_t *current_row, uint8_t current_col) {
    *current_row |= (1 << current_col);
}

void deregister_key(matrix_row_t *current_row, uint8_t current_col) {
    *current_row &= ~(1 << current_col);
}

void matrix_read_cols_static_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key) {
    if (*current_row & (1 << current_col)) {
        if (key->value < MAX(g_config.actuation_point - g_config.release_hysteresis, 0)) {
            deregister_key(current_row, current_col);
        }
    } else {
        if (key->value > MIN(g_config.actuation_point + g_config.press_hysteresis, 255)) {
            register_key(current_row, current_col);
        }
    }
}

/* Extremum is the highest or lowest value of the key reached
this functionality changes based on whether the key is pressed or not,
assuming your sensor value decreases when the key is pressed,
if the key is pressed, the extremum is the lowest value reached,
if the key is not pressed, the extremum is the highest value reached. */

void matrix_read_cols_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key) {
    if (key->value > g_config.actuation_point) {
        /* In DA zone? */
        if (*current_row & (1 << current_col)) {
            /* Key is pressed
            Is key still moving down? */
            if (key->value > key->extremum) {
                update_extremum(key);
            } else if (key->value < key->extremum - g_config.release_sensitivity) {
                /* Has key moved up enough to be released? */
                deregister_key(current_row, current_col);
                update_extremum(key);
            }
        } else {
            /* Key is not pressed
            Is the key still moving up? */
            if (key->value < key->extremum) {
                update_extremum(key);
            } else if (key->value > key->extremum + g_config.press_sensitivity) {
                /* Has key moved down enough to be pressed? */
                register_key(current_row, current_col);
                update_extremum(key);
            }
        }
    } else {
        /* Out of DA zone
        Always deregister key */
        deregister_key(current_row, current_col);
        if (key->value > key->extremum) {
            update_extremum(key);
        }
    }
}

void matrix_read_cols_continuous_dynamic_actuation(matrix_row_t *current_row, uint8_t current_col, analog_key_t *key) {
    if (key->continuous_dynamic_actuation) {
        if (*current_row & (1 << current_col)) {
            /* Key is pressed
            Is key still moving down? */
            if (key->value > key->extremum) {
                update_extremum(key);

            } else if (key->value < key->extremum - g_config.release_sensitivity) {
                /* Has key moved up enough to be released? */
                deregister_key(current_row, current_col);
                update_extremum(key);
            }
        } else {
            /* Key is not pressed
            Is the key still moving up? */
            if (key->value < key->extremum) {
                update_extremum(key);
            } else if (key->value > key->extremum + g_config.press_sensitivity) {
                /* Has key moved down enough to be pressed? */
                register_key(current_row, current_col);
                update_extremum(key);
            }
        }
        if (key->value == 0) {
            deregister_key(current_row, current_col);
            update_extremum(key);
            key->continuous_dynamic_actuation = false;
        }
    } else if (key->value > g_config.actuation_point) {
        register_key(current_row, current_col);
        update_extremum(key);
        key->continuous_dynamic_actuation = true;
    }
}