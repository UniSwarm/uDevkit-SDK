
DEVICE = 33AK512MPS512
ARCHI = dspic33ak

DEV_PROG ?= PKOB4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_dsPIC33AK512MPS512.c
HEADER += curiosity_dsPIC33AK512MPS512.h
ARCHI_SRC += curiosity_dsPIC33AK512MPS512_fuses.c
