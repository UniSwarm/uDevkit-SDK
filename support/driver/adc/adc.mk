ifndef ADC_DRIVER
ADC_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += adc.h

ifeq ($(ARCHI), $(filter $(ARCHI), dspic33ch dspic33ck))
 ARCHI_SRC += adc_dspic33_sar12.c
 HEADER += adc_dspic33_sar12.h
endif
ifeq ($(ARCHI), $(filter $(ARCHI), dspic33ep dspic33ev))
 ifeq ($(DEVICE),$(filter $(DEVICE),33EP128GS702 33EP128GS704 33EP128GS705 \
   33EP128GS706 33EP128GS708 33EP128GS804 33EP128GS805 33EP128GS806 33EP128GS808 \
   33EP16GS202 33EP16GS502 33EP16GS504 33EP16GS505 33EP16GS506 33EP32GS202 \
   33EP32GS502 33EP32GS504 33EP32GS505 33EP32GS506 33EP64GS502 33EP64GS504 \
   33EP64GS505 33EP64GS506 33EP64GS708 33EP64GS804 33EP64GS805 33EP64GS806 33EP64GS808))
  ARCHI_SRC += adc_dspic33_sar12.c
  HEADER += adc_dspic33_sar12.h
 else
  ARCHI_SRC += adc_pic24e_dspic33e.c
  HEADER += adc_pic24e_dspic33e.h
 endif
endif
ifeq ($(ARCHI),$(filter $(ARCHI), pic32mm))
 ARCHI_SRC += adc_pic32mm.c
 HEADER += adc_pic32mm.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI), pic32mzef pic32mzda pic32mk))
 ARCHI_SRC += adc_pic32_sar12.c
 HEADER += adc_pic32_sar12.h
endif

SRC += adc.c
SIM_SRC += adc_sim.c

endif
