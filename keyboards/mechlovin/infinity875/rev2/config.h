/*
Copyright 2024 Mechlovin'

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef RGBLIGHT_ENABLE
// ── WS2812 via SPI2 (pin B15 = MOSI of SPID2) ── giữ nguyên từ config gốc ──
#define WS2812_SPI_DRIVER SPID2
#define WS2812_SPI_USE_CIRCULAR_BUFFER

// ── LED chain constants (dùng trong rev2.c/rev2.h) ───────────────────────────
//  LED  0 – 23  = Underglow PCB (24 bóng)
//  LED 24 – 43  = Ext module tối đa 20 bóng (daisy-chain sau LED 23)
//
//  KHÔNG define RGBLIGHT_LED_COUNT ở đây — để keyboard.json (led_count: 44)
//  làm nguồn duy nhất, tránh warning "overwriting rgblight.led_count in info.json".
#define UNDERGLOW_LED_COUNT  24
#define EXT_LED_MAX_COUNT    20
#define EXT_LED_START        UNDERGLOW_LED_COUNT   // = 24

// ── VIA custom EEPROM size ────────────────────────────────────────────────────
// Kích thước vùng lưu ext_led_state_t = 9 bytes (xem rev2.h)
// VIA_EEPROM_CUSTOM_CONFIG_ADDR được via.h định nghĩa tự động dựa vào size này.
// Fallback nếu QMK version chưa có: xem rev2.h
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE  9
#define DYNAMIC_KEYMAP_LAYER_COUNT     4

#endif // RGBLIGHT_ENABLE