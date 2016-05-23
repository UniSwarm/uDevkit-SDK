ifndef ASSERV_DRIVER
ASSERV_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += asserv.h

ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
 SRC += asserv_dspic.c
 HEADER += asserv_dspic.h
endif

endif
