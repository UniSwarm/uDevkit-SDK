ifndef I2C_DRIVER
I2C_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += i2c.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30 dspic33fj dspic33ep dspic33ev))
 ARCHI_SRC += i2c_pic24_dspic30_dspic33.c
 HEADER += i2c_pic24_dspic30_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += i2c_pic32.c
 HEADER += i2c_pic32.h
endif

SIM_SRC += i2c_sim.c

endif
