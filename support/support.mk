
# include robot definition file
include $(RTPROG)/support/robot/robot.mk

# include board definition file
include $(RTPROG)/support/board/board.mk

# check ARCHI variable exists, else auto detect from DEVICE
ifndef ARCHI
 ARCHI := $(shell echo $(DEVICE) |\
    sed -e 's/.*\(^32MZ\)[0-9]\+\([ED][CFA]\).*/pic\L\1\2/'\
    -e 's/.*\(^[23][42][MEF][PVJKMX]\).*/pic\L\1/'\
    -e 's/.*\(^3[03][EFC][PVJKH]*\).*/dspic\L\1/')
    ifeq ($(ARCHI),pic24fv)
        ARCHI := pic24f
    endif
endif

# include module definition file
include $(RTPROG)/support/module/module.mk

# include all drivers files
include $(RTPROG)/support/driver/driver.mk

# include all sys files
include $(RTPROG)/support/sys/sys.mk

# include archi definition file
include $(RTPROG)/support/archi/archi.mk

# include all simulator files
include $(RTPROG)/support/archi/simulator/simulator.mk

# generate list of used drivers modules
empty:=
space:= \n $(empty)
$(OUT_PWD)/modules.h : $(firstword $(MAKEFILE_LIST))
	@echo "$(YELLOW)generate module.h...$(NORM)"
	@test -d $(OUT_PWD) || mkdir -p $(OUT_PWD)
	@printf "\n// defines use of modules and drivers\n\
$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#define USE_$(DRIVER)\n))\n\
$(subst $(space),\n,$(foreach MODULE,$(sort $(MODULES)),#define USE_MODULE_$(MODULE)\n))\n\
// include all modules and drivers in project\n\
$(subst $(space),\n,$(foreach DRIVER,$(sort $(DRIVERS)),#include \"driver/$(DRIVER).h\"\n))\n\
$(subst $(space),\n,$(foreach MODULE,$(sort $(MODULES)),#include \"module/$(MODULE).h\"\n))\n\
" > $(OUT_PWD)/modules.h
