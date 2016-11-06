
# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
  SIM_EXE := $(PROJECT).exe
  DEFINES_SIM += -lws2_32
  RTSIM_EXE := $(RTPROG)/bin/rtsim.exe
else
  SIM_EXE := $(PROJECT)_sim
  RTSIM_EXE := $(RTPROG)/bin/rtsim
endif

$(RTSIM_EXE): $(shell find $(RTPROG)/tool/rtsim/ \( -name '*.h' -o -name '*.c' -o -name '*.pro' \))
	@echo "Building rtsim..."
	cd $(RTPROG)/tool/rtsim/ && make

SIMULATOR_PATH := $(RTPROG)/support/archi/simulator
DEFINES_SIM += -D SIMULATOR -I $(SIMULATOR_PATH)

vpath %.c $(SIMULATOR_PATH)
vpath %.c $(OUT_PWD)
SIM_SRC += simulator.c simulator_socket.c

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=_simo.o) $(SIM_SRC:.c=_simo.o)))

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%_simo.o : %.c
	@printf "CC %-36s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)gcc $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@gcc $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*_sim.d

# rule to link SIM_OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "LD %-36s => %s\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	$(VERB)gcc $(CCFLAGS) -o $(OUT_PWD)/$(SIM_EXE) $(addprefix $(OUT_PWD)/,$(notdir $(SIM_OBJECTS))) $(DEFINES_SIM) -lm

sim : $(OUT_PWD)/$(SIM_EXE) $(RTSIM_EXE)
	$(RTSIM_EXE) &
	sleep 1 && ./$(OUT_PWD)/$(SIM_EXE)
