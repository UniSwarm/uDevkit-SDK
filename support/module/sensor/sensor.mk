ifndef SENSOR_MODULE
SENSOR_MODULE=

SENSOR_PATH := $(MODULEPATH)

vpath %.c $(SENSOR_PATH)
vpath %.h $(SENSOR_PATH)

include $(foreach SENSOR_DRIVER,$(sort $(SENSOR_DRIVERS)),$(SENSOR_PATH)/driver/$(SENSOR_DRIVER)/$(SENSOR_DRIVER).mk)

$(OUT_PWD)/sensor_driver.h : Makefile
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@echo "$(YELLOW)generate sensor_driver.h...$(NORM)"
	@printf "\n// defines use of sensors drivers\n\
$(subst $(space),\n,$(foreach SENSOR_DRIVER,$(sort $(SENSOR_DRIVERS)),#define USE_$(SENSOR_DRIVER)\n))\n\
" > $(OUT_PWD)/sensor_driver.h
CONFIG_HEADERS += $(OUT_PWD)/sensor_driver.h

endif
