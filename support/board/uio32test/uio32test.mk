
ARCHI = dspic33ck
DEVICE = 33CK256MP506

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += sysclock gpio ccp

SRC += uio32test.c
HEADER += uio32test.h
ARCHI_SRC += uio32test_fuses.c
