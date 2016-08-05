
# variable that contain the root directory of rtprog
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

# if OUT_PWD undefined, OUT_PWD is forced to build/ sub directory
ifndef OUT_PWD
 OUT_PWD = build
endif

# make all as default rule
all:

# uncomment this line when all C includes will be in GPStudio
# CCFLAGS += -nostdinc

# include all support needed
include $(RTPROG)/support/support.mk

# construction of list of OBJECTS to build and include dependencies files if exist
OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)) $(notdir $(ARCHI_SRC:.c=.o)))
-include $(OBJECTS:.o=.d)

# include path set to the local project and rtprog include path
INCLUDEPATH += -I. -I$(RTPROG)/include

# cleaning rule project
clean: FORCE
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(PROJECT).elf

# dependencies
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)

# generate list of used drivers modules
empty:=
space:= \n $(empty)
modules.h : Makefile
	@echo "generate module.h..."
	@printf "\\n// include all modules in project\n$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n))\n// defines use of modules\n$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#define USE_$(DRIVER)\n))" > modules.h

FORCE : 
	
