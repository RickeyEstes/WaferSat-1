
PECAN = pecan-pico

source = $(PECAN)/source

# PKT library
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

# Packet
packet = $(source)/protocols/packet

# Drivers
drivers = $(source)/drivers
flash = $(drivers)/flash
usb = $(drivers)/usb

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
	    $(tools) \
	    $(packet) \
	    $(flash) \
	    $(usb) \

# Source files to be compiled
PECANSRC =  $(manager)/pktradio.c \
	    $(manager)/pktservice.c \
	    $(packet)/aprs.c \
	    $(rxtx)/radio.c \
	    $(PECAN)/portab.c \
	    $(config)/config.c \
	    $(aprs2)/ax25_pad.c \
	    $(channels)/rxpwm.c \
	    $(channels)/rxafsk.c \

