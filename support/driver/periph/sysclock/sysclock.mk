ifndef SYSCLOCK_DRIVER
SYSCLOCK_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += sysclock.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 ARCHI_SRC += sysclock_dspic.c
 HEADER += sysclock_dspic.h
endif

endif
