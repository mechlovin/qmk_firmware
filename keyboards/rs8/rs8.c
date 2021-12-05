// Copyright %(YEAR)s %(YOUR_NAME)s (@%(USER_NAME)s)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rs8.h"

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    writePinLow(C13);
}
