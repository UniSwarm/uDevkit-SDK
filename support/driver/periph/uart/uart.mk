ifndef UART_DRIVER
UART_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += uart.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic33fj dspic33ep dspic33ev))
 ARCHI_SRC += uart_pic24_dspic33.c
 HEADER += uart_pic24_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic30))
 ARCHI_SRC += uart_dspic30.c
 HEADER += uart_dspic30.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += uart_pic32.c
 HEADER += uart_pic32.h
endif

SIM_SRC += uart_sim.c

endif
