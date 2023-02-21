ifndef CAN_DRIVER
CAN_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += can.h can_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic33fj dspic33ep dspic33ev))
 #ARCHI_SRC += can_pic24_dspic33.c
 HEADER += can_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ch dspic33ck))
 ARCHI_SRC += can_dspic33c.c
 HEADER += can_dspic33c.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
 #ARCHI_SRC += can_dspic30f.c
 HEADER += can_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mx pic32mk pic32mzda pic32mzec pic32mzef))
 ifeq ($(DEVICE),$(filter $(DEVICE), 32MK0256MCJ048 32MK0256MCJ064 32MK0512MCJ048 32MK0512MCJ064 32MK0512MCM064 32MK0512MCM100 32MK1024MCM064 32MK1024MCM100))
  ARCHI_SRC += can_pic32_fd.c
  HEADER += can_pic32_fd.h
 else
  ARCHI_SRC += can_pic32.c
  HEADER += can_pic32.h
 endif
endif

SIM_SRC += can_sim.c

endif
