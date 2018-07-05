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
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ch dspic33ck))
 ARCHI_SRC += uart_dspic33c.c
 HEADER += uart_dspic33c.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
 ARCHI_SRC += uart_dspic30f.c
 HEADER += uart_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mx))
 ARCHI_SRC += uart_pic32mx.c
 HEADER += uart_pic32mx.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += uart_pic32mz_mm_mk.c
 HEADER += uart_pic32mz_mm_mk.h
endif

SIM_SRC += uart_sim.c

endif
