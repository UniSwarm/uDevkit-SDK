
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

ifndef OUT_PWD
 OUT_PWD = .
endif

include $(RTPROG)/support/support.mk

OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)))
-include $(OBJECTS:.o=.d)

INCLUDEPATH += -I. -I$(RTPROG)/include

.PHONY : all

clean: FORCE
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(PROJECT).elf

$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)

# generate list of used drivers modules
modules.h : Makefile
	@echo "generate module.h..."
	@printf "// include all modules in project\n$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n)" > modules.h

FORCE : 
	
