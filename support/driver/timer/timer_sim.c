/**
 * @file timer_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date September 27, 2016, 11:37 AM
 *
 * @brief Timer support for udevkit for simulation purpose
 */

#include "simulator.h"
#include "timer.h"

#include "driver/sysclock.h"

#if !defined(TIMER_COUNT) || TIMER_COUNT == 0
#    warning "No uart on the current device or unknow device"
#endif

#define TIMER_FLAG_UNUSED 0x00
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
    pthread_t thread_timer;
    uint32_t periodUs;
    uint32_t value;
    timer_status flags;
    void (*handler)(void);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

static struct timer_dev _timers[] = {
#if TIMER_COUNT >= 1
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 2
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 3
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 4
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 5
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 6
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 7
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 8
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
#if TIMER_COUNT >= 9
    {.periodUs = 1000, .value = 0, .flags = {{.val = TIMER_FLAG_UNUSED}}, .handler = NULL},
#endif
};

#if TIMER_COUNT >= 1 && !defined(TIMER1_DISABLE)
static void *_timer1_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        usleep(_timers[0].periodUs);
        _timers[0].value++;
        if (_timers[0].handler)
        {
            (*_timers[0].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 2 && !defined(TIMER2_DISABLE)
static void *_timer2_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[1].periodUs);
        _timers[1].value++;
        if (_timers[1].handler)
        {
            (*_timers[1].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 3 && !defined(TIMER3_DISABLE)
static void *_timer3_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[2].periodUs);
        _timers[2].value++;
        if (_timers[2].handler)
        {
            (*_timers[2].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 4 && !defined(TIMER4_DISABLE)
static void *_timer4_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[3].periodUs);
        _timers[3].value++;
        if (_timers[3].handler)
        {
            (*_timers[3].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 5 && !defined(TIMER5_DISABLE)
static void *_timer5_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[4].periodUs);
        _timers[4].value++;
        if (_timers[4].handler)
        {
            (*_timers[4].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 6 && !defined(TIMER6_DISABLE)
static void *_timer6_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[5].periodUs);
        _timers[5].value++;
        if (_timers[5].handler)
        {
            (*_timers[5].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 7 && !defined(TIMER7_DISABLE)
static void *_timer7_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[6].periodUs);
        _timers[6].value++;
        if (_timers[6].handler)
        {
            (*_timers[6].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 8 && !defined(TIMER8_DISABLE)
static void *_timer8_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[7].periodUs);
        _timers[7].value++;
        if (_timers[7].handler)
        {
            (*_timers[7].handler)();
        }
    }
    return NULL;
}
#endif

#if TIMER_COUNT >= 9 && !defined(TIMER9_DISABLE)
static void *_timer9_thread(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(_timers[8].periodUs);
        _timers[8].value++;
        if (_timers[8].handler)
        {
            (*_timers[8].handler)();
        }
    }
    return NULL;
}
#endif

/**
 * @brief Gives a free timer device number
 * @return timer device number
 */
rt_dev_t timer_getFreeDevice(void)
{
    uint8_t i;

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

    _timers[i].flags.used = 1;

    return MKDEV(DEV_CLASS_TIMER, i);
}

/**
 * @brief Open a timer
 * @param device timer device number
 */
int timer_open(rt_dev_t device)
{
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
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].flags.enabled = 1;

    switch (timer)
    {
#if TIMER_COUNT >= 1 && !defined(TIMER1_DISABLE)
        case 0:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer1_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 2 && !defined(TIMER2_DISABLE)
        case 1:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer2_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 3 && !defined(TIMER3_DISABLE)
        case 2:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer3_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 4 && !defined(TIMER4_DISABLE)
        case 3:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer4_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 5 && !defined(TIMER5_DISABLE)
        case 4:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer5_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 6 && !defined(TIMER6_DISABLE)
        case 5:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer6_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 7 && !defined(TIMER7_DISABLE)
        case 6:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer7_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 8 && !defined(TIMER8_DISABLE)
        case 7:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer8_thread, NULL);
            break;
#endif
#if TIMER_COUNT >= 9 && !defined(TIMER9_DISABLE)
        case 8:
            pthread_create(&_timers[timer].thread_timer, NULL, _timer9_thread, NULL);
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
    {
        return -1;
    }

    _timers[timer].flags.enabled = 0;

    pthread_cancel(_timers[timer].thread_timer);

    return 0;
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
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].handler = handler;

    return 0;
}

/**
 * @brief Sets the internal period
 * @param device timer device number
 * @param prvalue reset value of timer, does not consider the time
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriod(rt_dev_t device, uint32_t prvalue)
{
    UDK_UNUSED(device);
    UDK_UNUSED(prvalue);
    // TODO implement me !
    return 0;
}

/**
 * @brief Gets the internal period
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
uint32_t timer_period(rt_dev_t device)
{
    UDK_UNUSED(device);
    // TODO implement me !
    return 0;
}

/**
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodUs = periodMs * 1000;

    return 0;
}

/**
 * @brief Returns the current period in us
 * @param device timer device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t timer_periodMs(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return 0;
    }

    return _timers[timer].periodUs / 1000;
}

/**
 * @brief Sets the period in us of the timer module to work in timer mode
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setPeriodUs(rt_dev_t device, uint32_t periodUs)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].periodUs = periodUs;

    return 0;
}

/**
 * @brief Returns the current period in us
 * @param device timer device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t timer_periodUs(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return 0;
    }

    return _timers[timer].periodUs;
}

/**
 * @brief Returns the current value of timer
 * @param device timer device number
 * @return value if ok, 0 in case of error
 */
uint16_t timer_value(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return 0;
    }

    return _timers[timer].value;
}

/**
 * @brief Sets the current value of timer
 * @param device timer device number
 * @return 0 if ok, -1 in case of error
 */
int timer_setValue(rt_dev_t device, uint16_t value)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
    {
        return -1;
    }

    _timers[timer].value = value;

    return 0;
}

/**
 * @brief Reconfigure clocks for all activated TIMERs devices. Call this function on clock change.
 */
void timer_reconfig(void)
{
}
