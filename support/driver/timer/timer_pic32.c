/**
 * @file timer_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 01, 2016, 20:45 PM
 *
 * @brief Timer support for udevkit for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61105F :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf
 */

#include "timer.h"

#include <archi.h>
#include <driver/int.h>
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

#ifndef INT_MODE
#    define INT_MODE INT_DEFAULT_MODE
#endif
#ifndef TIMER_INTERRUPT_PRIORITY
#    define TIMER_INTERRUPT_PRIORITY 4
#endif
#ifndef TIMER1_INT_PRIORITY
#    define TIMER1_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER2_INT_PRIORITY
#    define TIMER2_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER3_INT_PRIORITY
#    define TIMER3_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER4_INT_PRIORITY
#    define TIMER4_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER5_INT_PRIORITY
#    define TIMER5_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER6_INT_PRIORITY
#    define TIMER6_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER7_INT_PRIORITY
#    define TIMER7_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER8_INT_PRIORITY
#    define TIMER8_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif
#ifndef TIMER9_INT_PRIORITY
#    define TIMER9_INT_PRIORITY TIMER_INTERRUPT_PRIORITY
#endif

static struct timer_dev _timers[] = {
#if TIMER_COUNT >= 1
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 2
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 3
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 4
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 5
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 6
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 7
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 8
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 9
    {.periodUs = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
};

#if (TIMER_COUNT >= 1) && !defined(TIMER1_DISABLE)
void T1Interrupt(void);
#endif
#if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
void T2Interrupt(void);
#endif
#if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
void T3Interrupt(void);
#endif
#if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
void T4Interrupt(void);
#endif
#if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
void T5Interrupt(void);
#endif
#if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
void T6Interrupt(void);
#endif
#if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
void T7Interrupt(void);
#endif
#if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
void T8Interrupt(void);
#endif
#if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
void T9Interrupt(void);
#endif

/**
 * @brief Gives a free timer device number
 * @return timer device number
 */
rt_dev_t timer_getFreeDevice(void)
{
#if TIMER_COUNT >= 1
    uint8_t timer_id;
    for (timer_id = 0; timer_id < TIMER_COUNT; timer_id++)
    {
        if (_timers[timer_id].flags.used == 0)
        {
            break;
        }
    }

    if (timer_id == TIMER_COUNT)
    {
        return NULLDEV;
    }
    rt_dev_t device = MKDEV(DEV_CLASS_TIMER, timer_id);

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
        case 0:
            T1CONbits.ON = 1;  // enable timer module
            _T1IF = 0;
            _T1IE = (_timers[0].handler != NULL) ? 1 : 0;
            _T1IP = TIMER1_INT_PRIORITY;
            break;
#    if TIMER_COUNT >= 2
        case 1:
            T2CONbits.ON = 1;  // enable timer module
            _T2IF = 0;
            _T2IE = (_timers[1].handler != NULL) ? 1 : 0;
            _T2IP = TIMER2_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 3
        case 2:
            T3CONbits.ON = 1;  // enable timer module
            _T3IF = 0;
            _T3IE = (_timers[2].handler != NULL) ? 1 : 0;
            _T3IP = TIMER3_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 4
        case 3:
            T4CONbits.ON = 1;  // enable timer module
            _T4IF = 0;
            _T4IE = (_timers[3].handler != NULL) ? 1 : 0;
            _T4IP = TIMER4_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 5
        case 4:
            T5CONbits.ON = 1;  // enable timer module
            _T5IF = 0;
            _T5IE = (_timers[4].handler != NULL) ? 1 : 0;
            _T5IP = TIMER5_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 6
        case 5:
            T6CONbits.ON = 1;  // enable timer module
            _T6IF = 0;
            _T6IE = (_timers[5].handler != NULL) ? 1 : 0;
            _T6IP = TIMER6_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 7
        case 6:
            T7CONbits.ON = 1;  // enable timer module
            _T7IF = 0;
            _T7IE = (_timers[6].handler != NULL) ? 1 : 0;
            _T7IP = TIMER7_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 8
        case 7:
            T8CONbits.ON = 1;  // enable timer module
            _T8IF = 0;
            _T8IE = (_timers[7].handler != NULL) ? 1 : 0;
            _T8IP = TIMER8_INT_PRIORITY;
            break;
#    endif
#    if TIMER_COUNT >= 9
        case 8:
            T9CONbits.ON = 1;  // enable timer module
            _T9IF = 0;
            _T9IE = (_timers[8].handler != NULL) ? 1 : 0;
            _T9IP = TIMER9_INT_PRIORITY;
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
        case 0:
            T1CONbits.ON = 0;  // disable timer module
            _T1IE = 0;
            break;
#    if TIMER_COUNT >= 2
        case 1:
            T2CONbits.ON = 0;  // disable timer module
            _T2IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 3
        case 2:
            T3CONbits.ON = 0;  // disable timer module
            _T3IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 4
        case 3:
            T4CONbits.ON = 0;  // disable timer module
            _T4IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 5
        case 4:
            T5CONbits.ON = 0;  // disable timer module
            _T5IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 6
        case 5:
            T6CONbits.ON = 0;  // disable timer module
            _T6IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 7
        case 6:
            T7CONbits.ON = 0;  // disable timer module
            _T7IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 8
        case 7:
            T8CONbits.ON = 0;  // disable timer module
            _T8IE = 0;
            break;
#    endif
#    if TIMER_COUNT >= 9
        case 8:
            T9CONbits.ON = 0;  // disable timer module
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
 * @brief Sets the internal period
 * @param device timer device number
 * @param prvalue reset value of timer, does not consider the time
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriod(rt_dev_t device, uint32_t period)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    // TODO PR and TMR are 32 bit width on T2 to T9 on PIC32MK
    uint8_t divisor = 0;
    if (period > 65535)
    {
        divisor = 0b111;  // 256 divisor for type A (0b11) and for type B (0b111)
        period >>= 8;
        if (period > 65535)
        {
            period = 65535;
        }
    }

    switch (timer)
    {
        case 0:
            T1CONbits.TCKPS = divisor;  // set divide number
            PR1 = period;               // pr value, comparator value
            break;
#    if TIMER_COUNT >= 2
        case 1:
            T2CONbits.TCKPS = divisor;  // set divide number
            PR2 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 3
        case 2:
            T3CONbits.TCKPS = divisor;  // set divide number
            PR3 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 4
        case 3:
            T4CONbits.TCKPS = divisor;  // set divide number
            PR4 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 5
        case 4:
            T5CONbits.TCKPS = divisor;  // set divide number
            PR5 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 6
        case 5:
            T6CONbits.TCKPS = divisor;  // set divide number
            PR6 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 7
        case 6:
            T7CONbits.TCKPS = divisor;  // set divide number
            PR7 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 8
        case 7:
            T8CONbits.TCKPS = divisor;  // set divide number
            PR8 = period;               // pr value, comparator value
            break;
#    endif
#    if TIMER_COUNT >= 9
        case 8:
            T9CONbits.TCKPS = divisor;  // set divide number
            PR9 = period;               // pr value, comparator value
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
        case 0:
            return PR1;
#    if TIMER_COUNT >= 2
        case 1:
            return PR2;
#    endif
#    if TIMER_COUNT >= 3
        case 2:
            return PR3;
#    endif
#    if TIMER_COUNT >= 4
        case 3:
            return PR4;
#    endif
#    if TIMER_COUNT >= 5
        case 4:
            return PR5;
#    endif
#    if TIMER_COUNT >= 6
        case 5:
            return PR6;
#    endif
#    if TIMER_COUNT >= 7
        case 6:
            return PR7;
#    endif
#    if TIMER_COUNT >= 8
        case 7:
            return PR8;
#    endif
#    if TIMER_COUNT >= 9
        case 8:
            return PR9;
#    endif
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
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodUs = periodMs * 1000;

    float clockMs = sysclock_periphFreq(SYSCLOCK_CLOCK_TIMER);
    float prvalue = clockMs / 1000.0 * (float)periodMs;

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
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodUs(rt_dev_t device, uint32_t periodUs)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodUs = periodUs;

    float clockMs = sysclock_periphFreq(SYSCLOCK_CLOCK_TIMER);
    float prvalue = clockMs / 1000000.0 * (float)periodUs;

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
 * @brief Returns the current value of timer
 * @param device timer device number
 * @return value if ok, 0 in case of error
 */
uint16_t timer_value(rt_dev_t device)
{
#if TIMER_COUNT >= 1
    uint8_t timer = MINOR(device);

    switch (timer)
    {
        case 0:
            return TMR1;
#    if TIMER_COUNT >= 2
        case 1:
            return TMR2;
#    endif
#    if TIMER_COUNT >= 3
        case 2:
            return TMR3;
#    endif
#    if TIMER_COUNT >= 4
        case 3:
            return TMR4;
#    endif
#    if TIMER_COUNT >= 5
        case 4:
            return TMR5;
#    endif
#    if TIMER_COUNT >= 6
        case 5:
            return TMR6;
#    endif
#    if TIMER_COUNT >= 7
        case 6:
            return TMR7;
#    endif
#    if TIMER_COUNT >= 8
        case 7:
            return TMR8;
#    endif
#    if TIMER_COUNT >= 9
        case 8:
            return TMR9;
#    endif
        default:
            return 0;
    }
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
        case 0:
            TMR1 = value;
            break;
#    if TIMER_COUNT >= 2
        case 1:
            TMR2 = value;
            break;
#    endif
#    if TIMER_COUNT >= 3
        case 2:
            TMR3 = value;
            break;
#    endif
#    if TIMER_COUNT >= 4
        case 3:
            TMR4 = value;
            break;
#    endif
#    if TIMER_COUNT >= 5
        case 4:
            TMR5 = value;
            break;
#    endif
#    if TIMER_COUNT >= 6
        case 5:
            TMR6 = value;
            break;
#    endif
#    if TIMER_COUNT >= 7
        case 6:
            TMR7 = value;
            break;
#    endif
#    if TIMER_COUNT >= 8
        case 7:
            TMR8 = value;
            break;
#    endif
#    if TIMER_COUNT >= 9
        case 8:
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
void INT_ISR(_TIMER_1_VECTOR, TIMER1_INT_PRIORITY, INT_MODE) __attribute__((weak)) T1Interrupt(void)
{
    if (_timers[0].handler != NULL)
    {
        (*_timers[0].handler)();
    }

    _T1IF = 0;
}
#endif

#if (TIMER_COUNT >= 2) && !defined(TIMER2_DISABLE)
void INT_ISR(_TIMER_2_VECTOR, TIMER2_INT_PRIORITY, INT_MODE) __attribute__((weak)) T2Interrupt(void)
{
    if (_timers[1].handler != NULL)
    {
        (*_timers[1].handler)();
    }

    _T2IF = 0;
}
#endif

#if (TIMER_COUNT >= 3) && !defined(TIMER3_DISABLE)
void INT_ISR(_TIMER_3_VECTOR, TIMER3_INT_PRIORITY, INT_MODE) __attribute__((weak)) T3Interrupt(void)
{
    if (_timers[2].handler != NULL)
    {
        (*_timers[2].handler)();
    }

    _T3IF = 0;
}
#endif

#if (TIMER_COUNT >= 4) && !defined(TIMER4_DISABLE)
void INT_ISR(_TIMER_4_VECTOR, TIMER4_INT_PRIORITY, INT_MODE) __attribute__((weak)) T4Interrupt(void)
{
    if (_timers[3].handler != NULL)
    {
        (*_timers[3].handler)();
    }

    _T4IF = 0;
}
#endif

#if (TIMER_COUNT >= 5) && !defined(TIMER5_DISABLE)
void INT_ISR(_TIMER_5_VECTOR, TIMER5_INT_PRIORITY, INT_MODE) __attribute__((weak)) T5Interrupt(void)
{
    if (_timers[4].handler != NULL)
    {
        (*_timers[4].handler)();
    }

    _T5IF = 0;
}
#endif

#if (TIMER_COUNT >= 6) && !defined(TIMER6_DISABLE)
void INT_ISR(_TIMER_6_VECTOR, TIMER6_INT_PRIORITY, INT_MODE) __attribute__((weak)) T6Interrupt(void)
{
    if (_timers[5].handler != NULL)
    {
        (*_timers[5].handler)();
    }

    _T6IF = 0;
}
#endif

#if (TIMER_COUNT >= 7) && !defined(TIMER7_DISABLE)
void INT_ISR(_TIMER_7_VECTOR, TIMER7_INT_PRIORITY, INT_MODE) __attribute__((weak)) T7Interrupt(void)
{
    if (_timers[6].handler != NULL)
    {
        (*_timers[6].handler)();
    }

    _T7IF = 0;
}
#endif

#if (TIMER_COUNT >= 8) && !defined(TIMER8_DISABLE)
void INT_ISR(_TIMER_8_VECTOR, TIMER8_INT_PRIORITY, INT_MODE) __attribute__((weak)) T8Interrupt(void)
{
    if (_timers[7].handler != NULL)
    {
        (*_timers[7].handler)();
    }

    _T8IF = 0;
}
#endif

#if (TIMER_COUNT >= 9) && !defined(TIMER9_DISABLE)
void INT_ISR(_TIMER_9_VECTOR, TIMER9_INT_PRIORITY, INT_MODE) __attribute__((weak)) T9Interrupt(void)
{
    if (_timers[8].handler != NULL)
    {
        (*_timers[8].handler)();
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
        if (_timers[i].flags.used == 1 && _timers[i].periodUs != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_TIMER, i);
            timer_setPeriodUs(device, _timers[i].periodUs);
        }
    }
}
