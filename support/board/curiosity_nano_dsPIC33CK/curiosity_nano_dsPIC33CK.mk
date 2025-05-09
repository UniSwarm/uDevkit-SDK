
DEVICE = 33CK64MP105
ARCHI = dspic33ck

DEV_PROG ?= PKOB4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_nano_dsPIC33CK.c
HEADER += curiosity_nano_dsPIC33CK.h
ARCHI_SRC += curiosity_nano_dsPIC33CK_fuses.c
