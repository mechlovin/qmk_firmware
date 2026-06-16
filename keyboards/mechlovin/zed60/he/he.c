/* Copyright 2023 RephlexZero (@RephlexZero)
SPDX-License-Identifier: GPL-2.0-or-later */
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "quantum.h"
#include "scanfunctions.h"
#include "print.h"
#include "multiplexer.h"
#include QMK_KEYBOARD_H  /* for the LAYOUT_* macro used by the actuation map */

#ifdef RGB_MATRIX_ENABLE
const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           |           LED Number in schematic
 *   |  |           |           |           |    Key Number in schematic
 *   |  |           |           |           |    |   LED Index  
 *   |  |           |           |           |    |   |*/
    {0,   SW1_CS39, SW1_CS38,   SW1_CS37}, //D93-SW2-0
    {0,   SW1_CS36, SW1_CS35,   SW1_CS34}, //D95-SW7-1
    {0,   SW1_CS33, SW1_CS32,   SW1_CS31}, //D97-SW13-2
    {0,   SW1_CS30, SW1_CS29,   SW1_CS28}, //D99-SW19-3
    {0,   SW1_CS21, SW1_CS20,   SW1_CS19}, //D101-SW24-4
    {0,   SW1_CS18, SW1_CS17,   SW1_CS16}, //D103-SW29-5
    {0,   SW1_CS15, SW1_CS14,   SW1_CS13}, //D105-SW33-6
    {0,   SW1_CS12, SW1_CS11,   SW1_CS10}, //D107-SW39-7
    {0,   SW1_CS27, SW1_CS26,   SW1_CS25},  //D109-SW44-8
    {0,   SW1_CS24, SW1_CS23,   SW1_CS22},  //D111-SW49-9
    {0,    SW1_CS6,  SW1_CS5,    SW1_CS4}, //D113-SW54-10
    {0,    SW1_CS3,  SW1_CS2,    SW1_CS1}, //D115-SW60-11
    {0,    SW1_CS9,  SW1_CS8,    SW1_CS7}, //D117-SW66-12
    {0,    SW4_CS9,  SW4_CS8,    SW4_CS7}, //D86-SW72-13
    {0,    SW5_CS9,  SW5_CS8,    SW5_CS7}, //D180-SW80-14

    {0,   SW2_CS39, SW2_CS38,   SW2_CS37}, //D124-SW5-15
    {0,   SW2_CS36, SW2_CS35,   SW2_CS34}, //D127-SW9-16
    {0,   SW2_CS33, SW2_CS32,   SW2_CS31}, //D130-SW14-17
    {0,   SW2_CS30, SW2_CS29,   SW2_CS28}, //D133-SW20-18
    {0,   SW2_CS21, SW2_CS20,   SW2_CS19}, //D135-SW25-19
    {0,   SW2_CS18, SW2_CS17,   SW2_CS16}, //D137-SW30-20
    {0,   SW2_CS15, SW2_CS14,   SW2_CS13}, //D139-SW34-21
    {0,   SW2_CS12, SW2_CS11,   SW2_CS10}, //D142-SW40-22
    {0,   SW2_CS27, SW2_CS26,   SW2_CS25}, //D144-SW45-23
    {0,   SW2_CS24, SW2_CS23,   SW2_CS22}, //D146-SW50-24
    {0,    SW2_CS6,  SW2_CS5,    SW2_CS4}, //D148-SW55-25
    {0,    SW2_CS3,  SW2_CS2,    SW2_CS1}, //D151-SW61-26
    {0,    SW2_CS9,  SW2_CS8,    SW2_CS7}, //D154-SW67-27
    {0,    SW6_CS9,  SW6_CS8,    SW6_CS7}, //D179-SW73-28
    
    {0,   SW3_CS39, SW3_CS38,   SW3_CS37}, //D165-SW93-29
    {0,   SW3_CS36, SW3_CS35,   SW3_CS34}, //D167-SW11-30
    {0,   SW3_CS33, SW3_CS32,   SW3_CS31}, //D168-SW16-31
    {0,   SW3_CS30, SW3_CS29,   SW3_CS28}, //D169-SW22-32
    {0,   SW3_CS21, SW3_CS20,   SW3_CS19}, //D170-SW27-33
    {0,   SW3_CS18, SW3_CS17,   SW3_CS16}, //D171-SW32-34
    {0,   SW3_CS15, SW3_CS14,   SW3_CS13}, //D172-SW38-35
    {0,   SW3_CS12, SW3_CS11,   SW3_CS10}, //D173-SW43-36
    {0,   SW3_CS27, SW3_CS26,   SW3_CS25},  //D174-SW48-37
    {0,   SW3_CS24, SW3_CS23,   SW3_CS22},  //D175-SW53-38
    {0,    SW3_CS6,  SW3_CS5,    SW3_CS4}, //D176-SW58-39
    {0,    SW3_CS3,  SW3_CS2,    SW3_CS1}, //D177-SW64-40
    {0,    SW3_CS9,  SW3_CS8,    SW3_CS7}, //D87-SW94-41
    
    {0,   SW7_CS39, SW7_CS38,   SW7_CS37}, //D125-SW3-42
    {0,   SW7_CS36, SW7_CS35,   SW7_CS34}, //D131-SW15-43
    {0,   SW7_CS33, SW7_CS32,   SW7_CS31}, //D134-SW21-44
    {0,   SW7_CS30, SW7_CS29,   SW7_CS28}, //D136-SW26-45
    {0,   SW7_CS21, SW7_CS20,   SW7_CS19}, //D138-SW31-46
    {0,   SW7_CS18, SW7_CS17,   SW7_CS16}, //D140-SW35-47
    {0,   SW7_CS15, SW7_CS14,   SW7_CS13}, //D143-SW41-48
    {0,   SW7_CS12, SW7_CS11,   SW7_CS10},  //D145-SW46-49
    {0,   SW7_CS27, SW7_CS26,   SW7_CS25},  //D147-SW51-50
    {0,   SW7_CS24, SW7_CS23,   SW7_CS22}, //D149-SW56-51
    {0,    SW7_CS6,  SW7_CS5,    SW7_CS4}, //D152-SW62-52
    {0,    SW7_CS9,  SW7_CS8,    SW7_CS7}, //D160-SW74-53
    {0,    SW7_CS3,  SW7_CS2,    SW7_CS1}, //D155-SW68-54
    
    {0,   SW9_CS39, SW9_CS38,   SW9_CS37}, //D124-SW104-58
    {0,   SW9_CS36, SW9_CS35,   SW9_CS34}, //D127-SW106-59
    {0,   SW9_CS33, SW9_CS32,   SW9_CS31}, //D130-SW17-60
    {0,   SW9_CS18, SW9_CS17,   SW9_CS16}, //D140-SW35-47
    {0,   SW9_CS24, SW9_CS23,   SW9_CS22}, //D149-SW56-51
    {0,    SW9_CS6,  SW9_CS5,    SW9_CS4}, //D152-SW62-52
    {0,    SW9_CS9,  SW9_CS8,    SW9_CS7}, //D160-SW74-53
    {0,    SW9_CS3,  SW9_CS2,    SW9_CS1}, //D155-SW68-54
};
#endif

