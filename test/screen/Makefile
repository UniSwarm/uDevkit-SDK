RTPROG = ../..

PROJECT = testproj
BOARD = a6screenboard
OUT_PWD = build

DRIVERS += a6 timer
MODULES += gui

SRC += main.c
FONTS += core12b core18b Lucida_Console10

PICTURES += picture.png

include $(RTPROG)/rtprog.mk

all : hex
	@echo "DRIVERS asked         :" $(sort $(DRIVERS) $(BADDRIVERS))
	@echo "DRIVERS implemented   :" $(DRIVERS)
	@echo "BADDRIVERS sorted     :" $(sort $(BADDRIVERS))
	@echo DEVICE: $(DEVICE), ARCHI: $(ARCHI), CC: $(CC), DEFINES: $(DEFINES)
	@echo OBJECTS: $(OBJECTS)
	@echo SRC: $(SRC)
