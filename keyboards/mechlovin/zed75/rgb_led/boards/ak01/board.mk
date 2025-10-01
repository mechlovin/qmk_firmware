# List of all the board related files.
BOARDSRC = $(BOARD_PATH)/boards/ak01/board.c

# Required include directories
BOARDINC = $(BOARD_PATH)/boards/ak01

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
