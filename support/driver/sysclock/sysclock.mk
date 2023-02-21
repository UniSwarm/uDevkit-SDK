ifndef SYSCLOCK_DRIVER
SYSCLOCK_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += sysclock.h sysclock_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
 ARCHI_SRC += sysclock_dspic30f.c
 HEADER += sysclock_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ch dspic33ck))
 ARCHI_SRC += sysclock_dspic33c.c
 HEADER += sysclock_dspic33c.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += sysclock_pic24_dspic33.c
 HEADER += sysclock_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mx))
 ARCHI_SRC += sysclock_pic32mx.c
 HEADER += sysclock_pic32mx.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm))
 ARCHI_SRC += sysclock_pic32mm.c
 HEADER += sysclock_pic32mm.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mk pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += sysclock_pic32mz_mk.c
 HEADER += sysclock_pic32mz_mk.h
endif

SIM_SRC += sysclock_sim.c

endif
