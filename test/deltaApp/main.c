#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "robot.h"
#include "archi.h"

unsigned int pos[] = {
    1500, 1000,
    2000, 1000,
    2000, 1500,
    1500, 1500
};
unsigned char step = 2;

int main(void)
{
	unsigned int i, j;
    uint16_t value_x, value_y, value_z;
	rt_dev_t uartDbg;
	rt_dev_t i2c;
    rt_dev_t usb_serial;
	uint16_t value, value2;
	char buff[200];
	uint8_t acc[8];
    MrobotPose pose;

	sysclock_setClock(120000000);
	robot_init();

	usb_serial = usb_serial_getFreeDevice();
    board_setLed(0, 1);

	// warning keep this init order before remap support
	esp_init();
	ax12_init();
    a6_init();

	adc_init();

	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);

    // console init
    cmdline_init();
    cmdline_setDevice(usb_serial, usb_serial);

    // i2c init
    i2c = i2c_getFreeDevice();
    i2c_setBaudSpeed(i2c, I2C_BAUD_400K);
    i2c_enable(i2c);

    i2c_writereg(i2c, 0x38, 0x2A, 0x01, I2C_REG8 | I2C_REGADDR8);

    pose.x = 1500;
    pose.y = 1000;
    pose.t = 0;
    mrobot_setPose(pose);
    //mrobot_setMode(Asserv_Mode_Linear);

    //asserv_goTo(pos[0], pos[1]);

    j=0;
	while(1)
	{
		usb_serial_task();
        for(i=0;i<65000;i++);

        /*if(asserv_getDistance() <= 15.0)
        {
            for(j=0;j<10;j++) for(i=0;i<65000;i++);
            step += 2;
            if(step > 6)
                step = 0;
            asserv_goTo(pos[step], pos[step+1]);
        }*/

		value = sharp_convert(adc_getValue(24), FarSharp);	// AnS1
		/*value = adc_getValue(25);	// AnS2*/
		value2 = sharp_convert(adc_getValue(26), FarSharp);	// AnS3
		//ax12_moveTo(1, value, 512, 512);

        if(value < 150 || value2 < 150)
            mrobot_pause();
        else
            mrobot_restart();

        i2c_readregs(i2c, 0x38, 0x00, acc, 7, I2C_REG8 | I2C_REGADDR8);
        if(acc[0] & 0x08)
        {
            value_x = acc[1];
            value_y = acc[3];
            value_z = acc[5];
        }

        pose = mrobot_pose();
		sprintf(buff, "d1:%d\td2:%d\tx: %d\ty:%d\tt:%d\tacx:%d\tacy:%d\tacz:%d\r\n",
				value,
				value2,
				(int)pose.x,
				(int)pose.y,
				(int)pose.t,
                value_x, value_y, value_z
				);

        if(j++>10)
        {
            //a6_write(buff, strlen(buff)-1);
            //uart_write(uartDbg, buff, strlen(buff));
            //usb_serial_write(usb_serial, buff, strlen(buff));
        }

        cmdline_task();
	}

	return 0;
}
