
# $(warning $(DRIVERS))

define includedriver
 NDRIVER_FILES=
 ifneq "$(wildcard $(RTPROG)/support/driver/$(1)/$(1).mk)" ""
  ifeq (,$(findstring " $1 ",$(IDRIVERS)))
   DRIVER_FILES += $(RTPROG)/support/driver/$(1)/$(1).mk
   NDRIVER_FILES += $(RTPROG)/support/driver/$(1)/$(1).mk
   IDRIVERS += $(1)
  endif
 else
  ifeq (,$(findstring $1,$(BADDRIVERS)))
   BADDRIVERS += $(1)
  endif
 endif
endef

define includedrivers
 $(foreach DRIVER, $(filter-out $(sort $(BADDRIVERS) $(IDRIVERS)), $(sort $(DRIVERS))), $(eval $(call includedriver,$(DRIVER))))
 -include $(NDRIVER_FILES)
endef

$(eval $(includedrivers))
$(eval $(includedrivers))
$(eval $(includedrivers))
$(eval $(includedrivers))
$(eval $(includedrivers))

DRIVERS := $(sort $(IDRIVERS))
