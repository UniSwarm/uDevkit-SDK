
DEVICE = 32MZ2048EFH064
ARCHI = pic32mzef

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
vpath %.h $(dir $(lastword $(MAKEFILE_LIST)))

DRIVERS += gpio

SRC += emz64.c
HEADER += emz64.h
ARCHI_SRC += emz64_fuses.c

GUI_DRIVERS += ssd1306
