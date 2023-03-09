# MCU name
MCU = STM32F103

MCU_LDSCRIPT = ak01
BOARD = ak01

# Bootloader selection
BOOTLOADER = stm32duino

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3733
RGBLIGHT_ENABLE = yes
WS2812_DRIVER = spi