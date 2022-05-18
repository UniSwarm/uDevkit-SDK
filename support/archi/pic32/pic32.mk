
AS = xc32-as
CC = xc32-gcc
CXX = xc32-g++
LD = xc32-ld
AR = xc32-ar
HX = xc32-bin2hex
SIM = sim32
OBJDUMP = xc32-objdump

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
HEADER += pic32.h

-include $(UDEVKIT)/support/archi/microchip/microchip.mk
