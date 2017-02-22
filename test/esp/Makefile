
all:

main.exe: esp.o buffer.o main.o
	gcc esp.o buffer.o main.o -o main

esp.o: ../../support/module/network/driver/esp8266/esp8266.c
	gcc -c ../../support/module/network/driver/esp8266/esp8266.c -o esp.o -I ../../include
buffer.o: ../../support/sys/buffer.c
	gcc -c ../../support/sys/buffer.c -o buffer.o -I ../../include

main.o: main.c
	gcc -c main.c -o main.o -I ../../include

clean:
