
# SIM_EXE cmd
ifeq ($(OS),Windows_NT)
 SIM_EXE := $(PROJECT).exe
else
 SIM_EXE := $(PROJECT)
endif

# simulator support
SIM_OBJECTS := $(addprefix $(OUT_PWD)/, $(notdir $(SRC:.c=_sim.o) $(SIM_SRC:.c=_sim.o)))
-include $(SIM_OBJECTS:.o=.d)

QT_BASE_INCLUDES = $(shell qmake -query QT_INSTALL_HEADERS)
SIM_INCLUDES := -I$(QT_BASE_INCLUDES) -I$(QT_BASE_INCLUDES)/QtCore -I$(QT_BASE_INCLUDES)/QtGui -I$(QT_BASE_INCLUDES)/QtWidgets

SIM_LIBS = -L$(shell qmake -query QT_INSTALL_LIBEXECS) -lQt5Core -lQt5Gui -lQt5Widgets

$(OUT_PWD)/%_sim.o : %.c modules.h
	@printf "CC %-30s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	g++ $(CCFLAGS) -c  $< $(DEFINES) $(INCLUDEPATH) $(SIM_INCLUDES) -o  $(OUT_PWD)/$(notdir $@)
	g++ $(CCFLAGS) -MM $< $(DEFINES) $(INCLUDEPATH) $(SIM_INCLUDES) -MT $(OUT_PWD)/$(notdir $@) > $(OUT_PWD)/$*.d

# rule to link SIM_OBJECTS to an elf in OUT_PWD
$(OUT_PWD)/$(SIM_EXE) : $(SIM_OBJECTS)
	@printf "LD %-30s => %s\n" "*.o" $(OUT_PWD)/$(PROJECT).elf
	g++ $(CCFLAGS) -o $(OUT_PWD)/$(SIM_EXE) $(addprefix $(OUT_PWD)/,$(notdir $(SIM_OBJECTS))) $(SIM_LIBS)

sim : $(OUT_PWD)/$(SIM_EXE)
	echo $(SIM_INCLUDES)
	./$(OUT_PWD)/$(SIM_EXE)
