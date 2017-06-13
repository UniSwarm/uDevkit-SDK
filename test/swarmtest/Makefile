RTPROG = ../..

PROJECT = swarmtest
BOARD = swarmtips
OUT_PWD = build

# CCFLAGS += -pedantic

DRIVERS += uart adc i2c timer

MODULES += network
NETWORK_DRIVERS = esp8266

MODULES += sensor
SENSOR_DRIVERS = VL6180X

SRC += main.c steppers.c

include $(RTPROG)/rtprog.mk

all : hex
