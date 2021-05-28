MAKEFLAGS += --no-builtin-rules
.SUFFIXES:
	MAKEFLAGS += -r
CONFIG_HEADERS = $(OUT_PWD)/modules.h

# variable that contain the root directory of uDevkit-SDK
UDEVKIT := $(dir $(lastword $(MAKEFILE_LIST)))

# if OUT_PWD undefined, OUT_PWD is forced to build/ sub directory
ifndef OUT_PWD
  OUT_PWD = build
endif
OUT_PWD := $(strip $(OUT_PWD))

YELLOW := $(shell command -v tput > /dev/null && tput setaf 3)
GREEN := $(shell command -v tput > /dev/null && tput setaf 2)
NORM := $(shell command -v tput > /dev/null && tput sgr0)

ifndef SLAVE
  COMPCOLOR := $(GREEN)
else
  COMPCOLOR := $(YELLOW)
endif

# VERBOSE variable to set the verbosity if VERBOSE=1
ifdef VERBOSE
  VERB :=
else
  VERB := @
endif

# make all as default rule
all:

# uncomment this line when all C includes will be in uDevkit-SDK
# CCFLAGS += -nostdinc

# include all support needed
include $(UDEVKIT)/support/support.mk

# include path set to the local project and uDevkit-SDK include path
INCLUDEPATH += -I. -I$(UDEVKIT)/include -I$(OUT_PWD)

# cleaning rule project
.PHONY: clean
clean:
	rm -f $(OUT_PWD)/*.o $(OUT_PWD)/*.d $(OUT_PWD)/*.c $(OUT_PWD)/*.h $(OUT_PWD)/*.s $(OUT_PWD)/*.lst $(OUT_PWD)/*.map
	rm -f $(OUT_PWD)/$(PROJECT).elf $(OUT_PWD)/$(PROJECT).hex
	rm -f $(CONFIG_HEADERS)

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

.PHONY: rebuild
rebuild: clean hex

include $(MK_POST)
