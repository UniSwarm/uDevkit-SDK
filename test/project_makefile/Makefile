UDEVKIT = ../..

PROJECT = testproj
BOARD = rtboard1_1
OUT_PWD = build
# DEVICE = 33EP256MU806
# ARCHI = dspic33ep

# CCFLAGS += -pedantic

DRIVERS += timer uart ax12 adc i2c pwm
MODULES += mrobot

MODULES += network
NETWORK_DRIVERS = esp8266 a6

MODULES += sensor
SENSOR_DRIVERS = sharp

SRC += main.c

include $(UDEVKIT)/udevkit.mk

all : hex
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
