
DEVICE = 33CK256MP505
ARCHI = dspic33ck

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += uio44.c
HEADER += uio44.h
ARCHI_SRC += uio44_fuses.c
