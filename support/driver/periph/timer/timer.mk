ifndef TIMER_DRIVER
TIMER_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += timer.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += timer_pic24_dspic30_dspic33.c
 HEADER += timer_pic24_dspic30_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += timer_pic32.c
 HEADER += timer_pic32.h
endif

SIM_SRC += timer_sim.c

endif
