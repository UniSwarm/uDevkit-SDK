/**
 * @file oc_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief OC support for udevkit for PIC32MK, PIC32MX, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61111E :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61111E.pdf
 */

#include "oc.h"

#include <driver/timer.h>

#include <archi.h>

#if !defined(OC_COUNT) || OC_COUNT == 0
#    warning "No output compare (OC) on the current device or unknow device"
#endif

enum
{
    OC_FLAG_UNUSED = 0x00
};
typedef struct
{
    union
    {
        struct
        {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned imode : 3;
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

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

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

enum
{
    OC_PIC32_DISABLE = 0b000,
    OC_PIC32_PWM = 0b110,
    OC_PIC32_SINGLE_LOW = 0b010,
    OC_PIC32_SINGLE_HIGH = 0b001,
    OC_PIC32_CONTINOUS_TOGGLE = 0b011,
    OC_PIC32_SINGLE_LOWHIGH = 0b100,
    OC_PIC32_CONTINOUS_LOWHIGH = 0b101
};

static int _oc_setInternalMode(rt_dev_t device, uint8_t mode);

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
 * @brief OC sdk state
 * @param device OC device number
 * @return true if OC was openned by OC_open function
 */
bool oc_isOpened(rt_dev_t device)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    return (_ocs[oc].flags.used == 1);
}

int _oc_setInternalMode(rt_dev_t device, uint8_t mode)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device), enabled = 0;
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    if (mode != OC_PIC32_DISABLE)
    {
        enabled = 1;
    }

    switch (oc)
    {
#    if (OC_COUNT >= 1) && !defined(OC1_DISABLE)
        case OC1_ID:
            OC1CONbits.OCM = mode;
            OC1CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 2) && !defined(OC2_DISABLE)
        case OC2_ID:
            OC2CONbits.OCM = mode;
            OC2CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 3) && !defined(OC3_DISABLE)
        case OC3_ID:
            OC3CONbits.OCM = mode;
            OC3CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 4) && !defined(OC4_DISABLE)
        case OC4_ID:
            OC4CONbits.OCM = mode;
            OC4CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 5) && !defined(OC5_DISABLE)
        case OC5_ID:
            OC5CONbits.OCM = mode;
            OC5CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 6) && !defined(OC6_DISABLE)
        case OC6_ID:
            OC6CONbits.OCM = mode;
            OC6CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 7) && !defined(OC7_DISABLE)
        case OC7_ID:
            OC7CONbits.OCM = mode;
            OC7CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 8) && !defined(OC8_DISABLE)
        case OC8_ID:
            OC8CONbits.OCM = mode;
            OC8CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 9) && !defined(OC9_DISABLE)
        case OC9_ID:
            OC9CONbits.OCM = mode;
            OC9CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 10) && !defined(OC10_DISABLE)
        case OC10_ID:
            OC10CONbits.OCM = mode;
            OC10CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 11) && !defined(OC11_DISABLE)
        case OC11_ID:
            OC11CONbits.OCM = mode;
            OC11CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 12) && !defined(OC12_DISABLE)
        case OC12_ID:
            OC12CONbits.OCM = mode;
            OC12CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 13) && !defined(OC13_DISABLE)
        case OC13_ID:
            OC13CONbits.OCM = mode;
            OC13CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 14) && !defined(OC14_DISABLE)
        case OC14_ID:
            OC14CONbits.OCM = mode;
            OC14CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 15) && !defined(OC15_DISABLE)
        case OC15_ID:
            OC15CONbits.OCM = mode;
            OC15CONbits.ON = enabled;
            break;
#    endif
#    if (OC_COUNT >= 16) && !defined(OC16_DISABLE)
        case OC16_ID:
            OC16CONbits.OCM = mode;
            OC16CONbits.ON = enabled;
            break;
#    endif
    }

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

    return _oc_setInternalMode(device, _ocs[oc].flags.imode);
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

    return _oc_setInternalMode(device, OC_PIC32_DISABLE);
#else
    return -1;
#endif
}

/**
 * @brief OC sdk enabled state
 * @param device OC device number
 * @return true if OC was enabled by OC_enable function
 */
