/* Copyright 2026 Mechlovin' Studio
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * module_effects.c — ring + center LED animation library implementation
 * See module_effects.h for API documentation and integration guide.
 */
#include "module_effects.h"

/* ════════════════════════════════════════════════════════════════
 * SHARED MATH HELPERS
 * ════════════════════════════════════════════════════════════════ */

/* XorShift8 PRNG — 8-bit, no stdlib dependency */
static uint8_t g_rng = 137;
static uint8_t rng8(void) {
    g_rng ^= g_rng << 3;
    g_rng ^= g_rng >> 5;
    g_rng ^= g_rng << 4;
    return g_rng;
}

/* ── sin² approximation ──────────────────────────────────────────
 *
 * Input  x : 0–255 = one full cycle
 * Output   : 0–255, peak at x = 128, zero at x = 0 and x = 255
 * Method   : triangle wave squared
 *
 * Properties vs plain triangle:
 *   sin²  — spends MORE time near peak, less near zero  (natural breathing)
 *   sin⁴  — even wider peak, sharper zero  (holds bright longer, dims fast)
 * ─────────────────────────────────────────────────────────────── */
static inline uint8_t sin2_8(uint8_t x) {
    uint8_t tri = (x < 128) ? (x << 1) : (uint8_t)(255u - ((x - 128u) << 1));
    return (uint8_t)((uint16_t)tri * tri >> 8);
}
static inline uint8_t sin4_8(uint8_t x) {
    uint8_t s2 = sin2_8(x);
    return (uint8_t)((uint16_t)s2 * s2 >> 8);
}

/* scale8: scale val by top, both 0–255.  Equivalent to val × top / 255. */
static inline uint8_t scale8(uint8_t val, uint8_t top) {
    return (uint8_t)((uint16_t)val * top >> 8);
}

/* ── Golden-angle phase offsets (24 entries) ─────────────────────
 *
 * Consecutive offsets are spaced by 98 ≈ 256 × (1 − 1/φ).
 * Since 24 and 98 are coprime mod 256, the 24 values hit distinct
 * phases → no two LEDs are in sync in Twinkle / Sparkle / Aurora.
 * ─────────────────────────────────────────────────────────────── */
static const uint8_t k_gold[24] = {
      0,  98, 196,  38, 136, 234,  76, 174,
     16, 114, 212,  54, 152, 250,  92, 190,
     32, 130, 228,  70, 168,  10, 108, 206
};

/* ════════════════════════════════════════════════════════════════
 * RING — INTERNAL STATE
 * ════════════════════════════════════════════════════════════════ */

static mechlovin_set_color_fn_t s_ring_set = NULL;
static mechlovin_get_color_fn_t s_ring_get = NULL;
static uint8_t                  s_ring_n   = 0;

/* Two 16-bit accumulators wrap naturally at 65536:
 *   r_pos  : fast (used by chase, rainbow, wave, sparkle, theater)
 *   r_phi  : slow = r_pos / 4 rate  (breathe, twinkle, mood, split, aurora) */
static uint16_t r_pos = 0;
static uint16_t r_phi = 0;

/* Per-LED state for Twinkle and Sparkle */
static uint8_t r_hue[RING_FX_MAX_LEDS];  /* current hue per LED            */
static uint8_t r_pp[RING_FX_MAX_LEDS];   /* previous pos-phase per LED      */
static uint8_t r_ph[RING_FX_MAX_LEDS];   /* previous phi-phase per LED      */

/* ── Chase tail brightness table — round(255 × 0.58ⁱ) ──────────
 * 0.58 chosen so the tail is visible but doesn't dominate the ring.
 * Guard entry at index TAIL_LEN+1 = 0 prevents array overrun.    */
#define TAIL_LEN 8
static const uint8_t k_tail[TAIL_LEN + 2] = {
    255, 148, 86, 50, 29, 17, 10, 6, 3, 0
};

/* Sub-LED interpolated brightness at Q8.8 distance from comet head.
 * dist = 0      → head (full brightness = 255)
 * dist = 256×i  → tail entry i                                    */
