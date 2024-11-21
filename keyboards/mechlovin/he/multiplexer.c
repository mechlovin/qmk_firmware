/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include "quantum.h"
#include "multiplexer.h"

const pin_t mux_pins[MUXES] = MUX_PINS;
const pin_t mux_selector_pins[MUX_SELECTOR_BITS] = MUX_SELECTOR_PINS;

void multiplexer_init(void) {
    for (uint8_t i = 0; i < MUX_SELECTOR_BITS; i++) {
        pin_t pin = mux_selector_pins[i];
        setPinOutput(pin);
    }
}

bool select_mux(uint8_t channel) {
    if (channel > MUX_CHANNELS) return 0;
    for (uint8_t i = 0; i < MUX_SELECTOR_BITS; i++) {
        writePin(mux_selector_pins[i], channel & (1 << i));
    }
    current_channel = channel;
    return 1;
}

const mux_t NC = {255,255}; // A coord with a Null pin (from JSON)
const mux_t mux_index[MUXES][MUX_CHANNELS] = {
    {{0,7},{0,6},{0,5},{0,4},{0,3},{0,2},{0,1},{0,0},{0,15},{0,14},{0,13},{0,12},{0,11},{0,10},   NC,{0,8}},
    {{1,7},{1,6},{1,5},{1,4},{1,3},{1,2},{1,1},{1,0},{1,15},{1,14},{1,13},{1,12},{1,11},{1,10},   NC,   NC},
    {{2,7},{2,6},{2,5},{2,4},{2,3},{2,2},{2,1},{2,0},{2,15},{2,14},{2,13},{2,12},    NC,{2,10},   NC,   NC},
    {   NC,{3,6},   NC,{3,4},{3,3},{3,2},{3,1},{3,0},{3,15},{3,14},{3,13},{3,12},{3,11},{3,10},   NC,{3,8}},
    {   NC,   NC,   NC,   NC,{4,3},{4,2},{4,1},{4,0},{4,15},{4,14},{4,13},{4,12},    NC,    NC,   NC,   NC},
};
