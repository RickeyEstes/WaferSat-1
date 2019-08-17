# List of all the board related files.
BOARDSRC = $(CHIBIOS)/os/hal/boards/WAFERSAT_3IN/board.c

# Required include directories
BOARDINC = $(CHIBIOS)/os/hal/boards/WAFERSAT_3IN

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
