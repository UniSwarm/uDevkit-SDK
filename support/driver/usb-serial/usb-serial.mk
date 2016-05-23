ifndef USB-SERIAL_DRIVER
USB-SERIAL_DRIVER=

DRIVERS += usb

vpath %.c $(DRIVERPATH)

INCLUDEPATH:= $(INCLUDEPATH) -I$(DRIVERPATH)

HEADER += usb-serial.h
SRC += usb-serial.c usb_descriptors.c usb_device_cdc.c

endif
