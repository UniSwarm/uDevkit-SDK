
SRC=$(wildcard cmd/*.c) cmdline.c
OBJS=$(SRC:.c=.o)

all : a.exe

a.exe: $(OBJS)
	gcc $(OBJS) -o a.exe

%.o : %.c
	gcc -c $< -o $@ -I../../../include/ -DTEST_CMDLINE
