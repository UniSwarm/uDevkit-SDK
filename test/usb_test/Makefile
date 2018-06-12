RTPROG = ../..

PROJECT = usb_test
BOARD = rtboard
OUT_PWD = build

DRIVERS += uart usb_serial ax12
MODULES += network

NETWORK_DRIVERS = esp8266 a6

SRC += main.c

include $(RTPROG)/udevkit.mk

all: hex
	@echo $(DRIVERS)
