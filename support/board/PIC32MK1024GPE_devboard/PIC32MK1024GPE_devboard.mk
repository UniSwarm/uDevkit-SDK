
DEVICE = 32MK1024GPE100
ARCHI = pic32mk

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

SRC += PIC32MK1024GPE_devboard.c
HEADER += PIC32MK1024GPE_devboard.h
ARCHI_SRC += PIC32MK1024GPE_devboard_fuses.c
