ifndef MROBOT_MODULE
MROBOT_MODULE=

vpath %.c $(MODULEPATH)

SRC += mrobot.c
include $(MODULEPATH)/asserv/asserv.mk

endif
