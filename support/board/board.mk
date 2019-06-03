
# check BOARD variable exists or DEVICE + ARCHI
# BOARD does not have to be defined. A project can be setted BOARD (ie. working with a labdec) 
ifndef BOARD
 ifndef DEVICE
  $(error Define BOARD or DEVICE in your project)
 endif
endif

ifdef BOARD
  BOARDPATH = $(dir $(lastword $(MAKEFILE_LIST)))
  UDEV_BOARD_FILE = $(BOARDPATH)/$(BOARD)/$(BOARD).mk
  OVERLAY_BOARD_FILE = ./support/board/$(BOARD)/$(BOARD).mk

  ifeq ("$(wildcard $(OVERLAY_BOARD_FILE))","")
    ifeq ("$(wildcard $(UDEV_BOARD_FILE))","")
      $(error Invalid BOARD name $(BOARD))
    else
      # include the udevkit board file
      include $(UDEV_BOARD_FILE)
      INCLUDEPATH += -I$(UDEVKIT)/support/board/$(BOARD)/
		endif
  else
    # include the overlay board file
    include $(OVERLAY_BOARD_FILE)
    INCLUDEPATH += -I./support/board/$(BOARD)/
  endif
endif
