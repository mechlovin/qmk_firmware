RGBLIGHT_ENABLE = yes        # Enable keyboard RGB underglow
WS2812_DRIVER = spi
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = NO        # Commands for debug and configuration

CIE1931_CURVE = yes

# project specific files
SRC =	keyboards/wilba_tech/wt_main.c \
		keyboards/wilba_tech/wt_rgb_backlight.c \
		quantum/color.c \
		drivers/led/issi/is31fl3218.c 
QUANTUM_LIB_SRC += i2c_master.c
