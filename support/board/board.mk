
BOARDPATH = $(dir $(lastword $(MAKEFILE_LIST)))

# check BOARD variable exists or DEVICE + ARCHI
# BOARD does not have to be defined. A project can be setted BOARD (ie. working with a labdec) 
ifndef BOARD
 ifndef DEVICE
  $(error Define BOARD or DEVICE in your project)
 endif
endif

ifdef BOARD
 BOARD_FILE = $(RTPROG)/support/board/$(BOARD)/$(BOARD).mk
 
 # check BOARD_FILE exists 
 ifeq ("$(wildcard $(BOARD_FILE))","")
  $(error Invalid BOARD name)
 endif
 
 # include the board file
 include $(BOARD_FILE)
 
 INCLUDEPATH += -I$(RTPROG)/support/board/$(BOARD)/
endif
