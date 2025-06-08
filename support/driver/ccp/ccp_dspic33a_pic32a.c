/**
 * @file ccp_dspic33a_pic32a.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date June 8, 2025, 07:37 PM
 *
 * @brief CCP support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip document DS70005539C, DS70005591A, DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
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
        case CCP1_ID:
            _CCT1IF = 0;
            _CCT1IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT1IP = 4;
            CCP1CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            _CCT2IF = 0;
            _CCT2IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT2IP = 4;
            CCP2CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            _CCT3IF = 0;
            _CCT3IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT3IP = 4;
            CCP3CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            _CCT4IF = 0;
            _CCT4IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT4IP = 4;
            CCP4CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            _CCT5IF = 0;
            _CCT5IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT5IP = 4;
            CCP5CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            _CCT6IF = 0;
            _CCT6IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT6IP = 4;
            CCP6CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            _CCT7IF = 0;
            _CCT7IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT7IP = 4;
            CCP7CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            _CCT8IF = 0;
            _CCT8IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT8IP = 4;
            CCP8CON1bits.ON = 1;  // enable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            _CCT9IF = 0;
            _CCT9IE = (_ccps[ccp].handler != NULL) ? 1 : 0;
            _CCT9IP = 4;
            CCP9CON1bits.ON = 1;  // enable ccp module
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
        case CCP1_ID:
            _CCT1IE = 0;
            CCP1CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            _CCT2IE = 0;
            CCP2CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            _CCT3IE = 0;
            CCP3CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            _CCT4IE = 0;
            CCP4CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            _CCT5IE = 0;
            CCP5CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            _CCT6IE = 0;
            CCP6CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            _CCT7IE = 0;
            CCP7CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            _CCT8IE = 0;
            CCP8CON1bits.ON = 0;  // disable ccp module
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            _CCT9IE = 0;
            CCP9CON1bits.ON = 0;  // disable ccp module
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
        case CCP1_ID:
            CCP1CON1bits.MOD = modeBit;
            CCP1CON1bits.T32 = t32bit;
            CCP1CON1bits.CCSEL = icBit;
            CCP1CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            CCP2CON1bits.MOD = modeBit;
            CCP2CON1bits.T32 = t32bit;
            CCP2CON1bits.CCSEL = icBit;
            CCP2CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            CCP3CON1bits.MOD = modeBit;
            CCP3CON1bits.T32 = t32bit;
            CCP3CON1bits.CCSEL = icBit;
            CCP3CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            CCP4CON1bits.MOD = modeBit;
            CCP4CON1bits.T32 = t32bit;
            CCP4CON1bits.CCSEL = icBit;
            CCP4CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            CCP5CON1bits.MOD = modeBit;
            CCP5CON1bits.T32 = t32bit;
            CCP5CON1bits.CCSEL = icBit;
            CCP5CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            CCP6CON1bits.MOD = modeBit;
            CCP6CON1bits.T32 = t32bit;
            CCP6CON1bits.CCSEL = icBit;
            CCP6CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            CCP7CON1bits.MOD = modeBit;
            CCP7CON1bits.T32 = t32bit;
            CCP7CON1bits.CCSEL = icBit;
            CCP7CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            CCP8CON1bits.MOD = modeBit;
            CCP8CON1bits.T32 = t32bit;
            CCP8CON1bits.CCSEL = icBit;
            CCP8CON2bits.OCAEN = outBit;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            CCP9CON1bits.MOD = modeBit;
            CCP9CON1bits.T32 = t32bit;
            CCP9CON1bits.CCSEL = icBit;
            CCP9CON2bits.OCAEN = outBit;
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
        case CCP1_ID:
            CCP1RA = cmpA;
            CCP1RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            CCP2RA = cmpA;
            CCP2RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            CCP3RA = cmpA;
            CCP3RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            CCP4RA = cmpA;
            CCP4RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            CCP5RA = cmpA;
            CCP5RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            CCP6RA = cmpA;
            CCP6RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            CCP7RA = cmpA;
            CCP7RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            CCP8RA = cmpA;
            CCP8RB = cmpB;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
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
        case CCP1_ID:
            CCP1PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            CCP2PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            CCP3PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            CCP4PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            CCP5PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            CCP6PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            CCP7PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            CCP8PR = prvalue;  // pr value, comparator value
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            CCP9PR = prvalue;  // pr value, comparator value
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
        case CCP1_ID:
            return CCP1PR;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            return CCP2PR;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            return CCP3PR;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            return CCP4PR;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            return CCP5PR;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            return CCP6PR;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            return CCP7PR;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            return CCP8PR;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            return CCP9PR;
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
        case CCP1_ID:
            value = CCP1TMR;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            value = CCP2TMR;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            value = CCP3TMR;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            value = CCP4TMR;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            value = CCP5TMR;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            value = CCP6TMR;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            value = CCP7TMR;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            value = CCP8TMR;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            value = CCP9TMR;
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
        case CCP1_ID:
            CCP1TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
        case CCP2_ID:
            CCP2TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
        case CCP3_ID:
            CCP3TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
        case CCP4_ID:
            CCP4TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
        case CCP5_ID:
            CCP5TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
        case CCP6_ID:
            CCP6TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
        case CCP7_ID:
            CCP7TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
        case CCP8_ID:
            CCP8TMR = value;
            break;
#    endif
#    if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
        case CCP9_ID:
            CCP9TMR = value;
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
    (*_ccps[CCP1_ID].handler)();
    _CCT1IF = 0;
}
#endif

#if (CCP_COUNT >= 2) && !defined(CCP2_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT2Interrupt(void)
{
    (*_ccps[CCP2_ID].handler)();
    _CCT2IF = 0;
}
#endif

#if (CCP_COUNT >= 3) && !defined(CCP3_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT3Interrupt(void)
{
    (*_ccps[CCP3_ID].handler)();
    _CCT3IF = 0;
}
#endif

#if (CCP_COUNT >= 4) && !defined(CCP4_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT4Interrupt(void)
{
    (*_ccps[CCP4_ID].handler)();
    _CCT4IF = 0;
}
#endif

#if (CCP_COUNT >= 5) && !defined(CCP5_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT5Interrupt(void)
{
    (*_ccps[CCP5_ID].handler)();
    _CCT5IF = 0;
}
#endif

#if (CCP_COUNT >= 6) && !defined(CCP6_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT6Interrupt(void)
{
    (*_ccps[CCP6_ID].handler)();
    _CCT6IF = 0;
}
#endif

#if (CCP_COUNT >= 7) && !defined(CCP7_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT7Interrupt(void)
{
    (*_ccps[CCP7_ID].handler)();
    _CCT7IF = 0;
}
#endif

#if (CCP_COUNT >= 8) && !defined(CCP8_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT8Interrupt(void)
{
    (*_ccps[CCP8_ID].handler)();
    _CCT8IF = 0;
}
#endif

#if (CCP_COUNT >= 9) && !defined(CCP9_DISABLE)
void __attribute__((interrupt, auto_psv, weak)) _CCT9Interrupt(void)
{
    (*_ccps[CCP9_ID].handler)();
    _CCT9IF = 0;
}
#endif
