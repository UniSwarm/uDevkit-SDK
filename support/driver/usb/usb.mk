
DRIVERS += titi

SRC := $(SRC) $(dir $(lastword $(MAKEFILE_LIST)))usb.c
