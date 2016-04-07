
# $(warning $(DRIVERS))

define checkfile
ifneq "$(wildcard $(RTPROG)/support/driver/$(1)/$(1).mk)" ""
DRIVER_FILES += $(RTPROG)/support/driver/$(1)/$(1).mk
endif
endef

$(foreach DRIVER, $(DRIVERS), $(eval $(call checkfile,$(DRIVER))))

-include $(DRIVER_FILES)

