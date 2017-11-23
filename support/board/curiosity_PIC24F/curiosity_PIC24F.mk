
DEVICE = 24FJ128GA204
ARCHI = pic24fj

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_PIC24F.c
HEADER += curiosity_PIC24F.h
ARCHI_SRC += curiosity_PIC24F_fuses.c
