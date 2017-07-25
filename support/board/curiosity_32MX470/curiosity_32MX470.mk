
DEVICE = 32MX470F512H
ARCHI = pic32mx

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

SRC += curiosity_32MX470.c
HEADER += curiosity_32MX470.h
ARCHI_SRC += fuses.c
