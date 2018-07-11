
MODULEPATH = $(dir $(lastword $(MAKEFILE_LIST)))

BADMODULES =
IMODULES =

define includemodule
 ifneq ("$(wildcard $(UDEVKIT)/support/module/$(1)/$(1).mk)","")
  ifeq (,$(findstring " $1 ",$(IMODULES)))
   MODULE_FILES += $(UDEVKIT)/support/module/$(1)/$(1).mk
   IMODULES += $(1)
   include $(UDEVKIT)/support/module/$(1)/$(1).mk
  endif
 else
  ifeq (,$(findstring $1,$(BADMODULES)))
   BADMODULES += $(1)
  endif
 endif
endef

define includemodules
 $(foreach MODULE, $(filter-out $(sort $(BADMODULES) $(IMODULES)), $(sort $(MODULES))), $(eval $(call includemodule,$(MODULE))))
endef

# 6 levels of inclusion modules
$(eval $(call $(includemodules)))
$(eval $(call $(includemodules)))
$(eval $(call $(includemodules)))
$(eval $(call $(includemodules)))
$(eval $(call $(includemodules)))
$(eval $(call $(includemodules)))

MODULES := $(sort $(IMODULES))
