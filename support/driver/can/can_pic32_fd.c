/**
 * @file can_pic32_fd.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date April 19, 2022, 10:57 PM
 *
 * @brief CAN support for udevkit for PIC32MK with CAN Fd
 *
 * Implementation based on Microchip document DS60001549A :
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/Section_56_Controller_Area_Network_with_Flexible_Data_rate_DS60001549A.pdf
 */

#include "can.h"

#include <archi.h>
#include <driver/int.h>
#include <driver/sysclock.h>

enum
{
    CAN_FLAG_UNUSED = 0x00
};
typedef struct
{
    union
    {
        struct
        {
            unsigned used : 1;
            unsigned enabled : 1;
            unsigned : 6;
        };
        uint8_t val;
    };
} can_status;

struct can_dev
{
    CAN_MODE mode;
    uint32_t bitRate;
    uint8_t propagSeg;
    uint8_t s1Seg;
    uint8_t s2Seg;
    can_status flags;
    void (*fifoHandler)(uint8_t fifo, uint8_t event);
};

#ifdef UDEVKIT_HAVE_CONFIG
#    include "udevkit_config.h"
#endif

#ifndef INT_MODE
#    define INT_MODE INT_DEFAULT_MODE
#endif
#ifndef CAN_INTERRUPT_PRIORITY
#    define CAN_INTERRUPT_PRIORITY 4
#endif
#ifndef CAN1_INT_TX_PRIORITY
#    define CAN1_INT_PRIORITY CAN_INTERRUPT_PRIORITY
#endif
#ifndef CAN2_INT_TX_PRIORITY
#    define CAN2_INT_PRIORITY CAN_INTERRUPT_PRIORITY
#endif
#ifndef CAN3_INT_TX_PRIORITY
#    define CAN3_INT_PRIORITY CAN_INTERRUPT_PRIORITY
#endif
#ifndef CAN4_INT_TX_PRIORITY
#    define CAN4_INT_PRIORITY CAN_INTERRUPT_PRIORITY
#endif

#if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
#    ifndef CAN1_FIFO_SIZE
#        define CAN1_FIFO_SIZE (32 * (CAN_MESSAGE_HEADER_SIZE + 8U))  // 32 messages of 8 bytes
#    endif
static uint8_t __attribute__((coherent, aligned(16), noload, section(".can1_fifos"))) _can1_fifo_buffer[CAN1_FIFO_SIZE];
void CAN1Interrupt(void);
#endif

#if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
#    ifndef CAN2_FIFO_SIZE
#        define CAN2_FIFO_SIZE (32 * (CAN_MESSAGE_HEADER_SIZE + 8U))  // 32 messages of 8 bytes
#    endif
static uint8_t __attribute__((coherent, aligned(16), noload, section(".can2_fifos"))) _can2_fifo_buffer[CAN2_FIFO_SIZE];
void CAN2Interrupt(void);
#endif

#if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
#    ifndef CAN3_FIFO_SIZE
#        define CAN3_FIFO_SIZE (32 * (CAN_MESSAGE_HEADER_SIZE + 8U))  // 32 messages of 8 bytes
#    endif
static uint8_t __attribute__((coherent, aligned(16), noload, section(".can3_fifos"))) _can3_fifo_buffer[CAN3_FIFO_SIZE];
void CAN3Interrupt(void);
#endif

#if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
#    ifndef CAN4_FIFO_SIZE
#        define CAN4_FIFO_SIZE (32 * (CAN_MESSAGE_HEADER_SIZE + 8U))  // 32 messages of 8 bytes
#    endif
static uint8_t __attribute__((coherent, aligned(16), noload, section(".can4_fifos"))) _can4_fifo_buffer[CAN4_FIFO_SIZE];
void CAN4Interrupt(void);
#endif

#ifndef CAN_TIMEOUT
#    define CAN_TIMEOUT 10000
#endif

static struct can_dev _cans[] = {
#if CAN_COUNT >= 1
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}, .fifoHandler = NULL},
#endif
#if CAN_COUNT >= 2
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}, .fifoHandler = NULL},
#endif
#if CAN_COUNT >= 3
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}, .fifoHandler = NULL},
#endif
#if CAN_COUNT >= 4
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}, .fifoHandler = NULL},
#endif
};

/**
 * @brief Gives a free CAN bus number and open it
 * @return CAN bus number
 */
rt_dev_t can_getFreeDevice(void)
{
#if CAN_COUNT >= 1
    uint8_t can_id;
    for (can_id = 0; can_id < CAN_COUNT; can_id++)
    {
        if (_cans[can_id].flags.used == 0)
        {
            break;
        }
    }

    if (can_id == CAN_COUNT)
    {
        return NULLDEV;
    }
    rt_dev_t device = MKDEV(DEV_CLASS_CAN, can_id);

    can_open(device);

    return device;
#else
    return NULLDEV;
#endif
}

/**
 * @brief Opens a CAN bus
 * @param can CAN bus id
 * @return 0 if ok, -1 in case of error
 */
int can_open(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }
    if (_cans[can].flags.used == 1)
    {
        return -1;
    }

    _cans[can].flags.used = 1;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Closes and release a CAN bus
 * @param device CAN bus number
 * @return 0 if ok, -1 in case of error
 */
