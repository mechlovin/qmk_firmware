// Copyright 2026 Mechlovin' Studio
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_fade.h"

#ifdef RGB_FADE_ENABLE

#    include "quantum.h"
#    include "rgblight.h"

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static uint8_t step_toward(uint8_t cur, uint8_t tgt, uint8_t step) {
    if (cur < tgt) return (tgt - cur > step) ? cur + step : tgt;
    if (cur > tgt) return (cur - tgt > step) ? cur - step : tgt;
    return cur;
}

// ---------------------------------------------------------------------------
// RGB Matrix
// ---------------------------------------------------------------------------

#    ifdef RGB_MATRIX_ENABLE

typedef enum {
    MX_IDLE,
    MX_POWER_OUT,
    MX_POWER_IN,
    MX_XFADE_OUT,
    MX_XFADE_IN,
} mx_state_t;

static mx_state_t mx_state     = MX_IDLE;
static uint8_t    mx_last_mode = 0xFF;
static uint8_t    mx_pend_mode = 0xFF;
static uint16_t   mx_step      = 0;
static uint8_t    mx_v_target  = 128;
static uint8_t    mx_v_cur     = 0;

static void mx_set_val(uint8_t v) {
    rgb_matrix_config.hsv.v = v;
    mx_v_cur                = v;
}

static void mx_start_fadein(void) {
    mx_v_target  = rgb_matrix_config.hsv.v ? rgb_matrix_config.hsv.v : 128;
    mx_last_mode = rgb_matrix_config.mode;
    mx_set_val(0);
    rgb_matrix_enable_noeeprom();
    mx_step  = 0;
    mx_state = MX_POWER_IN;
}

#    endif // RGB_MATRIX_ENABLE

// ---------------------------------------------------------------------------
// RGBLight
// ---------------------------------------------------------------------------

extern rgblight_config_t rgblight_config;

typedef enum {
    RL_IDLE,
    RL_FADE_OUT,
    RL_FADE_IN,
    RL_XFADE_OUT,
    RL_XFADE_IN,
} rl_state_t;

static rl_state_t rl_state     = RL_IDLE;
static uint8_t    rl_last_mode = 0xFF;
static uint8_t    rl_pend_mode = 0xFF;
static uint16_t   rl_step      = 0;
static uint8_t    rl_on_val    = 128;
static uint8_t    rl_cur       = 0;

// rgblight_sethsv_noeeprom triggers re-render each call.
// Required for static effects (solid, gradient, christmas...)
// that only render once on mode change and never again.
static void rl_set_val(uint8_t v) {
    rl_cur              = v;
    rgblight_config.val = v;
    rgblight_sethsv_noeeprom(rgblight_config.hue, rgblight_config.sat, v);
}

// ---------------------------------------------------------------------------
// Tick timer
// ---------------------------------------------------------------------------

static uint32_t last_tick = 0;

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

void rgb_fade_init(void) {
#    ifdef RGB_MATRIX_ENABLE
    mx_start_fadein();
#    endif

    // Do NOT call rgblight_enable_noeeprom() here.
    // QMK already enabled rgblight before keyboard_post_init runs.
    // Calling it again triggers an immediate SPI flush before the driver
    // is ready on some MCUs (e.g. STM32F103 WS2812-SPI), causing HardFault.
    rl_on_val    = rgblight_get_val() ? rgblight_get_val() : 128;
    rl_last_mode = rgblight_get_mode();
    rl_set_val(0);
    rl_step  = 0;
    rl_state = RL_FADE_IN;
}

void rgb_fade_matrix_in(void) {
#    ifdef RGB_MATRIX_ENABLE
    mx_start_fadein();
#    endif
}

void rgb_fade_matrix_out(void) {
#    ifdef RGB_MATRIX_ENABLE
    if (!rgb_matrix_is_enabled()) return;
    mx_step  = 0;
    mx_state = MX_POWER_OUT;
#    endif
}

void rgb_fade_rgblight_in(void) {
    rl_on_val    = rgblight_get_val() ? rgblight_get_val() : 128;
    rl_last_mode = rgblight_get_mode();
    rl_set_val(0);
    rgblight_enable_noeeprom();
    rl_step  = 0;
    rl_state = RL_FADE_IN;
}

void rgb_fade_rgblight_out(void) {
    rl_on_val = rgblight_get_val() ? rgblight_get_val() : rl_on_val;
    rl_set_val(rl_on_val);
    rl_step  = 0;
    rl_state = RL_FADE_OUT;
}

// ---------------------------------------------------------------------------
// Tick — drive both state machines
// ---------------------------------------------------------------------------

