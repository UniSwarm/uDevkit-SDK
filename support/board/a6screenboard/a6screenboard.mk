
DEVICE = 33EP512GP806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += a6screenboard.c
ARCHI_SRC += fuses.c
