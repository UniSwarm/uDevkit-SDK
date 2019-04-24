
CC_SIM ?= gcc
CPPC_SIM ?= g++
OUT_SIM_PWD ?= simbuild

# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
  SIM_EXE := $(PROJECT).exe
  LIBS_SIM += -lws2_32
  RTSIM_EXE := $(UDEVKIT)/bin/rtsim.exe
else
  SIM_EXE := $(PROJECT)_sim
  LIBS_SIM += -pthread
  RTSIM_EXE := $(UDEVKIT)/bin/rtsim
endif

$(RTSIM_EXE): $(shell find $(UDEVKIT)/tool/rtsim/ \( -name '*.h' -o -name '*.c' -o -name '*.cpp' -o -name '*.pro' \))
	@echo "Building rtsim..."
	cd $(UDEVKIT)/tool/rtsim/ && make

SIMULATOR_PATH := $(UDEVKIT)/support/archi/simulator
DEFINES_SIM += -D SIMULATOR -I $(SIMULATOR_PATH) -g

vpath %.c $(SIMULATOR_PATH)
vpath %.cpp $(SIMULATOR_PATH)
vpath %.c $(OUT_PWD)
SIM_SRC += simulator.cpp simulator_socket.c simulator_pthread.c

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=_simo.o) $(patsubst %.cpp,%_simcppo.o,$(SIM_SRC:.c=_simo.o))))
$(SIM_OBJECTS) : $(CONFIG_HEADERS)

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%_simo.o : %.c
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(COMPCOLOR)CC %-36s => %s$(NORM)\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC_SIM) $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CC_SIM) $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*_sim.d
$(OUT_PWD)/%_simcppo.o : %.cpp
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(COMPCOLOR)CPPC %-34s => %s$(NORM)\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CPPC_SIM) $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@$(CPPC_SIM) $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*_simcpp.d

# rule to link SIM_OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "$(COMPCOLOR)LD %-36s => %s$(NORM)\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)$(CPPC_SIM) $(CCFLAGS) -o $(OUT_PWD)/$(SIM_EXE) $(addprefix $(OUT_PWD)/,$(notdir $(SIM_OBJECTS))) $(LIBS_SIM) $(DEFINES_SIM) -lm

sim-exe: $(OUT_PWD)/$(SIM_EXE)

sim : sim-exe $(RTSIM_EXE)
	#killall rtsim || true
	$(RTSIM_EXE) $(OUT_PWD)/$(SIM_EXE)

sim-clean :
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c
	rm -f $(OUT_PWD)/$(SIM_EXE)
