
DRIVERPATH = $(dir $(lastword $(MAKEFILE_LIST)))

define includedriver
 ifneq "$(wildcard $(RTPROG)/support/driver/$(1)/$(1).mk)" ""
  ifeq (,$(findstring " $1 ",$(IDRIVERS)))
   DRIVER_FILES += $(RTPROG)/support/driver/$(1)/$(1).mk
   IDRIVERS += $(1)
   include $(RTPROG)/support/driver/$(1)/$(1).mk
  endif
 else
  ifneq "$(wildcard $(RTPROG)/support/driver/periph/$(1)/$(1).mk)" ""
   ifeq (,$(findstring " $1 ",$(IDRIVERS)))
    DRIVER_FILES += $(RTPROG)/support/driver/periph/$(1)/$(1).mk
    IDRIVERS += $(1)
    include $(RTPROG)/support/driver/periph/$(1)/$(1).mk
   endif
  else
   ifeq (,$(findstring $1,$(BADDRIVERS)))
    BADDRIVERS += $(1)
   endif
  endif
 endif
endef

define includedrivers
 $(foreach DRIVER, $(filter-out $(sort $(BADDRIVERS) $(IDRIVERS)), $(sort $(DRIVERS))), $(eval $(call includedriver,$(DRIVER))))
endef

# 6 levels of inclusion drivers
$(eval $(call $(includedrivers)))
$(eval $(call $(includedrivers)))
$(eval $(call $(includedrivers)))
$(eval $(call $(includedrivers)))
$(eval $(call $(includedrivers)))
$(eval $(call $(includedrivers)))

DRIVERS := $(sort $(IDRIVERS))
