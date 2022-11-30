ifndef CMDLINE_MODULE
CMDLINE_MODULE=

vpath %.h $(MODULEPATH) $(MODULEPATH)cmd
vpath %.c $(MODULEPATH) $(MODULEPATH)cmd

SRC += cmdline.c
HEADER += cmdline.h

SRC := $(SRC) cmd.c cmd_led.c cmd_reg.c

# include all commands
ifneq (,$(findstring gpio,$(DRIVERS)))
  SRC := $(SRC) cmd_gpio.c
endif
ifneq (,$(findstring uart,$(DRIVERS)))
  SRC := $(SRC) cmd_uart.c
endif
ifneq (,$(findstring i2c,$(DRIVERS)))
  SRC := $(SRC) cmd_i2c.c
endif
ifneq (,$(findstring adc,$(DRIVERS)))
  SRC := $(SRC) cmd_adc.c
endif
ifneq (,$(findstring ax,$(DRIVERS)))
  SRC := $(SRC) cmd_ax.c
endif
ifneq (,$(findstring can,$(DRIVERS)))
  SRC := $(SRC) cmd_can.c
endif

  SRC := $(SRC) cmd_sysclock.c

ifneq (,$(findstring mrobot,$(MODULES)))
  SRC := $(SRC) cmd_mrobot.c
endif

endif
