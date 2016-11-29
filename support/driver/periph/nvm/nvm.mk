ifndef NVM_DRIVER
NVM_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += nvm.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep pic24f pic24fj pic24hj dspic30f dspic33ep dspic33ev dspic33fj))
 ARCHI_SRC += nvm_pic24_dspic30_dspic33.c
 HEADER += nvm_pic24_dspic30_dspic33.h
endif

endif