he_config_t g_he; /* loaded from EEPROM in keyboard_post_init_kb */
uint8_t     he_tuning = 0; /* visualizer: suppress key output while measuring depth */

/* Which (row,col) cells have a real switch (from mux_index) — the visualizer
 * reports 0xFF for the rest so the app masks them. Built in post_init. */
static uint8_t he_connected[MATRIX_ROWS][MATRIX_COLS];

/* Default rapid-trigger config applied to every key on factory reset; the
 * actuation point itself comes from he_actuation_map below. */
#define HE_ACTUATION_DEFAULT 30 /* % travel — base per-key actuation point */
static const he_key_config_t he_default = {
    .actuation     = HE_ACTUATION_DEFAULT,
    .rt_enabled    = 1,  /* rapid trigger on */
    .rt_press      = 13, /* % */
    .rt_release    = 13, /* % */
    .rt_continuous = 0,
};

/* Per-key DEFAULT actuation map (% travel), written in the same visual order as
 * the keymap — edit a cell to change one key's factory default (e.g. a key with
 * a different switch/sensor). On factory reset this seeds every key's actuation;
 * the app can then override per-key live (persisted to EEPROM). Workflow: after
 * a sensor/switch change, Calibrate in the app, compute the actuation, write it
 * back per-key — and to bake it in permanently, copy the value into this map.
 * Gaps / out-of-range (11..89) cells fall back to HE_ACTUATION_DEFAULT. */
