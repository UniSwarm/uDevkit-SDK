#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

extern int ihm_d1, ihm_d2, ihm_d3;
extern float ihm_batt;

int main(void)
{
    unsigned int i, j;
    int16_t value;
    
    init_archi();
    board_init();

    // module init
    network_init();

    for(j=0;j<5;j++) for(i=0;i<65000;i++);
    value = sysclock_source();
    board_setLed(1, 1);

    // screen test

    ihm_init();

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
    
#ifndef SIMULATOR
    BOOST_SLEEP = 0;
    M1DIR = 1;
    pwm_setDuty(pwm_m1, 1000);
    M2DIR = 1;
    pwm_setDuty(pwm_m2, 1000);
#endif

    while(1)
    {
        #ifdef SIMULATOR
            usleep(1000);
        #endif
        network_task();
        ihm_task();
        ihm_batt = board_getPowerVoltage();

        value = VL6180X_getDistance(board_i2c_tof(), TOF1_ADDR);
        ihm_d1 = value;
        if(value < 15)
            value = 0;
        board_setLed(2, value);
        if(value < 50)
            board_setLed(3, 1);
        else
            board_setLed(3, 0);

        value = VL6180X_getDistance(board_i2c_tof(), TOF2_ADDR);
        ihm_d2 = value;
        if(value < 15)
            value = 0;
        board_setLed(1, value);
        if(value < 50)
        {
            pwm_setDuty(pwm_m1, 1000);
            pwm_setDuty(pwm_m2, 1000);
        }
        else
        {
            pwm_setDuty(pwm_m1, 500);
            pwm_setDuty(pwm_m2, 500);
        }

        value = VL6180X_getDistance(board_i2c_tof(), TOF3_ADDR);
        ihm_d3 = value;
        if(value < 15)
            value = 0;
        board_setLed(0, value);
        if(value < 50)
            board_setLed(4, 1);
        else
            board_setLed(4, 0);
    }

    return 0;
}
