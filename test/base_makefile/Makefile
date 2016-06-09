
DEVICE = 33EP256MU806

AS = xc16-as
CC = xc16-gcc
CCFLAGS = -mcpu=$(DEVICE)
LD = xc16-ld
AR = xc16-ar
HX = xc16-bin2hex
SIM = sim30

PROJECT = base_makefile

all: build/$(PROJECT).hex
	
build/$(PROJECT).hex : build/$(PROJECT).aaa
	$(HX) build/$(PROJECT).aaa

build/$(PROJECT).aaa : build/main.o build/setup.o
	$(CC) $(CCFLAGS) -o build/$(PROJECT).aaa build/main.o build/setup.o -T p$(DEVICE).gld

build/main.o : main.c setup.h
	@test -d build || mkdir -p build
	$(CC) $(CCFLAGS) -o build/main.o -c main.c

build/setup.o : setup.c setup.h
	@test -d build || mkdir -p build
	$(CC) $(CCFLAGS) -o build/setup.o -c setup.c

test: build/$(PROJECT).hex
	$(SIM) sim.cmd
	cat Uartout.txt

clean:
	rm -rf build/*.o
