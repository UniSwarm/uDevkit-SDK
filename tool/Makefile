
MAKE?=make

TOOLS = $(sort $(dir $(wildcard */Makefile)))

all: $(TOOLS)

%/: FORCE
	@echo
	@echo ======================= Building $@ : ========================
	cd $@ && $(MAKE) all
	@echo ======================== Tool built ==========================
	@echo

FORCE:
