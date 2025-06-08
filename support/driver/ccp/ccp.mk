ifndef CCP_DRIVER
CCP_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += ccp.h ccp_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ak pic32ak))
 ARCHI_SRC += ccp_dspic33a_pic32a.c
 HEADER += ccp_dspic33a_pic32a.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj dspic33ch dspic33ck))
 ARCHI_SRC += ccp_pic24_dspic33.c
 HEADER += ccp_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm))
 ARCHI_SRC += ccp_pic32.c
 HEADER += ccp_pic32.h
endif

SIM_SRC += ccp_sim.c

endif
