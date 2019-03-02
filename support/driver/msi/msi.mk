ifndef MSI_DRIVER
MSI_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += msi.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ch))
 SRC += msi_dspic33ch.c
 HEADER += msi_dspic33ch.h
endif

endif
