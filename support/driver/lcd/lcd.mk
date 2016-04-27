ifndef LCD_DRIVER
LCD_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += lcd.h
SRC += lcd.c

CCFLAGS += -mlarge-code -mlarge-arrays -mlarge-data

# rule to build image to OUT_PWD/*.c
$(OUT_PWD)/%.png.c : %.png pictures.h
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	$(RTPROG)/bin/img2raw -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.jpg.c : %.jpg pictures.h
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	$(RTPROG)/bin/img2raw -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.bmp.c : %.bmp pictures.h
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	$(RTPROG)/bin/img2raw -i  $< -o  $(OUT_PWD)/$(notdir $@)

# rule to build images *.<img>.c to OUT_PWD/*.o
$(OUT_PWD)/%.o : $(OUT_PWD)/%.c
	$(CC) $(CCFLAGS) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OUT_PWD)/$(notdir $@)

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
pictures.h: Makefile
	@echo "generate pictures.h..."
	@printf "#include <stdint.h>\n$(foreach PICTURE,$(PICTURES_NAME),extern __prog__ const uint16_t $(PICTURE)[] __attribute__((space(prog)));\n)" > pictures.h

$(OUT_PWD)/%.o : pictures.h

.SECONDARY: $(PICTURES_C)

endif
