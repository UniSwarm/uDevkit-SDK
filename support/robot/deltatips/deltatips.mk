
# set default board only if it is not already set
BOARD ?= rtboard

vpath %.c $(dir $(lastword $(MAKEFILE_LIST)))
MODULES += mrobot

SRC += deltatips.c
