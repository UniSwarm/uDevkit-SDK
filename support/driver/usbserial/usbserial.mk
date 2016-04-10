ifndef USBSERIAL_DRIVER
USBSERIAL_DRIVER=

DRIVERS += usb

vpath %.c $(DRIVERPATH)

SRC += usbserial.c usbserial_dspic.c
HEADER := $(HEADER)

endif
