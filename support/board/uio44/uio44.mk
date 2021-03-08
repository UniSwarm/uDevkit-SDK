
ARCHI = dspic33ck
DEVICE = 33CK256MP505

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += uio44.c
HEADER += uio44.h
ARCHI_SRC += uio44_fuses.c
