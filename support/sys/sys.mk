ifndef SYS_FILE
SYS_FILE=

vpath %.c $(UDEVKIT)/support/sys/
vpath %.h $(UDEVKIT)/include/sys/

SRC += fifo.c buffer.c device.c
HEADER += fifo.h buffer.h

$(OUT_PWD)/device.o: $(OUT_PWD)/modules.h

#test-fifo:
#	gcc $(UDEVKIT)/support/sys/fifo.c -Wall -Wextra -I$(UDEVKIT)/include -DTEST_FIFO -o a.exe && ./a.exe
#	rm a.exe

endif
