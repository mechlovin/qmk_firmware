/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * module_effects.h — Reusable LED animation library for QMK (ring + center zones)
 *
 * Keyboard-agnostic: zero knowledge of EEPROM, VIA, or hardware drivers.
 * Only needs two callbacks: set_color and get_color.
 *
 * ── Quick integration ───────────────────────────────────────────────────
 *
 *  // keyboard_post_init_kb:
 *  ring_fx_init(RING_N, _set_color, _get_color);
 *  center_fx_init(_set_color, _get_color);
 *
 *  // housekeeping_task_kb  (call once per zone with elapsed ms):
 *  ring_fx_tick(elapsed, &ring_cfg);
 *  center_fx_tick(elapsed, &ctr_cfg);
 *
 *  // rgb_matrix_indicators_kb:
 *  ring_fx_render(&ring_cfg, RING_LED_START);
 *  center_fx_render(&ctr_cfg, CENTER_LED_START);
 *
 *  // on mode change:
 *  ring_fx_reset();   // or center_fx_reset()
 *
 * ── rules.mk ────────────────────────────────────────────────────────────
 *  COMMON_VPATH += $(MECHLOVIN_LIB_PATH)
 *  SRC += module_effects.c
 */
#pragma once
#include "quantum.h"

/* ════════════════════════════════════════════════════════════════════════
 * CALLBACKS
 * ════════════════════════════════════════════════════════════════════════ */

/* Write one LED.  Signature matches rgb_matrix_driver_t.set_color. */
typedef void (*mechlovin_set_color_fn_t)(int index, uint8_t r, uint8_t g, uint8_t b);

/* Read back the current color of one LED (from a mirror buffer in keyboard.c).
 * Used by SYNC mode to apply a brightness cap over QMK's active effect.  */
typedef RGB (*mechlovin_get_color_fn_t)(int index);

/* ════════════════════════════════════════════════════════════════════════
 * SHARED CONFIG STRUCT  (for both ring and center zones)
 * ════════════════════════════════════════════════════════════════════════ */
typedef struct {
    uint8_t mode;   /* RING_FX_* or CENTER_FX_*                          */
    uint8_t h;      /* base hue        (0–255)                           */
    uint8_t s;      /* saturation      (0–255)                           */
    uint8_t v;      /* max brightness  (0–255, also applied in SYNC mode) */
    uint8_t speed;  /* animation speed (0–255, same scale as QMK)        */
} led_zone_cfg_t;

/* ════════════════════════════════════════════════════════════════════════
 * RING EFFECTS
 *
 * N LEDs in a circle (N ≤ RING_FX_MAX_LEDS, typically 16).
 *
 * TIMING MODEL at speed = 128 (QMK default):
 *
 *   Fast accumulator pos  += speed × elapsed_ms
 *     Full 16-bit cycle = 65536 / 128 ≈ 512 ms
 *     Chase / Dual:   head = pos >> 4   → 2 laps/s
 *     Rainbow:        hue  = pos >> 8   → full sweep / 512 ms
 *     Sparkle:        phase= pos >> 8   → flash / 512 ms per LED
 *     Wave:           phase= pos >> 8   → orbit / 512 ms
 *     Theater:        slot = f(pos>>8)  → 3 steps / 512 ms
 *
 *   Slow accumulator phi  += (speed >> 2) × elapsed_ms   (4× slower)
 *     Full cycle ≈ 2048 ms  ← matches QMK breathing period
 *     Breathe / Split / Mood / Aurora:  phase = phi >> 8
 *     Twinkle:  phase[i] = (phi>>8) + golden_offset[i]
 * ════════════════════════════════════════════════════════════════════════ */

#define RING_FX_SYNC    0  /* QMK rgb_matrix renders ring; v scales brightness */
#define RING_FX_CHASE   1  /* single comet, sub-LED smooth tail                */
#define RING_FX_BREATHE 2  /* all LEDs breathe together (sin⁴ curve)           */
#define RING_FX_STATIC  3  /* solid fixed color, no animation                  */
#define RING_FX_RAINBOW 4  /* full gradient rainbow spinning around ring        */
#define RING_FX_DUAL    5  /* two comets 180° apart                            */
#define RING_FX_TWINKLE 6  /* each LED breathes independently, random hue/cycle */
#define RING_FX_MOOD    7  /* whole ring drifts slowly through rainbow hues     */
#define RING_FX_SPARKLE 8  /* brief random flashes per LED, random hue each    */
#define RING_FX_WAVE    9  /* smooth sine-bell of light orbits the ring        */
#define RING_FX_THEATER 10 /* every 3rd LED lit, group marches clockwise       */
#define RING_FX_SPLIT   11 /* top half vs bottom half breathe in antiphase     */
#define RING_FX_AURORA  12 /* per-LED slow independent hue+brightness drift    */
#define RING_FX_MAX     12

