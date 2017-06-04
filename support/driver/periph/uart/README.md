# uart
UART driver support for hardware abstraction layer

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

### device assignation
`rt_dev_t uart_getFreeDevice()` Gives a free uart device number

`int uart_open(rt_dev_t device)` Open an uart

`int uart_close(rt_dev_t device)` Close an uart

### device enable/disable
`int uart_enable(rt_dev_t device)` Enable the specified uart device

`int uart_disable(rt_dev_t device)` Disable the specified uart device

### device settings
`int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)` Sets the speed of receive and transmit

`uint32_t uart_baudSpeed(rt_dev_t device)` Gets the true baud speed

`uint32_t uart_effectiveBaudSpeed(rt_dev_t device)` Gets the effective baud speed

`int uart_setBitConfig(rt_dev_t device, uint8_t bitLenght, uint8_t bitParity, uint8_t bitStop)` Sets the config bit (bit lenght, stop bits, parity)

`uint8_t uart_bitLenght(rt_dev_t device)` Gets the bit lenght of the device

`uint8_t uart_bitParity(rt_dev_t device)` Gets the uart parity mode

`uint8_t uart_bitStop(rt_dev_t device)` Gets number of stop bit

### device write
`ssize_t uart_write(rt_dev_t device, const char *data, size_t size)` Writes data to uart device

### device read
`ssize_t uart_read(rt_dev_t device, char *data, size_t size_max)` Gets all the data readden by uart device

`size_t uart_datardy(rt_dev_t device)` Gets number of data that could be read (in sw buffer)

## Development status
Device assignation, config, send and read data fully functionnal

### TODO :
+ error interrupt (only for pic24ep, pic24hj, dspic33ep, dspic33ev and PIC32MZ)
+ receive check flags
+ use hw buffer for receive + almost empty interrupt config

## Supported architectures

|Family|Implementation file|Implementation header|
|------|-------------------|---------------------|
|[pic24f](../../../archi/pic24f/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[pic24fj](../../../archi/pic24fj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[pic24ep](../../../archi/pic24ep/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[pic24hj](../../../archi/pic24hj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic33fj](../../../archi/dspic33fj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic33ep](../../../archi/dspic33ep/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic33ev](../../../archi/dspic33ev/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|[uart_pic24_dspic33.h](uart_pic24_dspic33.h)|
|[dspic30f](../../../archi/dspic30f/README.md)|[uart_dspic30f.c](uart_dspic30f.c)|[uart_dspic30f.h](uart_dspic30f.h)|
|[pic32mm](../../../archi/pic32mm/README.md)|[uart_pic32.c](uart_pic32.c)|[uart_pic32.h](uart_pic32.h)|
|[pic32mx](../../../archi/pic32mx/README.md)|[uart_pic32.c](uart_pic32.c)|[uart_pic32.h](uart_pic32.h)|
|[pic32mzec](../../../archi/pic32mzec/README.md)|[uart_pic32.c](uart_pic32.c)|[uart_pic32.h](uart_pic32.h)|
|[pic32mzef](../../../archi/pic32mzef/README.md)|[uart_pic32.c](uart_pic32.c)|[uart_pic32.h](uart_pic32.h)|
