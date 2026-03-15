# module_effects — Mechlovin' LED Animation Library

Thư viện LED dùng chung cho QMK firmware, dành cho các bàn phím Mechlovin' có vùng LED ring và center độc lập.

---

## Tổng quan kiến trúc

```
keyboards/mechlovin/
├── lib/
│   ├── module_effects.h     ← API công khai
│   └── module_effects.c     ← Toàn bộ logic hoạt hình
└── <keyboard>/
    ├── <keyboard>.h         ← #include "module_effects.h"
    ├── <keyboard>.c         ← Gọi API, xử lý EEPROM / VIA / driver
    └── rules.mk             ← SRC += module_effects.c
````

## Tích hợp nhanh

### 1. rules.mk

```makefile
MECHLOVIN_LIB_PATH := $(realpath $(KEYBOARD_PATH_1)/../../lib)
COMMON_VPATH += $(MECHLOVIN_LIB_PATH)
SRC += module_effects.c
```

> `KEYBOARD_PATH_1` trỏ đến thư mục bàn phím hiện tại.  
> Điều chỉnh số lượng `../` tùy theo độ sâu của thư mục so với `lib/`.

### 2. Định nghĩa callbacks trong keyboard.c

```c
// Mirror buffer — QMK ghi vào đây qua set_color,
// thư viện đọc lại để scale brightness ở SYNC mode.
static RGB s_led_buf[LED_COUNT];

static void _set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (index >= 0 && index < LED_COUNT)
        s_led_buf[index] = (RGB){r, g, b};
    // ghi vào hardware driver (IS31 hoặc WS2812)
    my_driver_set_color(index, r, g, b);
}

static RGB _get_color(int index) {
    if (index >= 0 && index < LED_COUNT)
        return s_led_buf[index];
    return (RGB){0, 0, 0};
}
```

> `_get_color` bắt buộc phải có để SYNC mode hoạt động.  
> Nếu không cần SYNC, truyền `NULL` vào `get_fn`.

### 3. Khởi tạo trong keyboard_post_init_kb

```c
void keyboard_post_init_kb(void) {
    ring_fx_init(RING_LED_COUNT, _set_color, _get_color);
    center_fx_init(_set_color, _get_color);
    keyboard_post_init_user();
}
```

### 4. Advance animation trong housekeeping_task_kb

```c
void housekeeping_task_kb(void) {
    static uint32_t ring_timer   = 0;
    static uint32_t center_timer = 0;

    uint32_t e;

    e = timer_elapsed32(ring_timer);
    if (e > 0) { ring_timer = timer_read32(); ring_fx_tick(e, &ring_cfg); }

    e = timer_elapsed32(center_timer);
    if (e > 0) { center_timer = timer_read32(); center_fx_tick(e, &center_cfg); }
}
```

### 5. Render trong rgb_matrix_indicators_kb

```c
bool rgb_matrix_indicators_kb(void) {
    ring_fx_render(&ring_cfg, RING_LED_START);
    center_fx_render(&center_cfg, CENTER_LED_START);
    return true;
}
```

### 6. Reset khi đổi mode (VIA / keymap)

```c
ring_fx_reset();    // khi ring_cfg.mode thay đổi
center_fx_reset();  // khi center_cfg.mode thay đổi
```

---

## Cấu trúc config

Cả ring và center đều dùng chung một struct:

```c
typedef struct {
    uint8_t mode;   // RING_FX_* hoặc CENTER_FX_*
    uint8_t h;      // hue   0–255
    uint8_t s;      // saturation 0–255
    uint8_t v;      // brightness 0–255  (cũng là cap ở SYNC mode)
    uint8_t speed;  // tốc độ 0–255, cùng scale với QMK rgb_matrix speed
} led_zone_cfg_t;
```

---

## Hiệu ứng Ring (13 mode)

Ring là vòng N LED sắp xếp thành hình tròn. Mặc định hỗ trợ tối đa 24 LED.  
Override bằng `#define RING_FX_MAX_LEDS 32` trước khi include header nếu cần nhiều hơn.

| Value | Tên | Mô tả |
|------:|-----|-------|
| `0` | **Sync with QMK** | QMK effect chạy bình thường. `v` giới hạn brightness tối đa — `v=255` không scale, `v=0` tắt ring. |
| `1` | **Chase** | Một "sao chổi" chạy vòng với đuôi fade mịn, interpolated sub-LED. |
| `2` | **Breathe** | Tất cả LED thở cùng nhau theo đường cong sin⁴ — peak rộng, tắt nhanh. |
| `3` | **Static** | Màu cố định, không có hoạt hình. |
| `4` | **Rainbow** | Gradient cầu vồng đủ màu quay liên tục. |
| `5` | **Dual Chase** | Hai sao chổi đối xứng 180°, chồng brightness khi gặp nhau. |
| `6` | **Twinkle** | Mỗi LED thở độc lập với hue ngẫu nhiên mỗi chu kỳ — giống hiệu ứng sao trên bầu trời. |
| `7` | **Mood** | Toàn bộ ring trôi chậm qua các hue — ambient, giống đèn ngủ. |
| `8` | **Sparkle** | Flash ngắn ngẫu nhiên, mỗi flash một hue khác — như glitter. Chỉ sáng ~18% thời gian. |
| `9` | **Wave** | Vùng sáng hình chuông sin⁴ lướt vòng — nửa ring sáng, nửa tối. Mượt hơn Chase. |
| `10` | **Theater Chase** | Cứ 3 LED thì 1 LED sáng, nhóm dịch chuyển liên tục theo kiểu rạp hát. |
| `11` | **Split** | Nửa trên và nửa dưới thở ngược pha 180° — ánh sáng "bơm" lên xuống. |
| `12` | **Aurora** | Mỗi LED drift hue và brightness độc lập, tất cả liên quan đến base hue — bắc cực quang. |

### Timing model

Hai accumulator 16-bit tự wrap tại 65536:

```
r_pos += speed × elapsed_ms          # fast — vòng ~512ms ở speed=128
r_phi += (speed >> 2) × elapsed_ms   # slow — chu kỳ ~2048ms ≈ QMK breathing
```

| Accumulator | Dùng cho |
|-------------|----------|
| `r_pos` (fast) | Chase, Dual, Rainbow, Wave, Theater, Sparkle |
| `r_phi` (slow) | Breathe, Twinkle, Mood, Split, Aurora |

---

## Hiệu ứng Center (10 mode)

Center là 4 LED ở 4 góc bàn phím, đánh số theo chiều kim đồng hồ từ góc trên-trái:

```
TL(0) ──── TR(1)
  │                │
BL(3) ──── BR(2)
```

> `led_start + 0` = TL, `+1` = TR, `+2` = BR, `+3` = BL

| Value | Tên | Mô tả |
|------:|-----|-------|
| `0` | **Sync with QMK** | QMK effect chạy. `v` cap brightness. |
| `1` | **Static** | 4 LED cùng màu cố định. |
| `2` | **Breathe** | Cả 4 thở cùng nhau, sin⁴. |
| `3` | **Rotate** | Sao chổi ngắn đuổi vòng TL→TR→BR→BL, đuôi 2 LED. |
| `4` | **Diagonal Pulse** | {TL,BR} và {TR,BL} thở ngược pha — tạo pattern chữ **×** nhấp nhô. |
| `5` | **Twinkle** | 4 sao thở độc lập, mỗi chu kỳ đổi hue ngẫu nhiên. |
| `6` | **Spin** | 4 hue cách nhau 90° trên bánh màu, gradient quay liên tục. |
| `7` | **Cascade** | TL sáng trước, rồi TR, BR, BL với delay 55/256 chu kỳ — hiệu ứng domino. |
| `8` | **Cross Pulse** | {TL,TR} và {BR,BL} thở ngược pha — pattern **—** / **—** trên/dưới. |
| `9` | **Knight** | Vùng sáng sin² quét mượt qua cả 4 góc, không LED nào tắt hoàn toàn. |

### Khác biệt Rotate vs Knight

- **Rotate**: Sao chổi có đuôi cứng, 1 LED hoàn toàn tối tại mọi thời điểm — chuyển động rõ ràng.
- **Knight**: Sin² wave qua 4 LED, tất cả luôn có ánh sáng — mượt và ambient hơn.

---

## SYNC mode — điều chỉnh brightness

Đây là tính năng chính cần giải thích kỹ:

