
DEVICE = 33EP512MU810
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

SRC += rtboard1_1.c
HEADER += rtboard1_1.h
ARCHI_SRC += rtboard1_1_fuses.c
