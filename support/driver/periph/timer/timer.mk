ifndef TIMER_DRIVER
TIMER_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += timer.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 SRC += timer_dspic.c
 HEADER += timer_dspic.h
endif

endif