int can_close(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    can_disable(device);

    _cans[can].flags.val = CAN_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief CAN sdk state
 * @param device can device number
 * @return true if can was openned by can_open function
 */
bool can_isOpened(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return (_cans[can].flags.used == 1);
}

/**
 * @brief Enables the specified CAN bus
 * @param device CAN bus number
 * @return 0 if ok, -1 in case of error
 */
int can_enable(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    _cans[can].flags.enabled = 1;

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            // assign memory
            CFD1FIFOBA = KVA_TO_PA(_can1_fifo_buffer);

            CFD1CONbits.BRSDIS = 0x0;
            CFD1CONbits.STEF = 0x0;  // Don't save transmitted messages in TEF
            CFD1CONbits.TXQEN = 0x1;

            // fifo 0 (transmit)
            CFD1TXQCONbits.FSIZE = 15;               // 16 messages
            CFD1TXQCONbits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data

            // fifo 1 (receive)
            CFD1FIFOCON1bits.FSIZE = 15;               // 16 messages
            CFD1FIFOCON1bits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data
            CFD1FIFOCON1bits.TXEN = 0;

            // filter 0 for fifo 1
            CFD1FLTCON0bits.F0BP = 1;       // Store messages in FIFO1
            CFD1FLTOBJ0bits.SID = 0x000;    // Filter 1 EID
            CFD1FLTOBJ0bits.EID = 0x00000;  // Filter 1 SID
            CFD1FLTOBJ0bits.EXIDE = 1;      // Filter EID messages
            CFD1FLTCON0bits.FLTEN0 = 1;     // Enable the filter

            // mask 0 for filter 0
            CFD1MASK0bits.MSID = 0x000;    // Ignore all bits in comparison
            CFD1MASK0bits.MEID = 0x00000;  // Ignore all bits in comparison
            CFD1MASK0bits.MIDE = 0;        // Match all message types
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            // assign memory
            CFD2FIFOBA = KVA_TO_PA(_can2_fifo_buffer);

            CFD2CONbits.BRSDIS = 0x0;
            CFD2CONbits.STEF = 0x0;  // Don't save transmitted messages in TEF
            CFD2CONbits.TXQEN = 0x1;

            // fifo 0 (transmit)
            CFD2TXQCONbits.FSIZE = 15;               // 16 messages
            CFD2TXQCONbits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data

            // fifo 1 (receive)
            CFD2FIFOCON1bits.FSIZE = 15;               // 16 messages
            CFD2FIFOCON1bits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data
            CFD2FIFOCON1bits.TXEN = 0;

            // filter 0 for fifo 1
            CFD2FLTCON0bits.F0BP = 1;       // Store messages in FIFO1
            CFD2FLTOBJ0bits.SID = 0x000;    // Filter 1 EID
            CFD2FLTOBJ0bits.EID = 0x00000;  // Filter 1 SID
            CFD2FLTOBJ0bits.EXIDE = 1;      // Filter EID messages
            CFD2FLTCON0bits.FLTEN0 = 1;     // Enable the filter

            // mask 0 for filter 0
            CFD2MASK0bits.MSID = 0x000;    // Ignore all bits in comparison
            CFD2MASK0bits.MEID = 0x00000;  // Ignore all bits in comparison
            CFD2MASK0bits.MIDE = 0;        // Match all message types
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            // assign memory
            CFD3FIFOBA = KVA_TO_PA(_can3_fifo_buffer);

            CFD3CONbits.BRSDIS = 0x0;
            CFD3CONbits.STEF = 0x0;  // Don't save transmitted messages in TEF
            CFD3CONbits.TXQEN = 0x1;

            // fifo 0 (transmit)
            CFD3TXQCONbits.FSIZE = 15;               // 16 messages
            CFD3TXQCONbits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data

            // fifo 1 (receive)
            CFD3FIFOCON1bits.FSIZE = 15;               // 16 messages
            CFD3FIFOCON1bits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data
            CFD3FIFOCON1bits.TXEN = 0;

            // filter 0 for fifo 1
            CFD3FLTCON0bits.F0BP = 1;       // Store messages in FIFO1
            CFD3FLTOBJ0bits.SID = 0x000;    // Filter 1 EID
            CFD3FLTOBJ0bits.EID = 0x00000;  // Filter 1 SID
            CFD3FLTOBJ0bits.EXIDE = 1;      // Filter EID messages
            CFD3FLTCON0bits.FLTEN0 = 1;     // Enable the filter

            // mask 0 for filter 0
            CFD3MASK0bits.MSID = 0x000;    // Ignore all bits in comparison
            CFD3MASK0bits.MEID = 0x00000;  // Ignore all bits in comparison
            CFD3MASK0bits.MIDE = 0;        // Match all message types
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            // assign memory
            CFD4FIFOBA = KVA_TO_PA(_can4_fifo_buffer);

            CFD4CONbits.BRSDIS = 0x0;
            CFD4CONbits.STEF = 0x0;  // Don't save transmitted messages in TEF
            CFD4CONbits.TXQEN = 0x1;

            // fifo 0 (transmit)
            CFD4TXQCONbits.FSIZE = 15;               // 16 messages
            CFD4TXQCONbits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data

            // fifo 1 (receive)
            CFD4FIFOCON1bits.FSIZE = 15;               // 16 messages
            CFD4FIFOCON1bits.PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data
            CFD4FIFOCON1bits.TXEN = 0;

            // filter 0 for fifo 1
            CFD4FLTCON0bits.F0BP = 1;       // Store messages in FIFO1
            CFD4FLTOBJ0bits.SID = 0x000;    // Filter 1 EID
            CFD4FLTOBJ0bits.EID = 0x00000;  // Filter 1 SID
            CFD4FLTOBJ0bits.EXIDE = 1;      // Filter EID messages
            CFD4FLTCON0bits.FLTEN0 = 1;     // Enable the filter

            // mask 0 for filter 0
            CFD4MASK0bits.MSID = 0x000;    // Ignore all bits in comparison
            CFD4MASK0bits.MEID = 0x00000;  // Ignore all bits in comparison
            CFD4MASK0bits.MIDE = 0;        // Match all message types
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disables the specified CAN bus
 * @param device CAN bus number
 * @return 0 if ok, -1 in case of error
 */
int can_disable(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    _cans[can].flags.enabled = 0;

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            _CAN1IE = 0;  // disable can global interrupt
            CFD1CONbits.REQOP = 4;
            while (CFD1CONbits.OPMOD != 4)
            {
                ;
            }
            CFD1CONbits.ON = 0;  // disable can
            while (CFD1CONbits.BUSY == 1)
            {
                ;
            }
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            _CAN2IE = 0;  // disable can global interrupt
            CFD2CONbits.REQOP = 4;
            while (CFD2CONbits.OPMOD != 4)
            {
                ;
            }
            CFD2CONbits.ON = 0;  // disable can
            while (CFD2CONbits.BUSY == 1)
            {
                ;
            }
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            _CAN3IE = 0;  // disable can global interrupt
            CFD3CONbits.REQOP = 4;
            while (CFD3CONbits.OPMOD != 4)
            {
                ;
            }
            CFD3CONbits.ON = 0;  // disable can
            while (CFD3CONbits.BUSY == 1)
            {
                ;
            }
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            _CAN4IE = 0;  // disable can global interrupt
            CFD4CONbits.REQOP = 4;
            while (CFD4CONbits.OPMOD != 4)
            {
                ;
            }
            CFD4CONbits.ON = 0;  // disable can
            while (CFD4CONbits.BUSY == 1)
            {
                ;
            }
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Can sdk enabled state
 * @param device can device number
 * @return true if can was enabled by can_enable function
 */
bool can_isEnabled(rt_dev_t device)
{
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }

    return (_cans[can].flags.enabled == 1);
}

/**
 * @brief Sets configuration (can version and mode) of the specified CAN bus
 * @param device CAN bus number
 * @param mode CAN mode of operation
 * @return 0 if ok, -1 in case of error
 */
int can_setMode(rt_dev_t device, CAN_MODE mode)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    uint8_t modeBits;
    int32_t timeout = CAN_TIMEOUT;
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    // check parameters
    switch (mode)
    {
        case CAN_MODE_NORMAL_FD:
            modeBits = 0b000;
            break;

        case CAN_MODE_DISABLED:
            modeBits = 0b001;
            break;

        case CAN_MODE_LOOPBACK:
            modeBits = 0b010;
            break;

        case CAN_MODE_LISTENONLY:
            modeBits = 0b011;
            break;

        case CAN_MODE_CONFIGURATION:
            modeBits = 0b100;
            break;

        case CAN_MODE_NORMAL:
            modeBits = 0b110;
            break;

        default:
            return -1;
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            CFD1CONbits.ON = 1;
            CFD1CONbits.REQOP = modeBits;
            while ((CFD1CONbits.OPMOD != modeBits) && (--timeout >= 0))
            {
                ;
            }
            if (CFD1CONbits.OPMOD != modeBits)
            {
                return -2;  // TODO map error enum
            }
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            CFD2CONbits.ON = 1;
            CFD2CONbits.REQOP = modeBits;
            while ((CFD2CONbits.OPMOD != modeBits) && (--timeout >= 0))
            {
                ;
            }
            if (CFD2CONbits.OPMOD != modeBits)
            {
                return -2;  // TODO map error enum
            }
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            CFD3CONbits.ON = 1;
            CFD3CONbits.REQOP = modeBits;
            while ((CFD3CONbits.OPMOD != modeBits) && (--timeout >= 0))
            {
                ;
            }
            if (CFD3CONbits.OPMOD != modeBits)
            {
                return -2;  // TODO map error enum
            }
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            CFD4CONbits.ON = 1;
            CFD4CONbits.REQOP = modeBits;
            while ((CFD4CONbits.OPMOD != modeBits) && (--timeout >= 0))
            {
                ;
            }
            if (CFD4CONbits.OPMOD != modeBits)
            {
                return -2;  // TODO map error enum
            }
            break;
#    endif
    }
    _cans[can].mode = mode;

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Returns the current bus mode of operation
 * @param device CAN device number
 * @return current mode of operation
 */
CAN_MODE can_mode(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return CAN_MODE_DISABLED;
    }

    return _cans[can].mode;
#else
    return 0;
#endif
}

/**
 * @brief Sets bit rate and segments timing
 *
 * Sum of all segments (propagSeg, s1Seg, s2Seg) + 1 must be contained in
 * the range of 8 to 25 quantums.
 *
 * CAN Bit Timing (8-25 Tq) segments computation
 *
 * | Sync | Propag seg | Phase seg 1 |Phase seg 2 |
 *
 * | 1 Tq |   1-8 Tq   |   1-8 Tq    |   1-8 Tq    |
 *
 *                              sample point
 *
 * @param device CAN device number
 * @param bitRate bit rate speed in bit/s
 * @param propagSeg propagation segment duration in number of quantum (1-8)
 * @param s1Seg segment 1 duration in number of quantum (1-8)
 * @param s2Seg segment 2 duration in number of quantum (1-8)
 * @return 0 if ok, -1 in case of error
 */
int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    uint8_t quantum;
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    if (propagSeg > 8 || s1Seg > 8 || s2Seg > 8)
    {
        return -1;
    }
    if (propagSeg < 1 || s1Seg < 1 || s2Seg < 1)
    {
        return -1;
    }
    quantum = propagSeg + s1Seg + s2Seg;
    if (quantum < 8 || quantum > 25)
    {
        return -1;
    }

    _cans[can].bitRate = bitRate;
    _cans[can].propagSeg = propagSeg;
    _cans[can].s1Seg = s1Seg;
    _cans[can].s2Seg = s2Seg;

    uint32_t can_freq = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN);
    uint16_t bitRateDiv = can_freq / (bitRate * quantum);
    if (bitRateDiv > 256)
    {
        bitRateDiv = 256;
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            CFD1CONbits.ON = 1;
            CFD1CONbits.REQOP = 4;
            while (CFD1CONbits.OPMOD != 4)
            {
                ;
            }
            CFD1CONbits.CLKSEL0 = 0b1;  // REFCLK4 clock selected

            // NOMINAL BIT TIME CONFIGURATION
            CFD1NBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD1NBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-256)
            CFD1NBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-128) SEG2PH >= SEG1PH
            CFD1NBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-128)

            // DATA BIT TIME CONFIGURATION
            CFD1DBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD1DBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-32)
            CFD1DBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-16) SEG2PH >= SEG1PH
            CFD1DBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-16)
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            CFD2CONbits.ON = 1;
            CFD2CONbits.REQOP = 4;
            while (CFD2CONbits.OPMOD != 4)
            {
                ;
            }
            CFD2CONbits.CLKSEL0 = 0b1;  // REFCLK4 clock selected

            // NOMINAL BIT TIME CONFIGURATION
            CFD2NBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD2NBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-256)
            CFD2NBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-128) SEG2PH >= SEG1PH
            CFD2NBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-128)

            // DATA BIT TIME CONFIGURATION
            CFD2DBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD2DBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-32)
            CFD2DBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-16) SEG2PH >= SEG1PH
            CFD2DBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-16)
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            CFD3CONbits.ON = 1;
            CFD3CONbits.REQOP = 4;
            while (CFD3CONbits.OPMOD != 4)
            {
                ;
            }
            CFD3CONbits.CLKSEL0 = 0b1;  // REFCLK4 clock selected

            // NOMINAL BIT TIME CONFIGURATION
            CFD3NBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD3NBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-256)
            CFD3NBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-128) SEG2PH >= SEG1PH
            CFD3NBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-128)

            // DATA BIT TIME CONFIGURATION
            CFD3DBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD3DBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-32)
            CFD3DBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-16) SEG2PH >= SEG1PH
            CFD3DBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-16)
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            CFD4CONbits.ON = 1;
            CFD4CONbits.REQOP = 4;
            while (CFD4CONbits.OPMOD != 4)
            {
                ;
            }
            CFD4CONbits.CLKSEL0 = 0b1;  // REFCLK4 clock selected

            // NOMINAL BIT TIME CONFIGURATION
            CFD4NBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD4NBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-256)
            CFD4NBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-128) SEG2PH >= SEG1PH
            CFD4NBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-128)

            // DATA BIT TIME CONFIGURATION
            CFD4DBTCFGbits.BRP = bitRateDiv - 1;  // bit rate divisor (1-256)
            CFD4DBTCFGbits.TSEG1 = s1Seg - 1;     // Phase Buffer Segment 1 (1-32)
            CFD4DBTCFGbits.TSEG2 = s2Seg - 1;     // Phase Buffer Segment 2 (1-16) SEG2PH >= SEG1PH
            CFD4DBTCFGbits.SJW = 0;               // Synchronization Jump Width (1-16)
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Returns the current bit rate in bits/s
 * @param device CAN device number
 * @return bit rate in bits/s if OK, 0 in case of error
 */
