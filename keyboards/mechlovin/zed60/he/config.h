/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#define MATRIX_ROWS 5
#define MATRIX_COLS 16

#define MUXES 5
/* COM pin of each 74HC4067 (IC1..IC5) -> all on ADC2 (see mcuconf.h) */
#define MUX_PINS { A4, A5, A6, A7, B2 }
#define MUX_SELECTOR_BITS 4
/* Shared channel-select lines S0, S1, S2, S3 */
#define MUX_SELECTOR_PINS { B11, B12, B14, B13 }

#define MUX_CHANNELS ( 1 << MUX_SELECTOR_BITS )

/* HE store: magic(2) + global+per-key config (405B) + 1 align pad + per-key
 * calibration rest/range/noise (uint16 ×3 ×80 = 480B) + autocal(1) + per-key gain
 * (80B) + 1 pad = 970B. == sizeof(he_config_t). */
#define EECONFIG_KB_DATA_SIZE 970

/* Per-key store + VIA dynamic keymap no longer fit the default 1 KB logical
 * EEPROM, so double the wear-leveling backing (-> 2 KB logical). */
#define WEAR_LEVELING_BACKING_SIZE 4096

/* Factory-default VIA layout option: Bottom Row = 7u (the shipped build). Bit 1 is
 * the Bottom-Row group (labels order Backspace, Right Shift, Bottom Row, Caps), so
 * 0x02 selects 7u out of the box; see he.c via_set_layout_options_kb. */
#define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00000002

/* #define DEBUG_ENABLE */         /* re-enable to stream the raw-ADC grid over `qmk console` */
/* #define DEBUG_MATRIX_SCAN_RATE */


#define ADC_RESOLUTION 12

/* ADC counts of key travel (distance of the reading from its resting value)
 * that map to a full 0..255 "value". Lower = more sensitive. Tune from the
 * raw-ADC swing you see over `qmk console` (rest vs fully pressed). */
#define HE_TRAVEL_RANGE 400

#ifdef RGB_MATRIX_ENABLE
#    define IS31FL3741_I2C_ADDRESS_1 IS31FL3741_I2C_ADDRESS_SDA
/* Fail fast if the LED driver does not ACK (e.g. LED hw not wired yet) — the
 * default 100 ms per I2C chunk × ~15 chunks would stall the loop ~1.5 s/flush
 * and make VIA loading crawl. */
#    define IS31FL3741_I2C_TIMEOUT 5
/* Each flush blocks the loop ~11 ms over I2C; cap to ~33 fps so VIA reads
 * are not starved during load (was 60 fps). */
#    define RGB_MATRIX_LED_FLUSH_LIMIT 30
#    define RGB_MATRIX_DISABLE_KEYCODES
#    define I2C1_SCL_PIN     A15
#    define I2C1_SDA_PIN     B7
#    define I2C1_CLOCK_SPEED 400000
#    define I2C1_DUTY_CYCLE  FAST_DUTY_CYCLE_2
#endif

