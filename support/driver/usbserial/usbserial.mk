ifndef USBSERIAL_DRIVER
USBSERIAL_DRIVER=

DRIVERS += usb

vpath %.c $(DRIVERPATH)

SRC += usb_serial.c usb_serial_dspic.c
HEADER := $(HEADER)

endif
