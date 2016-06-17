ifndef SPI_DRIVER
SPI_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += spi.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 ARCHI_SRC += spi_dspic.c
 HEADER += spi_dspic.h
endif

endif
