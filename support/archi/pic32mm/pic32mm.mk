
vpath %.c $(UDEVKIT)/support/archi/pic32mm/
vpath %.h $(UDEVKIT)/support/archi/pic32mm/
ARCHI_SRC += pic32mm.c
HEADER += pic32mm.h

include $(UDEVKIT)/support/archi/pic32/pic32.mk
