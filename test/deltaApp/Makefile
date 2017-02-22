RTPROG = ../..

PROJECT = deltaApp
ROBOT = deltatips
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart ax12 adc sharp i2c usb_serial
MODULES += cmdline network # fs

NETWORK_DRIVERS = esp8266 a6

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo CCFLAGS: $(CCFLAGS)

FORCE:

