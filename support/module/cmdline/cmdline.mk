ifndef CMDLINE_MODULE
CMDLINE_MODULE=

vpath %.c $(MODULEPATH) $(MODULEPATH)cmd

SRC += cmdline.c
HEADER += cmdline.h

# include all commands
SRC := $(SRC) $(wildcard $(MODULEPATH)cmd/*.c)

endif
