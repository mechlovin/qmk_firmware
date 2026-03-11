// Copyright 2026 Mechlovin' Studio
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

// Enable in config.h: #define RGB_FADE_ENABLE
//
// Timing defaults (override in config.h):
//   RGB_FADE_TICK_MS    8    tick interval (ms)
//   RGB_FADE_POWER_STEP 12   brightness step/tick for power on/off
//   RGB_FADE_OUT_MS     20   xfade-out duration
//   RGB_FADE_IN_MS      200  xfade-in duration

#ifndef RGB_FADE_ENABLE

static inline void rgb_fade_init(void) {}
static inline void rgb_fade_tick(void) {}
static inline void rgb_fade_matrix_in(void) {}
static inline void rgb_fade_matrix_out(void) {}
static inline void rgb_fade_rgblight_in(void) {}
static inline void rgb_fade_rgblight_out(void) {}

#else

#    ifndef RGB_FADE_TICK_MS
#        define RGB_FADE_TICK_MS 8
#    endif
#    ifndef RGB_FADE_POWER_STEP
#        define RGB_FADE_POWER_STEP 12
#    endif
#    ifndef RGB_FADE_OUT_MS
#        define RGB_FADE_OUT_MS 20
#    endif
#    ifndef RGB_FADE_IN_MS
#        define RGB_FADE_IN_MS 200
#    endif

#    define RGB_FADE_OUT_STEPS (RGB_FADE_OUT_MS / RGB_FADE_TICK_MS)
#    define RGB_FADE_IN_STEPS (RGB_FADE_IN_MS / RGB_FADE_TICK_MS)

// Call from keyboard_post_init_kb
void rgb_fade_init(void);
// Call from matrix_scan_kb
void rgb_fade_tick(void);

void rgb_fade_matrix_in(void);
void rgb_fade_matrix_out(void);
void rgb_fade_rgblight_in(void);
void rgb_fade_rgblight_out(void);

#endif // RGB_FADE_ENABLE