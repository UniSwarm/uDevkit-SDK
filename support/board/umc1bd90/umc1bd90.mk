
ARCHI = dspic33ch

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio ccp

HEADER += umc1bd90.h

ifdef SECONDARY
 DEVICE = 33CH512MP508S1
 SRC += umc1bd90_secondary.c
else
 DEVICE = 33CH512MP508
 SRC += umc1bd90.c
 ARCHI_SRC += umc1bd90_fuses.c
endif
