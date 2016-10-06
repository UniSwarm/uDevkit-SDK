#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "driver/motor.h"

int main(void)
{
	unsigned int i, j, byte_read, end=0;
    uint16_t status, value_x, value_y, value_z;
	rt_dev_t uartDbg;
	rt_dev_t i2c;
	uint16_t value, value2;
	char buff[200];
	char buffread[200];
	uint8_t acc[8];

	sysclock_setClock(120000000);
	init_board();

	usb_serial_init();
    LED = 0;

	// warning keep this init order before remap support
	esp_init();
	ax12_init();
    a6_init();

	adc_init();
    asserv_init();
    motor_init();
    asserv_setCoderEntrax(195.0);
    asserv_setCoderStep(0.00849123461395001864975755315181); // 72.5mm wheel

	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);

    i2c = i2c_getFreeDevice();
    i2c_setBaudSpeed(i2c, I2C_BAUD_400K);
    i2c_enable(i2c);

    i2c_writereg(i2c, 0x38, 0x2A, 0x01, I2C_REG8 | I2C_REGADDR8);

    asserv_setPos(1500, 1000, 0);
    asserv_goTo(2000, 1000);
    asserv_setSpeed(20);
    asserv_setMode(Asserv_Mode_Linear);

    /*motor_setPower(1, 200);
    motor_setPower(2, 200);*/

    j=0;
	while(1)
	{
		usb_serial_task();
		for(i=0;i<65000;i++);

		value = sharp_convert(adc_getValue(24), FarSharp);	// AnS1
		/*value = adc_getValue(25);	// AnS2*/
		value2 = sharp_convert(adc_getValue(26), FarSharp);	// AnS3
		ax12_moveTo(1, value, 512, 512);

        if(value < 150 || value2 < 150)
            asserv_setSpeed(0);
        else
            asserv_setSpeed(20);

        i2c_readregs(i2c, 0x38, 0x00, acc, 7, I2C_REG8 | I2C_REGADDR8);
        if(acc[0] & 0x08)
        {
            value_x = acc[1];
            value_y = acc[3];
            value_z = acc[5];
        }

		sprintf(buff, "d1: %d d2: %d x: %d y:%d t:%d acx:%d acy:%d acz:%d\n",
				value,
				value2,
				(int)asserv_getXPos(),
				(int)asserv_getYPos(),
				(int)asserv_getTPos(),
                value_x, value_y, value_z
				);

        if(j++>5)
        {
            a6_write(buff, strlen(buff)-1);
            //uart_write(uartDbg, buff, strlen(buff));
            //usb_serial_write(buff, strlen(buff));
        }

		/*value = uart_read(uartDbg, buff, 100);
		if(value>0)
			uart_write(uartDbg, buff, value);

		byte_read = uart_read(uartDbg, buff, 256);
		if(byte_read > 0)
			usb_serial_write(buff, byte_read);*/

		byte_read = usb_serial_read(buffread + end, 200);
		if(byte_read > 0)
        {
            int i;
            int valid = 0;
            for (i=end; i<end+byte_read; i++)
            {
                if(buffread[i]=='\n')
                {
                    valid = 1;
                    break;
                }
            }
            if(valid==0)
                end+=byte_read;

            if(valid==1)
            {
                uint8_t motor = buffread[0]-'0';
                if(buffread[1]==':')
                {
                    LED = ~LED;
                    int16_t pwm = strtol (buffread+2, NULL, 10);
                    motor_setPower(motor, pwm);
                }
                buffread[end]='\n';
                usb_serial_write(buffread, end+1);
                end=0;
            }
        }
	}

	return 0;
}
