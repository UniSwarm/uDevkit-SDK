/**
 * @file oc_pic24e_dspic33e.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver for PIC24EP, dspic33EP,
 * dsPIC33EV and PIC24FJxxxGA/GB/GC/DA
 *
 * Implementation based on Microchip document DS70005159A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005159a.pdf
 */

#include "oc.h"

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
    uint32_t rVal;
    uint32_t rsVal;
    oc_status flags;
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

static struct oc_dev _ocs[] = {
#if OC_COUNT >= 1
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 2
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 3
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 4
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 5
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 6
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 7
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 8
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 9
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 10
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 11
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 12
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 13
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 14
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 15
    {.flags = {{.val = OC_FLAG_UNUSED}}},
#endif
#if OC_COUNT >= 16
    {.flags = {{.val = OC_FLAG_UNUSED}}}
#endif
};

#define OC_PIC24E_dsPIC33E_DISABLE           0b000
#define OC_PIC24E_dsPIC33E_PWM               0b110
#define OC_PIC24E_dsPIC33E_PWM_CENTER        0b111
#define OC_PIC24E_dsPIC33E_SINGLE_LOW        0b010
#define OC_PIC24E_dsPIC33E_SINGLE_HIGH       0b001
#define OC_PIC24E_dsPIC33E_CONTINOUS_TOGGLE  0b011
#define OC_PIC24E_dsPIC33E_SINGLE_LOWHIGH    0b100
#define OC_PIC24E_dsPIC33E_CONTINOUS_LOWHIGH 0b101

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

int oc_setInternalMode(rt_dev_t device, uint8_t mode)
{
#if OC_COUNT >= 1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    switch (oc)
    {
#    if (OC_COUNT >= 1) && !defined(OC1_DISABLE)
        case OC1_ID:
            OC1CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 2) && !defined(OC2_DISABLE)
        case OC2_ID:
            OC2CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 3) && !defined(OC3_DISABLE)
        case OC3_ID:
            OC3CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 4) && !defined(OC4_DISABLE)
        case OC4_ID:
            OC4CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 5) && !defined(OC5_DISABLE)
        case OC5_ID:
            OC5CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 6) && !defined(OC6_DISABLE)
        case OC6_ID:
            OC6CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 7) && !defined(OC7_DISABLE)
        case OC7_ID:
            OC7CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 8) && !defined(OC8_DISABLE)
        case OC8_ID:
            OC8CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 9) && !defined(OC9_DISABLE)
        case OC9_ID:
            OC9CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 10) && !defined(OC10_DISABLE)
        case OC10_ID:
            OC10CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 11) && !defined(OC11_DISABLE)
        case OC11_ID:
            OC11CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 12) && !defined(OC12_DISABLE)
        case OC12_ID:
            OC12CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 13) && !defined(OC13_DISABLE)
        case OC13_ID:
            OC13CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 14) && !defined(OC14_DISABLE)
        case OC14_ID:
            OC14CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 15) && !defined(OC15_DISABLE)
        case OC15_ID:
            OC15CON1bits.OCM = mode;
            break;
#    endif
#    if (OC_COUNT >= 16) && !defined(OC16_DISABLE)
        case OC16_ID:
            OC16CON1bits.OCM = mode;
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

    return oc_setInternalMode(device, _ocs[oc].flags.imode);
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

    return oc_setInternalMode(device, OC_PIC24E_dsPIC33E_DISABLE);
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
    uint8_t imode = OC_PIC24E_dsPIC33E_DISABLE;
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    _ocs[oc].flags.mode = mode;

    switch (mode)
    {
        case OC_MODE_PWM:
            imode = OC_PIC24E_dsPIC33E_PWM;
            break;

        case OC_MODE_PWM_CENTER:
            imode = OC_PIC24E_dsPIC33E_PWM_CENTER;
            break;

        case OC_MODE_SINGLE_LOW:
            imode = OC_PIC24E_dsPIC33E_SINGLE_LOW;
            break;

        case OC_MODE_SINGLE_HIGH:
            imode = OC_PIC24E_dsPIC33E_SINGLE_HIGH;
            break;

        case OC_MODE_CONTINOUS_TOGGLE:
            imode = OC_PIC24E_dsPIC33E_CONTINOUS_TOGGLE;
            break;

        case OC_MODE_SINGLE_LOWHIGH:
            imode = OC_PIC24E_dsPIC33E_SINGLE_LOWHIGH;
            break;

        case OC_MODE_CONTINOUS_LOWHIGH:
            imode = OC_PIC24E_dsPIC33E_CONTINOUS_LOWHIGH;
            break;
    }
    _ocs[oc].flags.imode = imode;

    if (_ocs[oc].flags.enabled)
    {
        return oc_setInternalMode(device, imode);
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
        return -1;
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
        return -1;
    }

    return _ocs[oc].rsVal;
#else
    return 0;
#endif
}
