
DEVICE = 33EP512GP806
ARCHI = dspic33ep

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += a6screenboard.c
HEADER += a6screenboard.h
ARCHI_SRC += a6screenboard_fuses.c

GUI_DRIVERS += d51e5ta7601
