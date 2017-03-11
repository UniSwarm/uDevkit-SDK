ifndef PWM_DRIVER
PWM_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += pwm.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep pic24f pic24fj pic24hj dspic30f dspic33ep dspic33ev dspic33fj))
 ARCHI_SRC += pwm_pic24_dspic33.c
 HEADER += pwm_pic24_dspic33.h
 DRIVERS += oc sysclock
endif

endif
