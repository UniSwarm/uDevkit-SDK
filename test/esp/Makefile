RTPROG = ../..

PROJECT = deltaApp
BOARD = rtboard1_1
OUT_PWD = build

# CCFLAGS += -pedantic

MODULES += network
NETWORK_DRIVERS = esp8266

SRC += main.c html_fs_data.c

all : hex

INCLUDEPATH += -I$(RTPROG)/support/module/network/
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
html_fs_data.c: $(call rwildcard, html_fs/, *)
	../../bin/htmlGen -i html_fs/ -o html_fs_data.c

include $(RTPROG)/rtprog.mk