static uint8_t tail_bright(uint16_t dist) {
    uint8_t di = (uint8_t)(dist >> 8);
    uint8_t df = (uint8_t)(dist & 0xFF);
    if (di > TAIL_LEN) return 0;
    int16_t f0 = k_tail[di], f1 = k_tail[di + 1];
    return (uint8_t)(f0 + ((f1 - f0) * df >> 8));
}

/* Draw one comet into bright[] at Q8 head position head_pos ∈ [0, n×256).
 * Uses max() blend so two comets overlap without cancel.           */
static void draw_comet_ring(uint8_t *bright, uint16_t head_pos) {
    uint16_t period = (uint16_t)s_ring_n << 8;
    head_pos %= period;
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint16_t dist = (head_pos + period - ((uint16_t)i << 8)) % period;
        uint8_t  b    = tail_bright(dist);
        if (b > bright[i]) bright[i] = b;
    }
}

/* ════════════════════════════════════════════════════════════════
 * RING — EFFECT RENDERERS
 * ════════════════════════════════════════════════════════════════ */

/* 0. SYNC — scale brightness of QMK's active effect
 *
 * QMK calls set_color for all LEDs before rgb_matrix_indicators_kb.
 * Those colors are captured in the keyboard's mirror buffer.
 * We read them back, scale by cfg->v, and re-write.
 * v=255 → no scaling (early return, saves CPU).                   */
static void ring_do_sync(const led_zone_cfg_t *c, uint8_t s) {
    if (!s_ring_get || c->v == 255) return;
    for (uint8_t i = 0; i < s_ring_n; i++) {
        RGB col = s_ring_get(s + i);
        s_ring_set(s + i,
                   scale8(col.r, c->v),
                   scale8(col.g, c->v),
                   scale8(col.b, c->v));
    }
}

