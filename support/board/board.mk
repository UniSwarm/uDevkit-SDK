
# check BOARD variable exists or DEVICE + ARCHI
# BOARD does not have to be defined. A project can be setted BOARD (ie. working with a labdec) 
ifndef BOARD
 ifndef DEVICE
  $(error Define BOARD or DEVICE in your project)
 endif
endif

ifdef BOARD
 ifdef BOARD_VERSION
  DEFINES += -DBOARD_VERSION=$(BOARD_VERSION)
 endif
 ifeq ($(patsubst %.mk,,$(lastword $(BOARD))),) # if BOARD endwith ".mk"
  BOARD_FILE = $(BOARD)
  INCLUDEPATH += -I$(dir $(BOARD_FILE))/
  BOARDPATH = $(dir $(BOARD_FILE))/
 else
  BOARD_FILE = $(UDEVKIT)/support/board/$(BOARD)/$(BOARD).mk
  INCLUDEPATH += -I$(UDEVKIT)/support/board/$(BOARD)/
  BOARDPATH = $(UDEVKIT)/support/board/$(BOARD)/
 endif
 
 # check BOARD_FILE exists 
 ifeq ("$(wildcard $(BOARD_FILE))","")
  $(error Invalid BOARD name)
 endif
 
 # include the board file
 include $(BOARD_FILE)
endif
