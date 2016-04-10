
RTPROG := $(dir $(lastword $(MAKEFILE_LIST)))

include $(RTPROG)/support/support.mk

ifndef OUT_PWD
 OUT_PWD = .
endif
OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)))

INCLUDEPATH += -I. -I$(RTPROG)/include

.PHONY : all

# rule to build OBJECTS to OUT_PWD
$(OUT_PWD)/%.o : %.c
	@test -d $(OUTPWD) || mkdir -p $(OUTPWD)
	$(CC) $(CCFLAGS) -c $< -o $(OUT_PWD)/$(notdir $@) $(DEFINES) $(INCLUDEPATH)

# rule to link OBJECTS to OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(OUT_PWD)/$(notdir $@) $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -T p$(DEVICE).gld

clean: FORCE
	rm -f $(OBJECTS)
	rm -f $(OUT_PWD)/$(PROJECT).elf

#test, ignored at the moment
modules.h : FORCE
	echo -e "// include all modules in project\n$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n)" > modules.h

FORCE : 

