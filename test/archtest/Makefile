
MAKE?=make
	
all: pic32mk

pic32mk:
	OUT_PWD=build_pic32mk ARCHI=pic32mk DEVICE=32MK1024MCF100 $(MAKE) -f Makefile.arch all

pic32mx:
	OUT_PWD=build_pic32mx ARCHI=pic32mx DEVICE=32MX330F064L $(MAKE) -f Makefile.arch all

clean:
	rm -rf build*
