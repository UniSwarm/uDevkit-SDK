
DEVICE = 33CK256MP508
ARCHI = dspic33ck

DEV_PROG ?= PKOB4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_dsPIC33CK.c
HEADER += curiosity_dsPIC33CK.h
ARCHI_SRC += curiosity_dsPIC33CK.c
