
vpath %.c $(UDEVKIT)/support/archi/pic32mzec/
vpath %.h $(UDEVKIT)/support/archi/pic32mzec/
ARCHI_SRC += pic32mzec.c
HEADER += pic32mzec.h

include $(UDEVKIT)/support/archi/pic32/pic32.mk
