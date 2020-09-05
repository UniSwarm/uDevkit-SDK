
ARCHI = dspic33ck
DEVICE = 33CK256MP506

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += sysclock gpio ccp

SRC += uio8ad.c
HEADER += uio8ad.h
ARCHI_SRC += uio8ad_fuses.c
