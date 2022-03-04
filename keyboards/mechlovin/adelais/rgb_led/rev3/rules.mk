# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3741
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
WS2812_DRIVER = spi
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no           # USB Nkey Rollover