ifndef GUI_MODULE
GUI_MODULE=

vpath %.c $(MODULEPATH)
vpath %.c $(MODULEPATH)/screenController

HEADER += gui.h
SRC += gui.c widget.c
ARCHI_SRC += screenController/d51e5ta7601.c
SIM_SRC += gui_sim.c

ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24ep pic24hj dspic30 dspic33fj dspic33ep dspic33ev))
 CCFLAGS_XC += -mlarge-code -mlarge-arrays -mlarge-data
endif

# IMG2RAW_EXE cmd
ifeq ($(OS),Windows_NT)
 IMG2RAW_EXE := $(RTPROG)/bin/img2raw.exe
else
 IMG2RAW_EXE := $(RTPROG)/bin/img2raw
endif
$(IMG2RAW_EXE): $(RTPROG)/tool/img2raw/img2raw.cpp $(RTPROG)/tool/img2raw/img2raw.pro
	@echo "Building img2raw..."
	cd $(RTPROG)/tool/img2raw/ && make

################ IMAGE SUPPORT ################
# rule to build image to OUT_PWD/*.c
$(OUT_PWD)/%.png.c : %.png pictures.h $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "IMG %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.jpg.c : %.jpg pictures.h $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "IMG %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.bmp.c : %.bmp pictures.h $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "IMG %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i  $< -o  $(OUT_PWD)/$(notdir $@)

# rule to build images *.<img>.c to OUT_PWD/*.o
$(OUT_PWD)/%.o : $(OUT_PWD)/%.c
	@printf "µCC %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
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
main.c: pictures.h
pictures.h: Makefile
	@echo "generate pictures.h..."
	@printf "#ifndef _PICTURES_\n#define _PICTURES_\n\n\
	#include <stdint.h>\n#include <gui/picture.h>\n\
	$(foreach PICTURE,$(PICTURES_NAME),\nextern const Picture $(PICTURE);)\n\n\
	#endif //_PICTURES_\
	" > pictures.h

$(OUT_PWD)/%.o : pictures.h

################ FONT SUPPORT ################
FONTS_C := $(addprefix $(OUT_PWD)/, $(addsuffix .font.c, $(FONTS)))
SRC += $(FONTS_C)

main.c: fonts.h
fonts.h: Makefile
	@echo "generate fonts.h..."
	@printf "#ifndef _FONTS_\n#define _FONTS_\n\n\
	#include <stdint.h>\n#include <gui/font.h>\n\
	$(foreach FONT,$(FONTS),\nextern const Font $(FONT);)\n\n\
	#endif //_FONTS_\
	" > fonts.h

#.PHONY : $(FONTS_C)
$(OUT_PWD)/%.font.o : $(OUT_PWD)/%.font.c
$(OUT_PWD)/%.font.c : $(IMG2RAW_EXE)
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "IMG %-35s => %s\n" $(notdir $<) $(OUT_PWD)/$(notdir $@)
	$(VERB)$(IMG2RAW_EXE) -i $* -o  $(OUT_PWD)/$(notdir $@)
	
.SECONDARY: $(PICTURES_C) $(FONTS_C)

endif
