ifndef ASSERV_DRIVER
ASSERV_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += qei motor

HEADER += asserv.h
SRC += asserv.c

endif
