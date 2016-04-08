
# $(warning $(DRIVERS))

define checkfile
ifneq "$(wildcard $(RTPROG)/support/driver/$(1)/$(1).mk)" ""
DRIVER_FILES += $(RTPROG)/support/driver/$(1)/$(1).mk
IDRIVERS += $(1)
else
BADDRIVERS += $(1)
endif
endef

define includedrivers
$(foreach DRIVER, $(DRIVERS), $(eval $(call checkfile,$(DRIVER))))
endef

$(eval $(includedrivers))

-include $(DRIVER_FILES)

