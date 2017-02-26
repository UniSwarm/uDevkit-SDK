ifndef NETWORK_MODULE
NETWORK_MODULE=

NETPATH := $(MODULEPATH)

vpath %.c $(NETPATH)

include $(foreach net_driver,$(sort $(NETWORK_DRIVERS)),$(NETPATH)/driver/$(net_driver)/$(net_driver).mk)

network_driver.h : Makefile
	@echo "generate network_driver.h..."
	@printf "\n// defines use of modules and drivers\n\
$(subst $(space),\n,$(foreach NETWORK_DRIVER,$(sort $(NETWORK_DRIVERS)),#define USE_$(NETWORK_DRIVER)\n))\n\
" > network_driver.h
CONFIG_HEADERS += network_driver.h

endif
