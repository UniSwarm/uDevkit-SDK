
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

ifndef OUT_PWD
 OUT_PWD = .
endif

include $(RTPROG)/support/support.mk

OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)))
-include $(OBJECTS:.o=.d)

INCLUDEPATH += -I. -I$(RTPROG)/include

.PHONY : all

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%.o : %.c modules.h
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	 $(CC) $(CCFLAGS) -c  $< $(DEFINES) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

# rule to link OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(OUT_PWD)/$(notdir $@) $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc -T p$(DEVICE).gld

$(OUT_PWD)/$(PROJECT).hex : build/$(PROJECT).elf
	$(HX) $(OUT_PWD)/$(PROJECT).elf

elf : $(OUT_PWD)/$(PROJECT).elf
hex : $(OUT_PWD)/$(PROJECT).hex

prog : $(OUT_PWD)/$(PROJECT).hex
	ipecmd -P$(DEVICE) -TPPK3 -F$(OUT_PWD)/$(PROJECT).hex -M

clean: FORCE
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(PROJECT).elf

# generate list of used drivers modules
modules.h : Makefile
	@echo "generate module.h..."
	@printf "// include all modules in project\n$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n)" > modules.h

FORCE : 
	
