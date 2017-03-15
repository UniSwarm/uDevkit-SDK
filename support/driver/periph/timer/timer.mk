ifndef TIMER_DRIVER
TIMER_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += timer.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += timer_pic24_dspic30_dspic33.c
 HEADER += timer_pic24_dspic30_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += timer_pic32.c
 HEADER += timer_pic32.h
endif

SIM_SRC += timer_sim.c

test_timer:
	xc16-gcc -DARCHI_dspic33ep -DDEVICE_33FJ16MC102 -mcpu=33FJ16MC102 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/timer/timer_pic24_dspic30_dspic33.c -o timer_pic24_dspic30_dspic33.o
	#xc16-gcc -DARCHI_pic24f -DDEVICE_24FJ64GB412 -mcpu=24FJ64GB412 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/timer/timer_pic24_dspic30_dspic33.c -o timer_pic24_dspic30_dspic33.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH144 -mprocessor=32MZ1024EFH144 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/timer/timer_pic32.c -o timer_pic32.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -mprocessor=32MZ1024EFH064 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/timer/timer_pic32.c -o timer_pic32.o
	gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/timer/timer_sim.c -o timer_sim.o

endif
