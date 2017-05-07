ifndef ADC_DRIVER
ADC_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += adc.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj dspic33ev))
 ARCHI_SRC += adc_dspic.c
 HEADER += adc_dspic.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += adc_pic32mz.c
 HEADER += adc_pic32mz.h
endif

SIM_SRC += adc_sim.c

endif
