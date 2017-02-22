RTPROG = ../..

PROJECT = swarmtest
BOARD = swarmtips
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart adc i2c timer
MODULES += sensor network

NETWORK_DRIVERS = esp8266

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
