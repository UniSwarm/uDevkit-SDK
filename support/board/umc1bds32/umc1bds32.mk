
ARCHI = dspic33ch

DEV_PROG ?= ICD4

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio ccp

HEADER += umc1bds32.h

ifdef SECONDARY
 ifeq ($(BOARD_VERSION),$(filter $(BOARD_VERSION),101 102))
  DEVICE = 33CH128MP506S1
 else
  DEVICE = 33CH512MP508S1
 endif
 SRC += umc1bds32_secondary.c
else
 ifeq ($(BOARD_VERSION),$(filter $(BOARD_VERSION),101 102))
  DEVICE = 33CH128MP506
 else
  DEVICE = 33CH512MP508
 endif
 SRC += umc1bds32.c
 ARCHI_SRC += umc1bds32_fuses.c
endif
