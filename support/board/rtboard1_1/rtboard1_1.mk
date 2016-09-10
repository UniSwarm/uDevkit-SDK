
DEVICE = 33EP512MU810
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += rtboard1_1.c
ARCHI_SRC += fuses.c
