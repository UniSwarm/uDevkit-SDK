/**
 * @file ccp_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2020
 *
 * @date June 09, 2019, 00:50 AM
 *
 * @brief CCP support for udevkit for simulation purpose
 */

#include "ccp.h"

#include "driver/sysclock.h"
#include "simulator.h"

#if !defined(CCP_COUNT) || CCP_COUNT == 0
#    warning "No CCP on the current device or unknow device"
#endif

#define CCP_FLAG_UNUSED 0x00
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
} ccp_status;

struct ccp_dev
{
    pthread_t thread_ccp;
    uint32_t periodUs;
    uint32_t value;
    ccp_status flags;
    void (*handler)(void);
};

static struct ccp_dev ccps[] = {
#if CCP_COUNT >= 1
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 2
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 3
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 4
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 5
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 6
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 7
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 8
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
#if CCP_COUNT >= 9
    {.periodUs = 0, .flags = {{.val = CCP_FLAG_UNUSED}}, .handler = NULL},
#endif
};

#if CCP_COUNT >= 1
static void *ccp1_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        usleep(ccps[0].periodUs);
        ccps[0].value++;
        if (ccps[0].handler)
        {
            (*ccps[0].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 2
static void *ccp2_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[1].periodUs);
        ccps[1].value++;
        if (ccps[1].handler)
        {
            (*ccps[1].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 3
static void *ccp3_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[2].periodUs);
        ccps[2].value++;
        if (ccps[2].handler)
        {
            (*ccps[2].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 4
static void *ccp4_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[3].periodUs);
        ccps[3].value++;
        if (ccps[3].handler)
        {
            (*ccps[3].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 5
static void *ccp5_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[4].periodUs);
        ccps[4].value++;
        if (ccps[4].handler)
        {
            (*ccps[4].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 6
static void *ccp6_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[5].periodUs);
        ccps[5].value++;
        if (ccps[5].handler)
        {
            (*ccps[5].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 7
static void *ccp7_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[6].periodUs);
        ccps[6].value++;
        if (ccps[6].handler)
        {
            (*ccps[6].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 8
static void *ccp8_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[7].periodUs);
        ccps[7].value++;
        if (ccps[7].handler)
        {
            (*ccps[7].handler)();
        }
    }
    return NULL;
}
#endif

#if CCP_COUNT >= 9
static void *ccp9_handler(void *p_data)
{
    UDK_UNUSED(p_data);
    while (1)
    {
        psleep(ccps[8].periodUs);
        ccps[8].value++;
        if (ccps[8].handler)
        {
            (*ccps[8].handler)();
        }
    }
    return NULL;
}
#endif

/**
 * @brief Gives a free ccp device number
 * @return ccp device number
 */
rt_dev_t ccp_getFreeDevice()
{
#if CCP_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CCP_COUNT; i++)
    {
        if (ccps[i].flags.used == 0)
        {
            break;
        }
    }

    if (i == CCP_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_CCP, i);

    ccp_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open a ccp
 * @param device ccp device number
 */
int ccp_open(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }
    if (ccps[ccp].flags.used == 1)
    {
        return -1;
    }

    ccps[ccp].flags.used = 1;
    ccps[ccp].handler = NULL;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Close a ccp
 * @param device ccp device number
 */
int ccp_close(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    ccp_disable(device);

    ccps[ccp].flags.val = CCP_FLAG_UNUSED;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enable the specified ccp device
 * @param device ccp device number
 * @return 0 if ok, -1 in case of error
 */
int ccp_enable(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    ccps[ccp].flags.enabled = 1;

    switch (ccp)
    {
        case 0:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp1_handler, NULL);
            break;
#if CCP_COUNT >= 2
        case 1:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp2_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 3
        case 2:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp3_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 4
        case 3:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp4_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 5
        case 4:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp5_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 6
        case 5:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp6_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 7
        case 6:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp7_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 8
        case 7:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp8_handler, NULL);
            break;
#endif
#if CCP_COUNT >= 9
        case 8:
            pthread_create(&ccps[ccp].thread_ccp, NULL, ccp9_handler, NULL);
            break;
#endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disable the specified ccp device
 * @param device ccp device number
 * @return 0 if ok, -1 in case of error
 */
int ccp_disable(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    ccps[ccp].flags.enabled = 0;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the handler function that will be called on ccp interrupt
 * @param device ccp device number
 * @param handler void funtion pointer or null to remove the handler
 * @return 0 if ok, -1 in case of error
 */
int ccp_setHandler(rt_dev_t device, void (*handler)(void))
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    ccps[ccp].handler = handler;
    if (ccps[ccp].flags.enabled == 1)
    {
        ccp_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the CCP mode (PWM, ccp, OC, IC, ...)
 * @param device ccp device number
 * @param mode mode to set
 * @return 0 if ok, -1 in case of error
 */
int ccp_setMode(rt_dev_t device, CCP_MODE mode)
{
    UDK_UNUSED(mode);

#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    // TODO

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets both comparator for Dual edge / PWM mode
 * @param device ccp device number
 * @param cmpA value of A comparator
 * @param cmpB value of B comparator
 * @return 0 if ok, -1 in case of error
 */
int ccp_setCompare(rt_dev_t device, uint16_t cmpA, uint16_t cmpB)
{
    UDK_UNUSED(cmpA);
    UDK_UNUSED(cmpB);

#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    // TODO

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the internal period
 * @param device ccp device number
 * @param prvalue reset value of ccp, does not consider the time
 * @return 0 if ok, -1 in case of error
 */
int ccp_setPeriod(rt_dev_t device, uint32_t prvalue)
{
    UDK_UNUSED(prvalue);

#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    return 0;
#else
    UDK_UNUSED(device);
    return -1;
#endif
}

/**
 * @brief Gets the internal period
 * @param device ccp device number
 * @return 0 if ok, -1 in case of error
 */
uint32_t ccp_period(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the period in us of the ccp module to work in ccp mode
 * @param device ccp device number
 * @return 0 if ok, -1 in case of error
 */
int ccp_setPeriodMs(rt_dev_t device, uint32_t periodMs)
{
#if CCP_COUNT >= 1
    float prvalue;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    ccps[ccp].periodUs = periodMs * 1000;

    return ccp_setPeriod(device, (uint32_t)prvalue);
#else
    return -1;
#endif
}

/**
 * @brief Returns the current period in us
 * @param device ccp device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t ccp_periodMs(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return 0;
    }

    return ccps[ccp].periodUs / 1000;
#else
    return 0;
#endif
}

/**
 * @brief Sets the period in us of the ccp module to work in ccp mode
 * @param device ccp device number
 * @return 0 if ok, -1 in case of error
 */
int ccp_setPeriodUs(rt_dev_t device, uint32_t periodUs)
{
#if CCP_COUNT >= 1
    float prvalue;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    ccps[ccp].periodUs = periodUs;

    return ccp_setPeriod(device, (uint32_t)prvalue);
#else
    return -1;
#endif
}

/**
 * @brief Returns the current period in us
 * @param device ccp device number
 * @return period in us if ok, 0 in case of error
 */
uint32_t ccp_periodUs(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return 0;
    }

    return ccps[ccp].periodUs;
#else
    return 0;
#endif
}

/**
 * @brief Returns the current value of ccp
 * @param device ccp device number
 * @return value if ok, 0 in case of error
 */
uint32_t ccp_getValue(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint32_t value;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return 0;
    }

    return value;
#else
    return 0;
#endif
}

/**
 * @brief Sets the current value of ccp
 * @param device ccp device number
 * @return 0 if ok, -1 in case of error
 */
int ccp_setValue(rt_dev_t device, uint32_t value)
{
    UDK_UNUSED(value);

#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    return 0;
#else
    UDK_UNUSED(device);
    return -1;
#endif
}
