
PECAN = ./pecan-pico

# List of all the Userlib files
PECANSRC =  $(PECAN)/source/pkt/managers/pktradio.c \
	    $(PECAN)/source/pkt/managers/pktservice.c

source = $(PECAN)/source

# PKT
pkt = $(source)/pkt
manager = $(pkt)/managers
sys = $(pkt)/sys
protocols = $(pkt)/protocols
aprs2 = $(protocols)/aprs2
devices = $(pkt)/devices
filters = $(pkt)/filters
channels = $(pkt)/channels
decoders = $(pkt)/decoders
diagnostics = $(pkt)/diagnostics

# Drivers
drivers = $(source)/drivers

# Threads
threads = $(source)/threads
rxtx = $(threads)/rxtx

# Config
config = $(source)/config

# Tools
tools = $(source)/tools

# Required include directories
PECANINC =  $(PECAN) \
	    $(PECAN)/CMSIS/include/ \
	    $(pkt) \
	    $(manager) \
	    $(sys) \
	    $(protocols) \
	    $(aprs2) \
	    $(devices) \
	    $(filters) \
	    $(channels) \
	    $(decoders) \
	    $(diagnostics) \
	    $(drivers) \
	    $(rxtx) \
	    $(config) \
	    $(tools)
