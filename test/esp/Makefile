RTPROG = ../..

PROJECT = deltaApp
BOARD = rtboard1_1
OUT_PWD = build

# CCFLAGS += -pedantic

MODULES += network
NETWORK_DRIVERS = esp8266

SRC += main.c html_fs_data.c

all : hex


include $(RTPROG)/rtprog.mk

html_fs_data.c: $(HTMLGEN_EXE) $(call rwildcard, html_fs/, *)
	$(HTMLGEN_EXE) -i html_fs/ -o html_fs_data.c
