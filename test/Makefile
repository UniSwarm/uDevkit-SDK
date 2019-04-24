
MAKE?=make

TESTS := $(sort $(dir $(wildcard */Makefile)))
TESTS := $(TESTS:/=)
TESTSSIMS = $(filter-out archtest-sim, $(addsuffix -sim, $(TESTS)))

all: $(TESTS)
	@echo 

sims: $(TESTSSIMS)
	@echo 

%-sim:
	@echo
	@echo ===================== Building $@ SIM : =======================
	cd $* && $(MAKE) -j9 sim-exe
	@echo ==================== SIM Test passed ==========================
	@echo

%:
	@echo
	@echo ======================= Building $@ : =========================
	cd $@ && $(MAKE) -j9 all
	@echo ======================== Test passed ==========================
	@echo
