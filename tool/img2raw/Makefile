
all: ../../bin/img2raw

../../build/img2raw/Makefile:
	@test -d ../../build/img2raw/ || mkdir -p ../../build/img2raw/
	cd ../../build/img2raw && qmake ../../tool/img2raw/img2raw.pro

../../bin/img2raw: ../../build/img2raw/Makefile
	cd ../../build/img2raw && make release