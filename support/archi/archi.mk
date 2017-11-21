
ARCHIPATH = $(dir $(lastword $(MAKEFILE_LIST)))

ARCHI_FILE = $(RTPROG)/support/archi/$(ARCHI)/$(ARCHI).mk

# check BOARD_FILE exists 
ifeq ("$(wildcard $(ARCHI_FILE))","")
 $(error Invalid ARCHI name '$(ARCHI)')
endif

DEFINES += -DARCHI_$(ARCHI) -DDEVICE_$(DEVICE)

# include the architecture file
include $(ARCHI_FILE)
