/* Copyright 2020 Team Mechlovin'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "rev2.h"

uint32_t layer_state_set_user(uint32_t state)
{
  // if on layer 1, turn on D2 LED, otherwise off.
    if (biton32(state) == 0) {
        writePinLow(A0);
        writePinLow(A1);
        writePinLow(A2);
    } else {
        writePinHigh(A0);
        writePinHigh(A1);
        writePinHigh(A2);
    }
  // if on layer 2, turn on D1 LED, otherwise off.
    if (biton32(state) == 1) {
        writePinHigh(A0);
        writePinLow(A1);
        writePinLow(A2);
    } else {
        writePinHigh(A0);
        writePinHigh(A1);
        writePinHigh(A2);
    }

  // if on layer 3, turn on D0 LED, otherwise off.
    if (biton32(state) == 2) {
        writePinLow(A0);
        writePinHigh(A1);
        writePinLow(A2);
    } else {
        writePinHigh(A0);
        writePinHigh(A1);
        writePinHigh(A2);
    }

    return state;
}
