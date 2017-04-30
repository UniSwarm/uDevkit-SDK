#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

rt_dev_t i2c_ihm, i2c_acc, i2c_tof;

/*uint8_t spi_read(uint8_t addr)
{
    uint16_t value, i, bit, dat;
    ACC_CS = 0;
    TRISDbits.TRISD2 = 0;
    for(i=0;i<500;i++) nop();

    dat = addr | 0x80;
    for(bit=0; bit<8; bit++)
    {
        ACC_SCK = 0;
        ACC_SD0 = (dat & 0x80) ? 1 : 0;
        for(i=0;i<500;i++) nop();
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
        dat <<= 1;
    }

    value = 0;
    TRISDbits.TRISD2 = 1;
    for(bit=0; bit<8; bit++)
    {
        value <<= 1;
        ACC_SCK = 0;
        for(i=0;i<500;i++) nop();
        if(ACC_SDI == 1)
            value |= 0x01;
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
    }

    for(i=0;i<500;i++) nop();
    ACC_CS = 1;
    TRISDbits.TRISD2 = 0;
    for(i=0;i<1000;i++) nop();

    return value;
}

void spi_write(uint8_t addr, uint8_t value)
{
    uint16_t i, bit, dat;
    ACC_CS = 0;
    TRISDbits.TRISD2 = 0;
    for(i=0;i<500;i++) nop();

    dat = addr;
    for(bit=0; bit<8; bit++)
    {
        ACC_SCK = 0;
        ACC_SD0 = (dat & 0x80) ? 1 : 0;
        for(i=0;i<500;i++) nop();
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
        dat <<= 1;
    }
    dat = value;
    for(bit=0; bit<8; bit++)
    {
        ACC_SCK = 0;
        ACC_SD0 = (dat & 0x80) ? 1 : 0;
        for(i=0;i<500;i++) nop();
        ACC_SCK = 1;
        for(i=0;i<500;i++) nop();
        dat <<= 1;
    }

    for(i=0;i<500;i++) nop();
    ACC_CS = 1;
    for(i=0;i<1000;i++) nop();
}
*/
int main(void)
{
	unsigned int i,j;
    int16_t value;

    init_archi();
	sysclock_setClock(24000000);
	board_init();

	// warning keep this init order before remap support
	network_init();

    ACC_CS = 1;

    for(j=0;j<5;j++) for(i=0;i<65000;i++);
    sysclock_switchSourceTo(SYSCLOCK_SRC_POSC);
    value = sysclock_source();
    board_setLed(1, 1);

    // ihm board
    i2c_ihm = i2c(IHM_I2C_BUS);
    i2c_open(i2c_ihm);
    i2c_setBaudSpeed(i2c_ihm, I2C_BAUD_400K);
    i2c_enable(i2c_ihm);

    gui_init(i2c_ihm);

    i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 3, 0x0E, 0); // led IHM as output
    i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 0, 0); // led IHM off
    
    // ==== tof board ====
    i2c_tof = i2c(TOF_I2C_BUS);
    i2c_open(i2c_tof);
    i2c_setBaudSpeed(i2c_tof, I2C_BAUD_400K);
    i2c_enable(i2c_tof);

    i2c_writereg(i2c_tof, TOF_IOEXP_ADDR, 3, 0x00, 0); // all io as output
    i2c_writereg(i2c_tof, TOF_IOEXP_ADDR, 1, 0x00, 0); // leds off and disable tof 2 and tof 3

    // tof1
    VL6180X_setAddr(i2c_tof, 0x52, TOF1_ADDR);
    for(i=0;i<65000;i++);
    VL6180X_init(i2c_tof, TOF1_ADDR);

    // tof2
    i2c_writereg(i2c_tof, TOF_IOEXP_ADDR, 1, 0x01, 0); // enable tof 2
    for(i=0;i<65000;i++);
    VL6180X_setAddr(i2c_tof, 0x52, TOF2_ADDR);
    for(i=0;i<65000;i++);
    VL6180X_init(i2c_tof, TOF2_ADDR);

    // tof3
    i2c_writereg(i2c_tof, TOF_IOEXP_ADDR, 1, 0x03, 0); // enable tof 3
    for(i=0;i<65000;i++);
    VL6180X_setAddr(i2c_tof, 0x52, TOF3_ADDR);
    for(i=0;i<65000;i++);
    VL6180X_init(i2c_tof, TOF3_ADDR);

    /*i2c_acc = i2c(ACC_I2C_BUS);
    i2c_open(i2c_acc);
    i2c_setBaudSpeed(i2c_acc, I2C_BAUD_400K);
    i2c_enable(i2c_acc);

    value = i2c_readreg(i2c_acc, ACC_I2C_ADDR, 0x0F, 0);*/

	for(j=0;j<2;j++) for(i=0;i<65000;i++);

    // screen test
    gui_drawRect(16, 8, 32, 32);
    gui_ctrl_update();

    /*spi_write(0x12, 0x08);
    for (i=0; i<128; i++)
        spi_read(i);

    // spi read acc
    if(spi_read(0x0F) == 0b01101001)
        board_setLed(0, 1);*/

    OC1CON = 0x0000;// Turn off the OC1 when performing the setup
    OC1R = 0x0064;// Initialize primary Compare register
    OC1RS = 0x0064;// Initialize secondary Compare register
    PR2 = 0x00C7; // Set period
    OC1CON = 0x0006;// Configure for PWM mode without Fault pin // enabled

    //T2CON = 0x8030;// Enable Timer2
    //OC1CONSET = 0x8000;// Enable OC1

	while(1)
	{
        network_task();

        /*LED2 = C1A;
        LED3 = C1B;*/

        //for(i=0;i<65000;i++);
        value = i2c_readreg(i2c_ihm, IHM_IOEXP_ADDR, 0, 0);
        if((value & IHM_BTN1_MASK) == 0)
        {
            OC1R = 100;// Initialize primary Compare register
            OC1RS = 100;// Initialize secondary Compare register
            PR2 = 200; // Set period
            OC1CON = 0x0006;
            OC1CONSET = 0x8000;// Enable OC1
        }
        else if((value & IHM_BTN2_MASK) == 0)
        {
            OC1R = 200;// Initialize primary Compare register
            OC1RS = 200;// Initialize secondary Compare register
            PR2 = 400; // Set period
            OC1CON = 0x0006;
            OC1CONSET = 0x8000;// Enable OC1
        }
        else
        {
            OC1CON = 0x0000;
            OC1CONCLR = 0x8000;// Disable OC1
        }
        
        value = VL6180X_getDistance(i2c_tof, TOF1_ADDR);
        if(value < 50)
            board_setLed(2, 1);
        else
            board_setLed(2, 0);
        
        value = VL6180X_getDistance(i2c_tof, TOF2_ADDR);
        if(value < 50)
            board_setLed(1, 1);
        else
            board_setLed(1, 0);
        
        value = VL6180X_getDistance(i2c_tof, TOF3_ADDR);
        if(value < 50)
            board_setLed(0, 1);
        else
            board_setLed(0, 0);

        /*for(j=0;j<10;j++) for(i=0;i<65000;i++);
        board_setLed(2, 1);
        i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 0, 0); // led IHM on

        for(j=0;j<10;j++) for(i=0;i<65000;i++);
        board_setLed(2, 0);
        i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 1, 0); // led IHM off*/
	}

	return 0;
}
