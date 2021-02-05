
ARCHI = dspic33ch

DEV_PROG ?= PKOB

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

HEADER += curiosity_dsPIC33CH512.h
ifdef SLAVE
 DEVICE = 33CH512MP508S1
 SRC += curiosity_dsPIC33CH512_slave.c
else
 DEVICE = 33CH512MP508
 SRC += curiosity_dsPIC33CH512.c
 ARCHI_SRC += curiosity_dsPIC33CH512_fuses.c
endif
