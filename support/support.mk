
# include robot definition file
include $(RTPROG)/support/robot/robot.mk

# include board definition file
include $(RTPROG)/support/board/board.mk

# check ARCHI variable exists, else auto detect from DEVICE
ifndef ARCHI
 ARCHI := $(shell echo $(DEVICE) |\
    sed -e 's/.*\(^32MZ\)[0-9]\+\([ED][CFA]\).*/pic\L\1\2/'\
    -e 's/.*\(^[23][42][MEF][PVJKMX]\).*/pic\L\1/'\
    -e 's/.*\(^3[03][EF][PVJ]*\).*/dspic\L\1/')
 $(warning $(DEVICE) $(ARCHI))
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
