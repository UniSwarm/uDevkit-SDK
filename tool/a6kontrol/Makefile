
all: ../../bin/a6kontrol

ifeq ($(OS),Windows_NT)
 TARGET_EXE := release
else
 TARGET_EXE := all
endif

../../build/a6kontrol/Makefile: a6kontrol.pro
	@test -d ../../build/a6kontrol/ || mkdir -p ../../build/a6kontrol/
	cd ../../build/a6kontrol && qmake ../../tool/a6kontrol/a6kontrol.pro

../../bin/a6kontrol: ../../build/a6kontrol/Makefile FORCE
	cd ../../build/a6kontrol && make $(TARGET_EXE)

FORCE:
