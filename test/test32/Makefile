RTPROG = ../..

DEV_PROG = RICE
PROJECT = test32
BOARD = emz64
OUT_PWD = build 

# CCFLAGS += -pedantic

DRIVERS += sysclock uart i2c timer gpio
MODULES += gui

MODULES += cmdline

SRC += main.c

include $(RTPROG)/udevkit.mk

all : hex
	@echo "SRC asked         :" $(sort $(SRC) $(ARCHI_SRC))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