uint32_t can_bitRate(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    return _cans[can].bitRate;
#else
    return 0;
#endif
}

/**
 * @brief Gets the effective bit rate in hertz
 * @param device CAN device number
 * @return speed of receive and transmit in bits/s, 0 in case of error
 */
uint32_t can_effectiveBitRate(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    uint16_t bitRateDiv = 1;
    uint8_t quantums = _cans[can].propagSeg + _cans[can].s1Seg + _cans[can].s2Seg;

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            bitRateDiv = (CFD1NBTCFGbits.BRP + 1);  // bit rate divisor (1-256)
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            bitRateDiv = (CFD2NBTCFGbits.BRP + 1);  // bit rate divisor (1-256)
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            bitRateDiv = (CFD3NBTCFGbits.BRP + 1);  // bit rate divisor (1-256)
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            bitRateDiv = (CFD4NBTCFGbits.BRP + 1);  // bit rate divisor (1-256)
            break;
#    endif
    }

    uint32_t can_freq = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN);
    return can_freq / (bitRateDiv * quantums);
#else
    return 0;
#endif
}

/**
 * @brief Gets propagation segment duration in quantums
 * @param device CAN device number
 * @return propagation segment duration in quantums, 0 in case of error
 */
uint8_t can_propagSeg(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    return _cans[can].propagSeg;
#else
    return 0;
#endif
}

