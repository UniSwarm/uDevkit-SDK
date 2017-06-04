
AS = xc16-as
CC = xc16-gcc
LD = xc16-ld
LDFLAGS_XC += -Wl,--heap=$(HEAP),-Tp$(DEVICE).gld
AR = xc16-ar
HX = xc16-bin2hex
SIM = sim30
OBJDUMP = xc16-objdump

CCFLAGS += -Wall
CCFLAGS_XC += -no-legacy-libc
CCFLAGS_XC += -mcpu=$(DEVICE)
CCFLAGS_XC += -mno-eds-warn

# debug flags for MPLAB X, experimental
#
#LDFLAGS_XC += -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F
#LDFLAGS_XC += -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem
#
#CCFLAGS += -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -msfr-warn=off
#

-include $(RTPROG)/support/archi/microchip/microchip.mk
