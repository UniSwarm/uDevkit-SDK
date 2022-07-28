
vpath %.c $(UDEVKIT)/support/archi/pic32mx/
vpath %.h $(UDEVKIT)/support/archi/pic32mx/
ARCHI_SRC += pic32mx.c
HEADER += pic32mx.h

include $(UDEVKIT)/support/archi/pic32/pic32.mk
