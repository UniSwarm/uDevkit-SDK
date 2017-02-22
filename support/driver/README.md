# drivers support

Low level driver dependant (periph/) or not of the processor.

Each driver must have a particular directory with the same name of the driver which contains a 'driver-name'.mk file.

## Actual drivers supported

|Driver name|Description|
|-----------|-----------|
|[asserv](asserv/README.md)|motor control for robot movements|
|[ax12](ax12/README.md)|ax12 servo motor driver|
|[motor](motor/README.md)|motor abstraction drivers|
|[adc](periph/adc/README.md)|ADC analog converters driver|
|[i2c](periph/i2c/README.md)|I2C communication driver|
|[ic](periph/ic/README.md)|Input compare driver|
|[oc](periph/oc/README.md)|Output compare driver|
|[pwm](periph/pwm/README.md)|PWM driver|
|[qei](periph/qei/README.md)|Quadrature encoder driver|
|[spi](periph/spi/README.md)|SPI communication driver|
|[sysclock](periph/sysclock/README.md)|System clock|
|[timer](periph/timer/README.md)|Timer driver|
|[uart](periph/uart/README.md)|UART (serial) communication driver|
|[usb_hal](periph/usb_hal/README.md)|USB low layer driver|
|[usb_serial](usb_serial/README.md)|USB CDC driver|

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
	 ARCHI_SRC += timer_dspic.c
	 HEADER += timer_dspic.h
	endif
	else ifeq ($(ARCHI), pic24))
	 ARCHI_SRC += timer_pic24.c
	 HEADER += timer_pic24.h
	endif

To implement a simulator interface :

	SIM_SRC += timer_sim.c

And for global inclusion of the driver, add a header file that include needed include files of the support in include/driver/.
