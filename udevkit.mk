MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
	MAKEFLAGS += -r
CONFIG_HEADERS = $(OUT_PWD)/modules.h

# variable that contain the root directory of uDevkit-SDK
UDEVKIT := $(dir $(lastword $(MAKEFILE_LIST)))

# set OUT_PWD and OBJ_PWD default values
OUT_PWD ?= build
OUT_PWD := $(strip $(OUT_PWD))
OBJ_PWD ?= $(OUT_PWD)/objs
OBJ_PWD := $(strip $(OBJ_PWD))

BLUE := $(shell command -v tput > /dev/null && tput setaf 4)
YELLOW := $(shell command -v tput > /dev/null && tput setaf 3)
GREEN := $(shell command -v tput > /dev/null && tput setaf 2)
NORM := $(shell command -v tput > /dev/null && tput sgr0)

ifndef SECONDARY
  COMPCOLOR ?= $(GREEN)
else
  COMPCOLOR ?= $(YELLOW)
endif

# VERBOSE variable to set the verbosity if VERBOSE=1
ifdef VERBOSE
  VERB :=
else
  VERB := @
endif

# include all support needed
include $(UDEVKIT)/support/support.mk

# include path set to the local project and uDevkit-SDK include path
INCLUDEPATH += -I. -I$(UDEVKIT)/include -I$(OUT_PWD)

# cleaning rule project
.PHONY: clean
clean:
	$(VERB)rm -f $(OBJ_PWD)/*.o $(OBJ_PWD)/*.d $(OBJ_PWD)/*.lst
	$(VERB)rm -f $(OUT_PWD)/*.c $(OUT_PWD)/*.h $(OUT_PWD)/*.s
	$(VERB)rm -f $(OUT_PWD)/*.map $(OUT_PWD)/$(PROJECT).elf $(OUT_PWD)/$(PROJECT).hex
	$(VERB)rm -f $(CONFIG_HEADERS)

.PHONY: distrib
DISTRIB_PWD = distrib
$(DISTRIB_PWD)/%.c : %.c
	@test -d $(DISTRIB_PWD) || mkdir -p $(DISTRIB_PWD)
	@printf "$(GREEN)cp %-35s => %s$(NORM)\n" $(notdir $<) $(DISTRIB_PWD)/$(notdir $@)
	$(VERB)cp $< $(DISTRIB_PWD)/$(notdir $@)
$(DISTRIB_PWD)/%.h : %.h
	@test -d $(DISTRIB_PWD) || mkdir -p $(DISTRIB_PWD)
	@printf "$(GREEN)cp %-35s => %s$(NORM)\n" $(notdir $<) $(DISTRIB_PWD)/$(notdir $@)
	$(VERB)cp $< $(DISTRIB_PWD)/$(notdir $@)
$(DISTRIB_PWD)/%.s : %.s
	@test -d $(DISTRIB_PWD) || mkdir -p $(DISTRIB_PWD)
	@printf "$(GREEN)cp %-35s => %s$(NORM)\n" $(notdir $<) $(DISTRIB_PWD)/$(notdir $@)
	$(VERB)cp $< $(DISTRIB_PWD)/$(notdir $@)
distrib: $(addprefix $(DISTRIB_PWD)/, $(notdir $(SRC)) $(notdir $(ARCHI_SRC)) $(notdir $(HEADER)))

info:
	@printf "$(GREEN)PROJECT:    $(NORM)%s %s %s\n" "$(PROJECT)" "$(OUT_PWD)/$(PROJECT).elf" "$(OUT_PWD)/$(PROJECT).hex"
	@printf "$(GREEN)DRIVERS:    $(NORM)%s\n" "$(DRIVERS)"
	@printf "\n"
	@printf "$(GREEN)BOARD:      $(NORM)%s version: %s\n" "$(BOARD)" "$(BOARD_VERSION)"
	@printf "$(GREEN)DEVICE:     $(NORM)%s\n" "$(DEVICE)"
	@printf "$(GREEN)ARCHI:      $(NORM)%s\n" "$(ARCHI)"
	@printf "$(GREEN)COMPILER:   $(NORM)%s\n" "$(shell whereis $(CC))"
	@printf "$(GREEN)DEV_PROG:   $(NORM)%s\n" "$(DEV_PROG)"
	@printf "\n"
	@printf "$(GREEN)SRC:        $(NORM)%s\n" "$(SRC)"
	@printf "$(GREEN)HEADER:     $(NORM)%s\n" "$(HEADER)"
	@printf "\n"
	@printf "$(GREEN)ARCHI_SRC:  $(NORM)%s\n" "$(ARCHI_SRC)"
	@printf "\n"
	@printf "$(GREEN)SIM_SRC:    $(NORM)%s\n" "$(SIM_SRC)"
	@printf "$(GREEN)SIM_HEADER: $(NORM)%s\n" "$(SIM_HEADER)"

.PHONY: rebuild
rebuild: clean hex

include $(MK_POST)
