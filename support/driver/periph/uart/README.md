# uart
UART driver support for hardware abstraction layer

## Minimalist code

	// init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);
	
	// send data
	uart_putc(uart, 'A');

## Development status
Device assignation, config and send data fully functionnal

Data receive not implemented

## Supported architectures

* dsPIC33EP
* dsPIC33FJ
