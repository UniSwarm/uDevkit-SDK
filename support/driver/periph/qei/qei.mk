ifndef QEI_DRIVER
QEI_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += qei.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj dspic30 dspic33fj))
 ARCHI_SRC += qei_pic24f_dspic30f_dspic33f.c
 HEADER += qei_pic24f_dspic30f_dspic33f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev))
 ARCHI_SRC += qei_pic24e_dspic33e.c
 HEADER += qei_pic24e_dspic33e.h
endif

SIM_SRC += qei_sim.c

endif
