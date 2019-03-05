UDEVKIT = ../..

DEV_PROG = ICD4
PROJECT = dspic33c

BOARD = curiosity_dsPIC33CH

OUT_PWD = build 

CCFLAGS += -g -O3

DRIVERS += sysclock timer gpio uart qei i2c can adc msi

MODULES += cmdline

SRC += main.c build/dspic33c_slave.s

all : hex

build/dspic33c_slave.s: slave/build/dspic33c_slave.elf
	cd build; xc16-bin2hex ../slave/build/dspic33c_slave.elf --image dspic33c_slave || true

.PHONY: slave/build/dspic33c_slave.elf clean-slave
slave/build/dspic33c_slave.elf:
	cd slave; CCFLAGS="$(CCFLAGS)" $(MAKE)

clean: clean-slave
clean-slave:
	cd slave; $(MAKE) clean

all : hex

include $(UDEVKIT)/udevkit.mk
