ifndef MOTOR_DRIVER
MOTOR_DRIVER=

vpath %.c $(DRIVERPATH)
vpath %.h $(DRIVERPATH)

HEADER += motor.h
ARCHI_SRC += motor.c

SIM_SRC += motor_sim.c

endif
