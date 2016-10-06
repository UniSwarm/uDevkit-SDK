ifndef SPI_DRIVER
SPI_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += spi.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 ARCHI_SRC += spi_dspic.c
 HEADER += spi_dspic.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += spi_pic32.c
 HEADER += spi_pic32.h
endif

endif
