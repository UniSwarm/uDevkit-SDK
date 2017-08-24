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

test_uart:
	xc16-gcc -DARCHI_dspic33fj -DDEVICE_33FJ16MC102 -mcpu=33FJ16MC102 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/uart/uart_pic24_dspic33.c -o uart_pic24_dspic33.o
	xc16-gcc -DARCHI_pic24f -DDEVICE_24FJ64GB412 -mcpu=24FJ64GB412 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/uart/uart_pic24_dspic33.c -o uart_pic24_dspic33.o
	xc16-gcc -DARCHI_dspic30f -DDEVICE_30F6015 -mcpu=30F6015 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/uart/uart_dspic30f.c -o uart_dspic30f.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH144 -mprocessor=32MZ1024EFH144 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/uart/uart_pic32.c -o uart_pic32.o
	gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -DSIMULATOR -c -I$(RTPROG)include $(RTPROG)support/driver/periph/uart/uart_sim.c -o uart_sim.o

endif