/**
 * @brief Gets segment 1 duration in quantums
 * @param device CAN device number
 * @return segment 1 duration in quantums, 0 in case of error
 */
uint8_t can_s1Seg(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    return _cans[can].s1Seg;
#else
    return 0;
#endif
}

/**
 * @brief Gets segment 2 duration in quantums
 * @param device CAN device number
 * @return segment 2 duration in quantums, 0 in case of error
 */
uint8_t can_s2Seg(rt_dev_t device)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    return _cans[can].s2Seg;
#else
    return 0;
#endif
}

#define CFD1FIFOCON(fifo)    ((volatile uint32_t *)(&CFD1TXQCON + (((uint8_t)(fifo)) * 12)))
#define CFD1FIFOCONSET(fifo) (CFD1FIFOCON(fifo) + 2)
#define CFD1FIFOSTA(fifo)    ((volatile uint32_t *)(&CFD1TXQSTA + (((uint8_t)(fifo)) * 12)))
#define CFD1FIFOSTACLR(fifo) (CFD1FIFOSTA(fifo) + 1)
#define CFD1FIFOUA(fifo)     ((volatile uint32_t *)(&CFD1TXQUA + (((uint8_t)(fifo)) * 12)))

#define CFD2FIFOCON(fifo)    ((volatile uint32_t *)(&CFD2TXQCON + (((uint8_t)(fifo)) * 12)))
#define CFD2FIFOCONSET(fifo) (CFD2FIFOCON(fifo) + 2)
#define CFD2FIFOSTA(fifo)    ((volatile uint32_t *)(&CFD2TXQSTA + (((uint8_t)(fifo)) * 12)))
#define CFD2FIFOSTACLR(fifo) (CFD1FIFOSTA(fifo) + 1)
#define CFD2FIFOUA(fifo)     ((volatile uint32_t *)(&CFD2TXQUA + (((uint8_t)(fifo)) * 12)))