#define HE_AP HE_ACTUATION_DEFAULT
static const uint8_t he_actuation_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_all(
    HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP,
    HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP,
    HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP,
    HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP,
    HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP, HE_AP
);
#undef HE_AP

/* Per-key CALIBRATION default map: resting (released) and bottom-out (fully
 * pressed) RAW ADC, in MATRIX order [row = IC][col = channel]. 0 = uncalibrated
 * for that key → fall back to the auto-measured rest + HE_TRAVEL_RANGE.
 * To bake a calibration: open `qmk console`, run Calibrate + Save in the app —
 * the firmware streams both grids; paste them over the ones below, bump
 * HE_CONFIG_MAGIC, and reflash. (bottom = rest + travel; sign-agnostic since the
 * scan uses |raw - rest|.) */
static const uint16_t he_rest_map[MATRIX_ROWS][MATRIX_COLS] = {
    {788,798,790,787,791,790,793,795,795,795,791,787,785,787,788,785},
    {793,794,792,793,793,792,793,793,0,0,796,789,792,791,798,795},
    {795,801,791,794,790,791,786,799,0,0,797,0,787,788,787,791},
    {788,796,796,792,794,0,793,0,795,0,792,788,788,792,791,702},
    {802,793,795,0,795,0,0,0,0,0,0,0,0,795,798,793},
};
static const uint16_t he_bottom_map[MATRIX_ROWS][MATRIX_COLS] = {
    {717,729,722,724,722,713,713,709,739,720,715,734,719,718,719,716},
    {709,706,707,701,714,713,713,745,0,  0,  725,718,709,701,706,712},
    {708,710,707,713,703,723,706,770,0,  0,  716,  0,696,703,700,695},
    {702,721,712,697,707,0,  741,  0,713,0,  699,721,721,711,718,290},
    {750,738,735,0,  700,0,  0,  0,  0,  0,  0,  0,  0,  736,732,734},
};
/* Rest noise band per key (deadzone). 0 = no deadzone for a baked key. */
static const uint16_t he_noise_map[MATRIX_ROWS][MATRIX_COLS] = {
    {7,9,11,7,5,3,11,5,8,0,10,11,10,7,9,9},
    {9,9,11,8,7,10,9,11,0,0,8,10,8,9,9,10},
    {8,11,8,9,8,7,9,7,0,0,11,0,10,10,13,10},
    {9,9,9,10,6,0,11,0,9,0,8,0,11,8,8,10},
    {7,8,8,0,10,0,0,0,0,0,0,0,0,8,11,13},
};

#ifdef DEFERRED_EXEC_ENABLE
deferred_token idle_recalibrate_token;
bool           process_record_kb(uint16_t keycode, keyrecord_t *record) {
    extend_deferred_exec(idle_recalibrate_token, 300000);
    return process_record_user(keycode, record);
}

uint32_t idle_recalibrate_callback(uint32_t trigger_time, void *cb_arg) {
    get_sensor_offsets();
    return 10000;
}
#endif

#ifdef VIA_ENABLE
#    include "dynamic_keymap.h"
/* Bottom-row right-modifier remap. Channels [4,13]/[4,14] are physically SHARED
 * between the 6.25u and 7u bottom rows, so a single matrix cell must mean a
 * different modifier per layout. The "Bottom Row" VIA layout-option lands on bit 1
 * (label-group order is Backspace, Right Shift, Bottom Row, Caps -> the configurator
 * packs the last group into the LSB, so Bottom Row = bit 1). VIA calls this hook on
 * boot and whenever the option changes; we rewrite ONLY the base-layer keycodes of
 * those two cells, leaving every other key / layer untouched.
 *   6.25u (bit 1 = 0): [4,13]=Right GUI, [4,14]=Menu
 *   7u    (bit 1 = 1): [4,13]=Right Alt, [4,14]=Right GUI                          */
void via_set_layout_options_kb(uint32_t value) {
    bool is_7u = (value >> 1) & 1;
    dynamic_keymap_set_keycode(0, 4, 13, is_7u ? KC_RALT : KC_RGUI);
    dynamic_keymap_set_keycode(0, 4, 14, is_7u ? KC_RGUI : KC_APP);
}
#endif

static void values_set_defaults(void) {
    g_he.magic   = HE_CONFIG_MAGIC;
    g_he.global  = he_default;
    g_he.autocal = 0; /* continuous auto-calibration off by default */
    memset(g_he.gain, 0, sizeof(g_he.gain)); /* per-key oversample off (1x) */
    /* Seed each key from the baked maps in one pass: per-key actuation from
     * he_actuation_map (valid 11..89, else the default), and a fixed calibration
     * when both rest and bottom are set — otherwise 0 = uncalibrated, so the scan
     * falls back to the auto-measured rest + HE_TRAVEL_RANGE. */
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            g_he.key[r][c] = he_default;
            uint8_t a = he_actuation_map[r][c];
            if (a >= 11 && a <= 89) g_he.key[r][c].actuation = a;

            uint16_t rest = he_rest_map[r][c], bot = he_bottom_map[r][c];
            if (rest && bot && rest != bot) {
                g_he.cal_rest[r][c]  = rest;
                g_he.cal_range[r][c] = (bot > rest) ? (bot - rest) : (rest - bot);
                g_he.cal_noise[r][c] = he_noise_map[r][c];
            } else {
                g_he.cal_rest[r][c]  = 0;
                g_he.cal_range[r][c] = 0;
                g_he.cal_noise[r][c] = 0;
            }
        }
}

void values_save(void) {
    eeconfig_update_kb_datablock(&g_he);
}

void values_load(void) {
    eeconfig_read_kb_datablock(&g_he);
    /* Reset to defaults if the stored layout is from an older/other firmware. */
    if (g_he.magic != HE_CONFIG_MAGIC) {
        values_set_defaults();
        values_save();
    }
}

void eeconfig_init_kb(void) {
    values_set_defaults();
    values_save();
}

/* ── HE re-calibration (v5) — per-key rest + bottom-out capture ──────────────
 * CAL_MODE 1 samples the rest floor (hands off) for HE_CAL_FLOOR_MS, then auto-
 * advances to a capture phase (press every key fully). CAL_SAVE / CAL_MODE 3
 * stores each captured key's rest + travel to EEPROM. Output is suppressed
 * throughout so calibration presses don't type. */
#define HE_CAL_FLOOR_MS    300  /* rest-floor sampling window (hands off) */
#define HE_CAL_MIN_TRAVEL  40   /* absolute floor: smaller peaks never count as a press */
#define HE_CAL_NOISE_MULT  3    /* capture needs peak >= NOISE_MULT x noise (adaptive per sensor) */
#define HE_CAL_MIN_RANGE   60   /* floor for a captured key's stored travel */

uint8_t         he_cal_phase  = 0; /* 0 idle, 1 floor, 2 capture */
static uint8_t  he_cal_total  = 0; /* number of connected switches */
static uint16_t he_cal_floor[MATRIX_ROWS][MATRIX_COLS]; /* measured rest (avg) */
static uint16_t he_cal_peak[MATRIX_ROWS][MATRIX_COLS];  /* deepest press seen */
static uint16_t he_cal_noise[MATRIX_ROWS][MATRIX_COLS]; /* rest fluctuation band (max-min) */
static uint16_t he_cal_min[MATRIX_ROWS][MATRIX_COLS];
static uint16_t he_cal_max[MATRIX_ROWS][MATRIX_COLS];
static uint8_t  he_cal_done[MATRIX_ROWS][MATRIX_COLS];
static uint32_t he_cal_sum[MATRIX_ROWS][MATRIX_COLS];
static uint16_t he_cal_samples     = 0;
static uint32_t he_cal_floor_start = 0;
static int8_t   he_dump_idx        = -1; /* -1 idle; 0..4 rest, 5..9 bottom, 10..14 noise */
static uint32_t he_dump_timer      = 0;

bool he_output_suppressed(void) {
    return he_tuning || he_cal_phase != 0;
}

void he_cal_sample(uint8_t row, uint8_t col, uint16_t raw) {
    if (he_cal_phase == 1) { /* floor: average rest + track the noise band */
        he_cal_sum[row][col] += raw;
        if (raw < he_cal_min[row][col]) he_cal_min[row][col] = raw;
        if (raw > he_cal_max[row][col]) he_cal_max[row][col] = raw;
    } else if (he_cal_phase == 2) { /* capture: deepest press; threshold scales with noise */
        int32_t d = (int32_t)raw - (int32_t)he_cal_floor[row][col];
        if (d < 0) d = -d;
        if ((uint16_t)d > he_cal_peak[row][col]) he_cal_peak[row][col] = (uint16_t)d;
        uint16_t thresh = (uint16_t)(he_cal_noise[row][col] * HE_CAL_NOISE_MULT);
        if (thresh < HE_CAL_MIN_TRAVEL) thresh = HE_CAL_MIN_TRAVEL;
        if (he_cal_peak[row][col] >= thresh) he_cal_done[row][col] = 1;
    }
}

static void he_cal_begin(void) {
    memset(he_cal_sum, 0, sizeof(he_cal_sum));
    memset(he_cal_peak, 0, sizeof(he_cal_peak));
    memset(he_cal_done, 0, sizeof(he_cal_done));
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            he_cal_min[r][c] = 0xFFFF;
            he_cal_max[r][c] = 0;
        }
    he_cal_samples     = 0;
    he_cal_floor_start = timer_read32();
    he_cal_phase       = 1;
}

static void he_cal_finish_floor(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            he_cal_floor[r][c] = he_cal_samples ? (uint16_t)(he_cal_sum[r][c] / he_cal_samples) : keys[r][c].rest;
            he_cal_noise[r][c] = (he_cal_max[r][c] >= he_cal_min[r][c]) ? (he_cal_max[r][c] - he_cal_min[r][c]) : 0;
        }
    he_cal_phase = 2;
}

static void he_cal_commit(void) {
    for (uint8_t r = 0; r < MATRIX_ROWS; r++)
        for (uint8_t c = 0; c < MATRIX_COLS; c++)
            if (he_cal_done[r][c]) {
                g_he.cal_rest[r][c]  = he_cal_floor[r][c];
                g_he.cal_range[r][c] = he_cal_peak[r][c] < HE_CAL_MIN_RANGE ? HE_CAL_MIN_RANGE : he_cal_peak[r][c];
                g_he.cal_noise[r][c] = he_cal_noise[r][c];
            }
    values_save();
    he_cal_phase = 0;
    he_dump_idx  = 0; /* stream the new calibration over the console for baking */
}

static void he_cal_factory_reset(void) {
    memset(g_he.cal_rest, 0, sizeof(g_he.cal_rest));
    memset(g_he.cal_range, 0, sizeof(g_he.cal_range));
    memset(g_he.cal_noise, 0, sizeof(g_he.cal_noise));
    values_save();
    he_cal_phase = 0;
}

/* Stream the current calibration as three C grids over `qmk console`, one row
 * per ~40 ms so the HID console isn't overrun. Paste into he_rest_map /
 * he_bottom_map / he_noise_map to bake it. */
static void he_dump_tick(void) {
    if (he_dump_idx < 0 || timer_elapsed32(he_dump_timer) < 40) return;
    he_dump_timer = timer_read32();

    if (he_dump_idx == 0)  uprintf("\n== HE calibration (paste into he.c) ==\nec_rest_map:\n");
    if (he_dump_idx == 5)  uprintf("he_bottom_map:\n");
    if (he_dump_idx == 10) uprintf("he_noise_map:\n");

    uint8_t row   = he_dump_idx % 5;
    uint8_t which = he_dump_idx / 5; /* 0 rest, 1 bottom, 2 noise */
    char    buf[140];
    int     n = 0;
    buf[n++] = '{';
    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
        uint16_t cr   = g_he.cal_range[row][c];
        uint16_t rest = cr ? g_he.cal_rest[row][c] : keys[row][c].rest;
        uint16_t v    = (which == 0) ? rest
                      : (which == 1) ? (uint16_t)(rest + (cr ? cr : HE_TRAVEL_RANGE))
                                     : g_he.cal_noise[row][c];
        n += snprintf(buf + n, sizeof(buf) - n, "%u,", v);
    }
    snprintf(buf + n, sizeof(buf) - n, "},");
    uprintf("%s\n", buf);

    if (++he_dump_idx >= 15) he_dump_idx = -1;
}

void housekeeping_task_kb(void) {
    if (he_cal_phase == 1) {
        he_cal_samples++; /* one floor sample per scan loop */
        if (timer_elapsed32(he_cal_floor_start) >= HE_CAL_FLOOR_MS) he_cal_finish_floor();
    }
    he_dump_tick();
    /* Continuous auto-calibration: gently track each released key's rest baseline
     * toward its live reading (±1 every ~700 ms) so slow drift can't turn into a
     * false press. Only when idle (not calibrating) and only for released keys. */
    static uint32_t he_autocal_timer = 0;
    if (g_he.autocal && he_cal_phase == 0 && timer_elapsed32(he_autocal_timer) >= 700) {
        he_autocal_timer = timer_read32();
        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++)
                if (g_he.cal_range[r][c] && keys[r][c].value == 0) {
                    if (keys[r][c].raw > g_he.cal_rest[r][c])      g_he.cal_rest[r][c]++;
                    else if (keys[r][c].raw < g_he.cal_rest[r][c]) g_he.cal_rest[r][c]--;
                }
    }
    housekeeping_task_user();
}

/* Leave visualizer/calibration on sleep or unplug so output isn't left
 * suppressed if the app disconnects mid-session. */
void suspend_power_down_kb(void) {
    he_tuning    = 0;
    he_cal_phase = 0;
    suspend_power_down_user();
}

void keyboard_post_init_kb(void) {
#ifdef DEFERRED_EXEC_ENABLE
    idle_recalibrate_token = defer_exec(300000, idle_recalibrate_callback, NULL);
#endif
    /* Mark which matrix cells actually have a switch (for the HE visualizer
     * mask + the calibration "total switches" count). */
    for (uint8_t mux = 0; mux < MUXES; mux++) {
        for (uint8_t ch = 0; ch < MUX_CHANNELS; ch++) {
            uint8_t r = mux_index[mux][ch].row, c = mux_index[mux][ch].col;
            if (r < MATRIX_ROWS && c < MATRIX_COLS && !he_connected[r][c]) {
                he_connected[r][c] = 1;
                he_cal_total++;
            }
        }
    }
    values_load();
    keyboard_post_init_user();
}

#ifdef VIA_ENABLE
/* ── HE actuation tuning over VIA custom channel 1 ──────────────────────────
 * Wire protocol matches the configurator's analog-tuning custom channel (its
 * tuning / measure tabs send these value ids); numeric ids kept stable for app
 * compatibility. Channel 1 is the QMK backlight channel, unused here, so the core
 * leaves it to us. Values apply live; persisted to flash only on customSave(1). */
#define HE_CH             1
#define HE_VERSION_REPORT 7 /* + continuous auto-calibration (0x40) → app EC Tools shows the toggle */

enum he_value_id {
    he_id_actuation        = 0x01,
    he_id_rt_enabled       = 0x02,
    he_id_rt_press         = 0x03,
    he_id_rt_release       = 0x04,
    he_id_version          = 0x05,
    he_id_rt_continuous    = 0x06,
    he_id_select_key       = 0x10,
    he_id_pk_actuation     = 0x11,
    he_id_pk_rt_enabled    = 0x12,
    he_id_pk_rt_press      = 0x13,
    he_id_pk_rt_release    = 0x14,
    he_id_pk_rt_continuous = 0x15,
    he_id_pk_cal_read      = 0x18, /* get after select: measured rest, bottom, noise (raw, BE) — for baking */
    he_id_write_cal        = 0x19, /* set after select: rest, bottom, noise (raw, BE) — host-driven calib */
    he_id_set_gain         = 0x1C, /* set/get after select: per-key ADC oversample shift (0..4) */
    he_id_tuning_mode      = 0x20, /* v4: set 1=enter (suppress output) / 0=exit */
    he_id_analog_row_base  = 0x22, /* v4: get 0x22+row -> 16 depth bytes (0..100, 0xFF=no switch) */
    he_id_cal_mode         = 0x30, /* v5: set 0=abort,1=start floor,2=force capture,3=commit,4=factory reset */
    he_id_cal_status       = 0x31, /* v5: get -> phase, #captured, #total, captured bitmap */
    he_id_cal_save         = 0x33, /* v5: set 1 = commit + persist (alias of cal_mode 3) */
    he_id_autocal          = 0x40, /* set/get 0/1: continuous background auto-calibration */
    he_id_raw_row_base     = 0x50, /* get 0x50+row*2+half -> 8 keys x2B raw ADC (BE); 0xFFFF=no switch */
};

