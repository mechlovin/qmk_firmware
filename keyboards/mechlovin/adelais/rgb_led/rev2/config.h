#pragma once

#define PRODUCT_ID   0xAEC2
#define PRODUCT      Adelais En Ciel Rev2  

#define MATRIX_ROW_PINS { B1, A0, C13, A1, A2}
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B11, B10, B8, B4, B5, B3, C14, A7 }

/*
#define RGBLED_NUM      23
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

//rgb matrix setting
// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 0b1110100 AD <-> GND
// 0b1110111 AD <-> VCC
// 0b1110101 AD <-> SCL
// 0b1110110 AD <-> SDA
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110110
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 32
#define DRIVER_2_LED_TOTAL 36
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_PINWHEEL // Sets the default mode, if none has been set

#define RGB_MATRIX_DISABLE_KEYCODES
*/
#define ENCODERS_PAD_A { A4 }
#define ENCODERS_PAD_B { A3 }
#define ENCODER_RESOLUTION 4

#define TAP_CODE_DELAY 10

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN A15
#define RGBLED_NUM       23
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif


#define RGB_DI_PIN A15
#define WS2812_LED_TOTAL 23

#define RGB_UNDERGLOW_ALPHA_TOP_START 0
#define RGB_UNDERGLOW_ALPHA_TOP_END   6   
#define RGB_UNDERGLOW_ALPHA_BOT_START 12
#define RGB_UNDERGLOW_ALPHA_BOT_END   15


/* Backlight options */

#define RGB_BACKLIGHT_ENABLED 1

#define RGB_BACKLIGHT_ML_AEC

// they aren't really used if RGB_BACKLIGHT_NEBULA65 defined
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 1
#define RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 1
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 0
#define RGB_BACKLIGHT_USE_ISO_ENTER 0
#define RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 0

// disable backlight after timeout in minutes, 0 = no timeout
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0

// the default brightness
#define RGB_BACKLIGHT_BRIGHTNESS 255

// the default effect (RGB test)
#define RGB_BACKLIGHT_EFFECT 255

// the default effect speed (0-3)
#define RGB_BACKLIGHT_EFFECT_SPEED 0

// the default color1 and color2
#define RGB_BACKLIGHT_COLOR_1 { .h = 0, .s = 255 }
#define RGB_BACKLIGHT_COLOR_2 { .h = 127, .s = 255 }

#define DRIVER_COUNT 2
#define DRIVER_LED_TOTAL 91

// These define which keys in the matrix are alphas/mods
// Used for backlight effects so colors are different for
// alphas vs. mods
// Each value is for a row, bit 0 is column 0
// Alpha=0 Mod=1
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_0 0b0110000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_1 0b0100000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_2 0b0110000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_3 0b0111000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 0b0111111000000111

#define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_1_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_2_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }
#define RGB_BACKLIGHT_LAYER_3_INDICATOR { .color = { .h = 0, .s = 0 }, .index = 255 }

// Backlight config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 32

// VIA lighting is handled by the keyboard-level code
#define VIA_CUSTOM_LIGHTING_ENABLE