#define CFD3FIFOCON(fifo)    ((volatile uint32_t *)(&CFD3TXQCON + (((uint8_t)(fifo)) * 12)))
#define CFD3FIFOCONSET(fifo) (CFD3FIFOCON(fifo) + 2)
#define CFD3FIFOSTA(fifo)    ((volatile uint32_t *)(&CFD3TXQSTA + (((uint8_t)(fifo)) * 12)))
#define CFD3FIFOSTACLR(fifo) (CFD1FIFOSTA(fifo) + 1)
#define CFD3FIFOUA(fifo)     ((volatile uint32_t *)(&CFD3TXQUA + (((uint8_t)(fifo)) * 12)))

#define CFD4FIFOCON(fifo)    ((volatile uint32_t *)(&CFD4TXQCON + (((uint8_t)(fifo)) * 12)))
#define CFD4FIFOCONSET(fifo) (CFD4FIFOCON(fifo) + 2)
#define CFD4FIFOSTA(fifo)    ((volatile uint32_t *)(&CFD4TXQSTA + (((uint8_t)(fifo)) * 12)))
#define CFD4FIFOSTACLR(fifo) (CFD1FIFOSTA(fifo) + 1)
#define CFD4FIFOUA(fifo)     ((volatile uint32_t *)(&CFD4TXQUA + (((uint8_t)(fifo)) * 12)))

int can_setTxFifo(rt_dev_t device, uint8_t fifo, uint8_t messageCount)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    if (fifo >= CAN_FIFO_COUNT)
    {
        return -1;
    }
    if (messageCount > 32)
    {
        return -1;
    }

    __CFD1TXQCONbits_t *conBits = NULL;
    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD1FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD2FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD3FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD4FIFOCON(fifo);
            break;
#    endif
        default:
            return -1;
    }

    conBits->FSIZE = messageCount - 1;
    conBits->PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data
    conBits->TXEN = 1;

    return 0;
#else
    return -1;
#endif
}

int can_setRxFifo(rt_dev_t device, uint8_t fifo, uint8_t messageCount)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    if (fifo == 0)
    {
        return -1;
    }
    if (fifo >= CAN_FIFO_COUNT)
    {
        return -1;
    }
    if (messageCount > 32)
    {
        return -1;
    }

    __CFD1TXQCONbits_t *conBits = NULL;
    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD1FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD2FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD3FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            conBits = (__CFD1TXQCONbits_t *)CFD4FIFOCON(fifo);
            break;
#    endif
        default:
            return -1;
    }

    conBits->FSIZE = messageCount - 1;
    conBits->PLSIZE = CAN_FIFO_DATA8;  // 8 bytes of data
    conBits->TXEN = 0;

    return 0;
#else
    return -1;
#endif
}

int can_setFifoHandler(rt_dev_t device, void (*handler)(uint8_t fifo, uint8_t event))
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            CFD1INTbits.RXIE = 1;
            CFD1INTbits.TXIE = 1;
            _CAN1IP = CAN1_INT_PRIORITY;
            _CAN1IE = 1;
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            CFD2INTbits.RXIE = 1;
            CFD2INTbits.TXIE = 1;
            _CAN2IP = CAN2_INT_PRIORITY;
            _CAN2IE = 1;
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            CFD3INTbits.RXIE = 1;
            CFD3INTbits.TXIE = 1;
            _CAN3IP = CAN3_INT_PRIORITY;
            _CAN3IE = 1;
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            CFD4INTbits.RXIE = 1;
            CFD4INTbits.TXIE = 1;
            _CAN4IP = CAN4_INT_PRIORITY;
            _CAN4IE = 1;
            break;
#    endif
        default:
            return -1;
    }
    _cans[can].fifoHandler = handler;

    return 0;
#else
    return -1;
#endif
}

int can_setFifoEventsHandler(rt_dev_t device, uint8_t fifo, CAN_FIFO_EVENTS eventBits)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    if (fifo == 0)
    {
        return -1;
    }
    if (fifo >= CAN_FIFO_COUNT)
    {
        return -1;
    }

    __CFD1FIFOCON1bits_t *conBits = NULL;
    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            conBits = (__CFD1FIFOCON1bits_t *)CFD1FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            conBits = (__CFD1FIFOCON1bits_t *)CFD2FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            conBits = (__CFD1FIFOCON1bits_t *)CFD3FIFOCON(fifo);
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            conBits = (__CFD1FIFOCON1bits_t *)CFD4FIFOCON(fifo);
            break;
