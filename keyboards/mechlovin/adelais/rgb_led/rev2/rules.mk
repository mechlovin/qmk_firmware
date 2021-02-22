# MCU name
MCU = atmega32a

# Bootloader selection
BOOTLOADER = bootloadHID

F_CPU ?= 16000000

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = IS31FL3731
ENCODER_ENABLE = no
RGBLIGHT_ENABLE = no
NKRO_ENABLE = no           # USB Nkey Rollover
EXTRAKEY_ENABLE = yes       # Audio control and System control
