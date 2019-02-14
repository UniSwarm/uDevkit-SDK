
DEVICE = 33CK256MP505
ARCHI = dspic33ck

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += uio44fr.c
HEADER += uio44fr.h
ARCHI_SRC += uio44fr_fuses.c
