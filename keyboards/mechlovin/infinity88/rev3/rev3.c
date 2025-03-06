#include "quantum.h"
#include "rgblight.h"
#include "via.h"

// Định nghĩa các giá trị
enum via_rgblight_value {
    id_rgblight_logo_toggle = 1, // Value ID cho bật/tắt rgblight_logo
    id_rgblight_ug_toggle   = 2, // Value ID cho bật/tắt rgblight_ug
};

// Cấu trúc lưu trữ trạng thái
typedef struct {
    bool logo_enabled; // Trạng thái bật/tắt rgblight_logo
    bool ug_enabled;   // Trạng thái bật/tắt rgblight_ug
} custom_rgblight_config_t;

custom_rgblight_config_t g_custom_rgblight_config = {
    .logo_enabled = false,
    .ug_enabled = false,
};

// Prototype các hàm
void rgblight_config_set_value(uint8_t *data);
void rgblight_config_get_value(uint8_t *data);
void rgblight_config_save(void);
void update_rgblight(void);

// Hàm xử lý command từ VIA
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value:
                rgblight_config_set_value(value_id_and_data);
                break;
            case id_custom_get_value:
                rgblight_config_get_value(value_id_and_data);
                break;
            case id_custom_save:
                rgblight_config_save();
                break;
            default:
                *command_id = id_unhandled;
                break;
        }
        return;
    }
    *command_id = id_unhandled;
}

// Hàm thiết lập giá trị
void rgblight_config_set_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_rgblight_logo_toggle:
            g_custom_rgblight_config.logo_enabled = (bool)*value_data;
            break;
        case id_rgblight_ug_toggle:
            g_custom_rgblight_config.ug_enabled = (bool)*value_data;
            break;
    }
    update_rgblight();
}

// Hàm lấy giá trị
void rgblight_config_get_value(uint8_t *data) {
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_rgblight_logo_toggle:
            *value_data = (uint8_t)g_custom_rgblight_config.logo_enabled;
            break;
        case id_rgblight_ug_toggle:
            *value_data = (uint8_t)g_custom_rgblight_config.ug_enabled;
            break;
    }
}

// Hàm lưu giá trị vào EEPROM
#define CUSTOM_RGBLIGHT_CONFIG_EEPROM_ADDR 0x2000
void rgblight_config_save(void) {
    eeprom_update_block(&g_custom_rgblight_config, (void*)CUSTOM_RGBLIGHT_CONFIG_EEPROM_ADDR, sizeof(custom_rgblight_config_t));
}

// Hàm cập nhật trạng thái LED
void update_rgblight(void) {
    if (g_custom_rgblight_config.logo_enabled && g_custom_rgblight_config.ug_enabled) {
        // Nếu cả hai đang bật, logo sáng cùng hiệu ứng với UG
        rgblight_enable();
        rgblight_set_effect_range(0, 30);
    } else if (!g_custom_rgblight_config.logo_enabled && !g_custom_rgblight_config.ug_enabled) {
        // Nếu cả hai đều tắt, tắt toàn bộ LED
        rgblight_disable();
    } else {
        // Nếu chỉ bật logo
        if (g_custom_rgblight_config.logo_enabled) {
            rgblight_enable();
            rgblight_set_effect_range(24, 5);
        } else {
            rgblight_enable();
            rgblight_sethsv_range(0, 0, 0, 24, 30);
        }

        // Nếu chỉ bật UG
        if (g_custom_rgblight_config.ug_enabled) {
            rgblight_enable();
            rgblight_set_effect_range(0, 24);
        } else {
            rgblight_enable();
            rgblight_sethsv_range(0, 0, 0, 0, 24);
        }
    }
    
}
