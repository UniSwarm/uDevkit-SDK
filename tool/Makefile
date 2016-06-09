
TOOLS = $(sort $(dir $(wildcard */Makefile)))

all: $(TOOLS)

%/: FORCE
	@echo
	@echo ======================= Building $@ : ========================
	cd $@ && make all
	@echo ======================== Tool built ==========================
	@echo

FORCE:
