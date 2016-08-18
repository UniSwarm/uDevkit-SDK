ifndef UART_DRIVER
UART_DRIVER=

vpath %.c $(DRIVERPATH)

DRIVERS += sysclock

HEADER += uart.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += uart_pic24_dspic33.c
 HEADER += uart_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic30))
 ARCHI_SRC += uart_dspic30.c
 HEADER += uart_dspic30.h
endif

SIM_SRC += uart_sim.c

endif
