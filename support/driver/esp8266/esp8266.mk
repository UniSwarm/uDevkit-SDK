ifndef QEI_DRIVER
QEI_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += uart

HEADER += esp8266.h
SRC += esp8266.c

endif
