
AS = xc-dsc-as
CC = xc-dsc-gcc
LD = xc-dsc-ld
AR = xc-dsc-ar
HX = xc-dsc-bin2hex
SIM = sim30
OBJDUMP = xc-dsc-objdump

CC_VERSION := $(shell $(CC) --version | egrep -o "v([0-9]+\\.[0-9]+)")
CC_VERSION_MAJOR := $(shell echo $(CC_VERSION) | cut -f2 -dv | cut -f1 -d.)
CC_VERSION_MINOR := $(shell echo $(CC_VERSION) | cut -f2 -d.)

$(info $(CC_VERSION) $(CC_VERSION_MAJOR))

XCDSC_PATH = $(abspath $(dir $(lastword $(shell whereis -b xc-dsc-gcc)))..)/
ifeq ("$(LK_SCRIPT)","")
 LK_SCRIPT = p$(DEVICE).gld
endif

CCFLAGS_XC += -mcpu=$(DEVICE)
CCFLAGS_XC += -std=c99
LDFLAGS_XC += -Wl,--heap=$(HEAP),-T$(LK_SCRIPT)
CCFLAGS += -Wall

LDFLAGS_XC += -Wl,-L$(XCDSC_PATH)support/dsPIC33A/gld/

-include $(UDEVKIT)/support/archi/microchip/microchip.mk
