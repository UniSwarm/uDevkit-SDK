#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "ihm.h"

extern int ihm_d1, ihm_d2, ihm_d3;
extern int ihm_c1, ihm_c2;
extern float ihm_batt;

int c1 = 0, c2 = 0;
int8_t c1_state = 0, c2_state = 0;
const signed char encoder_value[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
void process_coder()
{
	// c1_state => 0b0000 & previous_A & previous_B & A & B
	c1_state = (c1_state<<2) & 0b00001100;
	if (C1A == 1)
        c1_state+=2;
	if (C1B == 1)
        c1_state+=1;
	c1 += encoder_value[c1_state];
    ihm_c1 = c1;

	// c2_state => 0b0000 & previous_A & previous_B & A & B
	c2_state = (c2_state<<2) & 0b00001100;
	if (C2A == 1)
        c2_state+=1;
	if (C2B == 1)
        c2_state+=2;
	c2 += encoder_value[c2_state];
    ihm_c2 = c2;
}

int main(void)
{
    unsigned int i, j;
    int16_t value;

    init_archi();
    board_init();

    // module init
    network_init();

    for (j=0;j<5;j++)
        for (i=0;i<65000;i++);
    value = sysclock_source();
    board_setLed(1, 1);

    // screen test
    ihm_init();

    // timer coders
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1);
    timer_setHandler(timer, process_coder);
    timer_enable(timer);

    // motors test
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
