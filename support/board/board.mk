
# check BOARD variable exists
# BOARD does not have to be defined. A project can be setted BOARD (ie. working with a labdec) 
ifndef BOARD
 ifndef ARCHI
  ifndef DEVICE
   $(error Define BOARD or (ARCHI and DEVICE) in your project)
  endif
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
endif