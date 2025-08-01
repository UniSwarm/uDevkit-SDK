ifndef PMP_DRIVER
PMP_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += pmp.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24fj pic24ep pic24hj dspic33fj dspic33ep dspic33ck))
 ARCHI_SRC += pmp_pic24_dspic33.c
 HEADER += pmp_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += pmp_pic32.c
 HEADER += pmp_pic32.h
endif

endif
