
ARCHI = dspic33ch

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio ccp

HEADER += umc1bds32.h

ifdef SECONDARY
 DEVICE = 33CH512MP508S1
 SRC += umc1bds32_secondary.c
 CCFLAGS += -DSECONDARY
else
 DEVICE = 33CH512MP508
 SRC += umc1bds32.c
 ARCHI_SRC += umc1bds32_fuses.c
endif
