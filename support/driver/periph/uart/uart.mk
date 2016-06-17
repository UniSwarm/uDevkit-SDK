ifndef UART_DRIVER
UART_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += uart.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 ARCHI_SRC += uart_dspic.c
 HEADER += uart_dspic.h
endif

endif
