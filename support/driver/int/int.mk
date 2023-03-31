ifndef INT_DRIVER
INT_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += int.h int_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30f dspic33fj dspic33ep dspic33ev dspic33ch dspic33ck))
# ARCHI_SRC += int_pic24_dspic30f_dspic33.c
 HEADER += int_pic24_dspic30f_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
# ARCHI_SRC += int_pic32.c
 HEADER += int_pic32.h
endif

endif