static uint8_t he_sel_row = 0, he_sel_col = 0;

/* Map a value id to its field index (0..4) within he_key_config_t. */
static uint8_t he_field_of(uint8_t value_id) {
    switch (value_id) {
        case he_id_actuation:     case he_id_pk_actuation:     return 0;
        case he_id_rt_enabled:    case he_id_pk_rt_enabled:    return 1;
        case he_id_rt_press:      case he_id_pk_rt_press:      return 2;
        case he_id_rt_release:    case he_id_pk_rt_release:    return 3;
        case he_id_rt_continuous: case he_id_pk_rt_continuous: return 4;
        default:                                               return 0xFF;
    }
}

static uint8_t he_clamp(uint8_t field, uint8_t v) {
    switch (field) {
        case 0:          return v < 11 ? 11 : (v > 89 ? 89 : v);  /* actuation % */
        case 2: case 3:  return v < 1 ? 1 : (v > 100 ? 100 : v);  /* rt press/release % */
        default:         return v ? 1 : 0;                        /* rt enabled / continuous */
    }
}

static void he_set_value(uint8_t *data) {
    uint8_t value_id = data[0];
    if (value_id == he_id_select_key) {
        if (data[1] < MATRIX_ROWS && data[2] < MATRIX_COLS) {
            he_sel_row = data[1];
            he_sel_col = data[2];
        }
        return;
    }
    if (value_id == he_id_tuning_mode) {
        he_tuning = data[1] ? 1 : 0; /* enter/exit the live visualizer */
        return;
    }
    if (value_id == he_id_cal_mode) {
        switch (data[1]) {
            case 0: he_cal_phase = 0;                             break; /* abort */
            case 1: he_cal_begin();                               break; /* start: sample rest floor */
            case 2: if (he_cal_phase == 1) he_cal_finish_floor(); break; /* force capture phase */
            case 3: he_cal_commit();                              break; /* commit + persist */
            case 4: he_cal_factory_reset();                       break; /* clear calibration */
        }
        return;
    }
    if (value_id == he_id_cal_save) {
        he_cal_commit();
        return;
    }
    /* Host-driven calibration write (after SELECT_KEY): rest / bottom / noise as
     * raw ADC, big-endian. cal_range = |bottom - rest| (polarity-agnostic); a zero
     * range clears the key to uncalibrated. Persisted on customSave(1). */
    if (value_id == he_id_write_cal) {
        uint16_t rest  = (data[1] << 8) | data[2];
        uint16_t bot   = (data[3] << 8) | data[4];
        uint16_t ns    = (data[5] << 8) | data[6];
        uint16_t range = (bot > rest) ? (bot - rest) : (rest - bot);
        g_he.cal_rest[he_sel_row][he_sel_col]  = range ? rest : 0;
        g_he.cal_range[he_sel_row][he_sel_col] = range;
        g_he.cal_noise[he_sel_row][he_sel_col] = ns;
        return;
    }
    if (value_id == he_id_set_gain) {
        g_he.gain[he_sel_row][he_sel_col] = data[1] > 4 ? 4 : data[1]; /* oversample shift 0..4 */
        return;
    }
    if (value_id == he_id_autocal) {
        g_he.autocal = data[1] ? 1 : 0;
        values_save(); /* flag persists across reboot */
        return;
    }
    uint8_t field = he_field_of(value_id);
    if (field == 0xFF) return;
    uint8_t v = he_clamp(field, data[1]);
    if (value_id <= he_id_rt_continuous) {
        /* global broadcast → default + every key */
        ((uint8_t *)&g_he.global)[field] = v;
        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++)
                ((uint8_t *)&g_he.key[r][c])[field] = v;
    } else {
        /* per-key → the selected key */
        ((uint8_t *)&g_he.key[he_sel_row][he_sel_col])[field] = v;
    }
}

