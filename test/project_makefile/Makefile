RTPROG = ../..

PROJECT = testproj
BOARD = rtboard
# DEVICE = 33EP256MU806
# ARCHI = dspic33ep

DRIVERS += ax12 usbserial toto usbserial

SRC += main.c

-include $(RTPROG)/rtprog.mk

all : $(PROJECT).elf
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo "DRIVER_FILES mk files :" $(DRIVER_FILES) , $(MAKEFILE_LIST)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC)
	
	@echo SRC: $(SRC)
