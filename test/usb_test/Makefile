RTPROG = ../..

PROJECT = usb_test
BOARD = rtboard
OUT_PWD = build

DRIVERS += uart usb-serial esp8266 ax12 a6

SRC += main.c

include $(RTPROG)/rtprog.mk

all: hex
	@echo $(DRIVERS)
