
ARCHIPATH = $(dir $(lastword $(MAKEFILE_LIST)))

ARCHI_FILE = $(RTPROG)/support/archi/$(ARCHI)/$(ARCHI).mk

# check BOARD_FILE exists 
ifeq ("$(wildcard $(ARCHI_FILE))","")
 $(error Invalid ARCHI name)
endif

DEFINES += -DARCHI_$(ARCHI) -DDEVICE_$(DEVICE)

# include the achitechture file
include $(ARCHI_FILE)
