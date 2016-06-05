
AS = xc16-as
CC = xc16-gcc
CCFLAGS = -mcpu=$(DEVICE) -Wall
LD = xc16-ld
AR = xc16-ar
HX = xc16-bin2hex
SIM = sim30

-include $(RTPROG)/support/archi/microchip/microchip.mk