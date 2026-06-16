/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "quantum.h"
#include "analog.h"
#include "multiplexer.h"
#include "scanfunctions.h"

#ifndef HE_TRAVEL_RANGE
#    define HE_TRAVEL_RANGE 400 /* ADC counts of travel that map to a full 0..255 value */
#endif

#ifndef HE_FALLBACK_NOISE
/* Deadzone (ADC counts) for UNCALIBRATED keys (cal_range == 0). The calibrated
 * path below rejects rest jitter via the per-key cal_noise band; without an
 * equivalent here an uncalibrated key (e.g. one missing from the baked maps, like
 * slash [3,11]) had ZERO noise rejection and could drift past actuation / read
 * stuck. Keep it a touch above the baked noise values (~5..13). */
#    define HE_FALLBACK_NOISE 25
#endif

analog_key_t         keys[MATRIX_ROWS][MATRIX_COLS]        = {0};

void matrix_init_custom(void) {
    multiplexer_init();

    get_sensor_offsets();
    wait_ms(100); // Let ADC reach steady state
    get_sensor_offsets();
}

static matrix_row_t previous_matrix[MATRIX_ROWS];
bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    memcpy(previous_matrix, current_matrix, sizeof(previous_matrix));
    for (uint8_t channel = 0; channel < MUX_CHANNELS; channel++) {
        uint8_t channel_greycoded = (channel >> 1) ^ channel;
        select_mux(channel_greycoded);
        for (uint8_t mux = 0; mux < MUXES; mux++) {
            uint8_t current_row = mux_index[mux][channel_greycoded].row;
            uint8_t current_col = mux_index[mux][channel_greycoded].col;

            if (current_row == 255 || current_col == 255) continue;

            analog_key_t *key = &keys[current_row][current_col];
            /* Per-key oversampling (resolution boost for weak / far-magnet keys):
             * average 1<<gain samples to cut ADC noise. gain 0 = single read. */
            uint8_t  g = g_he.gain[current_row][current_col];
            uint16_t raw;
            if (g) {
                uint8_t  n   = 1 << g;
                uint32_t acc = 0;
                for (uint8_t s = 0; s < n; s++) acc += analogReadPin(mux_pins[mux]);
                raw = (uint16_t)(acc / n);
            } else {
                raw = analogReadPin(mux_pins[mux]);
            }
            key->raw = raw;

            /* depth (key->value, 0..255) = how far the reading has moved from
             * rest, normalised to the key's travel. |raw - rest| handles either
             * magnet polarity. A calibrated key uses its OWN rest/range/noise so
             * sensors of different sensitivity all read 0 at rest and 255 fully
             * pressed; the noise band is a deadzone so jitter can't false-trigger. */
            uint16_t crange = g_he.cal_range[current_row][current_col];
            if (crange) {
                uint16_t margin = g_he.cal_noise[current_row][current_col];
                int32_t  delta  = (int32_t)raw - (int32_t)g_he.cal_rest[current_row][current_col];
                if (delta < 0) delta = -delta;
                if ((uint16_t)delta <= margin) {
                    key->value = 0;
                } else {
                    uint16_t span = (crange > margin) ? (crange - margin) : 1;
                    int32_t  eff  = delta - margin;
                    key->value = (eff >= span) ? 255 : (uint8_t)(eff * 255 / span);
                }
                /* Continuous auto-calibration: grow stored travel when a deeper
                 * press than ever seen arrives (auto-learns weak keys). */
                if (g_he.autocal && (uint16_t)delta > crange && delta < 1024)
                    g_he.cal_range[current_row][current_col] = (uint16_t)delta;
            } else {
                int32_t delta = (int32_t)raw - (int32_t)key->rest;
                if (delta < 0) delta = -delta;
                if (delta <= HE_FALLBACK_NOISE) {
                    key->value = 0;
                } else {
                    int32_t eff = delta - HE_FALLBACK_NOISE;
                    key->value = (eff >= HE_TRAVEL_RANGE) ? 255 : (uint8_t)(eff * 255 / HE_TRAVEL_RANGE);
                }
            }

            /* Feed the calibration sampler (no-op unless calibrating). */
            he_cal_sample(current_row, current_col, raw);

            /* Visualizer / calibration: keep measuring depth but don't register,
             * so pressing keys shows depth without typing. */
            if (he_output_suppressed()) {
                current_matrix[current_row] &= ~(1 << current_col);
                continue;
            }

            /* Resolve this key's actuation config (% travel -> 0..255 scale). */
            he_key_config_t *cfg = &g_he.key[current_row][current_col];
            uint8_t act = (uint16_t)cfg->actuation  * 255 / 100;
            uint8_t rp  = (uint16_t)cfg->rt_press    * 255 / 100;
            uint8_t rr  = (uint16_t)cfg->rt_release  * 255 / 100;

            if (!cfg->rt_enabled) {
                /* Static: fixed actuation point + small release hysteresis. */
                matrix_read_cols_static_actuation(&current_matrix[current_row], current_col, key, act, rr);
            } else if (cfg->rt_continuous) {
                matrix_read_cols_continuous_dynamic_actuation(&current_matrix[current_row], current_col, key, act, rp, rr);
            } else {
                matrix_read_cols_dynamic_actuation(&current_matrix[current_row], current_col, key, act, rp, rr);
            }
        }
    }
    return memcmp(previous_matrix, current_matrix, sizeof(previous_matrix)) != 0;
}