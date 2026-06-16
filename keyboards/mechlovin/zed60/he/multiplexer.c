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
    return 1;
}

static const mux_t NC = {255,255}; // A coord with a Null pin (not connected)

/* mux_index[ic][channel] = { row, col } of the switch wired to that 74HC4067
 * channel.  Wiring convention for Zed60-HE: row = IC index (IC1..IC5 -> 0..4),
 * col = channel index (I0..I15).  Channels marked NC have no switch.
 *
 *                I0     I1     I2     I3     I4     I5     I6     I7     I8     I9    I10    I11    I12    I13    I14    I15  */
const mux_t mux_index[MUXES][MUX_CHANNELS] = {
    /* IC1 r0 */ {{0, 0},{0, 1},{0, 2},{0, 3},{0, 4},{0, 5},{0, 6},{0, 7},{0, 8},{0, 9},{0,10},{0,11},{0,12},{0,13},{0,14},{0,15}},
    /* IC2 r1 */ {{1, 0},{1, 1},{1, 2},{1, 3},{1, 4},{1, 5},{1, 6},{1, 7},    NC,    NC,{1,10},{1,11},{1,12},{1,13},{1,14},{1,15}},
    /* IC3 r2 */ {{2, 0},{2, 1},{2, 2},{2, 3},{2, 4},{2, 5},{2, 6},{2, 7},    NC,    NC,{2,10},    NC,{2,12},{2,13},{2,14},{2,15}},
    /* IC4 r3 */ {{3, 0},{3, 1},{3, 2},{3, 3},{3, 4},    NC,{3, 6},    NC,{3, 8},{3, 9},{3,10},{3,11},{3,12},{3,13},{3,14},{3,15}},
    /* IC5 r4 */ {{4, 0},{4, 1},{4, 2},{4, 3},{4, 4},    NC,    NC,    NC,    NC,    NC,    NC,    NC,{4,12},{4,13},{4,14},{4,15}},
};
