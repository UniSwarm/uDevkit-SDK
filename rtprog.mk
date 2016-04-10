
include $(RTPROG)/support/support.mk

ifndef OUT_PWD
 OUT_PWD = .
endif
OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)))

.PHONY : all

$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	$(CC) $(CCFLAGS) -o $(OUT_PWD)/$(notdir $@) $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -T p$(DEVICE).gld

$(OUT_PWD)/ : $(OUT_PWD)/
	mkdir $(OUT_PWD)

$(OUT_PWD)/%.o : %.c
	@test -d $(OUTPWD) || mkdir -p $(OUTPWD)
	$(CC) $(CCFLAGS) -c $< -o $(OUT_PWD)/$(notdir $@) $(DEFINES)

clean: FORCE
	rm -f $(OBJECTS)
	rm -f $(OUT_PWD)/$(PROJECT).elf

$(OUT_PWD)/main.o: modules.h

modules.h : Makefile
	echo $(addprefix #include , $(DRIVERS)) >> modules.h

FORCE : 

