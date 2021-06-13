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

#include "atreus62.h"
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
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_TRNS,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_TRNS, KC_TRNS, KC_TRNS,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_CAPS,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_TRNS,             KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,   KC_BSLS, KC_Z,    KC_X,    KC_C,    KC_V,                               KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_LSFT,
        KC_LCTL,   KC_LGUI, KC_LALT, KC_SPC,  KC_LALT, KC_LGUI,                            MO(1),   KC_LCTL, KC_LEFT, KC_DOWN, KC_RGHT, KC_LEFT, KC_DOWN, KC_RGHT
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

int8_t axisCoordinate_x(uint8_t pin) {
  int8_t direction_x;
  int16_t range_x;
  int16_t distance_x;
  int16_t position_x = analogReadPin(pin);

  if (position_x == REST_AXIS_VALUE) {
    return 0;
  } else if (position_x < REST_AXIS_VALUE) {
    distance_x = REST_AXIS_VALUE - position_x;
    range_x = REST_AXIS_VALUE - LOW_AXIS_VALUE;
    direction_x = 1;
  } else {
    distance_x = position_x - REST_AXIS_VALUE;
    range_x = HIGH_AXIS_VALUE - REST_AXIS_VALUE;
    direction_x = -1;
  }

  float percent_x = (float)distance_x / range_x;
  int16_t coordinate_x = (int16_t)(percent_x * MAX_COORDINATE_VALUE);
  if (coordinate_x < 0) {
    return 0;
  } else if (coordinate_x > MAX_COORDINATE_VALUE) {
    return MAX_COORDINATE_VALUE * direction_x;
  } else {
    return coordinate_x * direction_x;
  }
}

int8_t axisToMouseComponent_x(uint8_t pin) {
  int coordinate_x = axisCoordinate_x(pin);
  if (coordinate_x == 0) {
    return 0;
  } else {
    int precisionRegulator_x = (lShiftPressed || rShiftPressed) ? 5000 : 1000;
    return abs(coordinate_x) * (float)coordinate_x / precisionRegulator_x;
  }
}

int8_t axisCoordinate_y(uint8_t pin) {
  int8_t direction_y;
  int16_t range_y;
  int16_t distance_y;
  int16_t position_y = analogReadPin(pin);

  if (position_y == REST_AXIS_VALUE) {
    return 0;
  } else if (position_y < REST_AXIS_VALUE) {
    distance_y = REST_AXIS_VALUE - position_y;
    range_y = REST_AXIS_VALUE - LOW_AXIS_VALUE;
    direction_y = -1;
  } else {
    distance_y = position_y - REST_AXIS_VALUE;
    range_y = HIGH_AXIS_VALUE - REST_AXIS_VALUE;
    direction_y = 1;
  }

  float percent_y = (float)distance_y / range_y;
  int16_t coordinate_y = (int16_t)(percent_y * MAX_COORDINATE_VALUE);
  if (coordinate_y < 0) {
    return 0;
  } else if (coordinate_y > MAX_COORDINATE_VALUE) {
    return MAX_COORDINATE_VALUE * direction_y;
  } else {
    return coordinate_y * direction_y;
  }
}

int8_t axisToMouseComponent_y(uint8_t pin) {
  int coordinate_y = axisCoordinate_y(pin);
  if (coordinate_y == 0) {
    return 0;
  } else {
    int precisionRegulator_y = (lShiftPressed || rShiftPressed) ? 5000 : 1000;
    return abs(coordinate_y) * (float)coordinate_y / precisionRegulator_y;
  }
}

uint16_t axisToKeycodeComponent(uint8_t layer, uint8_t x_pin, uint8_t y_pin) {
  const keypos_t keypos[] = {
    [0] = (keypos_t) {.row = 0, .col = 12 }, // UP
    [1] = (keypos_t) {.row = 2, .col = 13 }, // DOWN
    [2] = (keypos_t) {.row = 1, .col = 12 }, // LEFT
    [3] = (keypos_t) {.row = 2, .col = 12 }  // RIGHT
  };
  int8_t x = axisCoordinate_x(X_PIN);
  int8_t y = axisCoordinate_y(Y_PIN);

  if (abs(x) > abs(y)) {
    if (x > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[3]);
    } else if ((x * -1) > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[2]);
    }
  } else {
    if (y > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[1]);
    } else if ((y * -1) > COORDINATE_THRESHOLD_VALUE) {
      return keymap_key_to_keycode(layer, keypos[0]);
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
    joystick_status.axes[0] = axisCoordinate_x(X_PIN);
    joystick_status.axes[1] = axisCoordinate_y(Y_PIN);
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
      report.x = axisToMouseComponent_x(X_PIN);
      report.y = axisToMouseComponent_y(Y_PIN);
      pointing_device_set_report(report);
      pointing_device_send();
    }
  }
}


