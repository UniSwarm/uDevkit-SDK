
MAKE?=make

RULE ?= all

ORANGE:=$(shell command -v tput > /dev/null && tput setaf 3)
NORM:=$(shell command -v tput > /dev/null && tput sgr0)

.PHONY: all cpu_list allcpu

all: pic32 pic16b

allcpu: $(shell cat cpu_list)
cpu_list:
	ls /opt/microchip/xc16/v1.31/support/*/h |grep -E "p[23].*\.h"|grep -v -E "xxx" |sed 's/^p\(.*\)\.h/\1/' > cpu_list

.PHONY: pic16b dspic30f dspic33ep
pic16b: dspic30f dspic33ep
dspic30f: 30F6014A 30F6014A
dspic33ep: 33EP512MC506 33EP512GP506 33EP512MU810 33EP16GS506 33EP64GS808 33EP512GM710

.PHONY: pic32 pic32mm pic32mk pic32mx pic32mz
pic32: pic32mm pic32mk pic32mx pic32mk pic32mz
pic32mm: 32MM0064GPL028 32MM0256GPM048
pic32mk: 32MK1024MCF100
pic32mx: 32MX370F512L 32MX470F512H 32MX575F256H 32MX795F512L
pic32mz: 32MZ1024ECH100 32MZ0512EFF100 32MZ2064DAH169

curiosityMMUSB:
	@printf ">>> $(ORANGE)$@$(NORM)\n"
	@OUT_PWD=build_$@ BOARD=curiosity_32MM_USB $(MAKE) --no-print-directory -f Makefile.arch -j $(RULE) CCFLAGS=-DBOARD

clean:
	rm -rf build* log*

%:
	@printf "> $(ORANGE)$@$(NORM)\n"
	@OUT_PWD=build_$@ DEVICE=$@ $(MAKE) --no-print-directory -f Makefile.arch -j all

