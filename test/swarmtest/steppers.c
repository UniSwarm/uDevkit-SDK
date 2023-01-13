
#include "board.h"
#include "modules.h"

#define MMAX  1200
#define MMAX2 800

int16_t stepper_speed;
rt_dev_t stepper_timer;

void setup_PWM(void)
{
#ifndef SIMULATOR
    OC1CON1 = 0b0001110000000110;
    OC1CON2 = 0b0000000000011111;
    OC1R = 0;
    OC1RS = 1500;  // 20kz

    OC2CON1 = 0b0001110000000110;
    OC2CON2 = 0b0000000000011111;
    OC2R = 0;
    OC2RS = 1500;  // 20kz

    OC3CON1 = 0b0001110000000110;
    OC3CON2 = 0b0000000000011111;
    OC3R = 0;
    OC3RS = 1500;  // 20kz

    OC4CON1 = 0b0001110000000110;
    OC4CON2 = 0b0000000000011111;
    OC4R = 0;
    OC4RS = 1500;  // 20kz
#endif
}

void setM1A(short v)
{
    if (v >= 0)
    {
#ifndef SIMULATOR
        OC1R = v;
        OC1CON2bits.OCINV = 0;
        M1A = 0;
#endif
    }
    else
    {
#ifndef SIMULATOR
        OC1R = -v;
        OC1CON2bits.OCINV = 1;
        M1A = 1;
#endif
    }
}
void setM1B(short v)
{
    if (v >= 0)
    {
#ifndef SIMULATOR
        OC2R = v;
        OC2CON2bits.OCINV = 0;
        M1B = 0;
#endif
    }
    else
    {
#ifndef SIMULATOR
        OC2R = -v;
        OC2CON2bits.OCINV = 1;
        M1B = 1;
#endif
    }
}

void setM2A(short v)
{
    if (v >= 0)
    {
#ifndef SIMULATOR
        OC3R = v;
        OC3CON2bits.OCINV = 0;
        M2A = 0;
#endif
    }
    else
    {
#ifndef SIMULATOR
        OC3R = -v;
        OC3CON2bits.OCINV = 1;
        M2A = 1;
#endif
    }
}
void setM2B(short v)
{
    if (v >= 0)
    {
#ifndef SIMULATOR
        OC4R = v;
        OC4CON2bits.OCINV = 0;
        M2B = 0;
#endif
    }
    else
    {
#ifndef SIMULATOR
        OC4R = -v;
        OC4CON2bits.OCINV = 1;
        M2B = 1;
#endif
    }
}

void stepper_handler()
{
    static uint8_t step = 0;
    switch (step)
    {
        case 0:
            board_setLed(0, 0);
            setM1A(MMAX2);
            setM1B(MMAX2);
            setM2A(MMAX2);
            setM2B(MMAX2);
            break;

        case 1:
            setM1A(0);
            setM1B(MMAX);
            setM2A(0);
            setM2B(MMAX);
            break;

        case 2:
            setM1A(-MMAX2);
            setM1B(MMAX2);
            setM2A(-MMAX2);
            setM2B(MMAX2);
            break;

        case 3:
            setM1A(-MMAX);
            setM1B(0);
            setM2A(-MMAX);
            setM2B(0);
            break;

        case 4:
            board_setLed(0, 1);
            setM1A(-MMAX2);
            setM1B(-MMAX2);
            setM2A(-MMAX2);
            setM2B(-MMAX2);
            break;

        case 5:
            setM1A(0);
            setM1B(-MMAX);
            setM2A(0);
            setM2B(-MMAX);
            break;

        case 6:
            setM1A(MMAX2);
            setM1B(-MMAX2);
            setM2A(MMAX2);
            setM2B(-MMAX2);
            break;

        case 7:
            setM1A(MMAX);
            setM1B(0);
            setM2A(MMAX);
            setM2B(0);
            break;
    }

    step++;
    if (step >= 8)
        step = 0;
}

void steppers_init()
{
    setup_PWM();

    stepper_timer = timer_getFreeDevice();
    timer_setPeriodMs(stepper_timer, 100);
    timer_setHandler(stepper_timer, stepper_handler);
    timer_enable(stepper_timer);
}

void steppers_stop()
{
    timer_disable(stepper_timer);
}

void steppers_start()
{
    timer_enable(stepper_timer);
}

void steppers_setSpeed(int16_t speed)
{
    stepper_speed = speed;
    timer_setPeriodMs(stepper_timer, speed);
}
