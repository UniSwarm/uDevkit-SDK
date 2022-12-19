
AS = xc16-as
CC = xc16-gcc
LD = xc16-ld
AR = xc16-ar
HX = xc16-bin2hex
SIM = sim30
OBJDUMP = xc16-objdump

CC_VERSION := $(shell $(CC) --version | egrep -o "v([0-9]+\\.[0-9]+)")
CC_VERSION_MAJOR := $(shell echo $(CC_VERSION) | cut -f2 -dv | cut -f1 -d.)
CC_VERSION_MINOR := $(shell echo $(CC_VERSION) | cut -f2 -d.)

#$(info $(CC_VERSION) $(CC_VERSION_MAJOR))

XC16_PATH = $(abspath $(dir $(lastword $(shell whereis -b xc16-gcc)))..)/
ifeq ("$(LK_SCRIPT)","")
 LK_SCRIPT = p$(DEVICE).gld
endif

ifeq ("$(CC)","xc16-gcc") # XC16 compiler used
 ifeq ("$(CC_VERSION_MAJOR)","1")
  CCFLAGS_XC += -no-legacy-libc
 endif
 CCFLAGS_XC += -mcpu=$(DEVICE)
 CCFLAGS_XC += -mno-eds-warn
 CCFLAGS_XC += -std=c99
 LDFLAGS_XC += -Wl,--heap=$(HEAP),-T$(LK_SCRIPT)
 CCFLAGS += -Wall

 ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
  LDFLAGS_XC += -Wl,-L$(XC16_PATH)support/dsPIC30F/gld/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj))
  LDFLAGS_XC += -Wl,-L$(XC16_PATH)support/PIC24F/gld/ -Wl,-L$(XC16_PATH)support/PIC24H/gld/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep))
  LDFLAGS_XC += -Wl,-L$(XC16_PATH)support/PIC24E/gld/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33fj))
  LDFLAGS_XC += -Wl,-L$(XC16_PATH)support/dsPIC33F/gld/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33ev))
  LDFLAGS_XC += -Wl,-L$(XC16_PATH)support/dsPIC33E/gld/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ck dspic33ch))
  LDFLAGS_XC += -Wl,-DLD_PATH=$(XC16_PATH)support/dsPIC33C/gld/
 endif

else                      # other compiler used
 DEFPROC := $(shell echo $(DEVICE) |\
    sed -e 's/.*\(^[23][42][MEF].*\).*/PIC\1/'\
    -e 's/.*\(^3[03][EFC][PVJHK]*.*\).*/dsPIC\1/')
 CCFLAGS += -D_HOSTED -D__$(DEFPROC)__ -D__XC16__ -D__prog__ -D__pack_upper_byte 
 CCFLAGS += -Wno-attributes -Wno-unknown-pragmas
 CCFLAGS += -I$(XC16_PATH)include/ -I$(XC16_PATH)support/generic/h/

 ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
  CCFLAGS += -D__dsPIC30F__ -I$(XC16_PATH)support/dsPIC30F/h/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj))
  CCFLAGS += -D__PIC24F__ -I$(XC16_PATH)support/PIC24F/h/ -I$(XC16_PATH)support/PIC24H/h/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep))
  CCFLAGS += -D__PIC24E__ -I$(XC16_PATH)support/PIC24E/h/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33fj))
  CCFLAGS += -D__dsPIC33F__ -I$(XC16_PATH)support/dsPIC33F/h/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33ev))
  CCFLAGS += -D__dsPIC33E__ -I$(XC16_PATH)support/dsPIC33E/h/
 endif
 ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ck dspic33ch))
  CCFLAGS += -D__dsPIC33C__ -I$(XC16_PATH)support/dsPIC33C/h/
 endif
 CCFLAGS += -Wno-all
endif

vpath %.h $(UDEVKIT)/support/archi/pic16b/
HEADER += pic16b.h

# debug flags for MPLAB X, experimental
#
#LDFLAGS_XC += -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F
#LDFLAGS_XC += -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem
#
#CCFLAGS += -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -mno-eds-warn  -omf=elf -O0 -msmart-io=1 -msfr-warn=off
#

-include $(UDEVKIT)/support/archi/microchip/microchip.mk
