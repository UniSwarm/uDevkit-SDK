
MAKE?=make

GREEN:=$(shell command -v tput > /dev/null && tput setaf 2)
NORM:=$(shell command -v tput > /dev/null && tput sgr0)
	
all: pic32mm pic32mk pic32mx pic32mk

pic32mm: pic32mmgpl pic32mmgpm
pic32mmgpl:
	@printf "> $(GREEN)pic32mmgpl$(NORM)\n"
	OUT_PWD=build_pic32mmgpl ARCHI=pic32mm DEVICE=32MM0064GPL028 $(MAKE) -f Makefile.arch all > /dev/null
pic32mmgpm:
	@printf "> $(GREEN)pic32mmgpm$(NORM)\n"
	OUT_PWD=build_pic32mmgpm ARCHI=pic32mm DEVICE=32MM0256GPM048 $(MAKE) -f Makefile.arch all > /dev/null

pic32mk:
	@printf "> $(GREEN)pic32mk$(NORM)\n"
	OUT_PWD=build_pic32mk ARCHI=pic32mk DEVICE=32MK1024MCF100 $(MAKE) -f Makefile.arch all > /dev/null

pic32mx: pic32mx3 pic32mx5 pic32mx7
pic32mx3:
	@printf "> $(GREEN)pic32mx3$(NORM)\n"
	OUT_PWD=build_pic32mx3 ARCHI=pic32mx DEVICE=32MX330F064L $(MAKE) -f Makefile.arch all > /dev/null
pic32mx5:
	@printf "> $(GREEN)pic32mx5$(NORM)\n"
	OUT_PWD=build_pic32mx5 ARCHI=pic32mx DEVICE=32MX534F064H $(MAKE) -f Makefile.arch all > /dev/null
pic32mx7:
	@printf "> $(GREEN)pic32mx7$(NORM)\n"
	OUT_PWD=build_pic32mx7 ARCHI=pic32mx DEVICE=32MX795F512L $(MAKE) -f Makefile.arch all > /dev/null

pic32mz: pic32mzec pic32mzef pic32mzda
pic32mzec:
	@printf "> $(GREEN)pic32mzec$(NORM)\n"
	OUT_PWD=build_pic32mzec ARCHI=pic32mzec DEVICE=32MZ1024ECH100 $(MAKE) -f Makefile.arch all > /dev/null
pic32mzef:
	@printf "> $(GREEN)pic32mzef$(NORM)\n"
	OUT_PWD=build_pic32mzef ARCHI=pic32mzef DEVICE=32MZ0512EFF100 $(MAKE) -f Makefile.arch all > /dev/null
pic32mzda:
	@printf "> $(GREEN)pic32mzda$(NORM)\n"
	OUT_PWD=build_pic32mzda ARCHI=pic32mzda DEVICE=32MZ2064DAH169 $(MAKE) -f Makefile.arch all > /dev/null

clean:
	rm -rf build*
