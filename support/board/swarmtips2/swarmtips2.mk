
DEVICE = 32MZ2048EFH064
ARCHI = pic32mzef

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

SRC += swarmtips2.c
HEADER += swarmtips2.h
ARCHI_SRC += fuses.c
