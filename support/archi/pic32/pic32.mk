
AS = xc32-as
CC = xc32-gcc
CXX = xc32-g++
LD = xc32-ld
AR = xc32-ar
HX = xc32-bin2hex
SIM = sim32
OBJDUMP = xc32-objdump

CC_VERSION := $(shell $(CC) --version | egrep -o "v([0-9]+\\.[0-9]+)")
CC_VERSION_MAJOR := $(shell echo $(CC_VERSION) | cut -f2 -dv | cut -f1 -d.)
CC_VERSION_MINOR := $(shell echo $(CC_VERSION) | cut -f2 -d.)

#$(info $(ARCHI) $(XC) $(CC_VERSION) $(CC_VERSION_MAJOR))

define findmdfp
 $(info Possible MDFP_PATH for this chip :)
 $(foreach PIC, $(shell find /opt/microchip/mplabx/ ~/.mchp_packs/ -name *$(DEVICE).PIC), $(info $(abspath $(dir $(PIC))/..)))
 $(info Download support here if you can not find : https://packs.download.microchip.com/)
endef
ifeq ("$(CC_VERSION_MAJOR)","6")
  ifeq ("$(XC_MDFP_PATH)","")
   $(call findmdfp,)
   $(error "Please specify a XC_MDFP_PATH")
 endif
endif
ifneq ("$(XC_MDFP_PATH)","")
 ifeq ($(wildcard $(XC_MDFP_PATH)/xc32/*),)
  $(info Invalid MDFP path : $(XC_MDFP_PATH))
  $(call findmdfp,)
  $(error "Please specify a valid XC_MDFP_PATH")
 endif
 XC_MDFP += -mdfp=$(XC_MDFP_PATH)
 CCFLAGS_XC += $(XC_MDFP)
 HXFLAGS += $(XC_MDFP)
endif

ifeq ("$(CC)","xc32-gcc") # XC32 compiler used
 CXXFLAGS += -frtti -fno-enforce-eh-specs -fexceptions -fno-check-new -ffunction-sections -fdata-sections
 CCFLAGS_XC += -mprocessor=$(DEVICE)
 CCFLAGS += -Wall
 LDFLAGS_XC += -Wl,--defsym=_min_heap_size=$(HEAP)

 ifneq ($(filter %.cpp,$(SRC)),)
  LDFLAGS_XC += -Wl,--gc-sections
 endif
else                      # other compiler used
 XC32_PATH = $(abspath $(dir $(lastword $(shell whereis -b xc32-gcc)))..)/
 DEFPROC := $(shell echo $(DEVICE) |\
    sed -e 's/.*\(^[23][42][MEF].*\).*/\1/')
$(warning $(DEFPROC))
 CCFLAGS += -DMIPSEL
 CCFLAGS += -D_HOSTED -D__$(DEFPROC)__ -D__XC32__ -D__prog__ -D__LANGUAGE_C__
 CCFLAGS += -Wno-attributes -Wno-unknown-pragmas
 CCFLAGS += -I$(XC32_PATH)include/ -I$(XC32_PATH)pic32mx/include/
 CCFLAGS += -Wno-all
endif

vpath %.h $(UDEVKIT)/support/archi/pic32/
vpath %.c $(UDEVKIT)/support/archi/pic32/
ARCHI_SRC += pic32.c
HEADER += pic32.h

-include $(UDEVKIT)/support/archi/microchip/microchip.mk
