
# default rule for Microchip
all : hex

# IPE_EXE cmd
ifeq ($(OS),Windows_NT)
 IPE_EXE := ipecmd.exe
else
 IPE_EXE := ipecmd.sh
endif

DEV_PROG?=PK4
ifeq (,$(filter $(DEV_PROG),PKOB PKOB4 SNAP PK3 PK4 PK5 ICD3 ICD4 ICD5 RICE ICE4))
 $(error Invalid DEV_PROG name '$(DEV_PROG)', choose between 'PKOB', 'PKOB4', 'SNAP', 'PK3', 'PK4', 'ICD3', 'ICD4', 'ICE4' or 'RICE')
endif

# keep compatibility with old sdk revision
prog : flash
	@printf "$(YELLOW)'prog' rule is deprecated, please use 'flash' instead\n$(NORM)"

IPEFLAGS ?= -M -OA2
flash : $(OUT_PWD)/$(PROJECT).hex
	@printf "$(GREEN)Flash $(DEVICE) with $(DEV_PROG) ==> $(PROJECT).hex...\n$(NORM)"
	cd $(OUT_PWD)/ && $(IPE_EXE) -P$(DEVICE) -TP$(DEV_PROG) -F$(PROJECT).hex -OL $(IPEFLAGS) || true
	@rm -f $(OUT_PWD)/log.* $(OUT_PWD)/MPLABXLog.*

.PHONY: flash-read
flash-read :
	@printf "$(GREEN)Read $(DEVICE) with $(DEV_PROG) ==> $(PROJECT)_read.hex...\n$(NORM)"
	cd $(OUT_PWD)/ && $(IPE_EXE) -P$(DEVICE) -TP$(DEV_PROG) -GF$(PROJECT)_read.hex || true
	@rm -f $(OUT_PWD)/log.* $(OUT_PWD)/MPLABXLog.*

