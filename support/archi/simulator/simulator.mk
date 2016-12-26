
CC_SIM ?= gcc
CPPC_SIM ?= g++
OUT_SIM_PWD ?= simbuild

# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
  SIM_EXE := $(PROJECT).exe
  LIBS_SIM += -lws2_32
  RTSIM_EXE := $(RTPROG)/bin/rtsim.exe
else
  SIM_EXE := $(PROJECT)_sim
  LIBS_SIM += -pthread
  RTSIM_EXE := $(RTPROG)/bin/rtsim
endif

$(RTSIM_EXE): $(shell find $(RTPROG)/tool/rtsim/ \( -name '*.h' -o -name '*.c' -o -name '*.pro' \))
	@echo "Building rtsim..."
	cd $(RTPROG)/tool/rtsim/ && make

SIMULATOR_PATH := $(RTPROG)/support/archi/simulator
DEFINES_SIM += -D SIMULATOR -I $(SIMULATOR_PATH)

vpath %.c $(SIMULATOR_PATH)
vpath %.cpp $(SIMULATOR_PATH)
vpath %.c $(OUT_SIM_PWD)
SIM_SRC += simulator.cpp simulator_socket.c simulator_pthread.c

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_SIM_PWD)/, $(notdir $(SRC:.c=.o) $(patsubst %.cpp,%_simcppo.o,$(SIM_SRC:.c=.o))))

# rule to build OBJECTS to OUT_SIM_PWD and give dependencies
$(OUT_SIM_PWD)/%.o : %.c
	@test -d $(OUT_SIM_PWD) || mkdir -p $(OUT_SIM_PWD)
	@printf "CC %-36s => %s\n" $(notdir $<) $(OUT_SIM_PWD)/$(notdir $@)
	$(VERB)$(CC_SIM) $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_SIM_PWD)/$(notdir $@)
	@$(CC_SIM) $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_SIM_PWD)/$(notdir $@) > $(OUT_SIM_PWD)/$*_sim.d
$(OUT_SIM_PWD)/%_simcppo.o : %.cpp
	@test -d $(OUT_SIM_PWD) || mkdir -p $(OUT_SIM_PWD)
	@printf "CPPC %-34s => %s\n" $(notdir $<) $(OUT_SIM_PWD)/$(notdir $@)
	$(VERB)$(CPPC_SIM) $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_SIM_PWD)/$(notdir $@)
	@$(CPPC_SIM) $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_SIM_PWD)/$(notdir $@) > $(OUT_SIM_PWD)/$*_simcpp.d

# rule to link SIM_OBJECTS to an elf in OUT_SIM_PWD
$(OUT_SIM_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "LD %-36s => %s\n" "*.o" $(OUT_SIM_PWD)/$(PROJECT).elf
	$(VERB)$(CPPC_SIM) $(CCFLAGS) -o $(OUT_SIM_PWD)/$(SIM_EXE) $(addprefix $(OUT_SIM_PWD)/,$(notdir $(SIM_OBJECTS))) $(LIBS_SIM) $(DEFINES_SIM) -lm

sim : $(OUT_SIM_PWD)/$(SIM_EXE) $(RTSIM_EXE)
	killall rtsim || true
	$(RTSIM_EXE) &
	sleep 1 && ./$(OUT_SIM_PWD)/$(SIM_EXE)
