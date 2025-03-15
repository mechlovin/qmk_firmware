/* Copyright 2022 QMK
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

 #include "hd44780.h"
#include <util/delay.h>  // Thư viện delay

void keyboard_post_init_kb(void) {
    #ifdef keyboard_post_init_user
        keyboard_post_init_user();
    #endif

    // Khởi tạo màn hình LCD (tắt con trỏ, không nhấp nháy)
    hd44780_init(false, false);
    hd44780_clear();
    hd44780_set_cursor(0, 0);  // Đặt con trỏ về đầu

    // Chờ 2 giây trước khi hiển thị chữ
    _delay_ms(2000);

    // Hiển thị chữ "Hello"
    char text[] = "Hello";
    for (int i = 0; i < 5; i++) {
        hd44780_write(text[i], true);  // Thêm `true` để gửi dữ liệu ký tự
    }
}
