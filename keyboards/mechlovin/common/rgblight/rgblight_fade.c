#include "rgblight_fade.h"
#include "timer.h"
#include "rgblight.h"

// trạng thái fade
static bool    _fade_active     = false;
static uint8_t _fade_cur        = 0;
static uint8_t _fade_target     = 0;
static uint16_t _fade_last_tick = 0;

// nhớ on/off và mode trước đó
static bool    _last_enabled = false;
static uint8_t _last_mode    = 0;

// nhớ speed ban đầu để restore
static uint8_t _fade_saved_speed = 0;

void rgb_fade_init(void) {
    _last_enabled = rgblight_is_enabled();
    _last_mode    = rgblight_get_mode();
}

void rgb_fade_start(uint8_t target) {
    // 1) nhớ speed cũ và override lên max để chạy effect nhanh nhất
    _fade_saved_speed = rgblight_get_speed();
    rgblight_set_speed_noeeprom(UINT8_MAX);

    // 2) thiết lập fade
    _fade_target     = target;
    _fade_cur        = 0;
    _fade_last_tick  = timer_read();
    _fade_active     = true;

    // 3) reset LED về 0
    rgblight_disable_noeeprom();
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(
        rgblight_get_hue(),
        rgblight_get_sat(),
        0
    );
}

void rgb_fade_loop(void) {
    bool    en   = rgblight_is_enabled();
    uint8_t mode = rgblight_get_mode();

    // nếu chưa fade thì detect sự kiện
    if (!_fade_active) {
        if (!_last_enabled && en) {
            // toggle-on
            rgb_fade_start(rgblight_get_val());
        }
        else if (en && mode != _last_mode) {
            // mode-change
            rgb_fade_start(rgblight_get_val());
        }
        _last_enabled = en;
        _last_mode    = mode;
    }

    // nếu đang fade → thực thi
    if (_fade_active) {
        if (timer_elapsed(_fade_last_tick) < RGFL_FADE_INTERVAL) return;
        _fade_last_tick = timer_read();

        uint8_t step = RGFL_FADE_IN_STEP;
        if (_fade_cur + step < _fade_target) {
            _fade_cur += step;
            rgblight_sethsv_noeeprom(
                rgblight_get_hue(),
                rgblight_get_sat(),
                _fade_cur
            );
        } else {
            // hoàn tất fade: commit brightness và restore speed
            rgblight_sethsv(
                rgblight_get_hue(),
                rgblight_get_sat(),
                _fade_target
            );
            rgblight_set_speed_noeeprom(_fade_saved_speed);
            _fade_active = false;
        }
    }
}

// Ghi đè weak hooks trong core
void rgblight_init_user(void) {
    rgb_fade_init();
}
void rgblight_task_user(void) {
    rgb_fade_loop();
}