void rgb_fade_tick(void) {
    if (timer_elapsed32(last_tick) < RGB_FADE_TICK_MS) return;
    last_tick = timer_read32();

#    ifdef RGB_MATRIX_ENABLE
    switch (mx_state) {
        case MX_POWER_OUT:
            mx_set_val(step_toward(mx_v_cur, 0, RGB_FADE_POWER_STEP));
            if (mx_v_cur == 0) {
                rgb_matrix_disable_noeeprom();
                mx_state = MX_IDLE;
            }
            break;

        case MX_POWER_IN:
            mx_set_val(step_toward(mx_v_cur, mx_v_target, RGB_FADE_POWER_STEP));
            if (mx_v_cur >= mx_v_target) {
                mx_set_val(mx_v_target);
                mx_state = MX_IDLE;
            }
            break;

        case MX_XFADE_OUT:
            mx_step++;
            mx_set_val(mx_step >= RGB_FADE_OUT_STEPS ? 0 : (uint8_t)(mx_v_target - (uint32_t)mx_v_target * mx_step / RGB_FADE_OUT_STEPS));
            if (mx_step >= RGB_FADE_OUT_STEPS) {
                rgb_matrix_mode_noeeprom(mx_pend_mode);
                mx_pend_mode = 0xFF;
                mx_step      = 0;
                mx_state     = MX_XFADE_IN;
            }
            break;

        case MX_XFADE_IN:
            mx_step++;
            mx_set_val(mx_step >= RGB_FADE_IN_STEPS ? mx_v_target : (uint8_t)((uint32_t)mx_v_target * mx_step / RGB_FADE_IN_STEPS));
            if (mx_step >= RGB_FADE_IN_STEPS) {
                mx_set_val(mx_v_target);
                mx_state = MX_IDLE;
            }
            break;

        case MX_IDLE: {
            uint8_t m = rgb_matrix_config.mode;
            if (mx_last_mode == 0xFF) {
                mx_last_mode = m;
                mx_v_target  = rgb_matrix_config.hsv.v ? rgb_matrix_config.hsv.v : 128;
                break;
            }
            uint8_t v = rgb_matrix_config.hsv.v;
            if (v > 0) mx_v_target = v;
            if (m != mx_last_mode) {
                mx_set_val(mx_v_target);
                mx_pend_mode = m;
                mx_last_mode = m;
                mx_step      = 0;
                mx_state     = MX_XFADE_OUT;
            }
            break;
        }
    }
#    endif // RGB_MATRIX_ENABLE

    switch (rl_state) {
        case RL_FADE_OUT:
            rl_set_val(step_toward(rl_cur, 0, RGB_FADE_POWER_STEP));
            if (rl_cur == 0) {
                rgblight_disable_noeeprom();
                rl_state = RL_IDLE;
            }
            break;

        case RL_FADE_IN:
            rl_set_val(step_toward(rl_cur, rl_on_val, RGB_FADE_POWER_STEP));
            if (rl_cur >= rl_on_val) {
                rl_set_val(rl_on_val);
                rl_state = RL_IDLE;
            }
            break;

        case RL_XFADE_OUT:
            rl_step++;
            rl_set_val(rl_step >= RGB_FADE_OUT_STEPS ? 0 : (uint8_t)(rl_on_val - (uint32_t)rl_on_val * rl_step / RGB_FADE_OUT_STEPS));
            if (rl_step >= RGB_FADE_OUT_STEPS) {
                if (rl_pend_mode != 0xFF) {
                    rgblight_mode_noeeprom(rl_pend_mode);
                }
                rl_pend_mode = 0xFF;
                rl_step      = 0;
                rl_state     = RL_XFADE_IN;
            }
            break;

        case RL_XFADE_IN:
            rl_step++;
            rl_set_val(rl_step >= RGB_FADE_IN_STEPS ? rl_on_val : (uint8_t)((uint32_t)rl_on_val * rl_step / RGB_FADE_IN_STEPS));
            if (rl_step >= RGB_FADE_IN_STEPS) {
                rl_set_val(rl_on_val);
                rl_state = RL_IDLE;
            }
            break;

        case RL_IDLE: {
            uint8_t m = rgblight_get_mode();
            if (rl_last_mode == 0xFF) {
                rl_last_mode = m;
                rl_on_val    = rgblight_get_val();
                break;
            }
            uint8_t v = rgblight_get_val();
            if (v > 0) rl_on_val = v;
            if (m != rl_last_mode) {
                rl_set_val(0);
                rgblight_mode_noeeprom(rl_last_mode);
                rl_set_val(rl_on_val);
                rl_pend_mode = m;
                rl_last_mode = m;
                rl_step      = 0;
                rl_state     = RL_XFADE_OUT;
            }
            break;
        }
    }
}

#endif // RGB_FADE_ENABLE