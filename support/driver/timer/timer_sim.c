/**
 * @file timer_sim.c
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016
 *
 * @date September 27, 2016, 11:37 AM
 *
 * @brief Timer support for udevkit for simulation purpose
 */

#include "timer.h"
#include "simulator.h"

#include "driver/sysclock.h"

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
    pthread_t thread_timer;
    uint32_t periodMs;
    uint32_t value;
    timer_status flags;
    void (*handler)(void);
};

struct timer_dev timers[] = {
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#if TIMER_COUNT>=2
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=3
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=4
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=5
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=6
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=7
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=8
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if TIMER_COUNT>=9
    {
        .periodMs = 1000,
        .value = 0,
        .flags = {{.val = TIMER_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
};

#if TIMER_COUNT>=1
static void * timer1_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[0].periodMs);
        timers[0].value++;
        if(timers[0].handler)
            (*timers[0].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=2
static void * timer2_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[1].periodMs);
        timers[1].value++;
        if(timers[1].handler)
            (*timers[1].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=3
static void * timer3_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[2].periodMs);
        timers[2].value++;
        if(timers[2].handler)
            (*timers[2].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=4
static void * timer4_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[3].periodMs);
        timers[3].value++;
        if(timers[3].handler)
            (*timers[3].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=5
static void * timer5_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[4].periodMs);
        timers[4].value++;
        if(timers[4].handler)
            (*timers[4].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=6
static void * timer6_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[5].periodMs);
        timers[5].value++;
        if(timers[5].handler)
            (*timers[5].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=7
static void * timer7_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[6].periodMs);
        timers[6].value++;
        if(timers[6].handler)
            (*timers[6].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=8
static void * timer8_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[7].periodMs);
        timers[7].value++;
        if(timers[7].handler)
            (*timers[7].handler)();
    }
    return NULL;
}
#endif

#if TIMER_COUNT>=9
static void * timer9_handler (void * p_data)
{
    while (1)
    {
        psleep(timers[8].periodMs);
        timers[8].value++;
        if(timers[8].handler)
            (*timers[8].handler)();
    }
    return NULL;
}
#endif

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
 * @brief Open a timer
 * @param device timer device number
 */
int timer_open(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return -1;
    if (timers[timer].flags.used == 1)
        return -1;

    timers[timer].flags.used = 1;
    timers[timer].handler = NULL;

    return 0;
}

/**
 * @brief Close a timer
 * @param device timer device number
 */
int timer_close(rt_dev_t device)
{
#if TIMER_COUNT>=1
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return -1;

    timer_disable(device);

    timers[timer].flags.val = TIMER_FLAG_UNUSED;

    return 0;
#else
    return -1;
#endif
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
        pthread_create (&timers[timer].thread_timer, NULL, timer1_handler, NULL );
        break;
#if TIMER_COUNT>=2
    case 1:
        pthread_create (&timers[timer].thread_timer, NULL, timer2_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=3
    case 2:
        pthread_create (&timers[timer].thread_timer, NULL, timer3_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=4
    case 3:
        pthread_create (&timers[timer].thread_timer, NULL, timer4_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=5
    case 4:
        pthread_create (&timers[timer].thread_timer, NULL, timer5_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=6
    case 5:
        pthread_create (&timers[timer].thread_timer, NULL, timer6_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=7
    case 6:
        pthread_create (&timers[timer].thread_timer, NULL, timer7_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=8
    case 7:
        pthread_create (&timers[timer].thread_timer, NULL, timer8_handler, NULL );
        break;
#endif
#if TIMER_COUNT>=9
    case 8:
        pthread_create (&timers[timer].thread_timer, NULL, timer9_handler, NULL );
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

    pthread_cancel( timers[timer].thread_timer );

    return 0;
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
        return -1;

    timers[timer].handler = handler;

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
        return -1;

    timers[timer].periodMs = periodMs;

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
        return 0;

    return timers[timer].periodMs;
}

/**
 * @brief Returns the current value of timer
 * @param device timer device number
 * @return value if ok, 0 in case of error
 */
uint16_t timer_getValue(rt_dev_t device)
{
    uint8_t timer = MINOR(device);
    if (timer >= TIMER_COUNT)
        return 0;

    return timers[timer].value;
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
        return -1;

    return 0;
}
