
DEVICE = 33EP256MU806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += rtboard.c
ARCHI_SRC += fuses.c
