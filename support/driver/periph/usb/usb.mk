ifndef USB_DRIVER
USB_DRIVER=

vpath %.c $(DRIVERPATH)
INCLUDEPATH:= $(INCLUDEPATH) -I$(DRIVERPATH)

ifeq ($(ARCHI), $(filter $(ARCHI),dspic33ep dspic33fj))
 vpath %.c $(RTPROG)/contrib/microchip/mla_usb/src
 INCLUDEPATH:= $(INCLUDEPATH) -I$(RTPROG)/contrib/microchip/mla_usb/inc
 SRC += usb_device.c usb_device_generic.c system.c
endif

ifeq ($(ARCHI), pic24ep)
 SRC += usb_hal_pic24e.c
endif
ifeq ($(ARCHI), pic24fj)
 SRC += usb_hal_pic24f.c
endif
ifeq ($(ARCHI), dspic33ep)
 SRC += usb_hal_dspic33e.c
endif

endif
