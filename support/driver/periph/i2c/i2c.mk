ifndef I2C_DRIVER
I2C_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += i2c.h
ARCHI_SRC += i2c.c

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30 dspic33fj dspic33ep dspic33ev))
 ARCHI_SRC += i2c_pic24_dspic30_dspic33.c
 HEADER += i2c_pic24_dspic30_dspic33.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mk pic32mx pic32mzda pic32mzec pic32mzef))
 ARCHI_SRC += i2c_pic32.c
 HEADER += i2c_pic32.h
endif

SIM_SRC += i2c_sim.c

test_i2c:
	xc16-gcc -DARCHI_dspic33ep -DDEVICE_33FJ16MC102 -mcpu=33FJ16MC102 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/i2c/i2c_pic24_dspic30_dspic33.c -o i2c_pic24_dspic30_dspic33.o
	#xc16-gcc -DARCHI_pic24f -DDEVICE_24FJ64GB412 -mcpu=24FJ64GB412 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/i2c/i2c_pic24_dspic30_dspic33.c -o i2c_pic24_dspic30_dspic33.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH144 -mprocessor=32MZ1024EFH144 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/i2c/i2c_pic32.c -o i2c_pic32.o
	xc32-gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -mprocessor=32MZ1024EFH064 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/i2c/i2c_pic32.c -o i2c_pic32.o
	gcc -DARCHI_pic32mzef -DDEVICE_32MZ1024EFH064 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/i2c/i2c_sim.c -o i2c_sim.o

endif