.PHONY: flash-erase
flash-erase :
	@printf "$(GREEN)Erase $(DEVICE) with $(DEV_PROG)...\n$(NORM)"
	cd $(OUT_PWD)/ && $(IPE_EXE) -P$(DEVICE) -TP$(DEV_PROG) -E || true
	@rm -f $(OUT_PWD)/log.* $(OUT_PWD)/MPLABXLog.*

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
OBJECTS := $(OBJECTS:.cpp=.o)
OBJECTS := $(addprefix $(OBJ_PWD)/, $(OBJECTS))
-include $(wildcard $(OBJ_PWD)/*.d)
$(OBJECTS) : $(CONFIG_HEADERS)

# rule to build OBJECTS to OBJ_PWD and give dependencies
$(OBJ_PWD)/%.o : %.c $(firstword $(MAKEFILE_LIST)) $(filter %.mk, $(MAKEFILE_LIST))
	@test -d $(OBJ_PWD) || mkdir -p $(OBJ_PWD)
	@printf "$(COMPCOLOR)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OBJ_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OBJ_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OBJ_PWD)/$(notdir $@) > $(OBJ_PWD)/$*.d
	$(VERB)$(OBJDUMP) -S -r $(OBJ_PWD)/$(notdir $@) > $(OBJ_PWD)/$*.lst

$(OBJ_PWD)/%.o : %.S $(firstword $(MAKEFILE_LIST)) $(filter %.mk, $(MAKEFILE_LIST))
	@test -d $(OBJ_PWD) || mkdir -p $(OBJ_PWD)
	@printf "$(COMPCOLOR)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OBJ_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OBJ_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OBJ_PWD)/$(notdir $@) > $(OBJ_PWD)/$*.d

$(OBJ_PWD)/%.o : %.s $(firstword $(MAKEFILE_LIST)) $(filter %.mk, $(MAKEFILE_LIST))
	@test -d $(OBJ_PWD) || mkdir -p $(OBJ_PWD)
	@printf "$(COMPCOLOR)µCC %-35s => %s\n$(NORM)" $(notdir $<) $(OBJ_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OBJ_PWD)/$(notdir $@)
	@$(CC) $(CCFLAGS) $(CCFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OBJ_PWD)/$(notdir $@) > $(OBJ_PWD)/$*.d

$(OBJ_PWD)/%.o : %.cpp $(firstword $(MAKEFILE_LIST)) $(filter %.mk, $(MAKEFILE_LIST))
	@test -d $(OBJ_PWD) || mkdir -p $(OBJ_PWD)
	@printf "$(COMPCOLOR)µC++ %-34s => %s\n$(NORM)" $(notdir $<) $(OBJ_PWD)/$(notdir $@)
	$(VERB)$(CXX) $(CCFLAGS) $(CXXFLAGS) $(CCFLAGS_XC) $(CXXFLAGS_XC) -x c++ -c $< $(DEFINES) $(INCLUDEPATH) -o $(OBJ_PWD)/$(notdir $@)
	@$(CXX) $(CCFLAGS) $(CXXFLAGS) $(CCFLAGS_XC) $(CXXFLAGS_XC) -MM $< $(DEFINES) $(INCLUDEPATH) -MT $(OBJ_PWD)/$(notdir $@) > $(OBJ_PWD)/$*.d

HEAP?=100

.PHONY : showmem

ifneq ($(LINKER_SCRIPT),)
    #LDFLAGS_XC += -Wl,--script,$(LINKER_SCRIPT)
    LDFLAGS_XC += -T$(LINKER_SCRIPT)
endif

# rule to link OBJECTS to an elf in OUT_PWD
ifeq ($(filter %.cpp,$(SRC)),)
# Pure C project, link with gcc interface
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	@printf "$(COMPCOLOR)µLD %-35s => %s\n$(NORM)" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OBJ_PWD)/,$(notdir $(OBJECTS))) $(LIBS) $(LDFLAGS) $(LDFLAGS_XC) -Wl,-Map="$(OUT_PWD)/$(PROJECT).map" 2> $(OUT_PWD)/linker.log || (cat $(OUT_PWD)/linker.log >&2; rm $(OUT_PWD)/linker.log; false)
	@rm $(OUT_PWD)/linker.log

# prints memory report
showmem : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OBJ_PWD)/,$(notdir $(OBJECTS))) $(LIBS) $(LDFLAGS) $(LDFLAGS_XC) -Wl,-Map="$(OUT_PWD)/$(PROJECT).map",--report-mem
else
# Mixed C / C++ project, link with g++ interface
$(OUT_PWD)/$(PROJECT).elf : $(OBJECTS)
	@printf "$(COMPCOLOR)µLD++ %-33s => %s\n$(NORM)" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CXX) $(CCFLAGS) $(CCFLAGS_XC) $(CXXFLAGS) $(CXXFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OBJ_PWD)/,$(notdir $(OBJECTS))) $(LIBS) $(LDFLAGS) $(LDFLAGS_XC) -Wl,-Map="$(OUT_PWD)/$(PROJECT).map" 2> $(OUT_PWD)/linker.log || (cat $(OUT_PWD)/linker.log >&2; rm $(OUT_PWD)/linker.log; false)
	@rm $(OUT_PWD)/linker.log

# prints memory report
showmem : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CXX) $(CCFLAGS) $(CCFLAGS_XC) $(CXXFLAGS) $(CXXFLAGS_XC) -o $(OUT_PWD)/$(PROJECT).elf $(addprefix $(OBJ_PWD)/,$(notdir $(OBJECTS))) $(LIBS) $(LDFLAGS) $(LDFLAGS_XC) -Wl,-Map="$(OUT_PWD)/$(PROJECT).map",--report-mem
endif

$(OUT_PWD)/$(PROJECT).s : $(OUT_PWD)/$(PROJECT).elf
	@printf "$(COMPCOLOR)objdump %-31s => %s\n$(NORM)" "$(OUT_PWD)/$(PROJECT).elf" $(OUT_PWD)/$(PROJECT).s
	$(VERB)$(OBJDUMP) -S -r $(OUT_PWD)/$(PROJECT).elf > $(OUT_PWD)/$(PROJECT).s

.PHONY : dbg.% dbg
# lists symbol present in final elf
dbg : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(OBJDUMP) -S $(OUT_PWD)/$(PROJECT).elf |grep "F .text" |sort -k6

# shows a disassembly listing of the symbol after the dot
dbg.% : $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(OBJDUMP) -S $(OUT_PWD)/$(PROJECT).elf |sed -n -e '/^[a-f0-9]\+ <_*$*>:/,/^[a-f0-9]\+ <_.*>:/ p'

vpath %.h $(OUT_PWD)
vpath %.c $(OUT_PWD)
