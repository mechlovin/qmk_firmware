/* Copyright 2020 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


 #pragma once
 #include "quantum.h"
 
// Cấu trúc lưu trạng thái đèn LED
typedef struct {
    bool logo_enabled;
    bool ug_enabled;
} custom_rgblight_config_t;

// Biến cấu hình đèn (sử dụng trong keymap.c)
extern custom_rgblight_config_t g_custom_rgblight_config;

// Khai báo các hàm để sử dụng bên ngoài
void rgblight_config_save(void);
void rgblight_config_load(void);
void update_rgblight(void);
