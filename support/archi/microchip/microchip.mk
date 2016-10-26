
# IPE_EXE cmd
ifeq ($(OS),Windows_NT)
 IPE_EXE := ipecmd.exe
else
 IPE_EXE := ipecmd.sh
endif

prog : $(OUT_PWD)/$(PROJECT).hex
	$(IPE_EXE) -P$(DEVICE) -TPPK3 -F$(OUT_PWD)/$(PROJECT).hex -M -OL

# special cmd for hex creation
$(OUT_PWD)/$(PROJECT).hex : build/$(PROJECT).elf
	@printf "µHX %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	@$(HX) $(OUT_PWD)/$(PROJECT).elf

elf : $(OUT_PWD)/$(PROJECT).elf
hex : $(OUT_PWD)/$(PROJECT).hex

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%.o : %.c
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "µCC %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(CC) -mcpu=$(DEVICE) $(CCFLAGS) $(CCFLAGS_XC) -c  $< $(DEFINES) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CC) -mcpu=$(DEVICE) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

# rule to link OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	@printf "µLD %-35s => %s\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc -T p$(DEVICE).gld

.PHONY : showmem dbg.% dbg
showmem :
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc -T p$(DEVICE).gld -Wl,--report-mem

dbg.% : $(OUT_PWD)/$(PROJECT).elf
	xc16-objdump -S $(OUT_PWD)/$(PROJECT).elf |sed -n -e '/<_*$*>/,/<_.*>/ p'
dbg : $(OUT_PWD)/$(PROJECT).elf
	xc16-objdump -t $(OUT_PWD)/$(PROJECT).elf |grep "F .text" |sort -k6
