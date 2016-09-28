ifndef TIMER_DRIVER
TIMER_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += timer.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24fj pic24ep dspic33fj dspic33ep))
 ARCHI_SRC += timer_pic24f_dspic33f_dspic30f.c
 HEADER += timer_pic24f_dspic33f_dspic30f.h
endif

endif
