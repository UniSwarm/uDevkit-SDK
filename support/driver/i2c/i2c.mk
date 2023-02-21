ifndef I2C_DRIVER
I2C_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += i2c.h i2c_device.h
ARCHI_SRC += i2c.c

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30f dspic33fj dspic33ep dspic33ev dspic33ch dspic33ck))
 ARCHI_SRC += i2c_pic24_dspic30f_dspic33.c
 HEADER += i2c_pic24_dspic30f_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += i2c_pic32.c
 HEADER += i2c_pic32.h
endif

SIM_SRC += i2c_sim.c

endif
