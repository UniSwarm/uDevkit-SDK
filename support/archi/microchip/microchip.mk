
# IPE_EXE cmd
ifeq ($(OS),Windows_NT)
 IPE_EXE := ipecmd.exe
else
 IPE_EXE := ipecmd.sh
endif

DEV_PROG?=PK3  # default value pickit3 (PK3), possible value: real ice (RICE) or ICD3 (ICD3)
prog : $(OUT_PWD)/$(PROJECT).hex
	$(IPE_EXE) -P$(DEVICE) -TP$(DEV_PROG) -F$(OUT_PWD)/$(PROJECT).hex -M -OL

# special cmd for hex creation
$(OUT_PWD)/$(PROJECT).hex : $(OUT_PWD)/$(PROJECT).elf
	@printf "$(GREEN)µHX %-35s => %s\n$(NORM)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(HX) $(OUT_PWD)/$(PROJECT).elf

elf : $(OUT_PWD)/$(PROJECT).elf
hex : $(OUT_PWD)/$(PROJECT).hex

# construction of list of OBJECTS to build and include dependencies files if exist
OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=.o)) $(notdir $(ARCHI_SRC:.c=.o)))
-include $(wildcard $(OUT_PWD)/*.d)
$(OBJECTS) : $(CONFIG_HEADERS)

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%.o : %.c
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(GREEN)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c  $< $(DEFINES) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

HEAP?=1000

# rule to link OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	@printf "$(GREEN)µLD %-35s => %s\n$(NORM)" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc $(LDFLAGS_XC)

.PHONY : showmem dbg.% dbg
# prints memory report
showmem : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) -lc $(LDFLAGS_XC) -Wl,--report-mem

# lists symbol present in final elf
dbg : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(OBJDUMP) -t $(OUT_PWD)/$(PROJECT).elf |grep "F .text" |sort -k6

# shows a disassembly listing of the symbol after the dot
dbg.% : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(OBJDUMP) -S $(OUT_PWD)/$(PROJECT).elf |sed -n -e '/^[a-f0-9]\+ <_*$*>:/,/^[a-f0-9]\+ <_.*>:/ p'
