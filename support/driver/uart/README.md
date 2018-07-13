# UART

UART driver support for hardware abstraction layer.

## Minimalist code

```C
char buff[20];
rt_dev_t uart;

// init
uart = uart_getFreeDevice();
uart_setBaudSpeed(uart, 115200);
uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
uart_enable(uart);

// send and receive data
uart_write(uart, "test\n", 5);
uart_read(uart, buff, 20);
```

## API

### Device assignation

#### uart_getFreeDevice

```C
rt_dev_t uart_getFreeDevice();
```
Gives a free uart device number and opens it

#### uart_open

```C
int uart_open(rt_dev_t device)
```
Opens an uart

#### uart_close

```C
int uart_close(rt_dev_t device);
```
Closes an uart

### Device enable/disable

#### uart_enable

```C
int uart_enable(rt_dev_t device);
```
Enables the specified uart device

#### uart_disable

```C
int uart_disable(rt_dev_t device);
```
Disables the specified uart device

### Device settings

#### uart_setBaudSpeed

```C
int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed);
```
Sets the speed of receive and transmit

#### uart_baudSpeed

```C
uint32_t uart_baudSpeed(rt_dev_t device);
```
 Gets the true baud speed

#### uart_effectiveBaudSpeed

```C
uint32_t uart_effectiveBaudSpeed(rt_dev_t device);
```
Gets the effective baud speed

#### uart_setBitConfig

```C
int uart_setBitConfig(rt_dev_t device, uint8_t bitLength, uint8_t bitParity, uint8_t bitStop);
```
Sets the configuration bit (bit length, stop bits, parity)

#### uart_bitLength

```C
uint8_t uart_bitLength(rt_dev_t device);
```
Gets the bit length of the device

#### uart_bitParity

```C
uint8_t uart_bitParity(rt_dev_t device);
```
Gets the uart parity mode

#### uart_bitStop

```C
uint8_t uart_bitStop(rt_dev_t device);
```
Gets number of stop bit

### Device read / write

#### uart_write

```C
ssize_t uart_write(rt_dev_t device, const char *data, size_t size);
```
Writes data to uart device

#### uart_read

```C
ssize_t uart_read(rt_dev_t device, char *data, size_t size_max);
```
Reads `size_max` data received by uart device

#### uart_datardy

```C
size_t uart_datardy(rt_dev_t device);
```
Gets number of data that could be read (in sw buffer)

## Development status

Device assignation, configuration, send and read data fully functional

### TODO

+ error interrupt not implemented (only for pic24ep, pic24hj, dspic33c, dspic33ep, dspic33ev and PIC32MZ)
+ receive function needs to check flags
+ address mode
+ inversed line
+ hafl / full duplex mode

## Supported architectures

Header file : [uart.h](uart.h)

|Family|Implementation files|
|------|--------------------|
|[dspic33ch](../../archi/dspic33ch/README.md)|[uart_dspic33c.c](uart_dspic33c.c) / [uart_dspic33c.h](uart_dspic33c.h)|
|[dspic33ck](../../archi/dspic33ck/README.md)|[uart_dspic33c.c](uart_dspic33c.c) / [uart_dspic33c.h](uart_dspic33c.h)|
|[pic24f](../../archi/pic24f/README.md)  |[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[pic24fj](../../archi/pic24fj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[pic24ep](../../archi/pic24ep/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[pic24hj](../../archi/pic24hj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic33fj](../../archi/dspic33fj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic33ep](../../archi/dspic33ep/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic33ev](../../archi/dspic33ev/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c) / [uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic30f](../../archi/dspic30f/README.md)|[uart_dspic30f.c](uart_dspic30f.c) / [uart_dspic30f.h](uart_dspic30f.h)|
|[pic32mm](../../archi/pic32mm/README.md)|[uart_pic32mz_mm_mk.c](uart_pic32mz_mm_mk.c) / [uart_pic32mz_mm_mk.h](uart_pic32mz_mm_mk.h)|
|[pic32mk](../../archi/pic32mk/README.md)|[uart_pic32mz_mm_mk.c](uart_pic32mz_mm_mk.c) / [uart_pic32mz_mm_mk.h](uart_pic32mz_mm_mk.h)|
|[pic32mzec](../../archi/pic32mzec/README.md)|[uart_pic32mz_mm_mk.c](uart_pic32mz_mm_mk.c) / [uart_pic32mz_mm_mk.h](uart_pic32mz_mm_mk.h)|
|[pic32mzef](../../archi/pic32mzef/README.md)|[uart_pic32mz_mm_mk.c](uart_pic32mz_mm_mk.c) / [uart_pic32mz_mm_mk.h](uart_pic32mz_mm_mk.h)|
|[pic32mzda](../../archi/pic32mzda/README.md)|[uart_pic32mz_mm_mk.c](uart_pic32mz_mm_mk.c) / [uart_pic32mz_mm_mk.h](uart_pic32mz_mm_mk.h)|
|[pic32mx](../../archi/pic32mx/README.md)|[uart_pic32mx.c](uart_pic32mx.c) / [uart_pic32mx.h](uart_pic32mx.h)|
