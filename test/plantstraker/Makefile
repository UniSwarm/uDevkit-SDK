RTPROG = ../..

PROJECT = plantsTraker
BOARD = rtboard1_1
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart adc usb_serial
MODULES += cmdline network

NETWORK_DRIVERS = esp8266

SRC += main.c

include $(RTPROG)/rtprog.mk

all: elf

verb : FORCE
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo CCFLAGS: $(CCFLAGS)

FORCE:

