
# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
 SIM_EXE := $(PROJECT).exe
else
 SIM_EXE := $(PROJECT)
endif

DEFINES_SIM := -D SIMULATOR

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=_sim.o) $(SIM_SRC:.c=_sim.o)))

# QT_BASE_INCLUDES = $(shell qmake -query QT_INSTALL_HEADERS)
# SIM_INCLUDES := -I$(QT_BASE_INCLUDES) -I$(QT_BASE_INCLUDES)/QtCore -I$(QT_BASE_INCLUDES)/QtGui -I$(QT_BASE_INCLUDES)/QtWidgets

# SIM_LIBS = -L$(shell qmake -query QT_INSTALL_LIBEXECS) -lQt5Core -lQt5Gui -lQt5Widgets

# rule to build OBJECTS to OUT_PWD and give dependencies
$(OUT_PWD)/%_sim.d : %.c
	@test -e modules.h || touch -t 197001010101 modules.h
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@gcc $(CCFLAGS) -MM $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*_sim.d

$(OUT_PWD)/%_sim.o : %.c $(OUT_PWD)/%_sim.d
	@printf "CC %-31s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	@gcc $(CCFLAGS) -c  $< $(DEFINES) $(DEFINES_SIM) $(INCLUDEPATH) -o  $(OUT_PWD)/$(notdir $@)

# rule to link SIM_OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "LD %-30s => %s\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	@gcc $(CCFLAGS) -o $(OUT_PWD)/$(SIM_EXE) $(addprefix $(OUT_PWD)/,$(notdir $(SIM_OBJECTS)))

sim : $(OUT_PWD)/$(SIM_EXE)
	./$(OUT_PWD)/$(SIM_EXE)
