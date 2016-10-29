# uart
UART driver support for hardware abstraction layer

## Minimalist code

	char buff[20];

	// init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);

	// send and receive data
	uart_write(uart, "test\n", 5);
	uart_read(uart, buff, 20);

## Development status
Device assignation, config, send and read data fully functionnal

TODO :
+ send data with sw buffer and interrupt DONE 29/10/2016
+ error interrupt (only for pic24ep, pic24hj, dspic33ep and dspic33ev)
+ receive checking
+ use hw buffer for receive

## Supported architectures

* pic24f
* pic24fj
* pic24ep
* pic24hj
* dspic33fj
* dspic33ep
* dspic33ev
