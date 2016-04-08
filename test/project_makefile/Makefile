RTPROG = ../..

BOARD = rtboard

DRIVERS += ax12 usbserial toto usbserial

-include $(RTPROG)/support/rtprog.mk


all :
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo "DRIVER_FILES mk files :" $(DRIVER_FILES)
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC)
	
	@echo SRC: $(SRC)
