/**
 * @file oc_sim.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date May 10, 2017, 13:00 PM
 *
 * @brief OC support for udevkit simulator
 */

#include "oc.h"
#include <driver/timer.h>

#include <archi.h>

#if !defined(OC_COUNT) || OC_COUNT == 0
#    warning "No output compare (OC) on the current device or unknow device"
#endif

#define OC_FLAG_UNUSED 0x00
typedef struct
{
    union
    {
        struct
        {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned mode : 3;
        };
        uint8_t val;
    };
} oc_status;

struct oc_dev
{
    uint16_t rVal;
    uint16_t rsVal;
    uint8_t timer;
    oc_status flags;
};

static struct oc_dev _ocs[] = {
#if OC_COUNT >= 1
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 2
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 3
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 4
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 5
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 6
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 7
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 8
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 9
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 10
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 11
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 12
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 13
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 14
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 15
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 16
    {.rVal = 0, .rsVal = 0, .timer = 0, .flags = {{.val = OC_FLAG_UNUSED}}}
#endif
};

/**
 * @brief Gives a free OC device number
 * @return OC device number
 */
rt_dev_t oc_getFreeDevice(void)
{
#if OC_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < OC_COUNT; i++)
    {
        if (_ocs[i].flags.used == 0)
        {
            break;
        }
    }

    if (i == OC_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_OC, i);

    oc_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Open an OC
 * @param device OC device number
 * @return 0 if ok, -1 in case of error
 */
int oc_open(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }
    if (_ocs[oc].flags.used == 1)
    {
        return -1;
    }

    _ocs[oc].flags.used = 1;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Release an OC device
 * @param device OC device number
 * @return 0 if ok, -1 in case of error
 */
int oc_close(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    oc_disable(device);

    _ocs[oc].flags.val = OC_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enable the specified OC device
 * @param device OC device number
 * @return 0 if ok, -1 in case of error
 */
int oc_enable(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    _ocs[oc].flags.enabled = 1;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disable the specified OC device
 * @param device OC device number
 * @return 0 if ok, -1 in case of error
 */
int oc_disable(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    _ocs[oc].flags.enabled = 0;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Configures mode of the specified OC device
 * @param device OC device number
 * @param mode OC mode
 * @return 0 if ok, -1 in case of error
 */
int oc_setMode(rt_dev_t device, uint8_t mode)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    _ocs[oc].flags.mode = mode;

    if (_ocs[oc].flags.enabled)
    {
        return 0;
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Gives the current mode of the specified OC device
 * @param device OC device number
 * @return current mode OC mode
 */
uint8_t oc_mode(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return 0;
    }

    return _ocs[oc].flags.mode;
#else
    return 0;
#endif
}

/**
 * @brief Configures primary and secondary compare value
 * @param device OC device number
 * @param rVal OC primary compare value
 * @param rsVal OC secondary compare value
 * @return 0 if ok, -1 in case of error
 */
int oc_setRVal(rt_dev_t device, uint32_t rVal, uint32_t rsVal)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    _ocs[oc].rVal = rVal;
    _ocs[oc].rsVal = rsVal;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Returns the current rVal value
 * @param device OC device number
 * @return current rVal value
 */
uint32_t oc_rVal(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return 0;
    }

    return _ocs[oc].rVal;
#else
    return 0;
#endif
}

/**
 * @brief Returns the current rVal value
 * @param device OC device number
 * @return current rVal value
 */
uint32_t oc_rsVal(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return 0;
    }

    return _ocs[oc].rsVal;
#else
    return 0;
#endif
}

int oc_setTimer(rt_dev_t device, uint8_t timer)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    if (timer > 1)
    {
        return -1;  // invalid timer id
    }

    _ocs[oc].timer = timer;

    return 0;
#else
    return -1;
#endif
}

rt_dev_t oc_getTimer(rt_dev_t device)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return NULLDEV;
    }

    // if (CFGCONbits.OCACLK == 0)
    {
        if (_ocs[oc].timer == 0)
        {
            return timer(2);  // timer 2
        }
        else
        {
            return timer(3);  // timer 3
        }
    }
    /*else
    {
        switch(oc)
        {
        case 0:
        case 1:
        case 2:
            if (_ocs[oc].timer == 0)
            {
                return timer(4); // timer 4
            }
            else
            {
                return timer(5); // timer 5
            }
            break;
#if OC_COUNT>=6
        case 3:
        case 4:
        case 5:
            if (_ocs[oc].timer == 0)
            {
                return timer(2); // timer 2
            }
            else
            {
                return timer(3); // timer 3
            }
            break;
#endif
#if OC_COUNT>=9
        case 6:
        case 7:
        case 8:
            if (_ocs[oc].timer == 0)
            {
                return timer(6); // timer 6
            }
            else
            {
                return timer(7); // timer 7
            }
            break;
#endif
        }
    }*/
#endif

    return NULLDEV;
}
