ifndef I2C_DRIVER
I2C_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += i2c.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24fj pic24ep dspic33fj dspic33ep))
 ARCHI_SRC += i2c_pic24f_dspic33f_dspic30f.c
 HEADER += i2c_pic24f_dspic33f_dspic30f.h
endif

endif
