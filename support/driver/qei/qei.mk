ifndef QEI_DRIVER
QEI_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += qei.h qei_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += qei_pic24f_dspic33f.c
 HEADER += qei_pic24f_dspic33f.h
endif
ifeq ($(ARCHI),dspic30f)
 ARCHI_SRC += qei_dspic30f.c
 HEADER += qei_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev dspic33ch dspic33ck))
 ARCHI_SRC += qei_pic24e_dspic33e.c
 HEADER += qei_pic24e_dspic33e.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mk))
 ARCHI_SRC += qei_pic32mk.c
 HEADER += qei_pic32mk.h
endif

SIM_SRC += qei_sim.c

endif
