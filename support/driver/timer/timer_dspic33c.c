/**
 * @file timer_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date June 01, 2018, 05:28 PM
 *
 * @brief Timer support for udevkit dsPIC33CH, dsPIC33CK
 *
 * Implementation based on Microchip document DS70005279B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-Timer1-Module-70005279B.pdf
 */

#include "timer.h"

#include <archi.h>
#include <driver/sysclock.h>

#if !defined(TIMER_COUNT) || TIMER_COUNT == 0
#    warning "No timer on the current device or unknow device"
#endif

enum
{
    TIMER_FLAG_UNUSED = 0x00
};
typedef struct
{
    union
    {
        struct
        {
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
    uint32_t periodUs;
    timer_status flags;
    void (*handler)(void);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

static struct timer_dev _timers[] = {
#if TIMER_COUNT >= 1
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
};

#if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE) && !defined(TIMER1_INT_DISABLE)
void _T1Interrupt(void);
#endif

/**
 * @brief Gives a free timer device number
 * @return timer device number
 */
rt_dev_t timer_getFreeDevice(void)
{
#if TIMER_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < TIMER_COUNT; i++)
    {
        if (_timers[i].flags.used == 0)
        {
            break;
        }
    }

    if (i == TIMER_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_TIMER, i);

    timer_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open a timer
 * @param device timer device number
 */
int timer_open(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }
    if (_timers[timer].flags.used == 1)
    {
        return -1;
    }

    _timers[timer].flags.used = 1;
    _timers[timer].handler = NULL;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Close a timer
 * @param device timer device number
 */
int timer_close(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    timer_disable(device);

    _timers[timer].flags.val = TIMER_FLAG_UNUSED;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Timer sdk state
 * @param device timer device number
 * @return true if timer was openned by timer_open function
 */
bool timer_isOpened(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    return (_timers[timer].flags.used == 1);
}

/**
 * @brief Enable the specified timer device
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_enable(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].flags.enabled = 1;

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            T1CONbits.TON = 1;  // enable timer module
            _T1IF = 0;
            if (_timers[TIMER1_ID].handler)
            {
                _T1IE = 1;
            }
            else
            {
                _T1IE = 0;
            }
            _T1IP = 1;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disable the specified timer device
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_disable(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].flags.enabled = 0;

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            T1CONbits.TON = 0;  // disable timer module
            _T1IE = 0;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Timer sdk enabled state
 * @param device timer device number
 * @return true if timer was enabled by timer_enable function
 */
bool timer_isEnabled(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    return (_timers[timer].flags.enabled == 1);
}

/**
 * @brief Sets the handler function that will be called on timer interrupt
 * @param device timer device number
 * @param handler void funtion pointer or null to remove the handler
 * @return 0 if ok, -1 in case of error
 */
int timer_setHandler(rt_dev_t device, void (*handler)(void))
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].handler = handler;
    if (_timers[timer].flags.enabled == 1)
    {
        timer_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the internal period
 * @param device timer device number
 * @param prvalue reset value of timer, does not consider the time
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriod(rt_dev_t device, uint32_t prvalue)
{
#if TIMER_COUNT >= 1
    uint8_t divisor = 0;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    if (prvalue > 65535)
    {
        divisor = 0b01;  // 8 divider
        prvalue >>= 3;
        if (prvalue > 65535)
        {
            divisor = 0b11;  // 256 divider
            prvalue >>= 5;
            if (prvalue > 65535)
            {
                prvalue = 65535;
            }
        }
    }

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            T1CONbits.TCKPS = divisor;  // set divide number
            PR1 = prvalue;              // pr value, comparator value
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Gets the internal period
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
uint32_t timer_period(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            return PR1;
#    endif
    }
    return -1;
#else
    return -1;
#endif
}

/**
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs)
{
#if TIMER_COUNT >= 1
    uint32_t prvalue;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodUs = periodMs * 1000;

    prvalue = sysclock_periphFreq(SYSCLOCK_CLOCK_TIMER) / 1000 * periodMs;
    timer_setPeriod(device, prvalue);

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodUs(rt_dev_t device, uint32_t periodUs)
{
#if TIMER_COUNT >= 1
    float prvalue;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodUs = periodUs;

    uint32_t freqCCp = sysclock_periphFreq(SYSCLOCK_CLOCK_TIMER);
    prvalue = (float)freqCCp / 1000000.0 * (float)periodUs;

    return timer_setPeriod(device, (uint32_t)prvalue);
#else
    return -1;
#endif
}

/**
 * @brief Returns the current period in us
 * @param device timer device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t timer_periodUs(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return 0;
    }

    return _timers[timer].periodUs;
#else
    return 0;
#endif
}

/**
 * @brief Returns the current period in us
 * @param device timer device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t timer_periodMs(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return 0;
    }

    return _timers[timer].periodUs / 1000;
#else
    return 0;
#endif
}

/**
 * @brief Returns the current value of timer
 * @param device timer device number
 * @return value if ok, 0 in case of error
 */
uint16_t timer_value(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint16_t value;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return 0;
    }

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            value = TMR1;
            break;
#    endif
    }

    return value;
#else
    return 0;
#endif
}

/**
 * @brief Sets the current value of timer
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setValue(rt_dev_t device, uint16_t value)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            TMR1 = value;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

#if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE) && !defined(TIMER1_INT_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _T1Interrupt(void)
{
    if (_timers[TIMER1_ID].handler)
    {
        (*_timers[TIMER1_ID].handler)();
    }

    _T1IF = 0;
}
#endif

/**
 * @brief Reconfigure clocks for all activated TIMERs devices. Call this function on clock change.
 */
void timer_reconfig(void)
{
    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        if (_timers[i].flags.used == 1 && _timers[i].periodUs != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_TIMER, i);
            timer_setPeriodUs(device, _timers[i].periodUs);
        }
    }
}
