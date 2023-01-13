
MAKE?=make

NPROC:=$(shell nproc || echo 2)

TESTS := $(sort $(dir $(wildcard */Makefile)))
TESTS := $(filter-out archtest, $(TESTS:/=))

TESTS_HEX = $(addsuffix -hex, $(TESTS))
TESTS_SIM = $(addsuffix -sim, $(TESTS))
TESTS_CLEAN = $(addsuffix -clean, $(TESTS))

all: $(TESTS_HEX)
	@echo $(TESTS)

sims: $(TESTS_SIM)
	@echo 

clean: $(TESTS_CLEAN)
	@echo 

%-sim:
	@echo
	@echo ===================== Building $* SIM : =======================
	cd $* && $(MAKE) -j$(NPROC) sim-exe
	@echo ==================== SIM Test passed ==========================
	@echo

%-clean:
	@echo
	@echo ===================== Cleaning $* : =======================
	cd $* && $(MAKE) clean
	@echo ==================== SIM Test passed ==========================
	@echo

%-hex:
	@echo
	@echo ======================= Building $* : =========================
	cd $* && $(MAKE) -j$(NPROC) hex
	@echo ======================== Test passed ==========================
	@echo

FORCE:
	
