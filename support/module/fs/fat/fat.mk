ifndef FS_MODULE
FS_MODULE=

vpath %.c $(UDEVKIT)/contrib/fatfs/src
SRC += ff.c

ARCHI_SRC += diskio.c
SIM_SRC += diskio_sim.c

endif
