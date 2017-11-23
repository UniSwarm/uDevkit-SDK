
DEVICE = 32MX470F512H
ARCHI = pic32mx

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += curiosity_32MX470.c
HEADER += curiosity_32MX470.h
ARCHI_SRC += curiosity_32MX470_fuses.c
