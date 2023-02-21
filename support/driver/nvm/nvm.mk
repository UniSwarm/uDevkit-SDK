ifndef NVM_DRIVER
NVM_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += nvm.h nvm_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep pic24f pic24fj pic24hj dspic30f dspic33ep dspic33ev dspic33fj dspic33ch dspic33ck))
 ARCHI_SRC += nvm_pic24_dspic30f_dspic33.c
 HEADER += nvm_pic24_dspic30f_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += nvm_pic32.c
 HEADER += nvm_pic32.h
endif

SIM_SRC += nvm_sim.c

endif
