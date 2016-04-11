
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

include $(RTPROG)/support/support.mk

ifndef OUT_PWD
 OUT_PWD = .
endif
OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)))
-include $(OBJECTS:.o=.d)

INCLUDEPATH += -I. -I$(RTPROG)/include

.PHONY : all

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%.o : %.c
	@test -d $(OUTPWD) || mkdir -p $(OUTPWD)
	 $(CC) $(CCFLAGS) -c  $< $(DEFINES) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

# rule to link OBJECTS to OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(OUT_PWD)/$(notdir $@) $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -T p$(DEVICE).gld

elf : $(OUT_PWD)/$(PROJECT).elf

clean: FORCE
	rm -f $(OBJECTS)
	rm -f $(OUT_PWD)/$(PROJECT).elf 

#test, ignored at the moment
modules.h : Makefile
	printf "// include all modules in project\n$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n)" > modules.h

FORCE : 
	
