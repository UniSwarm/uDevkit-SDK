
DEVICE = 33EP256MU806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += fuses.c rtboard.c