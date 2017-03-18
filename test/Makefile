
MAKE?=make

TESTS = $(sort $(dir $(wildcard */Makefile)))

all: $(TESTS)

%/: FORCE
	@echo
	@echo ======================= Building $@ : ========================
	cd $@ && $(MAKE) clean && $(MAKE) -j9 all
	@echo ======================== Test passed ==========================
	@echo

FORCE:
