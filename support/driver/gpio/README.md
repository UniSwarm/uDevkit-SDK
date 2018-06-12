# GPIO
GPIO driver support for hardware abstraction layer

## Minimalist code

```C
// port
rt_dev_t port;
port = gpio_port(GPIO_PORTA);
gpio_setPortConfig(port, GPIO_OUTPUT);
gpio_writePort(port, 0xA5);

// bit
rt_dev_t btn, led;
btn = gpio_pin(GPIO_PORTF, 8);
gpio_setBitConfig(btn, GPIO_INPUT | GPIO_PULLUP);

led = gpio_pin(GPIO_PORTE, 4);
gpio_setBitConfig(btn, GPIO_OUTPUT);

while (1)
    gpio_writeBit(led, gpio_readBit(btn));

```

## API

### GPIO bit access and settings

`rt_dev_t gpio_pin(port, pin)` Macro to choose a bit of a port

`int gpio_setBitConfig(rt_dev_t device, uint16_t config)` Set GPIO bit configuration (input / output / open-drain / pull-up / pull-down)

`void gpio_setBit(rt_dev_t device)` Set a bit of a GPIO to 1 (HIGH)

`void gpio_clearBit(rt_dev_t device)` Set a bit of a GPIO to 0 (LOW)

`void gpio_toggleBit(rt_dev_t device)` Toggle (invert) a bit of a GPIO from 1 to 0 or from 0 to 1

`void gpio_writeBit(rt_dev_t device, GPIO_VALUE value)` Write a specific value of a bit of a GPIO

`GPIO_VALUE gpio_readBit(rt_dev_t device)` Read a bit of a GPIO

### bit / port settings

`rt_dev_t gpio_port(port)` Macro to choose a whole port

`int gpio_setPortConfig(rt_dev_t device, uint16_t config)` Set GPIO port configuration (input / output)

`void gpio_writePort(rt_dev_t device, port_type value)` Set GPIO port value (complete port)

`port_type gpio_readPort(rt_dev_t device)` Read GPIO port value (complete port)

## Development status
Device assignation, configuration, write and read data fully functional

### TODO :
+ add special pins settings
+ complete pic16b port settings

## Supported architectures

|Family|Implementation file|Implementation header|
|------|-------------------|---------------------|
|[pic24f](../../../archi/pic24f/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[pic24fj](../../../archi/pic24fj/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[pic24ep](../../../archi/pic24ep/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[pic24hj](../../../archi/pic24hj/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[dspic33fj](../../../archi/dspic33fj/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[dspic33ep](../../../archi/dspic33ep/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[dspic33ev](../../../archi/dspic33ev/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[dspic30f](../../../archi/dspic30f/README.md)|[gpio_pic24_dspic30f_dspic33.c](gpio_pic24_dspic30f_dspic33.c)|[gpio_pic24_dspic30f_dspic33.h](gpio_pic24_dspic30f_dspic33.h)|
|[pic32mm](../../../archi/pic32mm/README.md)|[gpio_pic32.c](gpio_pic32.c)|[gpio_pic32.h](gpio_pic32.h)|
|[pic32mk](../../../archi/pic32mk/README.md)|[gpio_pic32.c](gpio_pic32.c)|[gpio_pic32.h](gpio_pic32.h)|
|[pic32mx](../../../archi/pic32mx/README.md)|[gpio_pic32.c](gpio_pic32.c)|[gpio_pic32.h](gpio_pic32.h)|
|[pic32mzec](../../../archi/pic32mzec/README.md)|[gpio_pic32.c](gpio_pic32.c)|[gpio_pic32.h](gpio_pic32.h)|
|[pic32mzef](../../../archi/pic32mzef/README.md)|[gpio_pic32.c](gpio_pic32.c)|[gpio_pic32.h](gpio_pic32.h)|
|[pic32mzda](../../../archi/pic32mzda/README.md)|[gpio_pic32.c](gpio_pic32.c)|[gpio_pic32.h](gpio_pic32.h)|
