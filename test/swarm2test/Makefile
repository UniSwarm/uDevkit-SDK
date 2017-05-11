RTPROG = ../..

PROJECT = swarm2test
BOARD = swarmtips2
OUT_PWD = build

DEV_PROG?=ICD3

# CCFLAGS += -pedantic

DRIVERS += uart i2c timer pwm adc # usb_hal

MODULES += network
NETWORK_DRIVERS = esp8266

MODULES += gui
GUI_DRIVERS = ssd1306

MODULES += sensor
SENSOR_DRIVERS = VL6180X

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex

	
echo:
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo CCFLAGS: $(CCFLAGS)
	@echo SRC: $(SRC)
	@echo OBJECTS: $(OBJECTS)
