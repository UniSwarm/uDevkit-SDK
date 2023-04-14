/**
 * @file ccp_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2023
 *
 * @date May 08, 2019, 09:40 AM
 *
 * @brief CCP capture/compare/PWM/Timer support driver for PIC24 and dsPIC33C
 *
 * Implementation based on Microchip document DS30003035B:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/30003035b.pdf
 */

#include "ccp.h"

#include <archi.h>
#include <driver/sysclock.h>

#if !defined(CCP_COUNT) || (CCP_COUNT == 0)
#    warning "No CCP on the current device or unknow device"
#endif

enum
{
    CCP_FLAG_UNUSED = 0x00
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
} ccp_status;

struct ccp_dev
{
    uint32_t periodUs;
    ccp_status flags;
    void (*handler)(void);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

#if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT1Interrupt(void);
#endif
#if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT2Interrupt(void);
#endif
#if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT3Interrupt(void);
#endif
#if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT4Interrupt(void);
#endif
#if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT5Interrupt(void);
#endif
#if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT6Interrupt(void);
#endif
#if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT7Interrupt(void);
#endif
#if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT8Interrupt(void);
#endif
#if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT9Interrupt(void);
#endif

static struct ccp_dev _ccps[] = {
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

/**
 * @brief Gives a free ccp device number
 * @return ccp device number
 */
rt_dev_t ccp_getFreeDevice(void)
{
#if CCP_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CCP_COUNT; i++)
    {
        if (_ccps[i].flags.used == 0)
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
    if (_ccps[ccp].flags.used == 1)
    {
        return -1;
    }

    _ccps[ccp].flags.used = 1;
    _ccps[ccp].handler = NULL;

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

    _ccps[ccp].flags.val = CCP_FLAG_UNUSED;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief CCP sdk state
 * @param device ccp device number
 * @return true if ccp was openned by ccp_open function
 */
bool ccp_isOpened(rt_dev_t device)
{
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    return (_ccps[ccp].flags.used == 1);
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

    _ccps[ccp].flags.enabled = 1;

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            _CCT1IF = 0;
            _CCT1IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT1IP = 4;
            CCP1CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            _CCT2IF = 0;
            _CCT2IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT2IP = 4;
            CCP2CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            _CCT3IF = 0;
            _CCT3IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT3IP = 4;
            CCP3CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            _CCT4IF = 0;
            _CCT4IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT4IP = 4;
            CCP4CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            _CCT5IF = 0;
            _CCT5IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT5IP = 4;
            CCP5CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            _CCT6IF = 0;
            _CCT6IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT6IP = 4;
            CCP6CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            _CCT7IF = 0;
            _CCT7IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT7IP = 4;
            CCP7CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            _CCT8IF = 0;
            _CCT8IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT8IP = 4;
            CCP8CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            _CCT9IF = 0;
            _CCT9IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT9IP = 4;
            CCP9CON1Lbits.CCPON = 1;  // enable ccp module
            break;
#    endif
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

    _ccps[ccp].flags.enabled = 0;

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            _CCT1IE = 0;
            CCP1CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            _CCT2IE = 0;
            CCP2CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            _CCT3IE = 0;
            CCP3CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            _CCT4IE = 0;
            CCP4CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            _CCT5IE = 0;
            CCP5CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            _CCT6IE = 0;
            CCP6CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            _CCT7IE = 0;
            CCP7CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            _CCT8IE = 0;
            CCP8CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            _CCT9IE = 0;
            CCP9CON1Lbits.CCPON = 0;  // disable ccp module
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief CCP sdk enabled state
 * @param device ccp device number
 * @return true if ccp was enabled by ccp_enable function
 */
bool ccp_isEnabled(rt_dev_t device)
{
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    return (_ccps[ccp].flags.enabled == 1);
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

    _ccps[ccp].handler = handler;
    if (_ccps[ccp].flags.enabled == 1)
    {
        ccp_enable(device);
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Sets the CCP mode (PWM, timer, OC, IC, ...)
 * @param device ccp device number
 * @param mode mode to set
 * @return 0 if ok, -1 in case of error
 */
int ccp_setMode(rt_dev_t device, CCP_MODE mode)
{
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    uint8_t modeBit = 0;
    uint8_t t32bit = 0;
    uint8_t icBit = 0;
    uint8_t outBit = 0;
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    switch (mode)
    {
        case CCP_MODE_TIMER:
            modeBit = 0b0000;  // mode
            t32bit = 1;        // 32 bits mode
            icBit = 0;         // Output compare / PWM
            outBit = 0;        // Output pin off
            break;

        case CCP_MODE_PWM:
            modeBit = 0b0101;  // mode
            t32bit = 0;        // 16 bits mode
            icBit = 0;         // Output compare / PWM
            outBit = 1;        // Output pin onff
            break;

        case CCP_MODE_PWMC:
            modeBit = 0b0110;  // mode
            t32bit = 0;        // 16 bits mode
            icBit = 0;         // Output compare / PWM
            outBit = 1;        // Output pin onff
            break;

        case CCP_MODE_OCH:
            modeBit = 0b0001;  // mode
            t32bit = 1;        // 32 bits mode
            icBit = 0;         // Output compare / PWM
            outBit = 1;        // Output pin onff
            break;

        case CCP_MODE_OCL:
            modeBit = 0b0010;  // mode
            t32bit = 1;        // 32 bits mode
            icBit = 0;         // Output compare / PWM
            outBit = 1;        // Output pin onff
            break;

        case CCP_MODE_OCT:
            modeBit = 0b0011;  // mode
            t32bit = 1;        // 32 bits mode
            icBit = 0;         // Output compare / PWM
            outBit = 1;        // Output pin onff
            break;
    }

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            CCP1CON1Lbits.MOD = modeBit;
            CCP1CON1Lbits.T32 = t32bit;
            CCP1CON1Lbits.CCSEL = icBit;
            CCP1CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            CCP2CON1Lbits.MOD = modeBit;
            CCP2CON1Lbits.T32 = t32bit;
            CCP2CON1Lbits.CCSEL = icBit;
            CCP2CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            CCP3CON1Lbits.MOD = modeBit;
            CCP3CON1Lbits.T32 = t32bit;
            CCP3CON1Lbits.CCSEL = icBit;
            CCP3CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            CCP4CON1Lbits.MOD = modeBit;
            CCP4CON1Lbits.T32 = t32bit;
            CCP4CON1Lbits.CCSEL = icBit;
            CCP4CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            CCP5CON1Lbits.MOD = modeBit;
            CCP5CON1Lbits.T32 = t32bit;
            CCP5CON1Lbits.CCSEL = icBit;
            CCP5CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            CCP6CON1Lbits.MOD = modeBit;
            CCP6CON1Lbits.T32 = t32bit;
            CCP6CON1Lbits.CCSEL = icBit;
            CCP6CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            CCP7CON1Lbits.MOD = modeBit;
            CCP7CON1Lbits.T32 = t32bit;
            CCP7CON1Lbits.CCSEL = icBit;
            CCP7CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            CCP8CON1Lbits.MOD = modeBit;
            CCP8CON1Lbits.T32 = t32bit;
            CCP8CON1Lbits.CCSEL = icBit;
            CCP8CON2Hbits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            CCP9CON1Lbits.MOD = modeBit;
            CCP9CON1Lbits.T32 = t32bit;
            CCP9CON1Lbits.CCSEL = icBit;
            CCP9CON2Hbits.OCAEN = outBit;
            break;
#    endif
    }

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
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            CCP1RA = cmpA;
            CCP1RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            CCP2RA = cmpA;
            CCP2RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            CCP3RA = cmpA;
            CCP3RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            CCP4RA = cmpA;
            CCP4RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            CCP5RA = cmpA;
            CCP5RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            CCP6RA = cmpA;
            CCP6RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            CCP7RA = cmpA;
            CCP7RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            CCP8RA = cmpA;
            CCP8RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            CCP9RA = cmpA;
            CCP9RB = cmpB;
            break;
#    endif
    }

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
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            CCP1PRH = prvalue >> 16;
            CCP1PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            CCP2PRH = prvalue >> 16;
            CCP2PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            CCP3PRH = prvalue >> 16;
            CCP3PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            CCP4PRH = prvalue >> 16;
            CCP4PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            CCP5PRH = prvalue >> 16;
            CCP5PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            CCP6PRH = prvalue >> 16;
            CCP6PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            CCP7PRH = prvalue >> 16;
            CCP7PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            CCP8PRH = prvalue >> 16;
            CCP8PRL = (uint16_t)prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            CCP9PRH = prvalue >> 16;
            CCP9PRL = (uint16_t)prvalue;  // pr value, comparator value
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

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            return ((uint32_t)CCP1PRH << 16) + CCP1PRL;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            return ((uint32_t)CCP2PRH << 16) + CCP2PRL;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            return ((uint32_t)CCP3PRH << 16) + CCP3PRL;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            return ((uint32_t)CCP4PRH << 16) + CCP4PRL;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            return ((uint32_t)CCP5PRH << 16) + CCP5PRL;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            return ((uint32_t)CCP6PRH << 16) + CCP6PRL;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            return ((uint32_t)CCP7PRH << 16) + CCP7PRL;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            return ((uint32_t)CCP8PRH << 16) + CCP8PRL;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            return ((uint32_t)CCP9PRH << 16) + CCP9PRL;
#    endif
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

    _ccps[ccp].periodUs = periodMs * 1000;

    uint32_t freqCCp = sysclock_periphFreq(SYSCLOCK_CLOCK_CCP);
    prvalue = (float)freqCCp / 1000.0 * (float)periodMs;

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

    return _ccps[ccp].periodUs / 1000;
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

    _ccps[ccp].periodUs = periodUs;

    uint32_t freqCCp = sysclock_periphFreq(SYSCLOCK_CLOCK_CCP);
    prvalue = (float)freqCCp / 1000000.0 * (float)periodUs;

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

    return _ccps[ccp].periodUs;
#else
    return 0;
#endif
}

/**
 * @brief Returns the current value of ccp
 * @param device ccp device number
 * @return value if ok, 0 in case of error
 */
uint32_t ccp_value(rt_dev_t device)
{
#if CCP_COUNT >= 1
    uint32_t value = 0;
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return 0;
    }

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            value = ((uint32_t)CCP1TMRH << 16) + CCP1TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            value = ((uint32_t)CCP2TMRH << 16) + CCP2TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            value = ((uint32_t)CCP3TMRH << 16) + CCP3TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            value = ((uint32_t)CCP4TMRH << 16) + CCP4TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            value = ((uint32_t)CCP5TMRH << 16) + CCP5TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            value = ((uint32_t)CCP6TMRH << 16) + CCP6TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            value = ((uint32_t)CCP7TMRH << 16) + CCP7TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            value = ((uint32_t)CCP8TMRH << 16) + CCP8TMRL;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            value = ((uint32_t)CCP9TMRH << 16) + CCP9TMRL;
            break;
#    endif
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
#if CCP_COUNT >= 1
    uint8_t ccp = MINOR(device);
    if (ccp >= CCP_COUNT)
    {
        return -1;
    }

    switch (ccp)
    {
#    if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
        case 0:
            CCP1TMRH = value >> 16;
            CCP1TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case 1:
            CCP2TMRH = value >> 16;
            CCP2TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case 2:
            CCP3TMRH = value >> 16;
            CCP3TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case 3:
            CCP4TMRH = value >> 16;
            CCP4TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case 4:
            CCP5TMRH = value >> 16;
            CCP5TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case 5:
            CCP6TMRH = value >> 16;
            CCP6TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case 6:
            CCP7TMRH = value >> 16;
            CCP7TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case 7:
            CCP8TMRH = value >> 16;
            CCP8TMRL = (uint16_t)value;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case 8:
            CCP9TMRH = value >> 16;
            CCP9TMRL = (uint16_t)value;
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

#if (CCP_COUNT >= 1) && !defined(CCP1_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT1Interrupt(void)
{
    (*_ccps[0].handler)();
    _CCT1IF = 0;
}
#endif

#if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT2Interrupt(void)
{
    (*_ccps[1].handler)();
    _CCT2IF = 0;
}
#endif

#if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT3Interrupt(void)
{
    (*_ccps[2].handler)();
    _CCT3IF = 0;
}
#endif

#if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT4Interrupt(void)
{
    (*_ccps[3].handler)();
    _CCT4IF = 0;
}
#endif

#if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT5Interrupt(void)
{
    (*_ccps[4].handler)();
    _CCT5IF = 0;
}
#endif

#if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT6Interrupt(void)
{
    (*_ccps[5].handler)();
    _CCT6IF = 0;
}
#endif

#if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT7Interrupt(void)
{
    (*_ccps[6].handler)();
    _CCT7IF = 0;
}
#endif

#if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT8Interrupt(void)
{
    (*_ccps[7].handler)();
    _CCT8IF = 0;
}
#endif

#if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT9Interrupt(void)
{
    (*_ccps[8].handler)();
    _CCT9IF = 0;
}
#endif
