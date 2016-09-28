/**
 * @file timer_pic24f_dspic33f_dspic30f.c
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date September 27, 2016, 11:37 AM
 *
 * @brief Timer support for rtprog (dsPIC33 family)
 */

#include "timer.h"

#include "driver/sysclock.h"

#include <xc.h>

#if !defined (TIMER_COUNT) || TIMER_COUNT==0
  #warning "No uart on the current device or unknow device"
#endif

#define TIMER_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned bit32 : 1;
            unsigned : 5;
        };
        uint8_t val;
    };
} timer_status;

struct timer_dev
{
    uint32_t periodMs;
    timer_status flags;
};

struct timer_dev timers[] = {
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#if TIMER_COUNT>=2
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=3
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=4
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=5
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=6
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=7
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=8
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=9
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=10
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
#if TIMER_COUNT>=11
    {
        .periodMs = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}}
    },
#endif
};

/**
 * @brief Gives a free timer device number
 * @return timer device number
 */
rt_dev_t timer_getFreeDevice()
{
    uint8_t i;

    for (i = 0; i < TIMER_COUNT; i++)
        if (timers[i].flags.used == 0)
            break;

    if (i == TIMER_COUNT)
        return NULLDEV;

    timers[i].flags.used = 1;

    return MKDEV(DEV_CLASS_TIMER, i);
}

/**
 * @brief Release a timer
 * @param device timer device number
 */
void timer_releaseDevice(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return;

    timers[timer].flags.val = TIMER_FLAG_UNUSED;
}

/**
 * @brief Enable the specified timer device
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_enable(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return -1;

    timers[timer].flags.enabled = 1;

    switch (timer)
    {
    case 0:
        T1CONbits.TON = 1;  // enable timer module
        break;
#if TIMER_COUNT>=2
    case 1:
        T2CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=3
    case 2:
        T3CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=4
    case 3:
        T4CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=5
    case 4:
        T5CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=6
    case 5:
        T6CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=7
    case 6:
        T7CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=8
    case 7:
        T8CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=9
    case 8:
        T9CONbits.TON = 1;  // enable timer module
        break;
#endif
#if TIMER_COUNT>=10
    case 9:
        T10CONbits.TON = 1; // enable timer module
        break;
#endif
#if TIMER_COUNT>=11
    case 10:
        T11CONbits.TON = 1; // enable timer module
        break;
#endif
    }

    return 0;
}

/**
 * @brief Disable the specified timer device
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_disable(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return -1;

    timers[timer].flags.enabled = 0;

    switch (timer)
    {
    case 0:
        T1CONbits.TON = 0;  // disable timer module
        break;
#if TIMER_COUNT>=2
    case 1:
        T2CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=3
    case 2:
        T3CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=4
    case 3:
        T4CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=5
    case 4:
        T5CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=6
    case 5:
        T6CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=7
    case 6:
        T7CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=8
    case 7:
        T8CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=9
    case 8:
        T9CONbits.TON = 0;  // disable timer module
        break;
#endif
#if TIMER_COUNT>=10
    case 9:
        T10CONbits.TON = 0; // disable timer module
        break;
#endif
#if TIMER_COUNT>=11
    case 10:
        T11CONbits.TON = 0; // disable timer module
        break;
#endif
    }

    return 0;
}

/**
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs)
{
    uint64_t prvalue;
    uint8_t div = 0;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return -1;

    timers[timer].periodMs = periodMs;

    prvalue = getSystemClockPeriph() / 1000 * periodMs;
    if(prvalue > 65535)
    {
        div = 0b11;
        prvalue <<= 8;
        if(prvalue > 65535)
            prvalue = 65535;
    }

    switch (timer)
    {
    case 0:
        T1CONbits.TCKPS = div;   // set divide number
        PR1 = prvalue;           // pr value, comparator value
        break;
#if TIMER_COUNT>=2
    case 1:
        T2CONbits.TCKPS = div;   // set divide number
        PR2 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=3
    case 2:
        T3CONbits.TCKPS = div;   // set divide number
        PR3 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=4
    case 3:
        T4CONbits.TCKPS = div;   // set divide number
        PR4 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=5
    case 4:
        T5CONbits.TCKPS = div;   // set divide number
        PR5 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=6
    case 5:
        T6CONbits.TCKPS = div;   // set divide number
        PR6 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=7
    case 6:
        T7CONbits.TCKPS = div;   // set divide number
        PR7 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=8
    case 7:
        T8CONbits.TCKPS = div;   // set divide number
        PR8 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=9
    case 8:
        T9CONbits.TCKPS = div;   // set divide number
        PR9 = prvalue;           // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=10
    case 9:
        T10CONbits.TCKPS = div;  // set divide number
        PR10 = prvalue;          // pr value, comparator value
        break;
#endif
#if TIMER_COUNT>=11
    case 10:
        T11CONbits.TCKPS = div;  // set divide number
        PR11 = prvalue;          // pr value, comparator value
        break;
#endif
    }

    return 0;
}

/**
 * @brief Returns the curent period in us
 * @param device timer device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t timer_periodMs(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return 0;

    return timers[timer].periodMs;
}

/**
 * @brief Returns the curent value of timer
 * @param device timer device number
 * @return value if ok, 0 in case of error
 */
uint16_t timer_getValue(rt_dev_t device)
{
    uint16_t value;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return 0;

    switch (timer)
    {
    case 0:
        value = TMR1;
        break;
#if TIMER_COUNT>=2
    case 1:
        value = TMR2;
        break;
#endif
#if TIMER_COUNT>=3
    case 2:
        value = TMR3;
        break;
#endif
#if TIMER_COUNT>=4
    case 3:
        value = TMR4;
        break;
#endif
#if TIMER_COUNT>=5
    case 4:
        value = TMR5;
        break;
#endif
#if TIMER_COUNT>=6
    case 5:
        value = TMR6;
        break;
#endif
#if TIMER_COUNT>=7
    case 6:
        value = TMR7;
        break;
#endif
#if TIMER_COUNT>=8
    case 7:
        value = TMR8;
        break;
#endif
#if TIMER_COUNT>=9
    case 8:
        value = TMR9;
        break;
#endif
#if TIMER_COUNT>=10
    case 9:
        value = TMR10;
        break;
#endif
#if TIMER_COUNT>=11
    case 10:
        value = TMR11;
        break;
#endif
    }

    return value;
}

/**
 * @brief Sets the curent value of timer
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setValue(rt_dev_t device, uint16_t value)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return -1;

    switch (timer)
    {
    case 0:
        TMR1 = value;
        break;
#if TIMER_COUNT>=2
    case 1:
        TMR2 = value;
        break;
#endif
#if TIMER_COUNT>=3
    case 2:
        TMR3 = value;
        break;
#endif
#if TIMER_COUNT>=4
    case 3:
        TMR4 = value;
        break;
#endif
#if TIMER_COUNT>=5
    case 4:
        TMR5 = value;
        break;
#endif
#if TIMER_COUNT>=6
    case 5:
        TMR6 = value;
        break;
#endif
#if TIMER_COUNT>=7
    case 6:
        TMR7 = value;
        break;
#endif
#if TIMER_COUNT>=8
    case 7:
        TMR8 = value;
        break;
#endif
#if TIMER_COUNT>=9
    case 8:
        TMR9 = value;
        break;
#endif
#if TIMER_COUNT>=10
    case 9:
        TMR10 = value;
        break;
#endif
#if TIMER_COUNT>=11
    case 10:
        TMR11 = value;
        break;
#endif
    }

    return 0;
}
