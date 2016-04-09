ifndef USBSERIAL_DRIVER
USBSERIAL_DRIVER=

DRIVERS += usb

SRC := $(SRC) \
	$(DRIVERPATH)usb_serial.c \
	$(DRIVERPATH)usb_serial_dspic.c
HEADER := $(HEADER)

endif
