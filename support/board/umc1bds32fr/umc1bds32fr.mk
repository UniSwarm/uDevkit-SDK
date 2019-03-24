
ARCHI = dspic33ch

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

HEADER += umc1bds32fr.h

ifdef SLAVE
 DEVICE = 33CH128MP506S1
 SRC += umc1bds32fr_slave.c
else
 DEVICE = 33CH128MP506
 SRC += umc1bds32fr.c
 ARCHI_SRC += umc1bds32fr_fuses.c
endif
