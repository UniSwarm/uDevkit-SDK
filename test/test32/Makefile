UDEVKIT = ../..

DEV_PROG = SNAP
PROJECT = test32
BOARD = emz64
OUT_PWD = build 

# CCFLAGS += -pedantic

DRIVERS += sysclock uart i2c timer gpio
MODULES += gui

MODULES += cmdline

SRC += main.c

all : hex

include $(UDEVKIT)/udevkit.mk
