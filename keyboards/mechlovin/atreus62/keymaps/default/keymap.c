/* Copyright 2021 mechlovin
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
#include QMK_KEYBOARD_H

#include "enjoy.h"
#include "joystick.h"
#include "analog.h"
#include "pointing_device.h"

#define X_PIN B4
#define Y_PIN D7
#define LOW_AXIS_VALUE 1
#define REST_AXIS_VALUE 512
#define HIGH_AXIS_VALUE 1023
#define MAX_COORDINATE_VALUE 127
#define COORDINATE_THRESHOLD_VALUE 64

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,   KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_LSFT,
        KC_LCTL,   KC_LGUI, KC_LALT, KC_SPC,  KC_LALT,  KC_LGUI,MO(1), KC_LCTL,   KC_LEFT, KC_DOWN, KC_RGHT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
};

joystick_config_t joystick_axes[JOYSTICK_AXES_COUNT] = {
  [0] = JOYSTICK_AXIS_VIRTUAL,
  [1] = JOYSTICK_AXIS_VIRTUAL
  // [0] = JOYSTICK_AXIS_IN(X_PIN, LOW_AXIS_VALUE, REST_AXIS_VALUE, HIGH_AXIS_VALUE),
  // [1] = JOYSTICK_AXIS_IN(Y_PIN, LOW_AXIS_VALUE, REST_AXIS_VALUE, HIGH_AXIS_VALUE)
};

bool lShiftPressed = false;
bool rShiftPressed = false;
uint8_t timeoutThreshold = 10;
uint16_t lastTimestamp = 0;

int8_t axisCoordinate(uint8_t pin) {
  int8_t direction;
  int16_t range;
  int16_t distance;
  int16_t position = analogReadPin(pin);

  if (position == REST_AXIS_VALUE) {
    return 0;
  } else if (position < REST_AXIS_VALUE) {
    distance = REST_AXIS_VALUE - position;
    range = REST_AXIS_VALUE - LOW_AXIS_VALUE;
    direction = 1;
  } else {
    distance = position - REST_AXIS_VALUE;
    range = HIGH_AXIS_VALUE - REST_AXIS_VALUE;
    direction = -1;
  }

  float percent = (float)distance / range;
  int16_t coordinate = (int16_t)(percent * MAX_COORDINATE_VALUE);
  if (coordinate < 0) {
    return 0;
  } else if (coordinate > MAX_COORDINATE_VALUE) {
    return MAX_COORDINATE_VALUE * direction;
  } else {
    return coordinate * direction;
  }
}

int8_t axisToMouseComponent(uint8_t pin) {
  int coordinate = axisCoordinate(pin);
  if (coordinate == 0) {
    return 0;
  } else {
    int precisionRegulator = (lShiftPressed || rShiftPressed) ? 5000 : 1000;
    return abs(coordinate) * (float)coordinate / precisionRegulator;
  }
}

uint16_t axisToKeycodeComponent(uint8_t layer, uint8_t x_pin, uint8_t y_pin) {
  const keypos_t keypos[] = {
    [0] = (keypos_t) {.row = 2, .col = 1 }, // UP
    [1] = (keypos_t) {.row = 4, .col = 5 }, // DOWN
    [2] = (keypos_t) {.row = 6, .col = 1 }, // LEFT
    [3] = (keypos_t) {.row = 3, .col = 4 }  // RIGHT
  };
  int8_t x = axisCoordinate(X_PIN);
  int8_t y = axisCoordinate(Y_PIN);

  if (abs(x) > abs(y)) {
    if (x > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[3]);
    } else if ((x * -1) > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[2]);
    }
  } else {
    if (y > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[0]);
    } else if ((y * -1) > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[1]);
    }
  }
  return KC_NO;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {}
  return MACRO_NONE;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);
  if (layer == 1 || layer == 2) {
    if (timer_elapsed(lastTimestamp) > timeoutThreshold) {
      lastTimestamp = timer_read();
      uint16_t keycode = axisToKeycodeComponent(layer, X_PIN, Y_PIN);
      tap_code(keycode);
    }
  } else if (layer == 3) {
    joystick_status.axes[0] = axisCoordinate(X_PIN);
    joystick_status.axes[1] = axisCoordinate(Y_PIN);
    joystick_status.status |= JS_UPDATED;
  }
}

// void joystick_task(void) {
//   uint8_t layer = biton32(layer_state);
//   if (layer == 3) {
//     joystick_status.axes[0] = axisCoordinate(X_PIN);
//     joystick_status.axes[1] = axisCoordinate(Y_PIN);
//     joystick_status.status |= JS_UPDATED;
//   }
// }

void pointing_device_task(void) {
  uint8_t layer = biton32(layer_state);
  if (layer == 0) {
    if (timer_elapsed(lastTimestamp) > timeoutThreshold) {
      lastTimestamp = timer_read();
      report_mouse_t report = pointing_device_get_report();
      report.x = axisToMouseComponent(X_PIN);
      report.y = axisToMouseComponent(Y_PIN);
      pointing_device_set_report(report);
      pointing_device_send();
    }
  }
}