```
QMK rgb_matrix chạy effect → gọi _set_color cho tất cả LED
                                      ↓
                              s_led_buf[] (mirror buffer trong keyboard.c)
                                      ↓
rgb_matrix_indicators_kb được gọi
    → ring_fx_render / center_fx_render
        → SYNC mode: đọc s_led_buf qua _get_color
        → scale từng kênh R,G,B × (v / 255)
        → ghi lại qua _set_color
                                      ↓
flush() → hardware nhận giá trị đã scale
```

**Ví dụ thực tế:**

| `v` | Kết quả |
|-----|---------|
| `255` | Không scale, QMK effect đầy đủ brightness |
| `128` | Ring chỉ sáng 50% so với QMK effect |
| `0` | Ring tắt hoàn toàn dù QMK effect đang chạy |

Điều này cho phép 2 zone có brightness độc lập trong cùng một QMK effect, không cần tắt LED bằng tay.

---

## Khai báo EEPROM (8xv2)

```c
typedef struct {
    bool           ring_enabled;
    led_zone_cfg_t ring;           // 5 bytes: mode h s v speed
    bool           center_enabled;
    led_zone_cfg_t center;         // 5 bytes: mode h s v speed
    uint8_t        module_sel;
} kb_eeprom_t;                     // tổng 13 bytes
```

```c
// config.h
#define EECONFIG_KB_DATA_SIZE 13
```

> **Sau khi flash firmware mới:** giữ ESC khi cắm USB để clear EEPROM về default.

---

## Thêm hiệu ứng mới

### Bước 1 — Định nghĩa constant trong module_effects.h

```c
#define RING_FX_MYEFFECT  13
#define RING_FX_MAX       13   // cập nhật MAX
```

### Bước 2 — Viết renderer trong module_effects.c

```c
static void ring_do_myeffect(const led_zone_cfg_t *c, uint8_t s) {
    // c->h, c->s, c->v, c->speed — thông số từ VIA/EEPROM
    // r_pos — fast accumulator (đã advance trong ring_fx_tick)
    // r_phi — slow accumulator
    // s_ring_n — số LED thực tế
    for (uint8_t i = 0; i < s_ring_n; i++) {
        uint8_t b   = /* tính brightness */;
        RGB     rgb = hsv_to_rgb((HSV){c->h, c->s, b});
        s_ring_set(s + i, rgb.r, rgb.g, rgb.b);
    }
}
```

### Bước 3 — Thêm vào switch trong ring_fx_render

```c
case RING_FX_MYEFFECT: ring_do_myeffect(cfg, led_start); break;
```

### Bước 4 — Cập nhật VIA JSON

```json
"options": ["Sync with QMK", "Chase", ..., "Aurora", "My Effect"]
```

---

## Math helpers (nội bộ)

| Hàm | Input | Output | Dùng cho |
|-----|-------|--------|----------|
| `sin2_8(x)` | 0–255 | 0–255 | Breathing tự nhiên, peak ở x=128 |
| `sin4_8(x)` | 0–255 | 0–255 | Breathing "giữ peak lâu hơn", tắt nhanh |
| `scale8(v, top)` | 0–255, 0–255 | 0–255 | Nhân phần trăm không float |
| `rng8()` | — | 0–255 | PRNG XorShift8, không stdlib |
| `tail_bright(dist)` | Q8.8 | 0–255 | Brightness đuôi sao chổi nội suy |

**Golden-angle offsets** `k_gold[24]`: phase offset cho 24 LED, cách nhau 98 ≈ 256×(1−1/φ). Đảm bảo không có 2 LED nào cùng phase trong Twinkle / Sparkle / Aurora.

---

## Tương thích

| Thuộc tính | Giá trị |
|-----------|---------|
| QMK version | ≥ 0.18 |
| MCU | STM32F103CBT6, APM32F103CBT6 (và các MCU khác có ChibiOS) |
| LED driver | IS31FL3731 (I2C), WS2812 (PWM) — thông qua callback, không phụ thuộc trực tiếp |
| Ring size | 1–24 LED (override `RING_FX_MAX_LEDS` nếu cần hơn) |
| Center | Luôn cố định 4 LED |
| RAM | ~60 bytes state (ring) + ~20 bytes (center) |
| Flash | ~3 KB code |

---

## Bàn phím đang dùng thư viện này

| Bàn phím | Ring | Center | Module |
|---------|------|--------|--------|
| Matrix 8XV2 Add | 16 LED | 4 LED góc | IS31FL3731 / WS2812 hot-swap |

---

*Copyright 2026 Mechlovin' Studio — GPL-2.0-or-later*