UDEVKIT = ../..

PROJECT = swarm2test
BOARD = swarmtips2
OUT_PWD = build

DEV_PROG?=RICE

DRIVERS += uart i2c timer pwm adc gpio

MODULES += network
NETWORK_DRIVERS = esp8266

MODULES += gui
GUI_DRIVERS = ssd1306
FONTS += Lucida_Console9

MODULES += sensor
SENSOR_DRIVERS = VL6180X

SRC += main.c ihm.c html_fs_data.c restApi.c

all : hex

include $(UDEVKIT)/udevkit.mk

$(info SRC = $(SRC))

html_fs_data.c: $(HTMLGEN_EXE) $(call rwildcard, html_fs/, *)
	$(HTMLGEN_EXE) -i html_fs/ -o html_fs_data.c
