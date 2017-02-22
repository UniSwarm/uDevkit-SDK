ifndef SENSOR_MODULE
SENSOR_MODULE=

SENSOR_PATH := $(MODULEPATH)

vpath %.c $(SENSOR_PATH)

include $(foreach SENSOR_DRIVER,$(SENSOR_DRIVERS),$(SENSOR_PATH)/driver/$(SENSOR_DRIVER)/$(SENSOR_DRIVER).mk)

sensor_driver.h : Makefile
	@echo "generate sensor_driver.h..."
	@printf "\n// defines use of sensors drivers\n\
$(subst $(space),\n,$(foreach SENSOR_DRIVER,$(sort $(SENSOR_DRIVERS)),#define USE_$(SENSOR_DRIVER)\n))\n\
" > sensor_driver.h
CONFIG_HEADERS += sensor_driver.h

endif
