# drivers support

Each driver must have a particular directory with the same name of the driver which contains a 'driver-name'.mk file.

## How to add a driver support?
Create a directory with the name of the driver in this directory :

	mkdir <driver-name>

Add <driver-name>.mk in this directory. This file will be included by the makefile when a project ask the support for this driver.

To avoid multiple inclusion of <driver-name>.mk, add this (exemple with timer) :

	ifndef TIMER_DRIVER
	TIMER_DRIVER=
	
	content of file here ....
	
	endif

If the driver need the support of of another drivers, add it :

	DRIVERS += another_driver

To include C files directory to paths of sources, add this directives and as many you need :

	vpath %.c $(DRIVERPATH)
	vpath %.c $(DRIVERPATH)/other-source-dir

You just need to add header and source code files :

	SRC += timer.c
	HEADER += timer.h

And for specific architecture :

	ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
	 SRC += timer_dspic.c
	 HEADER += timer_dspic.h
	endif
	else ifeq ($(ARCHI), pic24))
	 SRC += timer_pic24.c
	 HEADER += timer_pic24.h
	endif
