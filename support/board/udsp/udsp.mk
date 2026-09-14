
DEVICE = 33AK256MPS505
ARCHI = dspic33ak

DEV_PROG ?= PKBASIC

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += udsp.c
HEADER += udsp.h
ARCHI_SRC += udsp_fuses.c
