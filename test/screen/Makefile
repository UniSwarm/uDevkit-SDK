RTPROG = ../..

PROJECT = testproj
BOARD = a6screenboard
OUT_PWD = build

DRIVERS += uart lcd

SRC += main.c

#PICTURES += picture.jpg

include $(RTPROG)/rtprog.mk

all : FORCE
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
	@echo SRC: $(SRC)
