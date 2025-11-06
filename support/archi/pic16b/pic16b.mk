
ifneq (,$(filter dspic%,$(ARCHI)))
 XC ?= XCDSC
else
 XC ?= XC16
endif

ifeq ($(XC), XC16)
 XC_PATH ?= $(abspath $(dir $(lastword $(shell whereis -b xc16-gcc)))..)/
 AS = $(XC_PATH)bin/xc16-as
 CC = $(XC_PATH)bin/xc16-gcc
 LD = $(XC_PATH)bin/xc16-ld
 AR = $(XC_PATH)bin/xc16-ar
 HX = $(XC_PATH)bin/xc16-bin2hex
 SIM = $(XC_PATH)bin/sim30
 OBJDUMP = xc16-objdump
else
 XC_PATH ?= $(abspath $(dir $(lastword $(shell whereis -b xc-dsc-gcc)))..)/
 AS = $(XC_PATH)bin/xc-dsc-as
 CC = $(XC_PATH)bin/xc-dsc-gcc
 LD = $(XC_PATH)bin/xc-dsc-ld
 AR = $(XC_PATH)bin/xc-dsc-ar
 HX = $(XC_PATH)bin/xc-dsc-bin2hex
 SIM = $(XC_PATH)bin/sim30
 OBJDUMP = xc-dsc-objdump
endif

CC_VERSION := $(shell $(CC) --version | egrep -o "v([0-9]+\\.[0-9]+)")
CC_VERSION_MAJOR := $(shell echo $(CC_VERSION) | cut -f2 -dv | cut -f1 -d.)
CC_VERSION_MINOR := $(shell echo $(CC_VERSION) | cut -f2 -d.)

#$(info $(ARCHI) $(XC) $(CC_VERSION) $(CC_VERSION_MAJOR))

define findmdfp
 $(info Possible MDFP_PATH for this chip :)
 $(foreach PIC, $(shell find /opt/microchip/mplabx/ ~/.mchp_packs/ -name *$(DEVICE).PIC), $(info $(abspath $(dir $(PIC))/..)))
 $(info Download support here if you can not find : https://packs.download.microchip.com/)
endef
ifeq ("$(CC_VERSION_MAJOR)","3")
 ifeq ($(shell test $(CC_VERSION_MINOR) -gt 21; echo $$?),0)
  ifeq ("$(XC_MDFP_PATH)","")
   $(call findmdfp,)
   $(error "Please specify a XC_MDFP_PATH")
  endif
 endif
endif
ifneq ("$(XC_MDFP_PATH)","")
 ifeq ($(wildcard $(XC_MDFP_PATH)/xc16/*),)
  $(info Invalid MDFP path : $(XC_MDFP_PATH))
  $(call findmdfp,)
  $(error "Please specify a valid XC_MDFP_PATH")
 endif
 XC_MDFP += -mdfp=$(XC_MDFP_PATH)/xc16/
 CCFLAGS_XC += $(XC_MDFP)
 HXFLAGS += $(XC_MDFP)
endif

ifeq ("$(LK_SCRIPT)","")
 LK_SCRIPT = p$(DEVICE).gld
endif

ifeq ("$(CC_VERSION_MAJOR)","1")
 CCFLAGS_XC += -no-legacy-libc
endif
CCFLAGS_XC += -mcpu=$(DEVICE)
CCFLAGS_XC += -mno-eds-warn
CCFLAGS_XC += -std=c99
LDFLAGS_XC += -Wl,--heap=$(HEAP),-T$(LK_SCRIPT)
CCFLAGS += -Wall

ifeq ($(ARCHI),$(filter $(ARCHI),dspic30f))
 LDFLAGS_XC += -Wl,-L$(XC_PATH)support/dsPIC30F/gld/
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24f pic24fj pic24hj))
 LDFLAGS_XC += -Wl,-L$(XC_PATH)support/PIC24F/gld/ -Wl,-L$(XC_PATH)support/PIC24H/gld/
endif
ifeq ($(ARCHI),$(filter $(ARCHI),pic24ep))
 LDFLAGS_XC += -Wl,-L$(XC_PATH)support/PIC24E/gld/
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33fj))
 LDFLAGS_XC += -Wl,-L$(XC_PATH)support/dsPIC33F/gld/
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33ev))
 LDFLAGS_XC += -Wl,-L$(XC_PATH)support/dsPIC33E/gld/
endif
ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ck dspic33ch))
 LDFLAGS_XC += -Wl,-DLD_PATH=$(XC_PATH)support/dsPIC33C/gld/
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
