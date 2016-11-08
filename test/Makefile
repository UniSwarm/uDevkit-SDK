
TESTS = $(sort $(dir $(wildcard */Makefile)))

all: $(TESTS)

%/: FORCE
	@echo
	@echo ======================= Building $@ : ========================
	cd $@ && make clean && make -j9 all
	@echo ======================== Test passed ==========================
	@echo

FORCE:
