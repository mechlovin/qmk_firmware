#include "quantum.h"
#include "gpio.h"
#include "hal.h"  // Chứa HAL ADC cho STM32

#define NUM_KEYS 16

// MUX control pins
#define S0_PIN MUX_SEL0_PIN
#define S1_PIN MUX_SEL1_PIN
#define S2_PIN MUX_SEL2_PIN
#define S3_PIN MUX_SEL3_PIN
#define COM_PIN HALL_SENSOR_COM_PIN

// Ngưỡng nhận biết có phím nhấn (tuỳ theo từ trường và điện trở pull-up/down)
#define THRESHOLD 1500  // Giá trị ADC tương ứng mức áp lực từ trường

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debounced[MATRIX_ROWS];

void matrix_init_custom(void) {
    // Setup MUX control
    setPinOutput(S0_PIN);
    setPinOutput(S1_PIN);
    setPinOutput(S2_PIN);
    setPinOutput(S3_PIN);

    // Setup analog input cho COM
    setPinInput(COM_PIN);
}

bool read_mux_key(uint8_t mux_index) {
    // Set select lines
    writePin(S0_PIN, mux_index & 0x01);
    writePin(S1_PIN, mux_index & 0x02);
    writePin(S2_PIN, mux_index & 0x04);
    writePin(S3_PIN, mux_index & 0x08);

    wait_us(10);  // đợi MUX ổn định

    // Đọc giá trị ADC trên chân COM (PA4)
    uint16_t adc_value = analogReadPin(COM_PIN);
    return adc_value < THRESHOLD;  // true nếu có nhấn
}

bool matrix_scan_custom(void) {
    bool changed = false;

    for (uint8_t i = 0; i < NUM_KEYS; i++) {
        uint8_t row = i / MATRIX_COLS;
        uint8_t col = i % MATRIX_COLS;

        bool pressed = read_mux_key(i);
        matrix_row_t mask = ((matrix_row_t)1 << col);

        if (pressed) {
            matrix[row] |= mask;
        } else {
            matrix[row] &= ~mask;
        }

        // debounce nếu cần
    }

    memcpy(matrix_debounced, matrix, sizeof(matrix));
    return changed;
}

matrix_row_t matrix_get_row(uint8_t row) {
    return matrix_debounced[row];
}
uint16_t analogReadPin(pin_t pin) {
    // Cấu hình ADC chỉ làm 1 lần nếu chưa khởi tạo
    static bool adc_initialized = false;

    if (!adc_initialized) {
        // Enable ADC Clock
        rcc_periph_clock_enable(RCC_ADC1);
        rcc_periph_clock_enable(RCC_GPIOA);

        // Cấu hình PA4 là analog
        gpio_mode_setup(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO4);

        // Bật ADC và khởi tạo
        adc_power_off(ADC1);
        adc_disable_scan_mode(ADC1);
        adc_set_single_conversion_mode(ADC1);
        adc_set_right_aligned(ADC1);
        adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_239DOT5CYC);
        adc_power_on(ADC1);
        adc_reset_calibration(ADC1);
        adc_calibrate(ADC1);
        adc_initialized = true;
    }

    // Đọc từ kênh ADC_IN9 tương ứng PA4
    uint8_t channel = 9;
    adc_set_regular_sequence(ADC1, 1, &channel);
    adc_start_conversion_regular(ADC1);
    while (!adc_eoc(ADC1));
    return adc_read_regular(ADC1);
}