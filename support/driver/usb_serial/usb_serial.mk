ifndef USB-SERIAL_DRIVER
USB-SERIAL_DRIVER=

DRIVERS += usb_hal

vpath %.c $(DRIVERPATH)

INCLUDEPATH:= $(INCLUDEPATH) -I$(DRIVERPATH)

HEADER += usb_serial.h
ARCHI_SRC += usb_serial.c usb_descriptors.c usb_device_cdc.c

SIM_SRC += usb_serial_sim.c

endif
