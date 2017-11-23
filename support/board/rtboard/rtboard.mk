
DEVICE = 33EP256MU806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += rtboard.c
HEADER += rtboard.h
ARCHI_SRC += rtboard_fuses.c
