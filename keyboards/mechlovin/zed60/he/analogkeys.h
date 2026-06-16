/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdbool.h>

/* Actuation config for one key (and the global default). Field ORDER and units
 * are indexed by offset in he.c (0 actuation, 1 rt_enabled, 2 rt_press,
 * 3 rt_release, 4 rt_continuous) — matching the configurator's tuning value ids. */
typedef struct {
    uint8_t actuation;     /* % travel 11..89 — actuation point (higher = deeper) */
    uint8_t rt_enabled;    /* 0/1 — rapid trigger */
    uint8_t rt_press;      /* % 1..100 — RT press sensitivity */
    uint8_t rt_release;    /* % 1..100 — RT release sensitivity */
    uint8_t rt_continuous; /* 0/1 — continuous rapid trigger */
} he_key_config_t; /* 5 bytes */

/* Bumped whenever the EEPROM layout below changes, so a firmware update with a
 * different datablock size resets to defaults instead of reading stale bytes.
 * 0x4847: force a one-time reset — earlier calibration may have been written
 * with wrong matrix coords (app coord bugs), leaving some keys un-actuatable.
 * 0x4848: force-reseed again — clears any stale/bad per-key calibration (e.g. a
 * slash [3,11] cal_rest left far from the live reading -> stuck-pressed); the
 * baked maps re-seed and uncalibrated keys fall back to the live auto-rest. */
#define HE_CONFIG_MAGIC 0x4848

typedef struct {
    uint16_t        magic;                           /* == HE_CONFIG_MAGIC when valid */
    he_key_config_t global;                          /* broadcast defaults (value ids 0x01..) */
    he_key_config_t key[MATRIX_ROWS][MATRIX_COLS];   /* per-key overrides (0x11.. after select) */
    /* Per-key calibration. cal_range == 0 → uncalibrated: the scan falls back to
     * the live rest + HE_TRAVEL_RANGE. Stored per key so sensors with different
     * sensitivity / rest / travel each normalise to their own 0..100%. */
    uint16_t cal_rest[MATRIX_ROWS][MATRIX_COLS];     /* released ADC level */
    uint16_t cal_range[MATRIX_ROWS][MATRIX_COLS];    /* travel = |bottom - rest| */
    uint16_t cal_noise[MATRIX_ROWS][MATRIX_COLS];    /* rest fluctuation band (deadzone) */
    uint8_t  autocal;                                /* continuous auto-calibration on/off */
    uint8_t  gain[MATRIX_ROWS][MATRIX_COLS];         /* per-key ADC oversample shift (0=1x … 4=16x) */
} he_config_t;
_Static_assert(sizeof(he_config_t) == EECONFIG_KB_DATA_SIZE, "Size mismatch");
extern he_config_t g_he;

/* Live-tuning visualizer (HE v4): while set, the scan keeps measuring depth but
 * suppresses key output so the user can press keys without typing. */
extern uint8_t he_tuning;

/* Re-calibration (HE v5): 0 idle, 1 sampling rest floor, 2 capturing presses. */
extern uint8_t he_cal_phase;

/* True while key output must be suppressed (visualizer or calibration active). */
bool he_output_suppressed(void);

/* Per-scan hook: feed each key's raw reading into the calibration sampler
 * (no-op when not calibrating). */
void he_cal_sample(uint8_t row, uint8_t col, uint16_t raw);

typedef struct {
    /* For individual analog key runtime state */
    uint8_t  value;
    uint16_t raw;  /* last raw ADC reading — exposed to the host via 0x50 for host-driven calib */
    uint16_t rest; /* calibrated resting ADC reading (key released) */
    uint8_t  extremum;
    bool     continuous_dynamic_actuation;
} analog_key_t;
extern analog_key_t keys[MATRIX_ROWS][MATRIX_COLS];

