
# IPE_EXE cmd
ifeq ($(OS),Windows_NT)
 IPE_EXE := ipecmd
else
 IPE_EXE := ipecmd.sh
endif

prog : $(OUT_PWD)/$(PROJECT).hex
	$(IPE_EXE) -P$(DEVICE) -TPPK3 -F$(OUT_PWD)/$(PROJECT).hex -M

# special cmd for hex creation
$(OUT_PWD)/$(PROJECT).hex : build/$(PROJECT).elf
	@printf "HX %-30s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	@$(HX) $(OUT_PWD)/$(PROJECT).elf

elf : $(OUT_PWD)/$(PROJECT).elf
hex : $(OUT_PWD)/$(PROJECT).hex
