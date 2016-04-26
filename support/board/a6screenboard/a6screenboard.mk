
DEVICE = 33EP512GP806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += fuses.c a6screenboard.c
