
# include robot definition file
include $(RTPROG)/support/robot/robot.mk

# include board definition file
include $(RTPROG)/support/board/board.mk

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
