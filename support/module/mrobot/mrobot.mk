ifndef MROBOT_MODULE
MROBOT_MODULE=

vpath %.c $(MODULEPATH)

SRC += mrobot.c
include $(MODULEPATH)/asserv/asserv.mk

SIM_SRC += mrobot_sim.c

endif
