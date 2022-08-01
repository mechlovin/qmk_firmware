# MCU name
MCU = RP2040

# Bootloader selection
BOOTLOADER = rp2040

# Build Options
#   change yes to no to disable
#
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3741
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
WS2812_DRIVER = vendor
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
LAYOUTS = alice alice_split_bs
