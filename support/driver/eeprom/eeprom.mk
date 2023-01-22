ifndef EEPROM_DRIVER
EEPROM_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += eeprom.h

ifeq ($(ARCHI),$(filter $(ARCHI),pic32mk))
 ARCHI_SRC += eeprom_pic32mk.c
 HEADER += eeprom_pic32mk.h
endif

SIM_SRC += eeprom_sim.c

endif
