PECAN = ./pecan

rwildcard    = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
PECANINC = $(sort $(dir $(call rwildcard, $(PECAN),*)))
PECANSRC := $(call rwildcard,$(PECAN),*.c)

