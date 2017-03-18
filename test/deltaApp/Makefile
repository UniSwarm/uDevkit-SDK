RTPROG = ../..

PROJECT = deltaApp
ROBOT = deltatips
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart ax12 adc i2c usb_serial spi
MODULES += cmdline # fs

MODULES += network
NETWORK_DRIVERS = esp8266 a6

MODULES += sensor
SENSOR_DRIVERS = sharp

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo CCFLAGS: $(CCFLAGS)
	
echo:
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo CCFLAGS: $(CCFLAGS)
	@echo SRC: $(SRC)
	@echo OBJECTS: $(OBJECTS)

FORCE:

