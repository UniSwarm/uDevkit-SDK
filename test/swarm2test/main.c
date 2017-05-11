#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

int main(void)
{
    unsigned int i,j;
    int16_t value;
    
    init_archi();
    board_init();

    // module init
    network_init();

    ACC_CS = 1;

    for(j=0;j<5;j++) for(i=0;i<65000;i++);
    value = sysclock_source();
    board_setLed(1, 1);

    // screen test
    gui_init(board_i2c_ihm());
    gui_drawRect(16, 8, 32, 32);
    gui_ctrl_update();

    // motors test
    PR3 = 512; // Set period
    T3CON = 0x8020;// Enable Timer3

    OC3CON = 0x0000;// Turn off the OC3 when performing the setup
    OC3R = 0;// Initialize primary Compare register
    OC3RS = 0;// Initialize secondary Compare register
    OC3CON = 0x0006;// Configure for PWM mode without Fault pin // enabled
    OC3CONbits.OCTSEL = 1; // timer y
    OC3CONSET = 0x8000;// Enable OC3

    OC4CON = 0x0000;// Turn off the OC4 when performing the setup
    OC4R = 0;// Initialize primary Compare register
    OC4RS = 0;// Initialize secondary Compare register
    OC4CON = 0x0006;// Configure for PWM mode without Fault pin // enabled
    OC4CONbits.OCTSEL = 1; // timer y
    OC4CONSET = 0x8000;// Enable OC4
    
    BOOST_SLEEP = 0;
    M1DIR = 1;
    //OC3R = 300;
    //OC3RS = 300;
    
    M2DIR = 1;
    //OC4R = 300;
    //OC4RS = 300;

	while(1)
	{
        network_task();

        /*LED2 = C1A;
        LED3 = C1B;*/
        
        if (board_button(0) == 1)
            board_buzz(200);
        else if (board_button(1) == 1)
            board_buzz(400);
        else
            board_buzz(0);

        value = VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR);
        if(value < 15)
            value = 0;
        board_setLed(2, value);
        if(value < 50)
            board_setLed(3, 1);
        else
            board_setLed(3, 0);

        value = VL6180X_getDistance(board_i2c_tof(), TOF2_ADDR);
        if(value < 15)
            value = 0;
        board_setLed(1, value);
        if(value < 50)
        {
            OC3R = 512;
            OC3RS = 512;

            OC4R = 512;
            OC4RS = 512;
        }
        else
        {
            OC3R = 200;
            OC3RS = 200;

            OC4R = 200;
            OC4RS = 200;
        }

        value = VL6180X_getDistance(board_i2c_tof(), TOF3_ADDR);
        if(value < 15)
            value = 0;
        board_setLed(0, value);
        if(value < 50)
            board_setLed(4, 1);
        else
            board_setLed(4, 0);

        /*for(j=0;j<10;j++) for(i=0;i<65000;i++);
        board_setLed(2, 1);
        i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 0, 0); // led IHM on

        for(j=0;j<10;j++) for(i=0;i<65000;i++);
        board_setLed(2, 0);
        i2c_writereg(i2c_ihm, IHM_IOEXP_ADDR, 1, 1, 0); // led IHM off*/
	}

	return 0;
}