static void he_get_value(uint8_t *data) {
    uint8_t value_id = data[0];
    if (value_id == he_id_version) {
        data[1] = HE_VERSION_REPORT;
        return;
    }
    /* Visualizer: 16 press depths (0..100% travel) for one matrix row. */
    if (value_id >= he_id_analog_row_base && value_id < he_id_analog_row_base + MATRIX_ROWS) {
        uint8_t row = value_id - he_id_analog_row_base;
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            data[1 + col] = he_connected[row][col]
                                ? (uint8_t)((uint16_t)keys[row][col].value * 100 / 255)
                                : 0xFF;
        }
        return;
    }
    /* Calibration status: phase, #captured, #total, then a 10-byte captured
     * bitmap (bit row*16+col). */
    if (value_id == he_id_cal_status) {
        uint8_t captured = 0;
        for (uint8_t i = 0; i < 10; i++) data[4 + i] = 0;
        for (uint8_t r = 0; r < MATRIX_ROWS; r++)
            for (uint8_t c = 0; c < MATRIX_COLS; c++)
                if (he_cal_done[r][c]) {
                    captured++;
                    uint8_t bit = r * 16 + c;
                    data[4 + (bit >> 3)] |= 1 << (bit & 7);
                }
        data[1] = he_cal_phase;
        data[2] = captured;
        data[3] = he_cal_total;
        return;
    }
    /* Per-key calibration readback (after SELECT_KEY): measured rest / bottom-out
     * / noise as raw ADC, big-endian — used by the app's Measure tab to bake the
     * he_*_map tables into he.c. 0,0,0 for an uncalibrated / unconnected key. */
    if (value_id == he_id_pk_cal_read) {
        uint16_t range  = g_he.cal_range[he_sel_row][he_sel_col];
        uint16_t rest   = range ? g_he.cal_rest[he_sel_row][he_sel_col] : 0;
        uint16_t bottom = range ? (uint16_t)(rest + range) : 0;
        uint16_t noise  = range ? g_he.cal_noise[he_sel_row][he_sel_col] : 0;
        data[1] = rest   >> 8; data[2] = rest   & 0xFF;
        data[3] = bottom >> 8; data[4] = bottom & 0xFF;
        data[5] = noise  >> 8; data[6] = noise  & 0xFF;
        return;
    }
    /* Raw ADC readback for host-driven calibration: get 0x50 + row*2 + half →
     * 8 keys × 2 bytes (BE). half 0 = cols 0..7, half 1 = cols 8..15. 0xFFFF =
     * unconnected. The host samples this live (no firmware threshold) to compute
     * rest / bottom / noise itself, then writes it back via 0x19. */
    if (value_id >= he_id_raw_row_base && value_id < he_id_raw_row_base + MATRIX_ROWS * 2) {
        uint8_t idx = value_id - he_id_raw_row_base, row = idx >> 1, half = idx & 1;
        for (uint8_t i = 0; i < 8; i++) {
            uint8_t  col = half * 8 + i;
            uint16_t v   = he_connected[row][col] ? keys[row][col].raw : 0xFFFF;
            data[1 + i * 2] = v >> 8;
            data[2 + i * 2] = v & 0xFF;
        }
        return;
    }
    if (value_id == he_id_autocal) {
        data[1] = g_he.autocal;
        return;
    }
    if (value_id == he_id_set_gain) {
        data[1] = g_he.gain[he_sel_row][he_sel_col];
        return;
    }
    uint8_t field = he_field_of(value_id);
    if (field == 0xFF) {
        data[1] = 0; /* unsupported id → 0 so the app hides that feature */
        return;
    }
    data[1] = (value_id <= he_id_rt_continuous)
                  ? ((uint8_t *)&g_he.global)[field]
                  : ((uint8_t *)&g_he.key[he_sel_row][he_sel_col])[field];
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    /* data = [ command_id, channel_id, value_id, value_data... ] */
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == HE_CH) {
        switch (*command_id) {
            case id_custom_set_value: he_set_value(value_id_and_data); break;
            case id_custom_get_value: he_get_value(value_id_and_data); break;
            case id_custom_save:      values_save();                   break;
            default:                  *command_id = id_unhandled;      break;
        }
        return;
    }

    *command_id = id_unhandled;
    /* DO NOT call raw_hid_send(data,length) here, let caller do this */
}
#endif
