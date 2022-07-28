
vpath %.c $(UDEVKIT)/support/archi/pic32mzef/
vpath %.h $(UDEVKIT)/support/archi/pic32mzef/
ARCHI_SRC += pic32mzef.c
HEADER += pic32mzef.h

include $(UDEVKIT)/support/archi/pic32/pic32.mk
