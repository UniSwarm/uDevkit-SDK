RTPROG = ../..

DEV_PROG = RICE
PROJECT = testproj
BOARD = emz64
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += timer uart i2c
MODULES += gui

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
