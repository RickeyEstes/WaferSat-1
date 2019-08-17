# List of all the board related files.
BOARDSRC = $(CONFDIR)/WAFERSAT_3IN/board.c

# Required include directories
BOARDINC = $(CONFDIR)/WAFERSAT_3IN

# Shared variables
ALLCSRC += $(BOARDSRC)
ALLINC  += $(BOARDINC)
