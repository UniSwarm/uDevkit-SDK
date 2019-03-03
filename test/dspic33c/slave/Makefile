UDEVKIT = ../../..

DEV_PROG = ICD4
PROJECT = dspic33c_slave

BOARD = curiosity_dsPIC33CH
SLAVE = 1

OUT_PWD = build

CCFLAGS += -g -O1

DRIVERS += sysclock timer gpio qei adc

SRC += main.c

all : hex

include $(UDEVKIT)/udevkit.mk
