
vpath %.c $(UDEVKIT)/support/archi/pic32mk/
vpath %.h $(UDEVKIT)/support/archi/pic32mk/
ARCHI_SRC += pic32mk.c
HEADER += pic32mk.h

include $(UDEVKIT)/support/archi/pic32/pic32.mk
