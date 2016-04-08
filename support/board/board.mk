
# check BOARD variable exists
# TODO: BOARD does not have to be defined. A project can be setted BOARD (ie. working with a labdec) 
ifndef BOARD
$(error Define BOARD in your project)
endif

BOARD_FILE = $(RTPROG)/support/board/$(BOARD)/$(BOARD).mk

# check BOARD_FILE exists 
ifeq ("$(wildcard $(BOARD_FILE))","")
$(error Invalid BOARD name)
endif

# include the board file
-include $(BOARD_FILE)
