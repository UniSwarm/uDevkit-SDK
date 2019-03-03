
ARCHI = dspic33ch

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

HEADER += curiosity_dsPIC33CH.h
ifdef SLAVE
 DEVICE = 33CH128MP508S1
 SRC += curiosity_dsPIC33CH_slave.c
else
 DEVICE = 33CH128MP508
 SRC += curiosity_dsPIC33CH.c
 ARCHI_SRC += curiosity_dsPIC33CH_fuses.c
endif
