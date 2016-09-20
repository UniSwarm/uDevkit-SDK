#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "driver/motor.h"

int main(void)
{
	unsigned int i,j;
	rt_dev_t uartDbg;
	rt_dev_t i2c;
	uint16_t value, value2;
	char buff[100];

	setSystemClock(120000000);
	init_board();

	// warning keep this init order before remap support
	esp_init();
	ax12_init();
    a6_init();

	adc_init();
    asserv_init();

    LED2 = 1;

	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);

    i2c = i2c_getFreeDevice();
    i2c_setBaudSpeed(i2c, I2C_BAUD_400K);
    i2c_enable(i2c);

    i2c_start(i2c);
    i2c_putc(i2c, 0x38);
    i2c_putc(i2c, 0x0D);
    i2c_restart(i2c);
    i2c_putc(i2c, 0x39);
    value = i2c_getc(i2c);
    i2c_nack(i2c);
    i2c_stop(i2c);

	for(j=0;j<20;j++) for(i=0;i<65000;i++);
    i2c_start(i2c);
    i2c_putc(i2c, 0x38);
    i2c_putc(i2c, 0x2A);
    i2c_putc(i2c, 0x01);
    i2c_stop(i2c);

    motor_setPower(1, -700);
    motor_setPower(2, 700);

	while(1)
	{
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
		LED = 0;
    LED3 = 1;
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
		LED = 1;
    LED3 = 0;

		/*value = adc_getValue(24);	// AnS1
		value = adc_getValue(25);	// AnS2*/
		value = adc_getValue(26);	// AnS3
		ax12_moveTo(1, value, 512, 512);

        i2c_start(i2c);
        i2c_putc(i2c, 0x38);
        i2c_putc(i2c, 0x01);
        i2c_restart(i2c);
        i2c_putc(i2c, 0x39);
        value2 = i2c_getc(i2c);
        i2c_nack(i2c);
        i2c_stop(i2c);

		sprintf(buff, "dist: %dmm x: %d y:%d ac:%d\n",
				sharp_convert(value, FarSharp),
				asserv_getXPos(),
				asserv_getYPos(),
                value2
				);

		a6_write(buff, strlen(buff)+1);
		uart_write(uartDbg, buff, strlen(buff)+1);

		value = uart_read(uartDbg, buff, 100);
		if(value>0)
			uart_write(uartDbg, buff, value);
	}

	return 0;
}
