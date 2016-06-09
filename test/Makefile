
TESTS = $(sort $(dir $(wildcard */Makefile)))

all: $(TESTS)

%/: FORCE
	@echo
	@echo ======================= Building $@ : ========================
	cd $@ && make clean all
	@echo ======================== Test pased ==========================
	@echo

FORCE:
