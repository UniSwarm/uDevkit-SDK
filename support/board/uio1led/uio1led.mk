
ARCHI = dspic33ck
ifeq ($(BOARD_VERSION),$(filter $(BOARD_VERSION),101))
 DEVICE = 33CK64MP502
else
 DEVICE = 33CK256MP502
endif

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += sysclock gpio

SRC += uio1led.c
HEADER += uio1led.h
ARCHI_SRC += uio1led_fuses.c
