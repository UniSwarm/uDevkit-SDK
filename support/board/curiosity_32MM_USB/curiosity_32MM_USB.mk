
DEVICE = 32MM0256GPM064
ARCHI = pic32mm

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

SRC += curiosity_32MM_USB.c
HEADER += curiosity_32MM_USB.h
ARCHI_SRC += fuses.c
