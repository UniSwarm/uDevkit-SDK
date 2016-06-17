ifndef I2C_DRIVER
I2C_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += i2c.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 ARCHI_SRC += i2c_dspic.c
 HEADER += i2c_dspic.h
endif

endif
