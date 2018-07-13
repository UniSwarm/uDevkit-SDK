# Drivers support

Low level drivers that dependant of the processor.

Each driver must have a particular directory with the same name of the driver which contains a 'driver-name'.mk file.

## Actual drivers supported

|Driver name|Description|Status|
|-----------|-----------|------|
|[ax12](ax12/README.md)|ax12 servo motor driver|Experimental|
|[motor](motor/README.md)|motor abstraction drivers|Experimental|
|[adc](adc/README.md)|ADC analog converters driver|Experimental|
|[i2c](i2c/README.md)|I2C communication driver|__Stable__|
|[ic](ic/README.md)|Input compare driver|Implementation needed|
|[oc](oc/README.md)|Output compare driver|Experimental|
|[pwm](pwm/README.md)|PWM driver|Experimental|
|[qei](qei/README.md)|Quadrature encoder driver|__Stable__|
|[spi](spi/README.md)|SPI communication driver|Implementation needed|
|[sysclock](sysclock/README.md)|System clock|__Stable__|
|[timer](timer/README.md)|Timer driver|__Stable__|
|[uart](uart/README.md)|UART (serial) communication driver|__Stable__|
|[usb_hal](usb_hal/README.md)|USB low layer driver|Experimental|
|[usb_serial](usb_serial/README.md)|USB CDC driver|Experimental|

## How to add a driver support?
Create a directory with the name of the driver in this directory :

	mkdir <driver-name>

Add <driver-name>.mk in this directory. This file will be included by the makefile when a project ask the support for this driver.

To avoid multiple inclusion of <driver-name>.mk, add this (example with timer) :

```Makefile
	ifndef TIMER_DRIVER
	TIMER_DRIVER=
	
	#content of file here ....
	
	endif
```

If the driver need the support of another drivers, add it :

```Makefile
	DRIVERS += another_driver
```

To include C files directory to paths of sources, add this directives and as many you need :

```Makefile
	vpath %.c $(DRIVERPATH)
	vpath %.h $(DRIVERPATH)
	vpath %.c $(DRIVERPATH)/other-source-dir
	vpath %.h $(DRIVERPATH)/other-source-dir
```

You just need to add header and source code files :

```Makefile
	SRC += timer.c
	HEADER += timer.h
```

And for specific architecture :

```Makefile
	ifeq ($(ARCHI),$(filter $(ARCHI),dspic33ep dspic33fj))
	 ARCHI_SRC += timer_dspic33.c
	 HEADER += timer_dspic33.h
	endif
	ifeq ($(ARCHI), pic24)
	 ARCHI_SRC += timer_pic24.c
	 HEADER += timer_pic24.h
	endif
```

To implement a simulator interface :

```Makefile
	SIM_SRC += timer_sim.c
```

And for global inclusion of the driver, add a header file that include needed include files of the support in include/driver/.
