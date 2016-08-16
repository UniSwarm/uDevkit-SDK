
DEVICE = 33EP512MC806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += swarmtips.c
ARCHI_SRC += fuses.c
