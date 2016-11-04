
# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
 SIM_EXE := $(PROJECT).exe
else
 SIM_EXE := $(PROJECT)
endif

SIMULATOR_PATH := $(RTPROG)/support/archi/simulator
DEFINES_SIM := -D SIMULATOR -I $(SIMULATOR_PATH)

vpath %.c $(SIMULATOR_PATH)
SIM_SRC += simulator.c simulator_socket.c

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=_sim.o) $(SIM_SRC:.c=_sim.o)))

# QT_BASE_INCLUDES = $(shell qmake -query QT_INSTALL_HEADERS)
# SIM_INCLUDES := -I$(QT_BASE_INCLUDES) -I$(QT_BASE_INCLUDES)/QtCore -I$(QT_BASE_INCLUDES)/QtGui -I$(QT_BASE_INCLUDES)/QtWidgets

# SIM_LIBS = -L$(shell qmake -query QT_INSTALL_LIBEXECS) -lQt5Core -lQt5Gui -lQt5Widgets

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%_sim.o : %.c
	@printf "CC %-36s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)gcc $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)
	@gcc $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*_sim.d

# rule to link SIM_OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "LD %-36s => %s\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	@gcc $(CCFLAGS) -o $(OUT_PWD)/$(SIM_EXE) $(addprefix $(OUT_PWD)/,$(notdir $(SIM_OBJECTS))) -lm

sim : $(OUT_PWD)/$(SIM_EXE)
	./$(OUT_PWD)/$(SIM_EXE)
