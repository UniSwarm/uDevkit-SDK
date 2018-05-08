
DEVICE = 32MK1024MCF100
ARCHI = pic32mk

DEV_PROG ?= PK3

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += UMC4D30CRU.c
HEADER += UMC4D30CRU.h
ARCHI_SRC += UMC4D30CRU_fuses.c
