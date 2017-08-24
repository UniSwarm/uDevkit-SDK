ifndef QEI_DRIVER
QEI_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += qei.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += qei_pic24f_dspic33f.c
 HEADER += qei_pic24f_dspic33f.h
endif
ifeq ($(ARCHI),dspic30f)
 ARCHI_SRC += qei_dspic30f.c
 HEADER += qei_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev))
 ARCHI_SRC += qei_pic24e_dspic33e.c
 HEADER += qei_pic24e_dspic33e.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mk))
 ARCHI_SRC += qei_pic32mk.c
 HEADER += qei_pic32mk.h
endif

SIM_SRC += qei_sim.c

test_qei:
	xc16-gcc -DARCHI_pic24ep -DDEVICE_24EP128MC202 -mcpu=24EP128MC202 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/qei/qei_pic24e_dspic33e.c -o qei_pic24e_dspic33e.o
	xc16-gcc -DARCHI_pic24f -DDEVICE_33FJ128MC510A -mcpu=33FJ128MC510A -c -I$(RTPROG)include $(RTPROG)support/driver/periph/qei/qei_pic24f_dspic33f.c -o qei_pic24f_dspic33f.o
	xc16-gcc -DARCHI_dspic30f -DDEVICE_30F3010 -mcpu=30F3010 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/qei/qei_dspic30f.c -o qei_dspic30f.o
	xc32-gcc -DARCHI_pic32mk -DDEVICE_32MK0512MCF100 -mprocessor=32MK0512MCF100 -c -I$(RTPROG)include $(RTPROG)support/driver/periph/qei/qei_pic32mk.c -o qei_pic32mk.o
	gcc -DARCHI_dspic30f -DDEVICE_30F3010 -DSIMULATOR -c -I$(RTPROG)include $(RTPROG)support/driver/periph/qei/qei_sim.c -o qei_sim.o

endif
