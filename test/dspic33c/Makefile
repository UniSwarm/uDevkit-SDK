UDEVKIT = ../..

DEV_PROG = ICD4
PROJECT = dspic33c

BOARD = curiosity_dsPIC33CH

OUT_PWD = build 

CCFLAGS += -g -O1

DRIVERS += sysclock timer gpio uart qei i2c can adc msi

MODULES += cmdline

SRC += main.c

all : hex

vpath %.s $(OUT_PWD)
ARCHI_SRC += dspic33c_secondary.s
build/dspic33c_secondary.s: secondary/build/dspic33c_secondary.elf
	cd build; xc16-bin2hex ../secondary/build/dspic33c_secondary.elf --image dspic33c_secondary || true

.PHONY: secondary/build/dspic33c_secondary.elf clean-secondary
secondary/build/dspic33c_secondary.elf:
	cd secondary; CCFLAGS="$(CCFLAGS)" $(MAKE)

clean: clean-secondary
clean-secondary:
	cd secondary; $(MAKE) clean

all : hex

include $(UDEVKIT)/udevkit.mk
