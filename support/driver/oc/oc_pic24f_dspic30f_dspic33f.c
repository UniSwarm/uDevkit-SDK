/**
 * @file oc_pic24f_dspic30f_dspic33f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2021
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver for dsPIC30F, dsPIC33FJ,
 * PIC24F, PIC24FJ, PIC24FV and PIC24HJ
 *
 * Warning ! PIC24FJxxxGA/GB/GC/DA use oc_pic24e_dspic33e driver
 *
 * Implementation based on Microchip document DS70005157A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005157a.pdf
 */

#include "oc.h"

#include <archi.h>
#include <driver/timer.h>

#if !defined (OC_COUNT) || OC_COUNT==0
  #warning "No output compare (OC) on the current device or unknow device"
#endif

#define OC_FLAG_UNUSED  0x00
typedef struct {
    union {
        struct {
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
    uint8_t timer;
    oc_status flags;
};

struct oc_dev ocs[] = {
#if OC_COUNT>=1
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=2
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=3
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=4
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=5
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=6
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=7
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=8
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
#endif
#if OC_COUNT>=9
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    }
#endif
};

#define OC_PIC24F_dsPIC33F_dsPIC30F_DISABLE           0b000
#define OC_PIC24F_dsPIC33F_dsPIC30F_PWM               0b110
#define OC_PIC24F_dsPIC33F_dsPIC30F_SINGLE_LOW        0b010
#define OC_PIC24F_dsPIC33F_dsPIC30F_SINGLE_HIGH       0b001
#define OC_PIC24F_dsPIC33F_dsPIC30F_CONTINOUS_TOGGLE  0b011
#define OC_PIC24F_dsPIC33F_dsPIC30F_SINGLE_LOWHIGH    0b100
#define OC_PIC24F_dsPIC33F_dsPIC30F_CONTINOUS_LOWHIGH 0b101

/**
 * @brief Gives a free OC device number
 * @return OC device number
 */
rt_dev_t oc_getFreeDevice(void)
{
#if OC_COUNT>=1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < OC_COUNT; i++)
    {
        if (ocs[i].flags.used == 0)
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }
    if (ocs[oc].flags.used == 1)
    {
        return -1;
    }

    ocs[oc].flags.used = 1;

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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    oc_disable(device);

    ocs[oc].flags.val = OC_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
}

int oc_setInternalMode(rt_dev_t device, uint8_t mode)
{
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    switch (oc)
    {
    case 0:
        OC1CONbits.OCM = mode;
        break;
#if OC_COUNT>=2
    case 1:
        OC2CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=3
    case 2:
        OC3CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=4
    case 3:
        OC4CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=5
    case 4:
        OC5CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=6
    case 5:
        OC6CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=7
    case 6:
        OC7CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=8
    case 7:
        OC8CONbits.OCM = mode;
        break;
#endif
#if OC_COUNT>=9
    case 8:
        OC9CONbits.OCM = mode;
        break;
#endif
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    ocs[oc].flags.enabled = 1;

    return oc_setInternalMode(device, ocs[oc].flags.imode);
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    ocs[oc].flags.enabled = 0;

    return oc_setInternalMode(device, OC_PIC24F_dsPIC33F_dsPIC30F_DISABLE);
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
#if OC_COUNT>=1
    uint8_t imode = OC_PIC24F_dsPIC33F_dsPIC30F_DISABLE;
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    ocs[oc].flags.mode = mode;

    switch (mode)
    {
    case OC_MODE_PWM:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_PWM;
        break;
    case OC_MODE_PWM_CENTER:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_PWM; // no PWM center support
        break;
    case OC_MODE_SINGLE_LOW:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_SINGLE_LOW;
        break;
    case OC_MODE_SINGLE_HIGH:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_SINGLE_HIGH;
        break;
    case OC_MODE_CONTINOUS_TOGGLE:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_CONTINOUS_TOGGLE;
        break;
    case OC_MODE_SINGLE_LOWHIGH:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_SINGLE_LOWHIGH;
        break;
    case OC_MODE_CONTINOUS_LOWHIGH:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_CONTINOUS_LOWHIGH;
        break;
    }
    ocs[oc].flags.imode = imode;

    if (ocs[oc].flags.enabled)
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return 0;
    }

    return ocs[oc].flags.mode;
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    ocs[oc].rVal = rVal;
    ocs[oc].rsVal = rsVal;

    switch (oc)
    {
    case 0:
        OC1R = rVal;
        OC1RS = rsVal;
        break;
#if OC_COUNT>=2
    case 1:
        OC2R = rVal;
        OC2RS = rsVal;
        break;
#endif
#if OC_COUNT>=3
    case 2:
        OC3R = rVal;
        OC3RS = rsVal;
        break;
#endif
#if OC_COUNT>=4
    case 3:
        OC4R = rVal;
        OC4RS = rsVal;
        break;
#endif
#if OC_COUNT>=5
    case 4:
        OC5R = rVal;
        OC5RS = rsVal;
        break;
#endif
#if OC_COUNT>=6
    case 5:
        OC6R = rVal;
        OC6RS = rsVal;
        break;
#endif
#if OC_COUNT>=7
    case 6:
        OC7R = rVal;
        OC7RS = rsVal;
        break;
#endif
#if OC_COUNT>=8
    case 7:
        OC8R = rVal;
        OC8RS = rsVal;
        break;
#endif
#if OC_COUNT>=9
    case 8:
        OC9R = rVal;
        OC9RS = rsVal;
        break;
#endif
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    return ocs[oc].rVal;
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
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    return ocs[oc].rsVal;
#else
    return 0;
#endif
}

int oc_setTimer(rt_dev_t device, uint8_t timer)
{
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return -1;
    }

    if (timer > 1)
    {
        return -1; // invalid timer id
    }

    ocs[oc].timer = timer;

    switch (oc)
    {
    case 0:
        OC1CONbits.OCTSEL = timer;
        break;
#if OC_COUNT>=2
    case 1:
        OC2CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=3
    case 2:
        OC3CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=4
    case 3:
        OC4CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=5
    case 4:
        OC5CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=6
    case 5:
        OC6CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=7
    case 6:
        OC7CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=8
    case 7:
        OC8CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=9
    case 8:
        OC9CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=10
    case 9:
        OC10CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=11
    case 10:
        OC11CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=12
    case 11:
        OC12CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=13
    case 12:
        OC13CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=14
    case 13:
        OC14CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=15
    case 14:
        OC15CONbits.OCTSEL = timer;
        break;
#endif
#if OC_COUNT>=16
    case 15:
        OC16CONbits.OCTSEL = timer;
        break;
#endif
    }

    return 0;
#else
    return -1;
#endif
}

rt_dev_t oc_getTimer(rt_dev_t device)
{
#if OC_COUNT>=1
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
    {
        return NULLDEV;
    }

    if (ocs[oc].timer == 0)
    {
        return timer(2); // timer 2
    }
    else
    {
        return timer(3); // timer 3
    }
#endif
    
    return NULLDEV;
}
