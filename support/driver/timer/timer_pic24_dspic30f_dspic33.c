/**
 * @file timer_pic24_dspic30f_dspic33.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date September 27, 2016, 11:37 AM
 *
 * @brief Timer support for udevkit dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip document DS70362B, DS39704A, DS70059D :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/S11.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/39704a.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70059D.pdf
 */

#include "timer.h"

#include <archi.h>
#include <driver/sysclock.h>

#if !defined(TIMER_COUNT) || TIMER_COUNT == 0
#    warning "No uart on the current device or unknow device"
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
    uint32_t periodMs;
    timer_status flags;
    void (*handler)(void);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

static struct timer_dev _timers[] = {
#if TIMER_COUNT >= 1
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 2
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 3
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 4
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 5
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 6
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 7
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 8
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 9
    {.periodMs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
};

#if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
void _T1Interrupt(void);
#endif
#if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
void _T2Interrupt(void);
#endif
#if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
void _T3Interrupt(void);
#endif
#if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
void _T4Interrupt(void);
#endif
#if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
void _T5Interrupt(void);
#endif
#if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
void _T6Interrupt(void);
#endif
#if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
void _T7Interrupt(void);
#endif
#if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
void _T8Interrupt(void);
#endif
#if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
void _T9Interrupt(void);
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
            _T1IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
        case TIMER2_ID:
            T2CONbits.TON = 1;  // enable timer module
            _T2IF = 0;
            if (_timers[TIMER2_ID].handler)
            {
                _T2IE = 1;
            }
            else
            {
                _T2IE = 0;
            }
            _T2IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
        case TIMER3_ID:
            T3CONbits.TON = 1;  // enable timer module
            _T3IF = 0;
            if (_timers[TIMER3_ID].handler)
            {
                _T3IE = 1;
            }
            else
            {
                _T3IE = 0;
            }
            _T3IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
        case TIMER4_ID:
            T4CONbits.TON = 1;  // enable timer module
            _T4IF = 0;
            if (_timers[TIMER4_ID].handler)
            {
                _T4IE = 1;
            }
            else
            {
                _T4IE = 0;
            }
            _T4IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
        case TIMER5_ID:
            T5CONbits.TON = 1;  // enable timer module
            _T5IF = 0;
            if (_timers[TIMER5_ID].handler)
            {
                _T5IE = 1;
            }
            else
            {
                _T5IE = 0;
            }
            _T5IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
        case TIMER6_ID:
            T6CONbits.TON = 1;  // enable timer module
            _T6IF = 0;
            if (_timers[TIMER6_ID].handler)
            {
                _T6IE = 1;
            }
            else
            {
                _T6IE = 0;
            }
            _T6IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
        case TIMER7_ID:
            T7CONbits.TON = 1;  // enable timer module
            _T7IF = 0;
            if (_timers[TIMER7_ID].handler)
            {
                _T7IE = 1;
            }
            else
            {
                _T7IE = 0;
            }
            _T7IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
        case TIMER8_ID:
            T8CONbits.TON = 1;  // enable timer module
            _T8IF = 0;
            if (_timers[TIMER8_ID].handler)
            {
                _T8IE = 1;
            }
            else
            {
                _T8IE = 0;
            }
            _T8IP = 4;
            break;
#    endif
#    if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
        case TIMER9_ID:
            T9CONbits.TON = 1;  // enable timer module
            _T9IF = 0;
            if (_timers[TIMER9_ID].handler)
            {
                _T9IE = 1;
            }
            else
            {
                _T9IE = 0;
            }
            _T9IP = 4;
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
#    if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
        case TIMER2_ID:
            T2CONbits.TON = 0;  // disable timer module
            _T2IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
        case TIMER3_ID:
            T3CONbits.TON = 0;  // disable timer module
            _T3IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
        case TIMER4_ID:
            T4CONbits.TON = 0;  // disable timer module
            _T4IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
        case TIMER5_ID:
            T5CONbits.TON = 0;  // disable timer module
            _T5IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
        case TIMER6_ID:
            T6CONbits.TON = 0;  // disable timer module
            _T6IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
        case TIMER7_ID:
            T7CONbits.TON = 0;  // disable timer module
            _T7IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
        case TIMER8_ID:
            T8CONbits.TON = 0;  // disable timer module
            _T8IE = 0;
            break;
#    endif
#    if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
        case TIMER9_ID:
            T9CONbits.TON = 0;  // disable timer module
            _T9IE = 0;
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
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs)
{
#if TIMER_COUNT >= 1
    uint32_t prvalue;
    uint8_t div = 0;
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodMs = periodMs;

    prvalue = sysclock_periphFreq(SYSCLOCK_CLOCK_TIMER) / 1000 * periodMs;
    if (prvalue > 65535)
    {
        div = 0b11;
        prvalue >>= 8;
        if (prvalue > 65535)
        {
            prvalue = 65535;
        }
    }

    switch (timer)
    {
#    if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
        case TIMER1_ID:
            T1CONbits.TCKPS = div;  // set divide number
            PR1 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
        case TIMER2_ID:
            T2CONbits.TCKPS = div;  // set divide number
            PR2 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
        case TIMER3_ID:
            T3CONbits.TCKPS = div;  // set divide number
            PR3 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
        case TIMER4_ID:
            T4CONbits.TCKPS = div;  // set divide number
            PR4 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
        case TIMER5_ID:
            T5CONbits.TCKPS = div;  // set divide number
            PR5 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
        case TIMER6_ID:
            T6CONbits.TCKPS = div;  // set divide number
            PR6 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
        case TIMER7_ID:
            T7CONbits.TCKPS = div;  // set divide number
            PR7 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
        case TIMER8_ID:
            T8CONbits.TCKPS = div;  // set divide number
            PR8 = prvalue;          // pr value, comparator value
            break;
#    endif
#    if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
        case TIMER9_ID:
            T9CONbits.TCKPS = div;  // set divide number
            PR9 = prvalue;          // pr value, comparator value
            break;
#    endif
    }

    return 0;
#else
    return -1;
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

    return _timers[timer].periodMs;
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
#    if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
        case TIMER2_ID:
            value = TMR2;
            break;
#    endif
#    if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
        case TIMER3_ID:
            value = TMR3;
            break;
#    endif
#    if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
        case TIMER4_ID:
            value = TMR4;
            break;
#    endif
#    if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
        case TIMER5_ID:
            value = TMR5;
            break;
#    endif
#    if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
        case TIMER6_ID:
            value = TMR6;
            break;
#    endif
#    if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
        case TIMER7_ID:
            value = TMR7;
            break;
#    endif
#    if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
        case TIMER8_ID:
            value = TMR8;
            break;
#    endif
#    if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
        case TIMER9_ID:
            value = TMR9;
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
#    if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
        case TIMER2_ID:
            TMR2 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
        case TIMER3_ID:
            TMR3 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
        case TIMER4_ID:
            TMR4 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
        case TIMER5_ID:
            TMR5 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
        case TIMER6_ID:
            TMR6 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
        case TIMER7_ID:
            TMR7 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
        case TIMER8_ID:
            TMR8 = value;
            break;
#    endif
#    if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
        case TIMER9_ID:
            TMR9 = value;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

#if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T1Interrupt(void)
{
    if (_timers[TIMER1_ID].handler)
    {
        (*_timers[TIMER1_ID].handler)();
    }

    _T1IF = 0;
}
#endif

#if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T2Interrupt(void)
{
    if (_timers[TIMER2_ID].handler)
    {
        (*_timers[TIMER2_ID].handler)();
    }

    _T2IF = 0;
}
#endif

#if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T3Interrupt(void)
{
    if (_timers[TIMER3_ID].handler)
    {
        (*_timers[TIMER3_ID].handler)();
    }

    _T3IF = 0;
}
#endif

#if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T4Interrupt(void)
{
    if (_timers[TIMER4_ID].handler)
    {
        (*_timers[TIMER4_ID].handler)();
    }

    _T4IF = 0;
}
#endif

#if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T5Interrupt(void)
{
    if (_timers[TIMER5_ID].handler)
    {
        (*_timers[TIMER5_ID].handler)();
    }

    _T5IF = 0;
}
#endif

#if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T6Interrupt(void)
{
    if (_timers[TIMER6_ID].handler)
    {
        (*_timers[TIMER6_ID].handler)();
    }

    _T6IF = 0;
}
#endif

#if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T7Interrupt(void)
{
    if (_timers[TIMER7_ID].handler)
    {
        (*_timers[TIMER7_ID].handler)();
    }

    _T7IF = 0;
}
#endif

#if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T8Interrupt(void)
{
    if (_timers[TIMER8_ID].handler)
    {
        (*_timers[TIMER8_ID].handler)();
    }

    _T8IF = 0;
}
#endif

#if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
void __attribute__((interrupt, no_auto_psv, weak)) _T9Interrupt(void)
{
    if (_timers[TIMER9_ID].handler)
    {
        (*_timers[TIMER9_ID].handler)();
    }

    _T9IF = 0;
}
#endif

/**
 * @brief Reconfigure clocks for all activated TIMERs devices. Call this function on clock change.
 */
void timer_reconfig(void)
{
    for (uint8_t i = 0; i < TIMER_COUNT; i++)
    {
        if (_timers[i].flags.used == 1 && _timers[i].periodMs != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_TIMER, i);
            timer_setPeriodMs(device, _timers[i].periodMs);
        }
    }
}
