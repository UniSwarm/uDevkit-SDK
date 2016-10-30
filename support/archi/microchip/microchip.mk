
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
	$(VERB)$(HX) $(OUT_PWD)/$(PROJECT).elf

elf : $(OUT_PWD)/$(PROJECT).elf
hex : $(OUT_PWD)/$(PROJECT).hex

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%.o : %.c
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "µCC %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC) -mcpu=$(DEVICE) $(CCFLAGS) $(CCFLAGS_XC) -c  $< $(DEFINES) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CC) -mcpu=$(DEVICE) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

HEAP=1000

# rule to link OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	@printf "µLD %-35s => %s\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc -Wl,--heap=$(HEAP),-Tp$(DEVICE).gld

.PHONY : showmem dbg.% dbg
# prints memory report
showmem : $(OBJECTS)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc -Wl,--heap=$(HEAP),-Tp$(DEVICE).gld,--report-mem

# lists symbol present in final elf
dbg : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)xc16-objdump -t $(OUT_PWD)/$(PROJECT).elf |grep "F .text" |sort -k6

# shows a disassembly listing of the symbol after the dot
dbg.% : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)xc16-objdump -S $(OUT_PWD)/$(PROJECT).elf |sed -n -e '/<_*$*>:/,/<_.*>/ p'
