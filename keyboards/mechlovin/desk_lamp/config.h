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

#define WS2812_SPI_DRIVER SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 6 // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5

// Dung lượng backing (flash thật dùng cho WL) và dung lượng logic trình bày cho EEPROM
// Giá trị an toàn thường dùng: 4096/2048; có thể tăng nếu còn flash trống.
#define WEAR_LEVELING_BACKING_SIZE 4096
#define WEAR_LEVELING_LOGICAL_SIZE 2048

// Số layer VIA lưu trong EEPROM (mặc định 8). Giảm xuống 4 hoặc 2.
#define DYNAMIC_KEYMAP_LAYER_COUNT 1

// Giảm/loại bỏ vùng macro của VIA (mặc định 16 macro).
#define DYNAMIC_KEYMAP_MACRO_COUNT 0

// Nếu có layout options của VIA, giảm về 0 byte.
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 0