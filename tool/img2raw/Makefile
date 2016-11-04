
NPROC:=$(shell nproc || echo 2)
TOOL_NAME := img2raw

ifeq ($(OS),Windows_NT)
 TARGET_EXE := release
 TARGET_NAME := $(TOOL_NAME)
else
 TARGET_EXE := all
 TARGET_NAME := $(TOOL_NAME).exe
endif

all: ../../bin/$(TARGET_NAME)

../../build/$(TOOL_NAME)/Makefile:
	@test -d ../../build/$(TOOL_NAME)/ || mkdir -p ../../build/$(TOOL_NAME)/
	cd ../../build/$(TOOL_NAME) && qmake ../../tool/$(TOOL_NAME)/$(TOOL_NAME).pro

../../bin/$(TARGET_NAME): ../../build/$(TOOL_NAME)/Makefile FORCE
	cd ../../build/$(TOOL_NAME) && make $(TARGET_EXE) -j$(NPROC)

FORCE:
