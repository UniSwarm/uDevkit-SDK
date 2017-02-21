ifndef SENSOR_MODULE
SENSOR_MODULE=

vpath %.c $(MODULEPATH)
vpath %.c $(MODULEPATH)/driver

# SRC += sensor.c

SRC += driver/VL6180X.c

endif
