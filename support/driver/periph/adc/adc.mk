ifndef ADC_DRIVER
ADC_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += adc.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 ARCHI_SRC += adc_dspic.c
 HEADER += adc_dspic.h
endif

SIM_SRC += adc_sim.c

endif
