MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
	MAKEFLAGS += -r
CONFIG_HEADERS = modules.h

# variable that contain the root directory of rtprog
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

# if OUT_PWD undefined, OUT_PWD is forced to build/ sub directory
ifndef OUT_PWD
 OUT_PWD = build
endif

# VERBOSE variable to set the verbosity if VERBOSE=1
ifdef VERBOSE
  VERB :=
else
  VERB := @
endif

# make all as default rule
all:

# uncomment this line when all C includes will be in RTProg
# CCFLAGS += -nostdinc

# include all support needed
include $(RTPROG)/support/support.mk

# include path set to the local project and rtprog include path
INCLUDEPATH += -I. -I$(RTPROG)/include

# cleaning rule project
.PHONY: clean
clean: sim-clean
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(PROJECT).elf
	rm -f $(CONFIG_HEADERS)

# generate list of used drivers modules
empty:=
space:= \n $(empty)
modules.h : Makefile
	@echo "generate module.h..."
	@printf "\n// defines use of modules and drivers\n\
$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#define USE_$(DRIVER)\n))\n\
$(subst $(space),\n,$(foreach MODULE,$(sort $(MODULES)),#define USE_MODULE_$(MODULE)\n))\n\
// include all modules and drivers in project\n\
$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n))\n\
$(subst $(space),\n,$(foreach MODULE,$(sort $(MODULES)),#include \"module/$(MODULE).h\"\n))\n\
" > modules.h
