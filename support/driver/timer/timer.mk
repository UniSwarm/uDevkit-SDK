ifndef TIMER_DRIVER
TIMER_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += timer.h timer_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev pic24f pic24fj pic24hj dspic33fj dspic30f))
 ARCHI_SRC += timer_pic24_dspic30f_dspic33.c
 HEADER += timer_pic24_dspic30f_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ch dspic33ck))
 ARCHI_SRC += timer_dspic33c.c
 HEADER += timer_dspic33c.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += timer_pic32.c
 HEADER += timer_pic32.h
endif

SIM_SRC += timer_sim.c

endif
