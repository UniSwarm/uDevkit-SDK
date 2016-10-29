RTPROG = ../..

PROJECT = deltaApp
ROBOT = deltatips
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart esp8266 ax12 adc sharp a6 asserv i2c usb_serial spi
MODULES += cmdline

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo CCFLAGS: $(CCFLAGS)
