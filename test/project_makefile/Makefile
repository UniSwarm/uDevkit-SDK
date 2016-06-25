RTPROG = ../..

PROJECT = testproj
BOARD = rtboard
OUT_PWD = build
# DEVICE = 33EP256MU806
# ARCHI = dspic33ep

# CCFLAGS += -pedantic

DRIVERS += timer uart esp8266 ax12 adc sharp a6 asserv

SRC += main.c

include $(RTPROG)/rtprog.mk

all : hex FORCE
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
