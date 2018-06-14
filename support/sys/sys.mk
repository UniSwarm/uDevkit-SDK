ifndef SYS_FILE
SYS_FILE=

vpath %.c $(UDEVKIT)/support/sys/

SRC += fifo.c buffer.c device.c

$(OUT_PWD)/device.o: $(OUT_PWD)/modules.h

#test-fifo:
#	gcc $(UDEVKIT)/support/sys/fifo.c -I../../include -DTEST_FIFO -o a.exe && ./a.exe
#	rm a.exe

endif
