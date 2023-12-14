CC_SIM ?= $(CROSS_COMPILE)gcc
CPPC_SIM ?= $(CROSS_COMPILE)g++
ifeq ($(CROSS_COMPILE),)
  OUT_SIM_PWD ?= build-sim
else
  OUT_SIM_PWD ?= build-sim-$(CROSS_COMPILE:-=)
endif

# SIM_EXE cmd
LIBS_SIM += -lm
ifeq ($(OS),Windows_NT)
  ifeq ($(CROSS_COMPILE),)
    SIM_EXE := $(PROJECT)_sim.exe
  else
    SIM_EXE := $(PROJECT)_sim-$(CROSS_COMPILE:-=).exe
  endif
  LIBS_SIM += -lws2_32
  UDKSIM_EXE := $(UDEVKIT)/bin/udk-sim.exe
else
  ifeq ($(CROSS_COMPILE),)
    SIM_EXE := $(PROJECT)_sim
  else
    SIM_EXE := $(PROJECT)_sim-$(CROSS_COMPILE:-=)
  endif
  LIBS_SIM += -pthread
  UDKSIM_EXE := $(UDEVKIT)/bin/udk-sim
endif

$(UDKSIM_EXE): $(shell find $(UDEVKIT)/tool/udk-sim/ \( -name '*.h' -o -name '*.c' -o -name '*.cpp' -o -name '*.pro' \))
	@echo "Building udk-sim..."
	cd $(UDEVKIT)/tool/udk-sim/ && make

SIMULATOR_PATH := $(UDEVKIT)/support/archi/simulator
DEFINES_SIM += -D SIMULATOR -I $(SIMULATOR_PATH)

vpath %.h $(SIMULATOR_PATH)
vpath %.c $(SIMULATOR_PATH)
vpath %.cpp $(SIMULATOR_PATH)
SIM_SRC += simulator.cpp simulator_socket.c simulator_pthread.c
SIM_HEADER += simulator.h simulator_socket.h simulator_pthread.h

vpath %.h $(OUT_SIM_PWD)
vpath %.c $(OUT_SIM_PWD)
INCLUDEPATH += -I$(OUT_SIM_PWD)

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_SIM_PWD)/, $(notdir $(SRC:.c=.o) $(patsubst %.cpp,%.o,$(SIM_SRC:.c=.o))))
-include $(wildcard $(OUT_SIM_PWD)/*.d)
$(SIM_OBJECTS) : $(CONFIG_HEADERS)

# rule to build OBJECTS to OUT_SIM_PWD and give dependencies
$(OUT_SIM_PWD)/%.o : %.c
	@test -d $(OUT_SIM_PWD) || mkdir -p $(OUT_SIM_PWD)
	@printf "$(COMPCOLOR)CC %-36s => %s$(NORM)\n" $(notdir $<) $(OUT_SIM_PWD)/$(notdir $@)
	$(VERB)$(CC_SIM) $(CCFLAGS) -c $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o $(OUT_SIM_PWD)/$(notdir $@)
	@$(CC_SIM) $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_SIM_PWD)/$(notdir $@) > $(OUT_SIM_PWD)/$*.d
$(OUT_SIM_PWD)/%.o : %.cpp
	@test -d $(OUT_SIM_PWD) || mkdir -p $(OUT_SIM_PWD)
	@printf "$(COMPCOLOR)CPPC %-34s => %s$(NORM)\n" $(notdir $<) $(OUT_SIM_PWD)/$(notdir $@)
	$(VERB)$(CPPC_SIM) $(CCFLAGS) -c $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o $(OUT_SIM_PWD)/$(notdir $@)
	@$(CPPC_SIM) $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_SIM_PWD)/$(notdir $@) > $(OUT_SIM_PWD)/$*.d

# rule to link SIM_OBJECTS to an elf in OUT_SIM_PWD
$(OUT_SIM_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "$(COMPCOLOR)LD %-36s => %s$(NORM)\n" "*.o" $(OUT_SIM_PWD)/$(SIM_EXE)
	$(VERB)$(CPPC_SIM) $(CCFLAGS) -o $(OUT_SIM_PWD)/$(SIM_EXE) $(addprefix $(OUT_SIM_PWD)/,$(notdir $(SIM_OBJECTS))) $(LIBS_SIM) $(DEFINES_SIM)

sim-exe: $(OUT_SIM_PWD)/$(SIM_EXE)

sim: sim-exe $(UDKSIM_EXE)
	#killall udk-sim || true
	$(UDKSIM_EXE) $(OUT_SIM_PWD)/$(SIM_EXE) $(SIM_ARGS)

clean: sim-clean
sim-clean :
	$(VERB)rm -f $(OUT_SIM_PWD)*/*.o $(OUT_SIM_PWD)*/*.d $(OUT_SIM_PWD)*/*.c
	$(VERB)rm -f $(OUT_SIM_PWD)*/$(SIM_EXE)*
