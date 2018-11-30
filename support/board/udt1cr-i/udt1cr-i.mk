
DEVICE = 32MZ2048EFH064
ARCHI = pic32mzef

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += udt1cr-i.c
HEADER += udt1cr-i.h
ARCHI_SRC += udt1cr-i_fuses.c
