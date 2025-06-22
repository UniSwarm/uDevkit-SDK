
DEVICE = 33AK128MC106
ARCHI = dspic33ak

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_dsPIC33AK128MC106.c
HEADER += curiosity_dsPIC33AK128MC106.h
ARCHI_SRC += curiosity_dsPIC33AK128MC106_fuses.c
