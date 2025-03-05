#include "quantum.h"
#include "rgblight.h"
#include "eeprom.h"

// Biến lưu trữ số lượng LED sáng và chế độ LED
uint8_t led_count = 0;
uint8_t led_mode = 0;

// Khai báo nguyên mẫu (prototype) của hàm apply_led_settings
void apply_led_settings(void);

// Hàm khởi tạo
void keyboard_post_init_user(void) {
    // Khôi phục số lượng LED sáng và chế độ LED từ EEPROM
    led_count = eeprom_read_byte((uint8_t*)0);
    led_mode = eeprom_read_byte((uint8_t*)1);

    // Đảm bảo giá trị khôi phục hợp lệ
    if (led_count > RGBLIGHT_LED_COUNT) {
        led_count = RGBLIGHT_LED_COUNT;
    }
    if (led_mode >= RGBLIGHT_MODES) { // RGBLIGHT_MODES là số lượng chế độ hiệu ứng
        led_mode = led_mode % RGBLIGHT_MODES; // Giữ nguyên giá trị hợp lệ
    }

    // Áp dụng cài đặt LED
    apply_led_settings();
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(led_mode); // Khôi phục chế độ LED
}

// Hàm áp dụng cài đặt LED
void apply_led_settings(void) {
    // Thiết lập phạm vi hiệu ứng
    rgblight_set_effect_range(0, led_count);

    // Tắt các LED nằm ngoài phạm vi
    for (uint8_t i = led_count; i < RGBLIGHT_LED_COUNT; i++) {
        rgblight_setrgb_at(0, 0, 0, i); // Tắt LED tại vị trí i
    }
}

// Hàm xử lý encoder
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        // Tăng số lượng LED sáng
        if (led_count < RGBLIGHT_LED_COUNT) {
            led_count++;
        }
    } else {
        // Giảm số lượng LED sáng
        if (led_count > 0) {
            led_count--;
        }
    }

    // Áp dụng cài đặt LED mới
    apply_led_settings();

    // Lưu số lượng LED sáng vào EEPROM
    eeprom_update_byte((uint8_t*)0, led_count);

    return true;
}

// Hàm xử lý thay đổi chế độ LED
void rgblight_mode_update_user(uint8_t mode) {
    eeprom_update_byte((uint8_t*)1, led_mode); // Lưu chế độ LED vào EEPROM
    led_mode = mode; // Cập nhật chế độ LED
}