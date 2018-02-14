ifndef CAN_DRIVER
CAN_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += can.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic33fj dspic33ep dspic33ev))
 #ARCHI_SRC += can_pic24_dspic33.c
 HEADER += can_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
 #ARCHI_SRC += can_dspic30f.c
 HEADER += can_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mx pic32mk pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += can_pic32.c
 HEADER += can_pic32.h
endif

SIM_SRC += can_sim.c

endif
