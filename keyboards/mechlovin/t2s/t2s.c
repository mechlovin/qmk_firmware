/* Copyright 2019 Mechlovin
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
#include "quantum.h"
#include "timer.h"

#define PIN_LED1 E6  // Chân D3
#define PIN_LED2 C6  // Chân F4

static bool blink_active = false;  // Trạng thái nhấp nháy
static uint16_t last_time = 0;     // Lưu thời gian lần cuối thay đổi LED
static bool led_state = false;     // Trạng thái LED (bật/tắt)

void led_init_ports(void) {
    gpio_set_pin_output(D3);
  
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, 1)) {
        blink_active = true;  // Kích hoạt nhấp nháy khi vào layer 1
        backlight_disable();  // Tắt backlight để dùng C6 làm LED nhấp nháy
    } else {
        blink_active = false;  // Dừng nhấp nháy khi rời khỏi layer 1
        gpio_write_pin_low(PIN_LED1); // Tắt LED D3
        gpio_write_pin_low(PIN_LED2); // Tắt LED F4
        backlight_enable();  // Bật lại backlight khi rời layer 1
    }
    if (layer_state_cmp(state, 2)) {
        gpio_write_pin_low(D3); // Tắt LED D3
    } else {
        gpio_write_pin_high(D3); // Tắt LED D3
    }
    return state;
}

void matrix_scan_user(void) {
    if (blink_active) {
        if (timer_elapsed(last_time) >= (led_state ? 500 : 500)) {  // Đổi trạng thái mỗi 50ms hoặc 20ms
            led_state = !led_state;
            gpio_set_pin_output(PIN_LED1);
            gpio_set_pin_output(PIN_LED2);
            gpio_write_pin(PIN_LED1, led_state);
            gpio_write_pin(PIN_LED2, led_state);
            last_time = timer_read();
        }
    }
}