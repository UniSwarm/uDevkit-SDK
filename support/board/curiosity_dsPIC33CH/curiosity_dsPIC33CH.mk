
DEVICE = 33CH128MP508
ARCHI = dspic33ch

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_dsPIC33CH.c
HEADER += curiosity_dsPIC33CH.h
ARCHI_SRC += curiosity_dsPIC33CH_fuses.c
