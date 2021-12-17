ifndef DMA_DRIVER
DMA_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += dma.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj dspic33ch dspic33ck))
 ARCHI_SRC += dma_dspic33c.c
 HEADER += dma_dspic33c.h
endif

SIM_SRC += dma_sim.c

endif
