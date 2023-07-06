/*
Copyright 2022 Mechlovin'

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "analog.h"
#include "qmk_midi.h"


// Potentiometer Slider, MIDI Control
uint8_t divisor = 0;
void slider(void){
  if (divisor++) { // only run the slider function 1/256 times it's called
      return;
  }
  midi_send_cc(&midi_device, 0, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN_1) >> 3));
  midi_send_cc(&midi_device, 1, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN_1) >> 3));
  midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN_1) >> 3));
  midi_send_cc(&midi_device, 3, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN_1) >> 3));
}

void matrix_scan_kb(void) {
  slider();
}