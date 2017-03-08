
AS = xc32-as
CC = xc32-gcc
LD = xc32-ld
AR = xc32-ar
HX = xc32-bin2hex
SIM = sim32
OBJDUMP = xc32-objdump

CCFLAGS += -Wall
CCFLAGS_XC += -no-legacy-libc
CCFLAGS_XC += -mprocessor=$(DEVICE)

-include $(RTPROG)/support/archi/microchip/microchip.mk
