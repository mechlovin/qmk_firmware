# MCU name
MCU = STM32F103

# Bootloader selection
BOOTLOADER = stm32duino

# Build Options
#   change yes to no to disable
#
RGB_MATRIX_ENABLE = no
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration

# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DCORTEX_ENABLE_WFI_IDLE=TRUE