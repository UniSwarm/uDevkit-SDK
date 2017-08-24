ifndef GPIO_DRIVER
GPIO_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += gpio.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30f dspic33fj dspic33ep dspic33ev))
 ARCHI_SRC += gpio_pic24_dspic30f_dspic33.c
 HEADER += gpio_pic24_dspic30f_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += gpio_pic32.c
 HEADER += gpio_pic32.h
endif

SIM_SRC += gpio_sim.c

test_gpio:
	xc16-gcc -DARCHI_dspic33ep -DDEVICE_33EP512MU814 -mcpu=33EP512MU814 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/gpio/gpio_pic24_dspic30f_dspic33.c -o gpio_pic24_dspic30f_dspic33.o
	xc16-gcc -DARCHI_pic24f -DDEVICE_24FJ64GB412 -mcpu=24FJ64GB412 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/gpio/gpio_pic24_dspic30f_dspic33.c -o gpio_pic24_dspic30f_dspic33.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH144 -mprocessor=32MZ1024EFH144 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/gpio/gpio_pic32.c -o gpio_pic32.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -mprocessor=32MZ1024EFH064 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/gpio/gpio_pic32.c -o gpio_pic32.o
	gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/gpio/gpio_sim.c -o gpio_sim.o

endif
