
MCU = STM32F401
BOARD = BLACKPILL_STM32_F401

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3741
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
LAYOUTS = alice alice_split_bs

KEYBOARD_SHARED_EP = yes
