UDEVKIT = ../..

PROJECT = swarmtest
BOARD = swarmtips
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart adc i2c timer

MODULES += network
NETWORK_DRIVERS = esp8266

MODULES += sensor
SENSOR_DRIVERS = VL6180X

SRC += main.c steppers.c html_fs_data.c restApi.c

include $(UDEVKIT)/udevkit.mk

all : hex

html_fs_data.c: $(HTMLGEN_EXE) $(call rwildcard, html_fs/, *)
	$(HTMLGEN_EXE) -i html_fs/ -o html_fs_data.c
