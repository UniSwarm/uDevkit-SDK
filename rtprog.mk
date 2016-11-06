MAKEFLAGS += --no-builtin-rules
.SUFFIXES:

# variable that contain the root directory of rtprog
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

# if OUT_PWD undefined, OUT_PWD is forced to build/ sub directory
ifndef OUT_PWD
 OUT_PWD = build
endif

# VERBOSE variable to set the verbosity if VERBOSE=1
ifeq ($(VERBOSE),1)
  VERB :=
else
  VERB := @
endif

# make all as default rule
all:

# uncomment this line when all C includes will be in GPStudio
# CCFLAGS += -nostdinc

# include all support needed
include $(RTPROG)/support/support.mk

# construction of list of OBJECTS to build and include dependencies files if exist
OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)) $(notdir $(ARCHI_SRC:.c=.o)))
-include $(wildcard $(OUT_PWD)/*.d)

# include path set to the local project and rtprog include path
INCLUDEPATH += -I. -I$(RTPROG)/include

# cleaning rule project
.PHONY: clean
clean:
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(PROJECT).elf
	rm -f modules.h pictures.h fonts.h

# dependencies
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)

# generate list of used drivers modules
main.c: modules.h
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
