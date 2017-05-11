#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "fonts.h"

int main(void)
{
    unsigned int i, j;
    float voltage;
    int16_t value;
    
    init_archi();
    board_init();

    // module init
    network_init();

    //ACC_CS = 1;

    for(j=0;j<5;j++) for(i=0;i<65000;i++);
    value = sysclock_source();
    board_setLed(1, 1);

    // screen test
    gui_init(board_i2c_ihm());
    gui_setFont(&core12b);
    
    gui_setPenColor(1);
    gui_drawLine(0, 0, 128, 64);
    gui_ctrl_update();
    
    gui_setBrushColor(1);
    gui_setPenColor(0);
    gui_drawFillRect(16, 30, 16, 30);
    gui_ctrl_update();
    
    gui_setBrushColor(0);
    gui_setPenColor(1);
    gui_drawText(0, 0, "swarm2");
    gui_drawRect(16, 8, 32, 32);
    gui_ctrl_update();

    // motors test
    /*PR3 = 512; // Set period
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
    OC4CONSET = 0x8000;// Enable OC4*/
    
    rt_dev_t pwm_m1 = pwm(3);
    pwm_open(pwm_m1);
    oc_setTimer(oc(3), 1);
    pwm_setFreq(pwm_m1, 20000);
    pwm_enable(pwm_m1);
    
    rt_dev_t pwm_m2 = pwm(4);
    pwm_open(pwm_m2);
    oc_setTimer(oc(4), 1);
    pwm_setFreq(pwm_m2, 20000);
    pwm_enable(pwm_m2);
    
    //BOOST_SLEEP = 1;
    //M1DIR = 1;
    //OC3R = 300;
    //OC3RS = 300;
    
    //M2DIR = 1;
    //OC4R = 300;
    //OC4RS = 300;

    while(1)
    {
        network_task();
        voltage = board_getPowerVoltage();
        
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
            /*OC3R = 512;
            OC3RS = 512;

            OC4R = 512;
            OC4RS = 512;*/
            pwm_setDuty(pwm_m1, 1000);
            pwm_setDuty(pwm_m2, 1000);
        }
        else
        {
            /*OC3R = 200;
            OC3RS = 200;

            OC4R = 200;
            OC4RS = 200;*/
            pwm_setDuty(pwm_m1, 500);
            pwm_setDuty(pwm_m2, 500);
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