#    endif
        default:
            return -1;
    }

    conBits->RXOVIE = ((eventBits & CAN_RXFIFO_OVERFLOW) != 0) ? 1 : 0;     // Overflow Interrupt Enable bit
    conBits->TFERFFIE = ((eventBits & CAN_RXFIFO_FULL) != 0) ? 1 : 0;       // Transmit/Receive FIFO Empty/Full Interrupt Enable bit
    conBits->TFHRFHIE = ((eventBits & CAN_RXFIFO_HALF_FULL) != 0) ? 1 : 0;  // Transmit/Receive FIFO Half Empty/Half Full Interrupt Enable bit
    conBits->TFNRFNIE = ((eventBits & CAN_RXFIFO_NOT_EMPTY) != 0) ? 1 : 0;  // Transmit/Receive FIFO Not Full/Not Empty Interrupt Enable bit

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Write a can message to fifo
 * @param device CAN device number
 * @param fifo fifo number to put the message
 * @param header CAN message header struct (id, flags, data size)
 * @return 0 if message is successfully putted inside fifo, -1 in case of error
 */
int can_send(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, const char *data)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    CAN_TxMsgBuffer *buffer = NULL;

    if (fifo >= CAN_FIFO_COUNT)
    {
        return -1;
    }

    switch (can)
    {
        case CAN1_ID:
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
            if ((*CFD1FIFOSTA(fifo) & _CFD1FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO full
                return 0;
            }
            buffer = (CAN_TxMsgBuffer *)PA_TO_KVA1(*CFD1FIFOUA(fifo));
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            if ((*CFD2FIFOSTA(fifo) & _CFD2FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO full
                return 0;
            }
            buffer = (CAN_TxMsgBuffer *)PA_TO_KVA1(*CFD2FIFOUA(fifo));
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            if ((*CFD3FIFOSTA(fifo) & _CFD3FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO full
                return 0;
            }
            buffer = (CAN_TxMsgBuffer *)PA_TO_KVA1(*CFD3FIFOUA(fifo));
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            if ((*CFD4FIFOSTA(fifo) & _CFD4FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO full
                return 0;
            }
            buffer = (CAN_TxMsgBuffer *)PA_TO_KVA1(*CFD4FIFOUA(fifo));
            break;
#    endif

        default:
            return -1;
    }

    if (buffer != NULL)
    {
        // clear the message header
        buffer->messageWord[0] = 0;
        buffer->messageWord[1] = 0;

        // set can id
        if ((header->flags & CAN_VERS2BA) == CAN_VERS2BA)
        {
            buffer->ctrl.IDE = 1;                   // extended id
            buffer->id.EID = header->id & 0x3FFFF;  // Message EID
            buffer->id.SID = header->id >> 18;      // Message EID
        }
        else
        {
            buffer->id.SID = header->id;  // Message SID
        }

        // RTR
        if (header->flags & CAN_RTR)
        {
            buffer->ctrl.RTR = 1;
            header->size = 0;
            buffer->ctrl.DLC = 0;
        }
        else
        {
            // set data and data size
            if (header->size > 8)
            {
                header->size = 8;
            }
            buffer->ctrl.DLC = header->size;  // Data Length
            for (unsigned int i = 0; i < header->size; i++)
            {
                buffer->data[i] = data[i];
            }
        }
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            *CFD1FIFOCONSET(fifo) = _CFD1FIFOCON1_UINC_MASK;   // Set the UINC
            *CFD1FIFOCONSET(fifo) = _CFD1FIFOCON1_TXREQ_MASK;  // Set the TXREQ bit
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            *CFD2FIFOCONSET(fifo) = _CFD2FIFOCON1_UINC_MASK;   // Set the UINC
            *CFD2FIFOCONSET(fifo) = _CFD2FIFOCON1_TXREQ_MASK;  // Set the TXREQ bit
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            *CFD3FIFOCONSET(fifo) = _CFD3FIFOCON1_UINC_MASK;   // Set the UINC
            *CFD3FIFOCONSET(fifo) = _CFD3FIFOCON1_TXREQ_MASK;  // Set the TXREQ bit
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            *CFD4FIFOCONSET(fifo) = _CFD4FIFOCON1_UINC_MASK;   // Set the UINC
            *CFD4FIFOCONSET(fifo) = _CFD4FIFOCON1_TXREQ_MASK;  // Set the TXREQ bit
            break;
#    endif
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Read a can message from fifo
 * @param device CAN device number
 * @param fifo fifo number to read the message
 * @param header CAN message header struct (id, flags, data size)
 * @return 0 if no message is read, -1 in case of error, 1 if a message is read
 */
int can_rec(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    CAN_FLAGS flagValue = CAN_VERS1;
    CAN_RxMsgBuffer *buffer = NULL;

    if (fifo == 0 || fifo >= CAN_FIFO_COUNT)
    {
        return -1;
    }

    switch (can)
    {
        case CAN1_ID:
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
            if ((*CFD1FIFOSTA(fifo) & _CFD1FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO empty
                return 0;
            }
            buffer = (CAN_RxMsgBuffer *)PA_TO_KVA1(*CFD1FIFOUA(fifo));
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            if ((*CFD2FIFOSTA(fifo) & _CFD2FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO empty
                return 0;
            }
            buffer = (CAN_RxMsgBuffer *)PA_TO_KVA1(*CFD2FIFOUA(fifo));
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            if ((*CFD3FIFOSTA(fifo) & _CFD3FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO empty
                return 0;
            }
            buffer = (CAN_RxMsgBuffer *)PA_TO_KVA1(*CFD3FIFOUA(fifo));
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            if ((*CFD4FIFOSTA(fifo) & _CFD4FIFOSTA1_TFNRFNIF_MASK) == 0)
            {
                // FIFO empty
                return 0;
            }
            buffer = (CAN_RxMsgBuffer *)PA_TO_KVA1(*CFD4FIFOUA(fifo));
            break;
#    endif

        default:
            return -1;
    }

    // ID
    if (buffer->ctrl.IDE == 1)
    {
        flagValue = (CAN_FLAGS)(flagValue + CAN_VERS2BA);  // extended ID
        header->id = buffer->id.EID + (buffer->id.SID << 18);
    }
    else
    {
        header->id = buffer->id.SID & 0x7FF;
    }

    // data read and copy
    header->size = buffer->ctrl.DLC;
    if (header->size > 8)
    {
        header->size = 0;
    }
    for (unsigned int i = 0; i < header->size; i++)
    {
        data[i] = buffer->data[i];
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            *CFD1FIFOCONSET(fifo) = _CFD1TEFCON_UINC_MASK;  // mark as read
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            *CFD2FIFOCONSET(fifo) = _CFD2TEFCON_UINC_MASK;  // mark as read
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN3_ID:
            *CFD3FIFOCONSET(fifo) = _CFD3TEFCON_UINC_MASK;  // mark as read
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN4_ID:
            *CFD4FIFOCONSET(fifo) = _CFD4TEFCON_UINC_MASK;  // mark as read
            break;
#    endif
    }

    // flags
    if (buffer->ctrl.BRS == 1)
    {
        flagValue = (CAN_FLAGS)(flagValue + CAN_RTR);
    }
    header->flags = flagValue;

    return 1;
#else
    return -1;
#endif
}

#define CFD1FLTOBJ(filter) ((volatile uint32_t *)(&CFD1FLTOBJ0 + (((uint8_t)(filter)) * 8)))
#define CFD1MASK(filter)   ((volatile uint32_t *)(&CFD1MASK0 + (((uint8_t)(filter)) * 8)))
#define CFD1FLTCON(filter) ((volatile uint8_t *)(&CFD1FLTCON0) + (((uint8_t)(filter)&0xFC) * 4 + ((uint8_t)(filter)&0x03)))

#define CFD2FLTOBJ(filter) ((volatile uint32_t *)(&CFD2FLTOBJ0 + (((uint8_t)(filter)) * 8)))
#define CFD2MASK(filter)   ((volatile uint32_t *)(&CFD2MASK0 + (((uint8_t)(filter)) * 8)))
#define CFD2FLTCON(filter) ((volatile uint8_t *)(&CFD2FLTCON0) + (((uint8_t)(filter)&0xFC) * 4 + ((uint8_t)(filter)&0x03)))

#define CFD3FLTOBJ(filter) ((volatile uint32_t *)(&CFD3FLTOBJ0 + (((uint8_t)(filter)) * 8)))
#define CFD3MASK(filter)   ((volatile uint32_t *)(&CFD3MASK0 + (((uint8_t)(filter)) * 8)))
#define CFD3FLTCON(filter) ((volatile uint8_t *)(&CFD3FLTCON0) + (((uint8_t)(filter)&0xFC) * 4 + ((uint8_t)(filter)&0x03)))

#define CFD4FLTOBJ(filter) ((volatile uint32_t *)(&CFD4FLTOBJ0 + (((uint8_t)(filter)) * 8)))
#define CFD4MASK(filter)   ((volatile uint32_t *)(&CFD4MASK0 + (((uint8_t)(filter)) * 8)))
#define CFD4FLTCON(filter) ((volatile uint8_t *)(&CFD4FLTCON0) + (((uint8_t)(filter)&0xFC) * 4 + ((uint8_t)(filter)&0x03)))

/**
 * @brief Configure the specified CAN filter
 * @param device CAN bus number,
 * @param nFilter number of the filter to configure
 * @param fifo fifo number where the message is stored
 * @param idFilter Id bits use for the filter
 * @param mask masked bits use for the filter
 * @param frame frames format filtering
 * @return 0 if ok, -1 in case of error
 */
int can_filterSet(rt_dev_t device, uint8_t nFilter, uint8_t fifo, uint32_t idFilter, uint32_t mask, CAN_FRAME_FORMAT_FLAGS frame)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    if (fifo >= CAN_FIFO_COUNT)
    {
        return -1;
    }

    if (nFilter >= CAN_FILTER_COUNT)
    {
        return -1;
    }

    uint32_t filterObj, filterMask;
    if (frame == CAN_FRAME_STD)
    {
        filterObj = idFilter & 0x000007FF;
        filterMask = _CFD1MASK0_MIDE_MASK | (mask & 0x000007FF);
    }
    else if (frame == CAN_FRAME_EXT)
    {
        filterObj = _CFD1FLTOBJ0_EXIDE_MASK | ((idFilter & 0x1FFC0000) >> 18) | ((idFilter & 0x0003FFFF) << 11);
        filterMask = _CFD1MASK0_MIDE_MASK | ((mask & 0x1FFC0000) >> 18) | ((mask & 0x0003FFFF) << 11);
    }
    else if (frame == CAN_FRAME_BOTH)
    {
        filterObj = _CFD1FLTOBJ0_EXIDE_MASK | ((idFilter & 0x1FFC0000) >> 18) | ((idFilter & 0x0003FFFF) << 11);
        filterMask = ((mask & 0x1FFC0000) >> 18) | ((mask & 0x0003FFFF) << 11);
    }
    else
    {
        return -1;
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            *CFD1FLTCON(nFilter) = 0;            // disable fifo
            *CFD1FLTCON(nFilter) = fifo & 0x1F;  // set destination fifo
            *CFD1MASK(nFilter) = filterMask;
            *CFD1FLTOBJ(nFilter) = filterObj;
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            *CFD2FLTCON(nFilter) = 0;            // disable fifo
            *CFD2FLTCON(nFilter) = fifo & 0x1F;  // set destination fifo
            *CFD2MASK(nFilter) = filterMask;
            *CFD2FLTOBJ(nFilter) = filterObj;
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            *CFD3FLTCON(nFilter) = 0;            // disable fifo
            *CFD3FLTCON(nFilter) = fifo & 0x1F;  // set destination fifo
            *CFD3MASK(nFilter) = filterMask;
            *CFD3FLTOBJ(nFilter) = filterObj;
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            *CFD4FLTCON(nFilter) = 0;            // disable fifo
            *CFD4FLTCON(nFilter) = fifo & 0x1F;  // set destination fifo
            *CFD4MASK(nFilter) = filterMask;
            *CFD4FLTOBJ(nFilter) = filterObj;
            break;
#    endif

        default:
            return -1;
    }

    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Enable the specified CAN filter
 * @param device CAN bus number
 * @param nFilter number of the filter to enable
 * @return 0 if ok, -1 in case of error
 */
int can_filterEnable(rt_dev_t device, uint8_t nFilter)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    if (nFilter >= CAN_FILTER_COUNT)
    {
        return -1;
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            *CFD1FLTCON(nFilter) |= _CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            *CFD2FLTCON(nFilter) |= _CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            *CFD3FLTCON(nFilter) |= _CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            *CFD4FLTCON(nFilter) |= _CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif

        default:
            return -1;
    }
    return 0;
#else
    return -1;
#endif
}

/**
 * @brief Disable the specified CAN filter
 * @param device CAN bus number
 * @param nFilter number of the filter to disable
 * @return 0 if ok, -1 in case of error
 */
int can_filterDisable(rt_dev_t device, uint8_t nFilter)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);

    if (nFilter >= CAN_FILTER_COUNT)
    {
        return -1;
    }

    switch (can)
    {
#    if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
        case CAN1_ID:
            *CFD1FLTCON(nFilter) &= ~_CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif
#    if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
        case CAN2_ID:
            *CFD2FLTCON(nFilter) &= ~_CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif
#    if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
        case CAN3_ID:
            *CFD3FLTCON(nFilter) &= ~_CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif
#    if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
        case CAN4_ID:
            *CFD4FLTCON(nFilter) &= ~_CFD1FLTCON0_FLTEN0_MASK;
            break;
#    endif

        default:
            return -1;
    }

    return 0;
#else
    return -1;
#endif
}

#if (CAN_COUNT >= 1) && !defined(CAN1_DISABLE)
void INT_ISR(_CAN1_VECTOR, CAN1_INT_PRIORITY, INT_MODE) __attribute__((weak)) CAN1Interrupt(void)
{
    uint8_t fifo = CFD1VECbits.ICODE;  // TODO this register get also global can interrupts
    if (_cans[CAN1_ID].fifoHandler != NULL)
    {
        (*_cans[CAN1_ID].fifoHandler)(fifo, *CFD1FIFOSTA(fifo) & 0x0000001F);
    }
    *CFD1FIFOSTACLR(fifo) = 0x0000001F;

    _CAN1IF = 0;
}
#endif

#if (CAN_COUNT >= 2) && !defined(CAN2_DISABLE)
void INT_ISR(_CAN2_VECTOR, CAN2_INT_PRIORITY, INT_MODE) __attribute__((weak)) CAN2Interrupt(void)
{
    uint8_t fifo = CFD2VECbits.ICODE;  // TODO this register get also global can interrupts
    if (_cans[CAN2_ID].fifoHandler != NULL)
    {
        (*_cans[CAN2_ID].fifoHandler)(fifo, *CFD2FIFOSTA(fifo) & 0x0000001F);
    }
    *CFD2FIFOSTACLR(fifo) = 0x0000001F;

    _CAN2IF = 0;
}
#endif

#if (CAN_COUNT >= 3) && !defined(CAN3_DISABLE)
void INT_ISR(_CAN3_VECTOR, CAN3_INT_PRIORITY, INT_MODE) __attribute__((weak)) CAN3Interrupt(void)
{
    uint8_t fifo = CFD3VECbits.ICODE;  // TODO this register get also global can interrupts
    if (_cans[CAN3_ID].fifoHandler != NULL)
    {
        (*_cans[CAN3_ID].fifoHandler)(fifo, *CFD3FIFOSTA(fifo) & 0x0000001F);
    }
    *CFD3FIFOSTACLR(fifo) = 0x0000001F;

    _CAN3IF = 0;
}
#endif

#if (CAN_COUNT >= 4) && !defined(CAN4_DISABLE)
void INT_ISR(_CAN4_VECTOR, CAN4_INT_PRIORITY, INT_MODE) __attribute__((weak)) CAN4Interrupt(void)
{
    uint8_t fifo = CFD4VECbits.ICODE;  // TODO this register get also global can interrupts
    if (_cans[CAN4_ID].fifoHandler != NULL)
    {
        (*_cans[CAN4_ID].fifoHandler)(fifo, *CFD4FIFOSTA(fifo) & 0x0000001F);
    }
    *CFD4FIFOSTACLR(fifo) = 0x0000001F;

    _CAN4IF = 0;
}
#endif

/**
 * @brief Reconfigure clocks for all activated CANs devices. Call this function on clock change.
 */
void can_reconfig(void)
{
    for (uint8_t can_id = 0; can_id < CAN_COUNT; can_id++)
    {
        if (_cans[can_id].flags.used == 1 && _cans[can_id].bitRate != 0)
        {
            rt_dev_t device = MKDEV(DEV_CLASS_UART, can_id);
            CAN_MODE oldMode = can_mode(device);
            can_setBitTiming(device, _cans[can_id].bitRate, _cans[can_id].propagSeg, _cans[can_id].s1Seg, _cans[can_id].s2Seg);
            can_setMode(device, oldMode);
        }
    }
}
