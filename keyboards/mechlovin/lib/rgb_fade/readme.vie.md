# rgb_fade

> Thư viện fade LED mượt cho QMK — RGB Matrix & RGBLight

Hỗ trợ RGB Matrix only, RGBLight only, hoặc cả hai đồng thời.  
Tự detect qua `RGB_MATRIX_ENABLE` / `RGBLIGHT_ENABLE` — không cần cấu hình thủ công.

---

## Bắt đầu

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

## Thời gian

Ghi đè trong `config.h`:

| Define | Mặc định | Mô tả |
|--------|----------|-------|
| `RGB_FADE_TICK_MS` | `8` | Chu kỳ tick của state machine (ms) |
| `RGB_FADE_POWER_STEP` | `12` | Bước sáng mỗi tick khi bật/tắt (~170ms) |
| `RGB_FADE_OUT_MS` | `20` | Thời gian fade out khi đổi effect |
| `RGB_FADE_IN_MS` | `200` | Thời gian fade in khi đổi effect |

Ví dụ:

```c
// config.h
#define RGB_FADE_OUT_MS      20
#define RGB_FADE_IN_MS       200
#define RGB_FADE_POWER_STEP  12
```

---

## API

| Function | Mô tả |
|----------|-------|
| `rgb_fade_init()` | Gọi từ `keyboard_post_init_kb` — bắt đầu fade-in lúc khởi động |
| `rgb_fade_tick()` | Gọi từ `matrix_scan_kb` — điều khiển state machine |
| `rgb_fade_matrix_in()` | Bật RGB Matrix có animation |
| `rgb_fade_matrix_out()` | Tắt RGB Matrix có animation |
| `rgb_fade_rgblight_in()` | Bật RGBLight có animation |
| `rgb_fade_rgblight_out()` | Tắt RGBLight có animation |

Khi không define `RGB_FADE_ENABLE`, tất cả function compile thành stub rỗng — không tốn tài nguyên.

---

## Cơ chế hoạt động

**Val-patching** — thay vì disable/enable LED driver khi chuyển effect, engine patch trực tiếp giá trị brightness (`hsv.v` cho RGB Matrix, `rgblight_config.val` cho RGBLight) mỗi tick. Driver luôn chạy, chỉ có brightness thay đổi.

```
Đổi effect:
  XFADE_OUT  brightness → 0         (RGB_FADE_OUT_MS)
  Midpoint   đổi mode khi tối — không chớp
  XFADE_IN   brightness 0 → target  (RGB_FADE_IN_MS)

Bật/tắt:
  POWER_OUT  brightness → 0         tăng RGB_FADE_POWER_STEP mỗi tick
  POWER_IN   brightness 0 → target  tăng RGB_FADE_POWER_STEP mỗi tick
```

> **Lưu ý:** Effect tĩnh của RGBLight (solid, gradient, christmas…) chỉ render một lần khi đổi mode. `rgb_fade` dùng `rgblight_sethsv_noeeprom()` để force re-render mỗi tick trong lúc fade.

---

## Tương thích

| MCU | RGBLight Driver | Đã test |
|-----|-----------------|---------|
| STM32F103 | WS2812 SPI | ✅ |
| STM32F103 | WS2812 bitbang | ✅ |

> **STM32F103 + WS2812 SPI:** Không gọi `rgblight_enable_noeeprom()` bên trong `rgb_fade_init()` — gọi trước khi SPI driver sẵn sàng sẽ gây HardFault. `rgb_fade` đã xử lý đúng điều này.

---

## Bàn phím đang dùng

| Bàn phím | RGB Matrix | RGBLight |
|----------|------------|----------|
| Zed65 RGB Rev1 | IS31FL3741 — 66 LED per-key | WS2812 — 32 LED underglow + logo |
| Zed60 | — | WS2812 SPI — 22 LED underglow |

---
