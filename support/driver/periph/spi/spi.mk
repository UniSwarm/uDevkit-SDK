ifndef SPI_DRIVER
SPI_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

DRIVERS += sysclock

HEADER += spi.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj dspic33fj))
 ARCHI_SRC += spi_pic24f_dspic33f.c
 HEADER += spi_pic24f_dspic33f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep dspic33ep dspic33ev))
 ARCHI_SRC += spi_pic24e_dspic33e.c
 HEADER += spi_pic24e_dspic33e.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
 ARCHI_SRC += spi_dspic30f.c
 HEADER += spi_dspic30f.h
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic32mm pic32mx pic32mzec pic32mzef))
 ARCHI_SRC += spi_pic32.c
 HEADER += spi_pic32.h
endif

endif
