#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

int main(void)
{
	unsigned int i,j;
    rt_dev_t i2c_ihm;

	sysclock_setClock(8000000);
	board_init();

	// warning keep this init order before remap support
	//network_init();

    board_setLed(0, 1);
    for(j=0;j<50;j++) for(i=0;i<65000;i++);
    sysclock_switchSourceTo(SYSCLOCK_SRC_POSC);
    board_setLed(1, 1);

    i2c_ihm = i2c(IHM_I2C_BUS);
    i2c_open(i2c_ihm);
    i2c_setBaudSpeed(i2c_ihm, I2C_BAUD_400K);
    i2c_enable(i2c_ihm);

    i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 3, 0x0E, 0); // led IHM as output

	for(j=0;j<2;j++) for(i=0;i<65000;i++);

	while(1)
	{
        //network_task();

        for(j=0;j<10;j++) for(i=0;i<65000;i++);
        board_setLed(2, 1);
        i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 0, 0); // led IHM on

        for(j=0;j<10;j++) for(i=0;i<65000;i++);
        board_setLed(2, 0);
        i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 1, 0); // led IHM off
	}

	return 0;
}
