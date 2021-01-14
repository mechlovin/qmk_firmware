
OPT_DEFS += -DNO_SUSPEND_POWER_DOWN

# Build Options
ENCODER_ENABLE = yes
CIE1931_CURVE = yes

# project specific files
SRC +=	keyboards/wilba_tech/wt_main.c \
		keyboards/wilba_tech/wt_rgb_backlight.c \
		quantum/color.c \
		drivers/issi/is31fl3731.c \
		ws2812.c
		
QUANTUM_LIB_SRC += drivers/chibios/i2c_master.c
