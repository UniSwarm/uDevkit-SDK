
DRIVERPATH = $(dir $(lastword $(MAKEFILE_LIST)))

BADDRIVERS =
IDRIVERS =

define includedriver
 ifneq ("$(wildcard $(UDEVKIT)/support/driver/$(1)/$(1).mk)","")
  ifeq (,$(findstring " $1 ",$(IDRIVERS)))
   DRIVER_FILES += $(UDEVKIT)/support/driver/$(1)/$(1).mk
   IDRIVERS += $(1)
   include $(UDEVKIT)/support/driver/$(1)/$(1).mk
  endif
 else
  ifeq (,$(findstring $1,$(BADDRIVERS)))
   BADDRIVERS += $(1)
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
