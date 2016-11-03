# uart
UART driver support for hardware abstraction layer

## Minimalist code

	char buff[20];

```C
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
`rt_dev_t uart_getFreeDevice()`
`void uart_releaseDevice(rt_dev_t device)`

### device enable/disable
`int uart_enable(rt_dev_t device)`
`int uart_disable(rt_dev_t device)`

### device settings
`int uart_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)`
`uint32_t uart_baudSpeed(rt_dev_t device)`
`uint32_t uart_effectiveBaudSpeed(rt_dev_t device)`

`int uart_setBitConfig(rt_dev_t device, uint8_t bitLenght, uint8_t bitParity, uint8_t bitStop)`
`uint8_t uart_bitLenght(rt_dev_t device)`
`uint8_t uart_bitParity(rt_dev_t device)`
`uint8_t uart_bitStop(rt_dev_t device)`

### device write
`ssize_t uart_write(rt_dev_t device, const char *data, size_t size)`

### device read
`ssize_t uart_read(rt_dev_t device, char *data, size_t size_max)`
`size_t uart_datardy(rt_dev_t device)`

## Development status
`Device assignation, config, send and read data fully functionnal`

### TODO :
+ send data with sw buffer and interrupt DONE 29/10/2016 (still bugged)
+ error interrupt (only for pic24ep, pic24hj, dspic33ep and dspic33ev)
+ receive checking
+ use hw buffer for receive

## Supported architectures

|Family|Implementation file|Implementation header|
|------|-------------------|---------------------|
|[pic24f](../../../archi/pic24f/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[pic24fj](../../../archi/pic24fj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[pic24ep](../../../archi/pic24ep/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[pic24hj](../../../archi/pic24hj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[dspic33fj](../../../archi/dspic33fj/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[dspic33ep](../../../archi/dspic33ep/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[dspic33ev](../../../archi/dspic33ev/README.md)|[uart_pic24_dspic33.c](uart_pic24_dspic33.c)|
|[dspic30f](../../../archi/dspic30f/README.md)|[uart_dspic30.c](uart_dspic30.c)|
