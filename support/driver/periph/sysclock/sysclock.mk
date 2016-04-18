ifndef SYSCLOCK_DRIVER
SYSCLOCK_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += sysclock.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 SRC += sysclock_dspic.c
 HEADER += sysclock_dspic.h
endif

endif