bool oc_isEnabled(rt_dev_t device)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    return (_ocs[oc].flags.enabled == 1);
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
    uint8_t imode = OC_PIC32_DISABLE;
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    _ocs[oc].flags.mode = mode;

    switch (mode)
    {
        case OC_MODE_PWM:
        case OC_MODE_PWM_CENTER:  // no PWM center support
            imode = OC_PIC32_PWM;
            break;

        case OC_MODE_SINGLE_LOW:
            imode = OC_PIC32_SINGLE_LOW;
            break;

        case OC_MODE_SINGLE_HIGH:
            imode = OC_PIC32_SINGLE_HIGH;
            break;

        case OC_MODE_CONTINOUS_TOGGLE:
            imode = OC_PIC32_CONTINOUS_TOGGLE;
            break;

        case OC_MODE_SINGLE_LOWHIGH:
            imode = OC_PIC32_SINGLE_LOWHIGH;
            break;

        case OC_MODE_CONTINOUS_LOWHIGH:
            imode = OC_PIC32_CONTINOUS_LOWHIGH;
            break;
    }
    _ocs[oc].flags.imode = imode;

    if (_ocs[oc].flags.enabled)
    {
        return _oc_setInternalMode(device, imode);
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

    switch (oc)
    {
#    if (OC_COUNT >= 1) && !defined(OC1_DISABLE)
        case OC1_ID:
            OC1R = rVal;
            OC1RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 2) && !defined(OC2_DISABLE)
        case OC2_ID:
            OC2R = rVal;
            OC2RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 3) && !defined(OC3_DISABLE)
        case OC3_ID:
            OC3R = rVal;
            OC3RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 4) && !defined(OC4_DISABLE)
        case OC4_ID:
            OC4R = rVal;
            OC4RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 5) && !defined(OC5_DISABLE)
        case OC5_ID:
            OC5R = rVal;
            OC5RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 6) && !defined(OC6_DISABLE)
        case OC6_ID:
            OC6R = rVal;
            OC6RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 7) && !defined(OC7_DISABLE)
        case OC7_ID:
            OC7R = rVal;
            OC7RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 8) && !defined(OC8_DISABLE)
        case OC8_ID:
            OC8R = rVal;
            OC8RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 9) && !defined(OC9_DISABLE)
        case OC9_ID:
            OC9R = rVal;
            OC9RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 10) && !defined(OC10_DISABLE)
        case OC10_ID:
            OC10R = rVal;
            OC10RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 11) && !defined(OC11_DISABLE)
        case OC11_ID:
            OC11R = rVal;
            OC11RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 12) && !defined(OC12_DISABLE)
        case OC12_ID:
            OC12R = rVal;
            OC12RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 13) && !defined(OC13_DISABLE)
        case OC13_ID:
            OC13R = rVal;
            OC13RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 14) && !defined(OC14_DISABLE)
        case OC14_ID:
            OC14R = rVal;
            OC14RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 15) && !defined(OC15_DISABLE)
        case OC15_ID:
            OC15R = rVal;
            OC15RS = rsVal;
            break;
#    endif
#    if (OC_COUNT >= 16) && !defined(OC16_DISABLE)
        case OC16_ID:
            OC16R = rVal;
            OC16RS = rsVal;
            break;
#    endif
    }

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

    switch (oc)
    {
#    if (OC_COUNT >= 1) && !defined(OC1_DISABLE)
        case OC1_ID:
            OC1CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 2) && !defined(OC2_DISABLE)
        case OC2_ID:
            OC2CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 3) && !defined(OC3_DISABLE)
        case OC3_ID:
            OC3CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 4) && !defined(OC4_DISABLE)
        case OC4_ID:
            OC4CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 5) && !defined(OC5_DISABLE)
        case OC5_ID:
            OC5CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 6) && !defined(OC6_DISABLE)
        case OC6_ID:
            OC6CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 7) && !defined(OC7_DISABLE)
        case OC7_ID:
            OC7CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 8) && !defined(OC8_DISABLE)
        case OC8_ID:
            OC8CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 9) && !defined(OC9_DISABLE)
        case OC9_ID:
            OC9CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 10) && !defined(OC10_DISABLE)
        case OC10_ID:
            OC10CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 11) && !defined(OC11_DISABLE)
        case OC11_ID:
            OC11CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 12) && !defined(OC12_DISABLE)
        case OC12_ID:
            OC12CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 13) && !defined(OC13_DISABLE)
        case OC13_ID:
            OC13CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 14) && !defined(OC14_DISABLE)
        case OC14_ID:
            OC14CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 15) && !defined(OC15_DISABLE)
        case OC15_ID:
            OC15CONbits.OCTSEL = timer;
            break;
#    endif
#    if (OC_COUNT >= 16) && !defined(OC16_DISABLE)
        case OC16_ID:
            OC16CONbits.OCTSEL = timer;
            break;
#    endif
    }

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

#    ifdef OC_HAVE_ALTERNATIVE_TIMER_SELECTION
    if (CFGCONbits.OCACLK == 0)
#    endif
    {
        if (_ocs[oc].timer == 0)
        {
            return timer(2);  // timer 2
        }

        return timer(3);  // timer 3
    }
#    ifdef OC_HAVE_ALTERNATIVE_TIMER_SELECTION

    switch (oc)
    {
#        if OC_COUNT >= 1
        case OC1_ID:
        case OC2_ID:
        case OC3_ID:
            if (_ocs[oc].timer == 0)
            {
                return timer(4);  // timer 4
            }
            else
            {
                return timer(5);  // timer 5
            }
            break;
#        endif
#        if OC_COUNT >= 4
        case OC4_ID:
        case OC5_ID:
        case OC6_ID:
            if (_ocs[oc].timer == 0)
            {
                return timer(2);  // timer 2
            }
            else
            {
                return timer(3);  // timer 3
            }
            break;
#        endif
#        if OC_COUNT >= 7
        case OC7_ID:
        case OC8_ID:
        case OC9_ID:
            if (_ocs[oc].timer == 0)
            {
                return timer(6);  // timer 6
            }
            else
            {
                return timer(7);  // timer 7
            }
            break;
#        endif
#        if OC_COUNT >= 10
        case OC10_ID:
        case OC11_ID:
        case OC12_ID:
            if (_ocs[oc].timer == 0)
            {
                return timer(8);  // timer 8
            }
            else
            {
                return timer(9);  // timer 9
            }
            break;
#        endif
#        if OC_COUNT >= 13
        case OC13_ID:
        case OC14_ID:
        case OC15_ID:
        case OC16_ID:
            if (_ocs[oc].timer == 0)
            {
                return timer(2);  // timer 2
            }
            else
            {
                return timer(3);  // timer 3
            }
            break;
#        endif
    }
#    endif
#endif

    return NULLDEV;
}
