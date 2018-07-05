ifndef GPIO_DRIVER
GPIO_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += gpio.h gpio_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30f dspic33fj dspic33ep dspic33ev dspic33ch dspic33ck))
 ARCHI_SRC += gpio_pic24_dspic30f_dspic33.c
 HEADER += gpio_pic24_dspic30f_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += gpio_pic32.c
 HEADER += gpio_pic32.h
endif

SIM_SRC += gpio_sim.c

endif
