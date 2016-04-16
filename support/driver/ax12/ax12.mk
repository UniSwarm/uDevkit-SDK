ifndef AX12_DRIVER
AX12_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += uart

SRC += ax12.c
HEADER += ax12.h

endif
