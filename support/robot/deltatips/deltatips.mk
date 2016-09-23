
# set default board only if it is not already set
BOARD ?= rtboard

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))

SRC += deltatips.c
