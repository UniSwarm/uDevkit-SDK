
# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
 SIM_EXE := $(PROJECT).exe
else
 SIM_EXE := $(PROJECT)
endif

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=_sim.o)))
-include $(SIM_OBJECTS:.o=.d)

$(OUT_PWD)/%_sim.o : %.c modules.h
	@printf "CC %-30s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@gcc $(CCFLAGS) -c  $< $(DEFINES) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@gcc $(CCFLAGS) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

sim : $(OUT_PWD)/$(SIM_EXE)
	./$(OUT_PWD)/$(SIM_EXE)
