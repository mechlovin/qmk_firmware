# MCU name
MCU = STM32F072

# Bootloader selection
BOOTLOADER = stm32-dfu

# Wildcard to allow APM32 MCU
DFU_SUFFIX_ARGS = -v FFFF -p FFFF

RGBLIGHT_ENABLE = yes
WS2812_DRIVER = spi
DEFAULT_FOLDER = mechlovin/adelais/standard_led/rev2