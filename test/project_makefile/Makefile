RTPROG = ../..

PROJECT = testproj
BOARD = rtboard1_1
OUT_PWD = build
# DEVICE = 33EP256MU806
# ARCHI = dspic33ep

# CCFLAGS += -pedantic

DRIVERS += timer uart ax12 adc sharp i2c pwm
MODULES += mrobot network

NETWORK_DRIVERS = esp8266 a6

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
