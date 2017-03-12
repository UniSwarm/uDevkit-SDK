
vpath %.c $(MODULEPATH)
vpath %.s $(MODULEPATH)

DRIVERS += i2c

HEADER += VL6180X.h
SRC += VL6180X.c
