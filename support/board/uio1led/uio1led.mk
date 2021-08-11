
ARCHI = dspic33ck
DEVICE = 33CK64MP502

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += sysclock gpio ccp

SRC += uio1led.c
HEADER += uio1led.h
ARCHI_SRC += uio1led_fuses.c
