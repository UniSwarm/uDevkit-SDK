
vpath %.c $(SENSOR_PATH)
vpath %.s $(SENSOR_PATH)

DRIVERS += i2c

HEADER += VL6180X.h
SRC += VL6180X.c
