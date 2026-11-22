
vpath %.h $(UDEVKIT)/support/archi/dspic33ak/
HEADER += dspic33ak.h

XC_PATH ?= $(abspath $(dir $(lastword $(shell whereis -b xc-dsc-gcc)))..)/
AS = $(XC_PATH)bin/xc-dsc-as
CC = $(XC_PATH)bin/xc-dsc-gcc
LD = $(XC_PATH)bin/xc-dsc-ld
AR = $(XC_PATH)bin/xc-dsc-ar
HX = $(XC_PATH)bin/xc-dsc-bin2hex
SIM = $(XC_PATH)bin/sim30
OBJDUMP = $(XC_PATH)bin/xc-dsc-objdump

CC_VERSION := $(shell $(CC) --version | egrep -o "v([0-9]+\\.[0-9]+)")
CC_VERSION_MAJOR := $(shell echo $(CC_VERSION) | cut -f2 -dv | cut -f1 -d.)
CC_VERSION_MINOR := $(shell echo $(CC_VERSION) | cut -f2 -d.)

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

$(info $(CC_VERSION) $(CC_VERSION_MAJOR))

XCDSC_PATH = $(abspath $(dir $(lastword $(shell whereis -b xc-dsc-gcc)))..)/
ifeq ("$(LK_SCRIPT)","")
 LK_SCRIPT = p$(DEVICE).gld
endif

CCFLAGS_XC += -mcpu=$(DEVICE)
LDFLAGS_XC += -Wl,--heap=$(HEAP),-T$(LK_SCRIPT)
CCFLAGS += -Wall

LDFLAGS_XC += -Wl,-L$(XCDSC_PATH)support/dsPIC33A/gld/

-include $(UDEVKIT)/support/archi/microchip/microchip.mk
