ifndef NETWORK_MODULE
NETWORK_MODULE=

NETPATH := $(MODULEPATH)

SRC += network.c
HEADER += network.h

vpath %.c $(NETPATH)
vpath %.h $(NETPATH)

include $(foreach net_driver,$(sort $(NETWORK_DRIVERS)),$(NETPATH)/driver/$(net_driver)/$(net_driver).mk)

$(OUT_PWD)/network_driver.h : $(firstword $(MAKEFILE_LIST))
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@echo "$(YELLOW)generate network_driver.h...$(NORM)"
	@printf "\n// defines use of modules and drivers\n\
$(subst $(space),\n,$(foreach NETWORK_DRIVER,$(sort $(NETWORK_DRIVERS)),#define USE_$(NETWORK_DRIVER)\n))\n\
" > $(OUT_PWD)/network_driver.h
CONFIG_HEADERS += $(OUT_PWD)/network_driver.h

# HTMLGEN_EXE cmd
ifeq ($(OS),Windows_NT)
 HTMLGEN_EXE := $(UDEVKIT)/bin/htmlGen.exe
else
 HTMLGEN_EXE := $(UDEVKIT)/bin/htmlGen
endif
$(HTMLGEN_EXE): $(UDEVKIT)/tool/htmlGen/htmlGen.cpp $(UDEVKIT)/tool/htmlGen/htmlGen.pro
	@echo "Building htmlGen..."
	cd $(UDEVKIT)/tool/htmlGen/ && make
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

endif
