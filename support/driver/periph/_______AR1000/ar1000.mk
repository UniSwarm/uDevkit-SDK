ifndef AR_DRIVER
AR_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += ar1000.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 SRC += ar1000.c
 HEADER += ar1000.h
endif

endif
