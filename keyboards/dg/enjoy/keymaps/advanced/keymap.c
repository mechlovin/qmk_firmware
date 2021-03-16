#include "enjoy.h"
#include "joystick.h"
#include "analog.h"
#include "pointing_device.h"

#define X_PIN F4
#define Y_PIN F5
#define LOW_AXIS_VALUE 1
#define REST_AXIS_VALUE 512
#define HIGH_AXIS_VALUE 1023
#define MAX_COORDINATE_VALUE 127
#define COORDINATE_THRESHOLD_VALUE 64

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_RSFT,
    KC_LCTL, MO(2),            KC_LALT,          KC_SPC,           KC_BTN1, KC_BTN2, KC_RALT, MO(1),   KC_RCTL,

             KC_TRNS,
    KC_TRNS, KC_BTN3,   KC_TRNS,
             KC_TRNS),

  [1] = LAYOUT(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
    KC_LGUI, KC_LBRC, KC_RBRC, KC_BSLS, KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_TRNS,          KC_INS,
    KC_CAPS,          KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END,  KC_TRNS,
    KC_VOLD, KC_TRNS,          KC_VOLU,          KC_MUTE,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

             KC_UP,
    KC_LEFT, KC_TRNS, KC_RGHT,
             KC_DOWN),

  [2] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS,          KC_TRNS,
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
    KC_TRNS, KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

             KC_PGUP,
    KC_HOME, KC_TRNS, KC_END,
             KC_PGDN),

  [3] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
    KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,            KC_NO,            KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,

             KC_NO,
    KC_NO,   KC_NO,   KC_NO,
             KC_NO)

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LSFT:
      lShiftPressed = record->event.pressed;
      break;

    case KC_RSFT:
      rShiftPressed = record->event.pressed;
      break;
  }
  return true;
}

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    DDRB |= (1 << 2); PORTB &= ~(1 << 2);
  } else {
    DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
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