#ifndef RING_FX_MAX_LEDS
#    define RING_FX_MAX_LEDS 24
#endif

/**
 * ring_fx_init — call once in keyboard_post_init_kb.
 * @param led_count  Number of ring LEDs (≤ RING_FX_MAX_LEDS).
 * @param set_fn     Callback to write one LED color.
 * @param get_fn     Callback to read back one LED color (from mirror buffer).
 *                   Used only for RING_FX_SYNC brightness scaling.
 *                   Pass NULL to disable SYNC scaling.
 */
void ring_fx_init(uint8_t led_count,
                  mechlovin_set_color_fn_t set_fn,
                  mechlovin_get_color_fn_t get_fn);

/** ring_fx_tick — advance animation state. Call from housekeeping_task_kb.
 *  @param elapsed_ms  ms since last call (use timer_elapsed32). */
void ring_fx_tick(uint32_t elapsed_ms, const led_zone_cfg_t *cfg);

/** ring_fx_render — write LED colors. Call from rgb_matrix_indicators_kb.
 *  RING_FX_SYNC: reads back QMK-rendered colors and scales by cfg->v. */
void ring_fx_render(const led_zone_cfg_t *cfg, uint8_t led_start);

/** ring_fx_reset — zero accumulators, re-seed per-LED hues.
 *  Call when mode or color changes. */
void ring_fx_reset(void);

/* ════════════════════════════════════════════════════════════════════════
 * CENTER EFFECTS
 *
 * Exactly 4 LEDs at keyboard corners, clockwise from top-left:
 *
 *   local index:  0 = TL    1 = TR
 *                 3 = BL    2 = BR
 *
 *    TL(0) ──── TR(1)
 *      │                │
 *    BL(3) ──── BR(2)
 *
 * TIMING: same accumulators as ring (pos / phi), same speed scale.
 *   pos → ROTATE, SPIN, KNIGHT
 *   phi → BREATHE, DIAGONAL, CROSS, TWINKLE, CASCADE
 * ════════════════════════════════════════════════════════════════════════ */

#define CENTER_FX_SYNC     0  /* QMK renders center; v scales brightness       */
#define CENTER_FX_STATIC   1  /* all 4 LEDs solid color                        */
#define CENTER_FX_BREATHE  2  /* all 4 breathe together (sin⁴)                 */
#define CENTER_FX_ROTATE   3  /* comet chases clockwise TL→TR→BR→BL            */
#define CENTER_FX_DIAGONAL 4  /* {TL,BR} and {TR,BL} breathe 180° apart        */
                              /*   → pulsing × pattern                         */
#define CENTER_FX_TWINKLE  5  /* each LED breathes independently, random hue   */
#define CENTER_FX_SPIN     6  /* rainbow gradient rotates around 4 corners      */
#define CENTER_FX_CASCADE  7  /* TL→TR→BR→BL trigger with staggered delay      */
#define CENTER_FX_CROSS    8  /* {TL,TR} top vs {BL,BR} bottom breathe 180°    */
                              /*   → pulsing − / − pattern                     */
#define CENTER_FX_KNIGHT   9  /* brightness peak orbits all 4 corners smoothly */
#define CENTER_FX_MAX      9

/**
 * center_fx_init — call once in keyboard_post_init_kb.
 * @param set_fn  Callback to write one LED color.
 * @param get_fn  Callback to read back one LED color. Pass NULL to disable SYNC scaling.
 */
void center_fx_init(mechlovin_set_color_fn_t set_fn,
                    mechlovin_get_color_fn_t get_fn);

void center_fx_tick(uint32_t elapsed_ms, const led_zone_cfg_t *cfg);
void center_fx_render(const led_zone_cfg_t *cfg, uint8_t led_start);
void center_fx_reset(void);