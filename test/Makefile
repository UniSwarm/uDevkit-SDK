
TESTS = $(sort $(dir $(wildcard */Makefile)))

all: $(TESTS)

%/: FORCE
	@echo
	@echo ======================= Building $@ : ========================
	cd $@ && make clean
	cd $@ && make -j9 all
	@echo ======================== Test pased ==========================
	@echo

FORCE:
