
ARCHI = dspic33ck
DEVICE = 33CK32MC103

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += sysclock gpio

SRC += umc-chop32.c
HEADER += umc-chop32.h
ARCHI_SRC += umc-chop32_fuses.c
