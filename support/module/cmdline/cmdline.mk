ifndef CMDLINE_MODULE
CMDLINE_MODULE=

CMDLINE_PATH := $(dir $(lastword $(MAKEFILE_LIST)))

vpath %.h $(MODULEPATH) $(MODULEPATH)cmd
vpath %.c $(MODULEPATH) $(MODULEPATH)cmd

SRC += cmdline.c
HEADER += cmdline.h \
  cmdline_curses.h \
  cmd.h \
  cmds.h \
  cmd_stdio.h

# include all commands
SRC += cmd.c \
  cmd_led.c \
  cmd_reg.c

ifneq (,$(findstring gpio,$(DRIVERS)))
  SRC += cmd_gpio.c
endif
ifneq (,$(findstring uart,$(DRIVERS)))
  SRC += cmd_uart.c
endif
ifneq (,$(findstring i2c,$(DRIVERS)))
  SRC += cmd_i2c.c
endif
ifneq (,$(findstring adc,$(DRIVERS)))
  SRC += cmd_adc.c
endif
ifneq (,$(findstring ax,$(DRIVERS)))
  SRC += cmd_ax.c
endif
ifneq (,$(findstring can,$(DRIVERS)))
  SRC += cmd_can.c
endif
ifneq (,$(findstring timer,$(DRIVERS)))
  SRC += cmd_timer.c
endif

  SRC += cmd_sysclock.c

ifneq (,$(findstring mrobot,$(MODULES)))
  SRC += cmd_mrobot.c
endif

INCLUDEPATH += -I$(CMDLINE_PATH)

endif