/* 1. CHASE — single comet, sub-LED interpolated tail */
static void ring_do_chase(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t bright[RING_FX_MAX_LEDS] = {0};
    draw_comet_ring(bright, r_pos >> 4);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t b = scale8(bright[i], c->v);
        RGB rgb   = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 2. BREATHE — all LEDs together, sin⁴ curve */
static void ring_do_breathe(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t b   = scale8(sin4_8((uint8_t)(r_phi >> 8)), c->v);
    RGB     rgb = hsv_to_rgb((HSV){c->h, c->s, b});
    for (uint8_t i = 0; i < s_ring_n; i++)
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
}

/* 3. STATIC — solid color, no animation */
static void ring_do_static(const led_zone_cfg_t *c, uint8_t s) {
    RGB rgb = hsv_to_rgb((HSV){c->h, c->s, c->v});
    for (uint8_t i = 0; i < s_ring_n; i++)
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
}

/* 4. RAINBOW — full gradient spinning clockwise */
static void ring_do_rainbow(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t base = (uint8_t)(r_pos >> 8);
    uint8_t step = (uint8_t)(256u / s_ring_n);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        RGB rgb = hsv_to_rgb((HSV){(uint8_t)(base + i * step), c->s, c->v});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 5. DUAL — two comets 180° apart */
static void ring_do_dual(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t  bright[RING_FX_MAX_LEDS] = {0};
    uint16_t period = (uint16_t)s_ring_n << 8;
    uint16_t h1     = (r_pos >> 4) % period;
    draw_comet_ring(bright, h1);
    draw_comet_ring(bright, (h1 + (period >> 1)) % period);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t b = scale8(bright[i], c->v);
        RGB rgb   = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 6. TWINKLE — each LED breathes independently, new random hue each cycle
 *
 * Phase of LED i = phi_hi + k_gold[i] so no two LEDs are in sync.
 * When phase wraps (decreases), the LED's hue is re-randomised.
 * Hue update happens in ring_fx_tick, not here.                   */
static void ring_do_twinkle(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(r_phi >> 8);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t b = scale8(sin2_8((uint8_t)(phi_hi + k_gold[i % 24])), c->v);
        RGB rgb   = hsv_to_rgb((HSV){r_hue[i], c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 7. MOOD — whole ring drifts slowly through hue wheel
 *
 * All LEDs same color; hue = phi_hi (advances at speed/4 rate).
 * At speed=64 the full rainbow takes ~4 s — very ambient.        */
static void ring_do_mood(const led_zone_cfg_t *c, uint8_t s) {
    RGB rgb = hsv_to_rgb((HSV){(uint8_t)(r_phi >> 8), c->s, c->v});
    for (uint8_t i = 0; i < s_ring_n; i++)
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
}

/* 8. SPARKLE — brief flashes per LED, each flash a new random hue
 *
 * Uses r_pos (fast) so flashes are quick.  Only the top 18% of the
 * sin² cycle produces light → each LED is dark ~82% of the time.
 * The narrow duty cycle, random hue, and asynchronous golden-angle
 * phasing together create a glitter / confetti effect.            */
#define SPARKLE_THRESH 210u
static void ring_do_sparkle(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t pos_hi = (uint8_t)(r_pos >> 8);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t s2 = sin2_8((uint8_t)(pos_hi + k_gold[i % 24]));
        uint8_t b  = 0;
        if (s2 > SPARKLE_THRESH) {
            uint8_t peak = (uint8_t)((uint16_t)(s2 - SPARKLE_THRESH) * 255u /
                                     (255u - SPARKLE_THRESH));
            b = scale8(peak, c->v);
        }
        RGB rgb = hsv_to_rgb((HSV){r_hue[i], c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 9. WAVE — smooth sine-bell of brightness orbits the ring
 *
 * Different from CHASE: no sharp comet tail.  Instead a sin⁴ bell
 * shaped zone of light glides around — half the ring is bright,
 * the other half fades to dark.  Looks like light reflecting off a
 * slowly rotating metallic surface.
 *
 * Implementation: dist = angular distance from peak, mapped 0–255
 * for a full ring.  Brightness = sin⁴(128 − dist/2):
 *   dist = 0   → sin⁴(128) = 255  (peak, full bright)
 *   dist = 128 → sin⁴(64)  ≈ 15   (quarter ring away, dim)
 *   dist = 255 → sin⁴(1)   ≈ 0    (opposite side, dark)         */
static void ring_do_wave(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t base = (uint8_t)(r_pos >> 8);
    uint8_t step = (uint8_t)(256u / s_ring_n);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t dist = base - (uint8_t)(i * step);          /* angular dist  */
        uint8_t bell = sin4_8((uint8_t)(128u - (dist >> 1)));
        uint8_t b    = scale8(bell, c->v);
        RGB     rgb  = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 10. THEATER — every 3rd LED on, group marches clockwise
 *
 * Classic theater-chase.  At any instant exactly ⌊n/3⌋ LEDs are lit.
 * The group cycles through 3 slots per full pos cycle (~512 ms at
 * speed=128 → each slot lasts ~171 ms).                           */
static void ring_do_theater(const led_zone_cfg_t *c, uint8_t s) {
    /* slot ∈ {0,1,2}: which residue class is lit this frame */
    uint8_t slot = (uint8_t)((uint16_t)((uint8_t)(r_pos >> 8)) * 3u >> 8);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t b = ((i % 3u) == slot) ? c->v : 0u;
        RGB rgb   = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 11. SPLIT — top half vs bottom half breathe in antiphase
 *
 * LEDs 0..n/2-1 (top):    phase = phi_hi
 * LEDs n/2..n-1 (bottom): phase = phi_hi + 128  (opposite phase)
 *
 * When the top half is at peak brightness the bottom is dark, and
 * vice-versa.  On a circular ring this creates an alternating glow
 * that travels "up and down" the keyboard case.                   */
static void ring_do_split(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(r_phi >> 8);
    uint8_t half   = s_ring_n >> 1;
    uint8_t bA     = scale8(sin4_8(phi_hi), c->v);
    uint8_t bB     = scale8(sin4_8(phi_hi + 128u), c->v);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t b = (i < half) ? bA : bB;
        RGB rgb   = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 12. AURORA — per-LED independent hue and brightness drift
 *
 * Each LED drifts independently in both hue and brightness:
 *   hue[i]        = base_hue + (phi_hi >> 1) + k_gold[i] / 3
 *   brightness[i] = sin²( phi_hi + k_gold[(i*7) % 24] )
 *
 * k_gold[(i*7)%24] cycles through all 24 golden-angle values in a
 * different order, ensuring hue and brightness desynchronise per LED.
 *
 * Result: a slowly shifting northern-lights look where colours are
 * all related to the base hue but each LED breathes at its own pace
 * with slightly different colour.  Best at low speed (32–64).     */
static void ring_do_aurora(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(r_phi >> 8);
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t h    = (uint8_t)(c->h + (phi_hi >> 1) + k_gold[i % 24] / 3u);
        uint8_t bidx = (uint8_t)((i * 7u) % 24u);
        uint8_t b    = scale8(sin2_8((uint8_t)(phi_hi + k_gold[bidx])), c->v);
        RGB rgb = hsv_to_rgb((HSV){h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* ════════════════════════════════════════════════════════════════
 * RING — PUBLIC API
 * ════════════════════════════════════════════════════════════════ */

void ring_fx_init(uint8_t n, mechlovin_set_color_fn_t set_fn, mechlovin_get_color_fn_t get_fn) {
    s_ring_n   = (n > RING_FX_MAX_LEDS) ? RING_FX_MAX_LEDS : n;
    s_ring_set = set_fn;
    s_ring_get = get_fn;
    ring_fx_reset();
}

void ring_fx_reset(void) {
    r_pos = 0;
    r_phi = 0;
    for (uint8_t i = 0; i < s_ring_n; i++) {
        r_hue[i] = rng8();
        r_pp[i]  = k_gold[i % 24];
        r_ph[i]  = k_gold[i % 24];
    }
}

void ring_fx_tick(uint32_t elapsed_ms, const led_zone_cfg_t *cfg) {
    /* SYNC and STATIC never advance */
    if (cfg->mode == RING_FX_SYNC || cfg->mode == RING_FX_STATIC) return;

    if (elapsed_ms > 20) elapsed_ms = 20;          /* cap jump on wakeup */
    uint8_t spd = cfg->speed ? cfg->speed : 1;
    r_pos += (uint16_t)(elapsed_ms * spd);
    r_phi += (uint16_t)(elapsed_ms * (spd >> 2));

    /* Re-seed per-LED hues when their brightness cycle wraps.
     * Detection: current phase < previous phase by more than 10
     *   (the gap guard prevents false triggers near boundary).    */
    if (cfg->mode == RING_FX_TWINKLE) {
        uint8_t phi_hi = (uint8_t)(r_phi >> 8);
        for (uint8_t i = 0; i < s_ring_n; i++) {
            uint8_t cur = phi_hi + k_gold[i % 24];
            if (cur < r_ph[i] && (r_ph[i] - cur) > 10) r_hue[i] = rng8();
            r_ph[i] = cur;
        }
    } else if (cfg->mode == RING_FX_SPARKLE) {
        uint8_t pos_hi = (uint8_t)(r_pos >> 8);
        for (uint8_t i = 0; i < s_ring_n; i++) {
            uint8_t cur = pos_hi + k_gold[i % 24];
            if (cur < r_pp[i] && (r_pp[i] - cur) > 10) r_hue[i] = rng8();
            r_pp[i] = cur;
        }
    }
}

void ring_fx_render(const led_zone_cfg_t *cfg, uint8_t led_start) {
    if (!s_ring_set) return;
    switch (cfg->mode) {
        case RING_FX_SYNC:    ring_do_sync(cfg,    led_start); break;
        case RING_FX_CHASE:   ring_do_chase(cfg,   led_start); break;
        case RING_FX_BREATHE: ring_do_breathe(cfg, led_start); break;
        case RING_FX_STATIC:  ring_do_static(cfg,  led_start); break;
        case RING_FX_RAINBOW: ring_do_rainbow(cfg, led_start); break;
        case RING_FX_DUAL:    ring_do_dual(cfg,    led_start); break;
        case RING_FX_TWINKLE: ring_do_twinkle(cfg, led_start); break;
        case RING_FX_MOOD:    ring_do_mood(cfg,    led_start); break;
        case RING_FX_SPARKLE: ring_do_sparkle(cfg, led_start); break;
        case RING_FX_WAVE:    ring_do_wave(cfg,    led_start); break;
        case RING_FX_THEATER: ring_do_theater(cfg, led_start); break;
        case RING_FX_SPLIT:   ring_do_split(cfg,   led_start); break;
        case RING_FX_AURORA:  ring_do_aurora(cfg,  led_start); break;
        default:              ring_do_chase(cfg,   led_start); break;
    }
}

/* ════════════════════════════════════════════════════════════════
 * CENTER — INTERNAL STATE
 *
 * 4 LEDs, clockwise: 0=TL  1=TR  2=BR  3=BL
 * ════════════════════════════════════════════════════════════════ */
#define CTR_N 4

static mechlovin_set_color_fn_t s_ctr_set = NULL;
static mechlovin_get_color_fn_t s_ctr_get = NULL;

static uint16_t c_pos = 0;   /* fast: rotate, spin, knight   */
static uint16_t c_phi = 0;   /* slow: breathe, twinkle, etc. */

static uint8_t c_hue[CTR_N];  /* per-LED hue for twinkle     */
static uint8_t c_ph[CTR_N];   /* previous phi phase per LED  */

/* Quarter-cycle offsets: 0°, 90°, 180°, 270° → peak cycles through corners */
static const uint8_t k_ctr_q[CTR_N] = { 0, 64, 128, 192 };

/* ════════════════════════════════════════════════════════════════
 * CENTER — EFFECT RENDERERS
 * ════════════════════════════════════════════════════════════════ */

/* 0. SYNC — scale QMK's rendered colors by cfg->v */
static void ctr_do_sync(const led_zone_cfg_t *c, uint8_t s) {
    if (!s_ctr_get || c->v == 255) return;
    for (uint8_t i = 0; i < CTR_N; i++) {
        RGB col = s_ctr_get(s + i);
        s_ctr_set(s + i,
                  scale8(col.r, c->v),
                  scale8(col.g, c->v),
                  scale8(col.b, c->v));
    }
}

/* 1. STATIC */
static void ctr_do_static(const led_zone_cfg_t *c, uint8_t s) {
    RGB rgb = hsv_to_rgb((HSV){c->h, c->s, c->v});
    for (uint8_t i = 0; i < CTR_N; i++)
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
}

/* 2. BREATHE — all 4 together, sin⁴ */
static void ctr_do_breathe(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t b   = scale8(sin4_8((uint8_t)(c_phi >> 8)), c->v);
    RGB     rgb = hsv_to_rgb((HSV){c->h, c->s, b});
    for (uint8_t i = 0; i < CTR_N; i++)
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
}

/* 3. ROTATE — comet chases clockwise TL→TR→BR→BL
 *
 * 4-LED comet: tail length 2 so 3 LEDs are lit, 1 is dark.
 * Longer tail would make it look "all on" at 4 LEDs.             */
#define CTR_TAIL_LEN 2
static const uint8_t k_ctr_tail[CTR_TAIL_LEN + 2] = { 255, 100, 30, 0 };

static void ctr_do_rotate(const led_zone_cfg_t *c, uint8_t s) {
    uint16_t period = (uint16_t)CTR_N << 8;
    uint16_t head   = (c_pos >> 4) % period;
    for (uint8_t i = 0; i < CTR_N; i++) {
        uint16_t dist = (head + period - ((uint16_t)i << 8)) % period;
        uint8_t  di   = (uint8_t)(dist >> 8);
        uint8_t  df   = (uint8_t)(dist & 0xFF);
        uint8_t  fade = 0;
        if (di <= CTR_TAIL_LEN) {
            int16_t f0 = k_ctr_tail[di], f1 = k_ctr_tail[di + 1];
            fade = (uint8_t)(f0 + ((f1 - f0) * df >> 8));
        }
        RGB rgb = hsv_to_rgb((HSV){c->h, c->s, scale8(fade, c->v)});
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 4. DIAGONAL — {TL,BR} vs {TR,BL} breathe 180° apart → pulsing X
 *
 * Pair A (main diagonal):    TL=0, BR=2   phase = phi_hi
 * Pair B (anti-diagonal):    TR=1, BL=3   phase = phi_hi + 128
 * One pair is always bright → center is never completely dark.   */
static void ctr_do_diagonal(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(c_phi >> 8);
    uint8_t bA     = scale8(sin2_8(phi_hi),        c->v);
    uint8_t bB     = scale8(sin2_8(phi_hi + 128u), c->v);
    RGB     rgbA   = hsv_to_rgb((HSV){c->h, c->s, bA});
    RGB     rgbB   = hsv_to_rgb((HSV){c->h, c->s, bB});
    s_ctr_set(s + 0, rgbA.r, rgbA.g, rgbA.b);   /* TL */
    s_ctr_set(s + 1, rgbB.r, rgbB.g, rgbB.b);   /* TR */
    s_ctr_set(s + 2, rgbA.r, rgbA.g, rgbA.b);   /* BR */
    s_ctr_set(s + 3, rgbB.r, rgbB.g, rgbB.b);   /* BL */
}

/* 5. TWINKLE — 4 stars breathing independently with random hues
 *
 * Quarter-cycle offsets (k_ctr_q) ensure one LED is always near
 * its peak → center is never completely dark.                    */
static void ctr_do_twinkle(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(c_phi >> 8);
    for (uint8_t i = 0; i < CTR_N; i++) {
        uint8_t b   = scale8(sin2_8((uint8_t)(phi_hi + k_ctr_q[i])), c->v);
        RGB     rgb = hsv_to_rgb((HSV){c_hue[i], c->s, b});
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 6. SPIN — rainbow gradient rotates clockwise around 4 corners
 *
 * Hue step = 64 per corner (quarter of color wheel) so all 4 hues
 * are always different.  base_hue advances → gradient rotates.   */
static void ctr_do_spin(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t base = (uint8_t)(c_pos >> 8);
    for (uint8_t i = 0; i < CTR_N; i++) {
        RGB rgb = hsv_to_rgb((HSV){(uint8_t)(base + i * 64u), c->s, c->v});
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 7. CASCADE — TL triggers first, then TR, BR, BL (domino effect)
 *
 * Phase offset grows by 55 per LED (55 × 4 = 220 ≈ 7/8 of a cycle)
 * so the last LED starts just before the first resets.           */
static const uint8_t k_casc[CTR_N] = { 0, 55, 110, 165 };
static void ctr_do_cascade(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(c_phi >> 8);
    for (uint8_t i = 0; i < CTR_N; i++) {
        uint8_t b   = scale8(sin2_8((uint8_t)(phi_hi + k_casc[i])), c->v);
        RGB     rgb = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* 8. CROSS — {TL,TR} top vs {BL,BR} bottom breathe 180° apart
 *
 * Complement to DIAGONAL: where DIAGONAL splits along diagonals,
 * CROSS splits along the horizontal midline.
 * Pair T (top):    TL=0, TR=1   phase = phi_hi
 * Pair B (bottom): BR=2, BL=3   phase = phi_hi + 128             */
static void ctr_do_cross(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t phi_hi = (uint8_t)(c_phi >> 8);
    uint8_t bT     = scale8(sin2_8(phi_hi),        c->v);
    uint8_t bB     = scale8(sin2_8(phi_hi + 128u), c->v);
    RGB rgbT = hsv_to_rgb((HSV){c->h, c->s, bT});
    RGB rgbB = hsv_to_rgb((HSV){c->h, c->s, bB});
    s_ctr_set(s + 0, rgbT.r, rgbT.g, rgbT.b);   /* TL */
    s_ctr_set(s + 1, rgbT.r, rgbT.g, rgbT.b);   /* TR */
    s_ctr_set(s + 2, rgbB.r, rgbB.g, rgbB.b);   /* BR */
    s_ctr_set(s + 3, rgbB.r, rgbB.g, rgbB.b);   /* BL */
}

/* 9. KNIGHT — brightness peak orbits all 4 corners smoothly
 *
 * Unlike ROTATE (sharp comet), here ALL 4 LEDs are always glowing.
 * Each LED's brightness = sin²(pos_hi + quarter_offset[i]).
 * Quarter offsets → the peak sweeps through each corner in turn.
 *
 * Visual: a soft spotlight that sweeps continuously around all
 * 4 corners without any LED ever going fully dark.               */
static void ctr_do_knight(const led_zone_cfg_t *c, uint8_t s) {
    uint8_t pos_hi = (uint8_t)(c_pos >> 8);
    for (uint8_t i = 0; i < CTR_N; i++) {
        uint8_t b   = scale8(sin2_8((uint8_t)(pos_hi + k_ctr_q[i])), c->v);
        RGB     rgb = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ctr_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}

/* ════════════════════════════════════════════════════════════════
 * CENTER — PUBLIC API
 * ════════════════════════════════════════════════════════════════ */

void center_fx_init(mechlovin_set_color_fn_t set_fn, mechlovin_get_color_fn_t get_fn) {
    s_ctr_set = set_fn;
    s_ctr_get = get_fn;
    center_fx_reset();
}

void center_fx_reset(void) {
    c_pos = 0;
    c_phi = 0;
    for (uint8_t i = 0; i < CTR_N; i++) {
        c_hue[i] = rng8();
        c_ph[i]  = k_ctr_q[i];
    }
}

void center_fx_tick(uint32_t elapsed_ms, const led_zone_cfg_t *cfg) {
    if (cfg->mode == CENTER_FX_SYNC || cfg->mode == CENTER_FX_STATIC) return;
    if (elapsed_ms > 20) elapsed_ms = 20;
    uint8_t spd = cfg->speed ? cfg->speed : 1;
    c_pos += (uint16_t)(elapsed_ms * spd);
    c_phi += (uint16_t)(elapsed_ms * (spd >> 2));

    /* Re-seed twinkle hues on phase wrap */
    if (cfg->mode == CENTER_FX_TWINKLE) {
        uint8_t phi_hi = (uint8_t)(c_phi >> 8);
        for (uint8_t i = 0; i < CTR_N; i++) {
            uint8_t cur = phi_hi + k_ctr_q[i];
            if (cur < c_ph[i] && (c_ph[i] - cur) > 10) c_hue[i] = rng8();
            c_ph[i] = cur;
        }
    }
}

void center_fx_render(const led_zone_cfg_t *cfg, uint8_t led_start) {
    if (!s_ctr_set) return;
    switch (cfg->mode) {
        case CENTER_FX_SYNC:     ctr_do_sync(cfg,     led_start); break;
        case CENTER_FX_STATIC:   ctr_do_static(cfg,   led_start); break;
        case CENTER_FX_BREATHE:  ctr_do_breathe(cfg,  led_start); break;
        case CENTER_FX_ROTATE:   ctr_do_rotate(cfg,   led_start); break;
        case CENTER_FX_DIAGONAL: ctr_do_diagonal(cfg, led_start); break;
        case CENTER_FX_TWINKLE:  ctr_do_twinkle(cfg,  led_start); break;
        case CENTER_FX_SPIN:     ctr_do_spin(cfg,     led_start); break;
        case CENTER_FX_CASCADE:  ctr_do_cascade(cfg,  led_start); break;
        case CENTER_FX_CROSS:    ctr_do_cross(cfg,    led_start); break;
        case CENTER_FX_KNIGHT:   ctr_do_knight(cfg,   led_start); break;
        default:                 ctr_do_static(cfg,   led_start); break;
    }
}