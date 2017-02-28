
AS = xc32-as
CC = xc32-gcc
CCFLAGS += -Wall
CCFLAGS_XC += -no-legacy-libc
CCFLAGS_XC += -mprocessor=$(DEVICE)
LD = xc32-ld
AR = xc32-ar
HX = xc32-bin2hex
SIM = sim32

-include $(RTPROG)/support/archi/microchip/microchip.mk
