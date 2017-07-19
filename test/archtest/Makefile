
MAKE?=make

GREEN:=$(shell command -v tput > /dev/null && tput setaf 2)
NORM:=$(shell command -v tput > /dev/null && tput sgr0)
	
all: pic32 pic16b

pic16b: dspic30f dspic33ep
dspic30f:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic30f DEVICE=30F6014A $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
	
dspic33ep: dspic33epmc5 dspic33epgp5 dspic33epmu8 dspic33epgs5 dspic33epgs8 dspic33epgm7
dspic33epmc5:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic33ep DEVICE=33EP512MC506 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
dspic33epgp5:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic33ep DEVICE=33EP512GP506 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
dspic33epmu8:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic33ep DEVICE=33EP512MU810 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
dspic33epgs5:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic33ep DEVICE=33EP16GS506 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
dspic33epgs8:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic33ep DEVICE=33EP64GS808 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
dspic33epgm7:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=dspic33ep DEVICE=33EP512GM710 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )

pic32: pic32mm pic32mk pic32mx pic32mk pic32mz

pic32mm: pic32mmgpl pic32mmgpm
pic32mmgpl:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mm DEVICE=32MM0064GPL028 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
pic32mmgpm:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mm DEVICE=32MM0256GPM048 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )

pic32mk:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mk DEVICE=32MK1024MCF100 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )

pic32mx: pic32mx3 pic32mx5 pic32mx7
pic32mx3:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mx DEVICE=32MX370F512L $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
pic32mx5:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mx DEVICE=32MX575F256H $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
pic32mx7:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mx DEVICE=32MX795F512L $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )

pic32mz: pic32mzec pic32mzef pic32mzda
pic32mzec:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mzec DEVICE=32MZ1024ECH100 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
pic32mzef:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mzef DEVICE=32MZ0512EFF100 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )
pic32mzda:
	@printf "> $(GREEN)$@$(NORM)\n"
	@OUT_PWD=build_$@ ARCHI=pic32mzda DEVICE=32MZ2064DAH169 $(MAKE) -f Makefile.arch -j all > log_$@ 2>&1 || ( cat log_$@ ; false )

clean:
	rm -rf build* log*
