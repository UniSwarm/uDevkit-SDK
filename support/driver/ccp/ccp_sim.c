/**
 * @file ccp_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019
 *
 * @date June 09, 2019, 00:50 AM
 *
 * @brief CCP support for udevkit for simulation purpose
 */

#include "ccp.h"

#include "simulator.h"
#include "driver/sysclock.h"

#if !defined (CCP_COUNT) || CCP_COUNT==0
  #warning "No CCP on the current device or unknow device"
#endif

#define CCP_FLAG_UNUSED  0x00
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
} ccp_status;

struct ccp_dev
{
    pthread_t thread_timer;
    uint32_t periodUs;
    ccp_status flags;
    void (*handler)(void);
};

struct ccp_dev ccps[] = {
#if CCP_COUNT>=1
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=2
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=3
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=4
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=5
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=6
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=7
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=8
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
#if CCP_COUNT>=9
    {
        .periodUs = 0,
        .flags = {{.val = CCP_FLAG_UNUSED}},
        .handler = NULL
    },
#endif
};

/**
 * @brief Gives a free ccp device number
 * @return ccp device number
 */
rt_dev_t ccp_getFreeDevice()
{
#if CCP_COUNT>=1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CCP_COUNT; i++)
        if (ccps[i].flags.used == 0)
            break;

    if (i == CCP_COUNT)
        return NULLDEV;
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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;
    if (ccps[ccp].flags.used == 1)
        return -1;

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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

    ccps[ccp].flags.enabled = 1;


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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

    ccps[ccp].handler = handler;
    if (ccps[ccp].flags.enabled == 1)
        ccp_enable(device);

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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;


    return 0;
#else
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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;


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
#if CCP_COUNT>=1
    float prvalue;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return 0;

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
#if CCP_COUNT>=1
    float prvalue;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return 0;

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
#if CCP_COUNT>=1
    uint32_t value;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return 0;



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
#if CCP_COUNT>=1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
        return -1;

    return 0;
#else
    return -1;
#endif
}

