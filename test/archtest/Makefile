
MAKE?=make

RULE ?= all

ORANGE:=$(shell command -v tput > /dev/null && tput setaf 3)
NORM:=$(shell command -v tput > /dev/null && tput sgr0)

.PHONY: all
all: 

.PHONY: boards boards16 boards32
boards: boards16 boards32
boards16: a6screenboard rtboard rtboard1_1 swarmtips curiosity_PIC24F curiosity_dsPIC33CH uio44fr umc1bds32fr udt1cr-i
boards32: curiosity_32MM_USB curiosity_32MX470 emz64 swarmtips2 curiosity_32MZ_EF PIC32MK1024GPE_devboard

.PHONY: cpu_list allcpu
allcpu: $(shell cat cpu_list)
cpu_list:
	ls /opt/microchip/xc16/v1.31/support/*/h |grep -E "p[23].*\.h"|grep -v -E "xxx" |sed 's/^p\(.*\)\.h/\1/' > cpu_list

.PHONY: pic
pic: pic16b pic32

.PHONY: pic16b dspic30f dspic33ep dspic33ch dspic33ck dspic33fj pic24
pic16b: dspic30f dspic33ep dspic33ch dspic33ck dspic33fj pic24
dspic30f: 30F6014A 30F6010 30F5011
dspic33ep: 33EP512MC506 33EP512GP506 33EP512MU810 33EP16GS506 33EP64GS808 33EP512GM710
dspic33ch: 33CH128MP208 33CH128MP208S1 33CK128MP506 33CK256MP508
dspic33ck: 33CK128MP202
dspic33fj: 33FJ32GP104 33FJ128GP206A 33FJ128GP306 33FJ256GP506 33FJ128GP706A 33FJ128GP804 33FJ16GS404 33FJ16GS502 33FJ32GS606 33FJ32MC104 33FJ64MC204 33FJ16MC304 33FJ128MC506A 33FJ256MC710A 33FJ64MC804
pic24:   # 24FJ512GA610 24FV16KA304 24F08KM204

.PHONY: pic32 pic32mm pic32mk pic32mx pic32mz
pic32: pic32mm pic32mk pic32mx pic32mk pic32mz
pic32mm: 32MM0064GPL028 32MM0256GPM048
pic32mk: 32MK1024MCF100
pic32mx: 32MX370F512L 32MX470F512H 32MX575F256H 32MX795F512L
pic32mz: 32MZ1024ECH100 32MZ0512EFF100 32MZ2064DAH169

a6screenboard rtboard rtboard1_1 swarmtips curiosity_PIC24F curiosity_dsPIC33CH curiosity_32MM_USB curiosity_32MX470 emz64 swarmtips2 curiosity_32MZ_EF PIC32MK1024GPE_devboard uio44fr umc1bds32fr udt1cr-i :
	@printf ">>> $(ORANGE)BOARD: $@$(NORM)\n"
	@OUT_PWD=build_$@ BOARD=$@ $(MAKE) --no-print-directory -f Makefile.arch -j $(RULE) CCFLAGS=-DBOARD

clean:
	rm -rf build* log*

%:
	@printf ">>> $(ORANGE)PROC : $@$(NORM)\n"
	@OUT_PWD=build_$@ DEVICE=$@ $(MAKE) --no-print-directory -f Makefile.arch -j $(RULE)

