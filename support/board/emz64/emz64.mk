
DEVICE = 32MZ2048EFM064
ARCHI = pic32mzef

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += emz64.c
HEADER += emz64.h
ARCHI_SRC += fuses.c
