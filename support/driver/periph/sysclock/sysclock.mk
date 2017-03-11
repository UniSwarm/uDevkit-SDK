ifndef SYSCLOCK_DRIVER
SYSCLOCK_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += sysclock.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += sysclock_pic24_dspic30_dspic33.c
 HEADER += sysclock_pic24_dspic30_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mx))
 ARCHI_SRC += sysclock_pic32mx.c
 HEADER += sysclock_pic32mx.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += sysclock_pic32mz.c
 HEADER += sysclock_pic32mz.h
endif

SIM_SRC += sysclock_sim.c

endif
