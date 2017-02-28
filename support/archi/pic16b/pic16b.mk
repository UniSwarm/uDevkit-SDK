
AS = xc16-as
CC = xc16-gcc
CCFLAGS += -Wall
CCFLAGS_XC += -no-legacy-libc
CCFLAGS_XC += -mcpu=$(DEVICE)
CCFLAGS_XC += -mno-eds-warn
LD = xc16-ld
AR = xc16-ar
HX = xc16-bin2hex
SIM = sim30

-include $(RTPROG)/support/archi/microchip/microchip.mk
