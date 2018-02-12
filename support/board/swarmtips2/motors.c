#include "motors.h"

#include "modules.h"
#include "board.h"

Motors_State motors_state_i = Motors_State_Stop;
uint8_t motors_stop_i = 1;
int16_t motors_speed_i = 0;
int fc1 = 0, fc2 = 0;

rt_dev_t pwm_m1, pwm_m2;

// ========================== coders ===============================
int c1 = 0, c2 = 0;
int8_t c1_state = 0, c2_state = 0;
const signed char encoder_value[16] = { 0, -1,  1,  0,
                                        1,  0,  0, -1,
                                       -1,  0,  0,  1,
                                        0,  1, -1,  0};

void process_coder()
{
	// c1_state => 0b0000 & previous_A & previous_B & A & B
	c1_state = (c1_state<<2) & 0b00001100;
	if (C1A == 1)
        c1_state+=2;
	if (C1B == 1)
        c1_state+=1;
	c1 += encoder_value[c1_state];

	// c2_state => 0b0000 & previous_A & previous_B & A & B
	c2_state = (c2_state<<2) & 0b00001100;
	if (C2A == 1)
        c2_state+=1;
	if (C2B == 1)
        c2_state+=2;
	c2 += encoder_value[c2_state];

    motors_task();
}

int getC1()
{
    return c1;
}

int getC2()
{
    return c2;
}

void motors_applyCommand(int16_t m1, int16_t m2)
{
    if (m1 > 0)
    {
        #ifndef SIMULATOR
            M1DIR = 1;
        #endif
        pwm_setDuty(pwm_m1, 1000 - m1);
    }
    else
    {
        #ifndef SIMULATOR
            M1DIR = 0;
        #endif
        pwm_setDuty(pwm_m1, m1);
    }
    if (m2 > 0)
    {
        #ifndef SIMULATOR
            M2DIR = 1;
        #endif
        pwm_setDuty(pwm_m2, 1000 - m2);
    }
    else
    {
        #ifndef SIMULATOR
            M2DIR = 0;
        #endif
        pwm_setDuty(pwm_m2, m2);
    }
    if (m1 == 0 && m2 == 0)
    {
        #ifndef SIMULATOR
            BOOST_SLEEP = 1;
        #endif
    }
    else
    {
        #ifndef SIMULATOR
            BOOST_SLEEP = 0;
        #endif
    }
}

void motors_init()
{
    // timer coders
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1);
    timer_setHandler(timer, process_coder);
    timer_enable(timer);

    // motors pwm
    pwm_m1 = pwm(3);
    pwm_open(pwm_m1);
    oc_setTimer(oc(3), 1);
    pwm_setFreq(pwm_m1, 20000);
    pwm_enable(pwm_m1);

    pwm_m2 = pwm(4);
    pwm_open(pwm_m2);
    oc_setTimer(oc(4), 1);
    pwm_setFreq(pwm_m2, 20000);
    pwm_enable(pwm_m2);

    motors_applyCommand(0, 0);
}

void motors_moveForward(int16_t distance)
{
    motors_state_i = Motors_State_Linear;

    fc1 = c1 + (float)distance / 1.1;
    fc2 = c2 + (float)distance / 1.1;
}

void motors_rotate(int16_t angle)
{
    motors_state_i = Motors_State_Rotate;

    fc1 = c1 + (float)angle / 1.85;
    fc2 = c2 - (float)angle / 1.85;
}

void motors_task()
{
    int16_t err1, err2;
    if (motors_stop_i == 1 || motors_state_i == Motors_State_Stop)
    {
        motors_applyCommand(0, 0);
        return;
    }

    err1 = (fc1 - c1) * 30;
    if (err1 > -100 && err1 < 100)
        err1 = 0;
    if (err1 > motors_speed_i)
        err1 = motors_speed_i;
    if (err1 < -motors_speed_i)
        err1 = -motors_speed_i;

    err2 = (fc2 - c2) * 30;
    if (err2 > -100 && err2 < 100)
        err2 = 0;
    if (err2 > motors_speed_i)
        err2 = motors_speed_i;
    if (err2 < -motors_speed_i)
        err2 = -motors_speed_i;

    if (err1 == 0 && err2 == 0)
        motors_state_i = Motors_State_Stop;

    motors_applyCommand(err1, err2);
}

void motors_start()
{
    motors_stop_i = 0;
}

void motors_stop()
{
    motors_stop_i = 1;
}

void motors_setSpeed(int16_t speed)
{
    motors_speed_i = speed;
}

Motors_State motors_state()
{
    return motors_state_i;
}
