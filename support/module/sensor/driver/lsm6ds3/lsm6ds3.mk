
vpath %.c $(MODULEPATH)
vpath %.s $(MODULEPATH)

DRIVERS += i2c

HEADER += lsm6ds3.h
SRC += lsm6ds3.c
