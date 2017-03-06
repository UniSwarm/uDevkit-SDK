MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
	MAKEFLAGS += -r
CONFIG_HEADERS = $(OUT_PWD)/modules.h

# variable that contain the root directory of rtprog
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

# if OUT_PWD undefined, OUT_PWD is forced to build/ sub directory
ifndef OUT_PWD
 OUT_PWD = build
endif

YELLOW:=$(shell type -p tput > /dev/null && tput setaf 3)
GREEN:=$(shell type -p tput > /dev/null && tput setaf 2)
NORM:=$(shell type -p tput > /dev/null && tput sgr0)

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
INCLUDEPATH += -I. -I$(RTPROG)/include -I$(OUT_PWD)

# cleaning rule project
.PHONY: clean
clean: sim-clean
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(PROJECT).elf
	rm -f $(CONFIG_HEADERS)

# generate list of used drivers modules
empty:=
space:= \n $(empty)
$(OUT_PWD)/modules.h : Makefile
	@echo "$(YELLOW)generate module.h...$(NORM)"
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "\n// defines use of modules and drivers\n\
$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#define USE_$(DRIVER)\n))\n\
$(subst $(space),\n,$(foreach MODULE,$(sort $(MODULES)),#define USE_MODULE_$(MODULE)\n))\n\
// include all modules and drivers in project\n\
$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n))\n\
$(subst $(space),\n,$(foreach MODULE,$(sort $(MODULES)),#include \"module/$(MODULE).h\"\n))\n\
" > $(OUT_PWD)/modules.h
