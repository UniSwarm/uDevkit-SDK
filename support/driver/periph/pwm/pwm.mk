ifndef PWM_DRIVER
PWM_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += pwm.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep pic24f pic24fj pic24hj dspic30f dspic33ep dspic33ev dspic33fj))
 ARCHI_SRC += pwm_pic24_dspic30f_dspic33.c
 HEADER += pwm_pic24_dspic30f_dspic33.h
 DRIVERS += oc sysclock
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += pwm_pic32.c
 HEADER += pwm_pic32.h
 DRIVERS += oc timer sysclock
endif

endif
