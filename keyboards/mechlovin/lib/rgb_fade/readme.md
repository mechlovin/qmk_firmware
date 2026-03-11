# rgb_fade

> Smooth LED fade engine for QMK — RGB Matrix & RGBLight

Supports RGB Matrix only, RGBLight only, or both simultaneously.  
Auto-detects via `RGB_MATRIX_ENABLE` / `RGBLIGHT_ENABLE` — no manual configuration needed.

---

## Getting Started

### 1. `rules.mk`

```makefile
SRC   += keyboards/mechlovin/lib/rgb_fade/rgb_fade.c
VPATH += keyboards/mechlovin/lib/rgb_fade
```

### 2. `config.h`

```c
#define RGB_FADE_ENABLE
```

### 3. Keyboard `.c`

```c
#include "rgb_fade.h"

void keyboard_post_init_kb(void) {
    rgb_fade_init();
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
    rgb_fade_tick();
    matrix_scan_user();
}
```

---

## Timing

Override in `config.h`:

| Define | Default | Description |
|--------|---------|-------------|
| `RGB_FADE_TICK_MS` | `8` | State machine tick interval (ms) |
| `RGB_FADE_POWER_STEP` | `12` | Brightness step per tick for power on/off (~170ms) |
| `RGB_FADE_OUT_MS` | `20` | Crossfade-out duration |
| `RGB_FADE_IN_MS` | `200` | Crossfade-in duration |

Example:

```c
// config.h
#define RGB_FADE_OUT_MS      20
#define RGB_FADE_IN_MS       200
#define RGB_FADE_POWER_STEP  12
```

---

## API

| Function | Description |
|----------|-------------|
| `rgb_fade_init()` | Call from `keyboard_post_init_kb` — starts boot fade-in |
| `rgb_fade_tick()` | Call from `matrix_scan_kb` — drives both state machines |
| `rgb_fade_matrix_in()` | RGB Matrix power on with fade |
| `rgb_fade_matrix_out()` | RGB Matrix power off with fade |
| `rgb_fade_rgblight_in()` | RGBLight power on with fade |
| `rgb_fade_rgblight_out()` | RGBLight power off with fade |

When `RGB_FADE_ENABLE` is not defined, all functions compile to empty stubs — zero overhead.

---

## How It Works

**Val-patching** — instead of disabling/enabling the LED driver on effect change, the engine patches the brightness value directly (`hsv.v` for RGB Matrix, `rgblight_config.val` for RGBLight) each tick. The driver always runs; only brightness changes.

```
Effect change:
  XFADE_OUT  brightness → 0         (RGB_FADE_OUT_MS)
  Midpoint   switch mode while dark — no flash
  XFADE_IN   brightness 0 → target  (RGB_FADE_IN_MS)

Power on/off:
  POWER_OUT  brightness → 0         step by RGB_FADE_POWER_STEP / tick
  POWER_IN   brightness 0 → target  step by RGB_FADE_POWER_STEP / tick
```

> **Note:** Static RGBLight effects (solid color, gradient, christmas…) only render once on mode change. `rgb_fade` uses `rgblight_sethsv_noeeprom()` to force a re-render each tick during fade.

---

## Compatibility

| MCU | RGBLight Driver | Tested |
|-----|-----------------|--------|
| STM32F103 | WS2812 SPI | ✅ |
| STM32F103 | WS2812 bitbang | ✅ |

> **STM32F103 + WS2812 SPI:** Do NOT call `rgblight_enable_noeeprom()` inside `rgb_fade_init()` — calling it before the SPI driver is fully ready causes a HardFault. `rgb_fade` handles this correctly.

---

## Keyboards

| Keyboard | RGB Matrix | RGBLight |
|----------|------------|----------|
| Zed65 RGB Rev1 | IS31FL3741 — 66 LED per-key | WS2812 — 32 LED underglow + logo |
| Zed60 | — | WS2812 SPI — 22 LED underglow |

---
