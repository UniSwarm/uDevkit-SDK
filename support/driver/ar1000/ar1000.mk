ifndef AR_DRIVER
AR_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += ar1000.h
SRC += ar1000.c

endif
