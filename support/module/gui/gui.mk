ifndef GUI_MODULE
GUI_MODULE=

vpath %.c $(MODULEPATH)
vpath %.c $(MODULEPATH)/screenController
vpath %.c $(OUT_PWD)

vpath %.h $(MODULEPATH)
vpath %.h $(MODULEPATH)/screenController

HEADER += gui.h
SRC += gui.c widget.c
SIM_SRC += gui_sim.c

########## SCREEN CONTROLER SUPPORT ##########

ARCHI_SRC += $(addsuffix .c, $(GUI_DRIVERS))
HEADER += $(addsuffix .h, $(GUI_DRIVERS))

$(OUT_PWD)/gui_driver.h : $(firstword $(MAKEFILE_LIST))
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@echo "$(YELLOW)generate gui_driver.h...$(NORM)"
	@printf "\n// defines use drivers screen\n\
$(subst $(space),\n,$(foreach GUI_DRIVER,$(sort $(GUI_DRIVERS)),#define USE_$(GUI_DRIVER)\n))\n\
" > $(OUT_PWD)/gui_driver.h
CONFIG_HEADERS += $(OUT_PWD)/gui_driver.h

######### EXTERNAL RESSOURCE SUPPORT #########
# IMG2RAW_EXE cmd
ifeq ($(OS),Windows_NT)
 IMG2RAW_EXE := $(RTPROG)/bin/img2raw.exe
else
 IMG2RAW_EXE := $(RTPROG)/bin/img2raw
endif
$(IMG2RAW_EXE): $(RTPROG)/tool/img2raw/img2raw.cpp $(RTPROG)/tool/img2raw/img2raw.pro
	@echo "Building img2raw..."
	cd $(RTPROG)/tool/img2raw/ && make

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30f dspic33fj dspic33ep dspic33ev))
 CCFLAGS_XC += -mlarge-code -mlarge-arrays -mlarge-data
endif

################ IMAGE SUPPORT ################
# rule to build image to OUT_PWD/*.c
$(OUT_PWD)/%.png.c : %.png $(OUT_PWD)/pictures.h $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(GREEN)IMG %-35s => %s$(NORM)\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.jpg.c : %.jpg $(OUT_PWD)/pictures.h $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(GREEN)IMG %-35s => %s$(NORM\n)" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.bmp.c : %.bmp $(OUT_PWD)/pictures.h $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(GREEN)IMG %-35s => %s$(NORM)\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i  $< -o  $(OUT_PWD)/$(notdir $@)

# rule to build images *.<img>.c to OUT_PWD/*.o
$(OUT_PWD)/%.o : $(OUT_PWD)/%.c
	@printf "$(GREEN)µCC %-35s => %s$(NORM)\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(CC) $(CCFLAGS) $(CCFLAGS_XC) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OUT_PWD)/$(notdir $@)

PICTURES_C := $(PICTURES)
PICTURES_NAME := $(PICTURES)
PICTURES_C := $(PICTURES_C:.jpg=.jpg.c)
PICTURES_NAME := $(PICTURES_NAME:.jpg=)
PICTURES_C := $(PICTURES_C:.png=.png.c)
PICTURES_NAME := $(PICTURES_NAME:.png=)
PICTURES_C := $(PICTURES_C:.bmp=.bmp.c)
PICTURES_NAME := $(PICTURES_NAME:.bmp=)
PICTURES_C := $(addprefix $(OUT_PWD)/, $(PICTURES_C))
SRC += $(PICTURES_C)

# generate list of used pictures
$(OUT_PWD)/pictures.h: $(firstword $(MAKEFILE_LIST))
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@echo "$(YELLOW)generate pictures.h...$(NORM)"
	@printf "#ifndef PICTURES_H\n#define PICTURES_H\n\n\
	#include <stdint.h>\n#include <gui/picture.h>\n\
	$(foreach PICTURE,$(PICTURES_NAME),\nextern const Picture $(PICTURE);)\n\n\
	#endif //PICTURES_H\
	" > $(OUT_PWD)/pictures.h
CONFIG_HEADERS += $(OUT_PWD)/pictures.h

################ FONT SUPPORT ################
FONTS_C := $(addprefix $(OUT_PWD)/, $(addsuffix .font.c, $(FONTS)))
SRC += $(FONTS_C)

$(OUT_PWD)/fonts.h: Makefile
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@echo "$(YELLOW)generate fonts.h...$(NORM)"
	@printf "#ifndef _FONTS_\n#define _FONTS_\n\n\
	#include <stdint.h>\n#include <gui/font.h>\n\
	$(foreach FONT,$(FONTS),\nextern const Font $(FONT);)\n\n\
	#endif //_FONTS_\
	" > $(OUT_PWD)/fonts.h
CONFIG_HEADERS += $(OUT_PWD)/fonts.h

#.PHONY : $(FONTS_C)
$(OUT_PWD)/%.font.o : $(OUT_PWD)/%.font.c
$(OUT_PWD)/%.font.c : $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "$(GREEN)IMG %-35s => %s$(NORM)\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i $* -o  $(OUT_PWD)/$(notdir $@)
	
.SECONDARY: $(PICTURES_C) $(FONTS_C)

endif
