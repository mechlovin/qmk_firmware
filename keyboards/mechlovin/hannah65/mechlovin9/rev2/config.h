#pragma once

#define PRODUCT_ID   0x6592
#define DEVICE_VER   0x0002
#define PRODUCTION   Mechlovin9 Rev2

#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4 }
#define MATRIX_COL_PINS { B2, B1, B0, B3, B4, B5, D0, D1, D5, D6, D7, C0, C3, C2, C1 }

//#define LED_NUM_LOCK_PIN D6
#define LED_CAPS_LOCK_PIN A7
//#define LED_SCROLL_LOCK_PIN D5
#define LED_PIN_ON_STATE 0
//#define LED_COMPOSE_PIN B3
//#define LED_KANA_PIN B4

#define BACKLIGHT_PIN D4
#define BACKLIGHT_BREATHING
#define BACKLIGHT_LEVELS 3