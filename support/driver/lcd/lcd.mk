ifndef LCD_DRIVER
LCD_DRIVER=

vpath %.c $(DRIVERPATH)

HEADER += lcd.h
SRC += lcd.c

CCFLAGS += -mlarge-code -mlarge-arrays -mlarge-data

# rule to build image to OUT_PWD/*.c
$(OUT_PWD)/%.png.c : %.png
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	$(RTPROG)/bin/img2raw -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.jpg.c : %.jpg
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	$(RTPROG)/bin/img2raw -i  $< -o  $(OUT_PWD)/$(notdir $@)
$(OUT_PWD)/%.bmp.c : %.bmp
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	$(RTPROG)/bin/img2raw -i  $< -o  $(OUT_PWD)/$(notdir $@)

# rule to build images *.<img>.c to OUT_PWD/*.o
$(OUT_PWD)/%.o : $(OUT_PWD)/%.c
	$(CC) $(CCFLAGS) -c $< $(DEFINES) $(INCLUDEPATH) -o $(OUT_PWD)/$(notdir $@)

PICTURES_C := $(PICTURES)
PICTURES_C := $(PICTURES_C:.jpg=.jpg.c)
PICTURES_C := $(PICTURES_C:.png=.png.c)
PICTURES_C := $(PICTURES_C:.bmp=.bmp.c)
PICTURES_C := $(addprefix $(OUT_PWD)/, $(PICTURES_C))
SRC += $(PICTURES_C)

.SECONDARY: $(PICTURES_C)

endif
