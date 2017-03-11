
DEVICE = 33EP512MC806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

SRC += swarmtips.c
HEADER += swarmtips.h
ARCHI_SRC += fuses.c
