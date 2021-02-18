#pragma once

#define PRODUCT_ID   0xAEC2
#define PRODUCT      Adelais En Ciel Rev2  

#define MATRIX_ROW_PINS { B5, B6, B7, D0, D1}
#define MATRIX_COL_PINS { D4, D5, D6, D7, C2, C3, C4, C5, C6, C7, A7, A6, A5, A4, A3 }

#ifdef RGB_MATRIX_ENABLE
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
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_PINWHEEL // Sets the default mode, if none has been set
#define DISABLE_RGB_MATRIX_SPLASH	
#define DISABLE_RGB_MATRIX_SOLID_SPLASH	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       	
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS 
#define DISABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define DISABLE_RGB_MATRIX_BAND_SAT       	
#define DISABLE_RGB_MATRIX_BAND_VAL 
#define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS 
#define DISABLE_RGB_MATRIX_DUAL_BEACON
#endif 

#ifdef RGBLIGHT_ENABLE
#define RGB_DI_PIN B3
#define RGBLED_NUM 9
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_TWINKLE
#endif 

#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A { A1 }
#define ENCODERS_PAD_B { A2 }
#define ENCODER_RESOLUTION 4
#endif 

#define USB_MAX_POWER_CONSUMPTION 500