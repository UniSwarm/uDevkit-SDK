ifndef FS_MODULE
FS_MODULE=

vpath %.c $(MODULEPATH)
include $(MODULEPATH)/fat/fat.mk

endif
