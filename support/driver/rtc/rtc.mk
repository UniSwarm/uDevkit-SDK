ifndef RTC_DRIVER
RTC_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += rtc.h rtc_device.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic33fj dspic33ep dspic33ev dspic33ch dspic33ck))
# ARCHI_SRC += rtc_pic24_dspic33.c
 HEADER += rtc_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += rtc_pic32.c
 HEADER += rtc_pic32.h
endif

# SIM_SRC += rtc_sim.c

endif
