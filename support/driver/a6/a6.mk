ifndef A6_DRIVER
A6_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += uart

HEADER += a6.h
SRC += a6.c

endif
