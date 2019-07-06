
MAKE?=make

NPROC:=$(shell nproc || echo 2)
TOOL_NAME := udk-sim

ifeq ($(OS),Windows_NT)
 TARGET_EXE := release
 TARGET_NAME := $(TOOL_NAME)
 TOOL_DEPLOY := cd ../../bin/ && windeployqt.exe .
else
 TARGET_EXE := all
 TARGET_NAME := $(TOOL_NAME).exe
 TOOL_DEPLOY := 
endif

all: ../../bin/$(TARGET_NAME)

../../build/$(TOOL_NAME)/Makefile:
	@test -d ../../build/$(TOOL_NAME)/ || mkdir -p ../../build/$(TOOL_NAME)/
	cd ../../build/$(TOOL_NAME) && qmake ../../tool/$(TOOL_NAME)/$(TOOL_NAME).pro

../../bin/$(TARGET_NAME): ../../build/$(TOOL_NAME)/Makefile FORCE
	cd ../../build/$(TOOL_NAME) && $(MAKE) $(TARGET_EXE) -j$(NPROC)
	$(TOOL_DEPLOY)

FORCE:
