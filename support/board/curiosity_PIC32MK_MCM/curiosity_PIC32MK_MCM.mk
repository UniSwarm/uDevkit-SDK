
DEVICE = 32MK1024MCM100
ARCHI = pic32mk

DEV_PROG ?= PKOB4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_PIC32MK_MCM.c
HEADER += curiosity_PIC32MK_MCM.h
ARCHI_SRC +=curiosity_PIC32MK_MCM_fuses.c
