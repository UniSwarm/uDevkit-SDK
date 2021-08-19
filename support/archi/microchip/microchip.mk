
# IPE_EXE cmd
ifeq ($(OS),Windows_NT)
 IPE_EXE := ipecmd.exe
else
 IPE_EXE := ipecmd.sh
endif

DEV_PROG?=PK3  # default value pickit3 (PK3), possible value: real ice (RICE), ICD3/4 (ICD3 / ICD4), pickit on board (PKOB) or pickit4 (PK4)
ifeq (,$(filter $(DEV_PROG),PKOB PK3 PK4 ICD3 ICD4 RICE))
 $(error Invalid DEV_PROG name '$(DEV_PROG)', choose between 'PKOB', 'PK3', 'PK4', 'ICD3', 'ICD4' or 'RICE')
endif

IPEFLAGS ?= -M
prog : $(OUT_PWD)/$(PROJECT).hex
	cd $(OUT_PWD)/ && $(IPE_EXE) -P$(DEVICE) -TP$(DEV_PROG) -F$(PROJECT).hex -OL $(IPEFLAGS) || true
	@rm $(OUT_PWD)/log.* $(OUT_PWD)/MPLABXLog.* || true

.PHONY: read
read :
	cd $(OUT_PWD)/ && $(IPE_EXE) -P$(DEVICE) -TP$(DEV_PROG) -GF$(PROJECT)_read.hex || true
	@rm $(OUT_PWD)/log.* $(OUT_PWD)/MPLABXLog.* || true

# special cmd for hex creation
$(OUT_PWD)/$(PROJECT).hex : $(OUT_PWD)/$(PROJECT).elf
	@printf "$(COMPCOLOR)µHX %-35s => %s\n$(NORM)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(HX) $(OUT_PWD)/$(PROJECT).elf

elf : $(OUT_PWD)/$(PROJECT).elf
hex : $(OUT_PWD)/$(PROJECT).hex

# construction of list of OBJECTS to build and include dependencies files if exist
OBJECTS := $(notdir $(SRC:.S=.o)) $(notdir $(ARCHI_SRC:.S=.o))
OBJECTS := $(OBJECTS:.s=.o)
OBJECTS := $(OBJECTS:.c=.o)
OBJECTS := $(addprefix $(OUT_PWD)/, $(OBJECTS))
-include $(wildcard $(OUT_PWD)/*.d)
$(OBJECTS) : $(CONFIG_HEADERS)

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%.o : %.c
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(COMPCOLOR)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OUT_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d
	$(VERB)$(OBJDUMP) -S $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.lst

$(OUT_PWD)/%.o : %.S
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(COMPCOLOR)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OUT_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

$(OUT_PWD)/%.o : %.s
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(COMPCOLOR)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OUT_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

HEAP?=100

# rule to link OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	@printf "$(COMPCOLOR)µLD %-35s => %s\n$(NORM)" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) $(LIBS) -lc $(LDFLAGS_XC) -Wl,-Map="$(OUT_PWD)/$(PROJECT).map"

.PHONY : showmem dbg.% dbg
# prints memory report
showmem : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OUT_PWD)/,$(notdir $(OBJECTS))) $(LIBS) -lc $(LDFLAGS_XC) -Wl,-Map="$(OUT_PWD)/$(PROJECT).map",--report-mem

# lists symbol present in final elf
dbg : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(OBJDUMP) -S $(OUT_PWD)/$(PROJECT).elf |grep "F .text" |sort -k6

# shows a disassembly listing of the symbol after the dot
dbg.% : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(OBJDUMP) -S $(OUT_PWD)/$(PROJECT).elf |sed -n -e '/^[a-f0-9]\+ <_*$*>:/,/^[a-f0-9]\+ <_.*>:/ p'

vpath %.h $(OUT_PWD)
vpath %.c $(OUT_PWD)
