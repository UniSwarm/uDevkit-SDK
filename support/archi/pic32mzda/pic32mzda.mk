
vpath %.c $(UDEVKIT)/support/archi/pic32mzda/
vpath %.h $(UDEVKIT)/support/archi/pic32mzda/
ARCHI_SRC += pic32mzda.c
HEADER += pic32mzda.h

include $(UDEVKIT)/support/archi/pic32/pic32.mk
