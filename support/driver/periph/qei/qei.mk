ifndef QEI_DRIVER
QEI_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += qei.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 SRC += qei_dspic.c
 HEADER += qei_dspic.h
endif

endif
