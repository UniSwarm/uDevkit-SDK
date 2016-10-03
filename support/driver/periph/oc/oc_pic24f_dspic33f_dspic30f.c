/**
 * @file oc_pic24f_dspic33f_dspic30f.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 18, 2016, 15:40 PM
 *
 * @brief Output Compare support driver for dsPIC30F, dsPIC33FJ, PIC24F, PIC24FJ, PIC24FV and PIC24HJ
 */

#include "oc.h"

#include <xc.h>

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
    oc_status flags;
};

struct oc_dev ocs[] = {
    {
        .flags = {{.val = OC_FLAG_UNUSED}}
    },
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

#define OC_PIC24F_dsPIC33F_dsPIC30F_DISABLE  0b000
#define OC_PIC24F_dsPIC33F_dsPIC30F_PWM      0b110

/**
 * @brief Gives a free OC device number
 * @return OC device number
 */
rt_dev_t oc_getFreeDevice()
{
    uint8_t i;

    for (i = 0; i < OC_COUNT; i++)
        if (ocs[i].flags.used == 0)
            break;

    if (i == OC_COUNT)
        return NULLDEV;

    ocs[i].flags.used = 1;

    return MKDEV(DEV_CLASS_OC, i);
}

/**
 * @brief Release an OC device
 * @param device OC device number
 */
void oc_releaseDevice(rt_dev_t device)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return;

    ocs[oc].flags.val = OC_FLAG_UNUSED;
}

int oc_setInternalMode(rt_dev_t device, uint8_t mode)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

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
}

/**
 * @brief Enable the specified OC device
 * @param device OC device number
 * @return 0 if ok, -1 in case of error
 */
int oc_enable(rt_dev_t device)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

    ocs[oc].flags.enabled = 1;
    
    return oc_setInternalMode(device, ocs[oc].flags.imode);
}

/**
 * @brief Disable the specified OC device
 * @param device OC device number
 * @return 0 if ok, -1 in case of error
 */
int oc_disable(rt_dev_t device)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

    ocs[oc].flags.enabled = 0;
    
    return oc_setInternalMode(device, OC_PIC24F_dsPIC33F_dsPIC30F_DISABLE);
}

/**
 * @brief Configures mode of the specified OC device
 * @param device OC device number
 * @param mode OC mode
 * @return 0 if ok, -1 in case of error
 */
int oc_setMode(rt_dev_t device, uint8_t mode)
{
    uint8_t imode = OC_PIC24F_dsPIC33F_dsPIC30F_DISABLE;
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

    ocs[oc].flags.mode = mode;
    
    switch (mode)
    {
    case OC_MODE_PWM:
        imode = OC_PIC24F_dsPIC33F_dsPIC30F_PWM;
        break;
    }
    ocs[oc].flags.imode = imode;

    if (ocs[oc].flags.enabled)
        return oc_setInternalMode(device, imode);
    return 0;
}

/**
 * @brief Gives the current mode of the specified OC device
 * @param device OC device number
 * @return current mode OC mode
 */
uint8_t oc_mode(rt_dev_t device)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

    return ocs[oc].flags.mode;
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
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

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
}

/**
 * @brief Returns the curent rVal value
 * @param device OC device number
 * @return curent rVal value
 */
int oc_rVal(rt_dev_t device, uint32_t rVal, uint32_t rsVal)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

    return ocs[oc].rVal;
}

/**
 * @brief Returns the curent rVal value
 * @param device OC device number
 * @return curent rVal value
 */
int oc_rsVal(rt_dev_t device, uint32_t rVal, uint32_t rsVal)
{
    uint8_t oc = MINOR(device);
    if (oc >= OC_COUNT)
        return -1;

    return ocs[oc].rsVal;
}
