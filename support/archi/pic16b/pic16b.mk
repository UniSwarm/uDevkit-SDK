
AS = xc16-as
CC = xc16-gcc
LD = xc16-ld
AR = xc16-ar
HX = xc16-bin2hex
SIM = sim30
OBJDUMP = xc16-objdump

ifeq ("$(CC)","xc16-gcc") # XC16 compiler used
 CCFLAGS_XC += -no-legacy-libc
 CCFLAGS_XC += -mcpu=$(DEVICE)
 CCFLAGS_XC += -mno-eds-warn
 LDFLAGS_XC += -Wl,--heap=$(HEAP),-Tp$(DEVICE).gld
 CCFLAGS += -Wall

else                      # other compiler used
 XC16_PATH = $(abspath $(dir $(lastword $(shell whereis -b xc16-gcc)))..)/
 DEFPROC := $(shell echo $(DEVICE) |\
    sed -e 's/.*\(^[23][42][MEF].*\).*/PIC\1/'\
    -e 's/.*\(^3[03][EF][PVJ]*.*\).*/dsPIC\1/')
$(warning $(DEFPROC))
 CCFLAGS += -D_HOSTED -D__$(DEFPROC)__ -D__XC16__ -D__prog__
 CCFLAGS += -Wno-attributes -Wno-unknown-pragmas
 CCFLAGS += -I$(XC16_PATH)include/ -I$(XC16_PATH)support/generic/h/
 CCFLAGS += -I$(XC16_PATH)support/dsPIC30F/h/ -I$(XC16_PATH)support/dsPIC33E/h/ -I$(XC16_PATH)support/dsPIC33F/h/ -I$(XC16_PATH)support/PIC24E/h/ -I$(XC16_PATH)support/PIC24F/h/ -I$(XC16_PATH)support/PIC24H/h/
 
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
  CCFLAGS += -D__dsPIC30F__
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj))
  CCFLAGS += -D__PIC24F__
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep))
  CCFLAGS += -D__PIC24E__
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33fj))
  CCFLAGS += -D__dsPIC33F__
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33ev))
  CCFLAGS += -D__dsPIC33E__
 endif
 CCFLAGS += -Wno-all
 OUT_PWD := $(OUT_PWD)_$(notdir $(CC))
endif

# debug flags for MPLAB X, experimental
#
#LDFLAGS_XC += -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F
#LDFLAGS_XC += -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem
#
#CCFLAGS += -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -msfr-warn=off
#

-include $(RTPROG)/support/archi/microchip/microchip.mk
