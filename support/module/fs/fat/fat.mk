ifndef FS_MODULE
FS_MODULE=

vpath %.c $(RTPROG)/contrib/fatfs/src
SRC += ff.c

ARCHI_SRC += diskio.c
SIM_SRC += diskio_sim.c

endif
