# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

ENCODER_ENABLE = yes
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration

CUSTOM_MATRIX = lite

SRC += matrix.c
