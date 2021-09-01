/**
 * @file can_pic32.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2017-2021
 *
 * @date December 8 2017, 09:10 AM
 *
 * @brief CAN support for udevkit for PIC32MK, PIC32MX, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61154C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61154C.pdf
 */

#include "can.h"

#include <archi.h>
#include <driver/sysclock.h>

#if !defined(CAN_COUNT) || CAN_COUNT == 0
#    warning "No can on the current device or unknow device"
#endif

#define CAN_FLAG_UNUSED 0x00
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
};

#if CAN_COUNT >= 1
unsigned int CAN1FIFO[32 * 4];
#endif
#if CAN_COUNT >= 2
unsigned int CAN2FIFO[32 * 4];
#endif
#if CAN_COUNT >= 3
unsigned int CAN3FIFO[32 * 4];
#endif
#if CAN_COUNT >= 4
unsigned int CAN4FIFO[32 * 4];
#endif

struct can_dev cans[] = {
#if CAN_COUNT >= 1
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}},
#endif
#if CAN_COUNT >= 2
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}},
#endif
#if CAN_COUNT >= 3
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}},
#endif
#if CAN_COUNT >= 4
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}},
#endif
};

/**
 * @brief Gives a free CAN bus number and open it
 * @return CAN bus number
 */
rt_dev_t can_getFreeDevice(void)
{
#if CAN_COUNT >= 1
    uint8_t i;
    rt_dev_t device;

    for (i = 0; i < CAN_COUNT; i++)
    {
        if (cans[i].flags.used == 0)
        {
            break;
        }
    }

    if (i == CAN_COUNT)
    {
        return NULLDEV;
    }
    device = MKDEV(DEV_CLASS_CAN, i);

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
    if (cans[can].flags.used == 1)
    {
        return -1;
    }

    cans[can].flags.used = 1;

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

    cans[can].flags.val = CAN_FLAG_UNUSED;
    return 0;
#else
    return -1;
#endif
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

    cans[can].flags.enabled = 1;

    switch (can)
    {
        case 0:
            // assign memory
            C1FIFOBA = KVA_TO_PA(CAN1FIFO);
            // fifo 0 (transmit)
            C1FIFOCON0bits.FSIZE = 15;
            C1FIFOCON0SET = 0x80;
            // fifo 1 (receive)
            C1FIFOCON1bits.FSIZE = 15;
            C1FIFOCON1CLR = 0x80;
            // filter 1
            C1FLTCON0bits.FSEL1 = 1;   // Store messages in FIFO1
            C1FLTCON0bits.MSEL1 = 1;   // Use Mask 1
            C1RXF1bits.SID = 0x000;    // Filter 1 EID
            C1RXF1bits.EID = 0x00000;  // Filter 1 SID
            C1RXF1bits.EXID = 1;       // Filter EID messages
            C1FLTCON0bits.FLTEN1 = 1;  // Enable the filter
            // mask 1
            C1RXM1bits.SID = 0x000;    // Ignore all bits in comparison
            C1RXM1bits.EID = 0x00000;  // Ignore all bits in comparison
            C1RXM1bits.MIDE = 0;       // Match all message types.
            break;

#    if CAN_COUNT >= 2
        case 1:
            // assign memory
            C2FIFOBA = KVA_TO_PA(CAN2FIFO);
            // fifo 0 (transmit)
            C2FIFOCON0bits.FSIZE = 15;
            C2FIFOCON0SET = 0x80;
            // fifo 1 (receive)
            C2FIFOCON1bits.FSIZE = 15;
            C2FIFOCON1CLR = 0x80;
            // filter 1
            C2FLTCON0bits.FSEL1 = 1;   // Store messages in FIFO1
            C2FLTCON0bits.MSEL1 = 1;   // Use Mask 1
            C2RXF1bits.SID = 0x000;    // Filter 1 EID
            C2RXF1bits.EID = 0x00000;  // Filter 1 SID
            C2RXF1bits.EXID = 1;       // Filter EID messages
            C2FLTCON0bits.FLTEN1 = 1;  // Enable the filter
            // mask 1
            C2RXM1bits.SID = 0x000;    // Ignore all bits in comparison
            C2RXM1bits.EID = 0x00000;  // Ignore all bits in comparison
            C2RXM1bits.MIDE = 0;       // Match all message types.
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            // assign memory
            C3FIFOBA = KVA_TO_PA(CAN3FIFO);
            // fifo 0 (transmit)
            C3FIFOCON0bits.FSIZE = 15;
            C3FIFOCON0SET = 0x80;
            // fifo 1 (receive)
            C3FIFOCON1bits.FSIZE = 15;
            C3FIFOCON1CLR = 0x80;
            // filter 1
            C3FLTCON0bits.FSEL1 = 1;   // Store messages in FIFO1
            C3FLTCON0bits.MSEL1 = 1;   // Use Mask 1
            C3RXF1bits.SID = 0x000;    // Filter 1 EID
            C3RXF1bits.EID = 0x00000;  // Filter 1 SID
            C3RXF1bits.EXID = 1;       // Filter only EID messages
            C3FLTCON0bits.FLTEN1 = 1;  // Enable the filter
            // mask 1
            C3RXM1bits.SID = 0x000;    // Ignore all bits in comparison
            C3RXM1bits.EID = 0x00000;  // Ignore all bits in comparison
            C3RXM1bits.MIDE = 1;       // Match only message types.
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            // assign memory
            C4FIFOBA = KVA_TO_PA(CAN4FIFO);
            // fifo 0 (transmit)
            C4FIFOCON0bits.FSIZE = 15;
            C4FIFOCON0SET = 0x80;
            // fifo 1 (receive)
            C4FIFOCON1bits.FSIZE = 15;
            C4FIFOCON1CLR = 0x80;
            // filter 1
            C4FLTCON0bits.FSEL1 = 1;   // Store messages in FIFO1
            C4FLTCON0bits.MSEL1 = 1;   // Use Mask 1
            C4RXF1bits.SID = 0x000;    // Filter 1 EID
            C4RXF1bits.EID = 0x00000;  // Filter 1 SID
            C4RXF1bits.EXID = 1;       // Filter only EID messages
            C4FLTCON0bits.FLTEN1 = 1;  // Enable the filter
            // mask 1
            C4RXM1bits.SID = 0x000;    // Ignore all bits in comparison
            C4RXM1bits.EID = 0x00000;  // Ignore all bits in comparison
            C4RXM1bits.MIDE = 1;       // Match only message types.
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

    cans[can].flags.enabled = 0;

    switch (can)
    {
        case 0:
            _CAN1IE = 0;  // disable can global interrupt
            C1CONbits.REQOP = 4;
            while (C1CONbits.OPMOD != 4)
                ;
            C1CONbits.ON = 0;  // disable can
            while (C1CONbits.CANBUSY == 1)
                ;
            break;

#    if CAN_COUNT >= 2
        case 1:
            _CAN2IE = 0;  // disable can global interrupt
            C2CONbits.REQOP = 4;
            while (C2CONbits.OPMOD != 4)
                ;
            C2CONbits.ON = 0;  // disable can
            while (C2CONbits.CANBUSY == 1)
                ;
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            _CAN3IE = 0;  // disable can global interrupt
            C3CONbits.REQOP = 4;
            while (C3CONbits.OPMOD != 4)
                ;
            C3CONbits.ON = 0;  // disable can
            while (C3CONbits.CANBUSY == 1)
                ;
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            _CAN4IE = 0;  // disable can global interrupt
            C4CONbits.REQOP = 4;
            while (C4CONbits.OPMOD != 4)
                ;
            C4CONbits.ON = 0;  // disable can
            while (C4CONbits.CANBUSY == 1)
                ;
            break;

#    endif
    }

    return 0;
#else
    return -1;
#endif
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
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    // check parameters
    switch (mode)
    {
        case CAN_MODE_NORMAL:
            modeBits = 0b000;
            break;

        case CAN_MODE_LISTENONLY:
            modeBits = 0b011;
            break;

        case CAN_MODE_LISTENALL:
            modeBits = 0b111;
            break;

        case CAN_MODE_LOOPBACK:
            modeBits = 0b010;
            break;

        case CAN_MODE_DISABLED:
            modeBits = 0b001;
            break;

        case CAN_MODE_CONFIGURATION:
            modeBits = 0b100;
            break;

        default:
            return -1;
    }
    cans[can].mode = mode;

    switch (can)
    {
        case 0:
            C1CONbits.ON = 1;
            C1CONbits.REQOP = modeBits;
            while (C1CONbits.OPMOD != modeBits)
                ;
            break;

#    if CAN_COUNT >= 2
        case 1:
            C2CONbits.ON = 1;
            C2CONbits.REQOP = modeBits;
            while (C2CONbits.OPMOD != modeBits)
                ;
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            C3CONbits.ON = 1;
            C3CONbits.REQOP = modeBits;
            while (C3CONbits.OPMOD != modeBits)
                ;
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            C4CONbits.ON = 1;
            C4CONbits.REQOP = modeBits;
            while (C4CONbits.OPMOD != modeBits)
                ;
            break;

#    endif
    }

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
        return 0;
    }

    return cans[can].mode;
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
    uint8_t bitRateDiv;
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
    quantum = propagSeg + s1Seg + s2Seg + 1;
    if (quantum < 8 || quantum > 25)
    {
        return -1;
    }

    cans[can].bitRate = bitRate;
    cans[can].propagSeg = propagSeg;
    cans[can].s1Seg = s1Seg;
    cans[can].s2Seg = s2Seg;

    /* possible work arround for PIC32MK
    if (can == 2 || can == 3)
    {
        quantum -= 2;
    }*/

    bitRateDiv = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN) / (bitRate * quantum * 2);
    if (bitRateDiv > 64)
    {
        bitRateDiv = 64;
    }
    bitRateDiv--;

    switch (can)
    {
        case 0:
            C1CONbits.ON = 1;
            C1CONbits.REQOP = 4;
            while (C1CONbits.OPMOD != 4)
                ;

            C1CFGbits.SJW = 0;                // Synchronization Jump Width (1-4)
            C1CFGbits.PRSEG = propagSeg - 1;  // Propagation Time Segment (1-8)
            C1CFGbits.SEG1PH = s1Seg - 1;     // Phase Buffer Segment 1 (1-8)
            C1CFGbits.SEG2PHTS = 1;           // Phase Buffer Segment 2 is freely programmable
            C1CFGbits.SEG2PH = s2Seg - 1;     // Phase Buffer Segment 2 (1-8) SEG2PH >= SEG1PH
            C1CFGbits.BRP = bitRateDiv;       // bit rate divisor (1-64) * 2
            break;

#    if CAN_COUNT >= 2
        case 1:
            C2CONbits.ON = 1;
            C2CONbits.REQOP = 4;
            while (C2CONbits.OPMOD != 4)
                ;

            C2CFGbits.SJW = 0;                // Synchronization Jump Width (1-4)
            C2CFGbits.PRSEG = propagSeg - 1;  // Propagation Time Segment (1-8)
            C2CFGbits.SEG1PH = s1Seg - 1;     // Phase Buffer Segment 1 (1-8)
            C2CFGbits.SEG2PHTS = 1;           // Phase Buffer Segment 2 is freely programmable
            C2CFGbits.SEG2PH = s2Seg - 1;     // Phase Buffer Segment 2 (1-8) SEG2PH >= SEG1PH
            C2CFGbits.BRP = bitRateDiv;       // bit rate divisor (1-64) * 2
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            C3CONbits.ON = 1;
            C3CONbits.REQOP = 4;
            while (C3CONbits.OPMOD != 4)
                ;

            C3CFGbits.SJW = 0;                // Synchronization Jump Width (1-4)
            C3CFGbits.PRSEG = propagSeg - 1;  // Propagation Time Segment (1-8)
            C3CFGbits.SEG1PH = s1Seg - 1;     // Phase Buffer Segment 1 (1-8)
            C3CFGbits.SEG2PHTS = 1;           // Phase Buffer Segment 2 is freely programmable
            C3CFGbits.SEG2PH = s2Seg - 1;     // Phase Buffer Segment 2 (1-8) SEG2PH >= SEG1PH
            C3CFGbits.BRP = bitRateDiv;       // bit rate divisor (1-64) * 2
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            C4CONbits.ON = 1;
            C4CONbits.REQOP = 4;
            while (C4CONbits.OPMOD != 4)
                ;

            C4CFGbits.SJW = 0;                // Synchronization Jump Width (1-4)
            C4CFGbits.PRSEG = propagSeg - 1;  // Propagation Time Segment (1-8)
            C4CFGbits.SEG1PH = s1Seg - 1;     // Phase Buffer Segment 1 (1-8)
            C4CFGbits.SEG2PHTS = 1;           // Phase Buffer Segment 2 is freely programmable
            C4CFGbits.SEG2PH = s2Seg - 1;     // Phase Buffer Segment 2 (1-8) SEG2PH >= SEG1PH
            C4CFGbits.BRP = bitRateDiv;       // bit rate divisor (1-64) * 2
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

    return cans[can].bitRate;
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
    uint8_t quantums = cans[can].propagSeg + cans[can].s1Seg + cans[can].s2Seg + 1;

    switch (can)
    {
        case 0:
            bitRateDiv = (C1CFGbits.BRP + 1) << 1;  // bit rate divisor (1-64) * 2
            break;

#    if CAN_COUNT >= 2
        case 1:
            bitRateDiv = (C2CFGbits.BRP + 1) << 1;  // bit rate divisor (1-64) * 2
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            bitRateDiv = (C3CFGbits.BRP + 1) << 1;  // bit rate divisor (1-64) * 2
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            bitRateDiv = (C4CFGbits.BRP + 1) << 1;  // bit rate divisor (1-64) * 2
            break;

#    endif
    }

    return sysclock_periphFreq(SYSCLOCK_CLOCK_CAN) / (bitRateDiv * quantums);
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

    return cans[can].propagSeg;
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

    return cans[can].s1Seg;
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

    return cans[can].s2Seg;
#else
    return 0;
#endif
}

/**
 * @brief Write a can message to fifo
 * @param device CAN device number
 * @param fifo fifo number to put the message
 * @param header CAN message header struct (id, flags, data size)
 * @return 0 if message is successfully putted inside fifo, -1 in case of error
 */
int can_send(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data)
{
    UDK_UNUSED(fifo);
#if CAN_COUNT >= 1
    unsigned int i;

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return 0;
    }

    CAN_TxMsgBuffer *buffer = NULL;

    switch (can)
    {
        case 0:
            if (C1FIFOINT0bits.TXNFULLIF == 0)
            {
                buffer = NULL;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)(PA_TO_KVA1(C1FIFOUA0));
            }
            break;

#    if CAN_COUNT >= 2
        case 1:
            if (C2FIFOINT0bits.TXNFULLIF == 0)
            {
                buffer = NULL;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)(PA_TO_KVA1(C2FIFOUA0));
            }
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            if (C3FIFOINT0bits.TXNFULLIF == 0)
            {
                buffer = NULL;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)(PA_TO_KVA1(C3FIFOUA0));
            }
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            if (C4FIFOINT0bits.TXNFULLIF == 0)
            {
                buffer = NULL;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)(PA_TO_KVA1(C4FIFOUA0));
            }
            break;

#    endif
    }

    if (buffer != NULL)
    {
        // clear the message header
        buffer->messageWord[0] = 0;
        buffer->messageWord[1] = 0;

        // set can id
        if ((header->flags & CAN_VERS2BA) == CAN_VERS2BA)
        {
            buffer->msgEID.IDE = 1;                     // extended id
            buffer->msgEID.EID = header->id & 0x3FFFF;  // Message EID
            buffer->msgSID.SID = header->id >> 18;      // Message EID
        }
        else
        {
            buffer->msgSID.SID = header->id;  // Message EID
        }

        // RTR
        if (header->flags & CAN_RTR)
        {
            buffer->msgEID.RTR = 1;
            header->size = 0;
            buffer->msgEID.DLC = 0;
        }
        else
        {
            // set data and data size
            if (header->size > 8)
            {
                header->size = 8;
            }
            buffer->msgEID.DLC = header->size;  // Data Length
            for (i = 0; i < header->size; i++)
            {
                buffer->data[i] = data[i];
            }
        }
    }

    switch (can)
    {
        case 0:
            if (buffer != NULL)
            {
                C1FIFOCON0SET = 0x2008;  // Set the UINC and TXREQ bit
            }
            else
            {
                C1FIFOCON0SET = 0x0008;  // Set the TXREQ bit
            }
            break;

#    if CAN_COUNT >= 2
        case 1:
            if (buffer != NULL)
            {
                C2FIFOCON0SET = 0x2008;  // Set the UINC and TXREQ bit
            }
            else
            {
                C2FIFOCON0SET = 0x0008;  // Set the TXREQ bit
            }
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            if (buffer != NULL)
            {
                C3FIFOCON0SET = 0x2008;  // Set the UINC and TXREQ bit
            }
            else
            {
                C3FIFOCON0SET = 0x0008;  // Set the TXREQ bit
            }
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            if (buffer != NULL)
            {
                C4FIFOCON0SET = 0x2008;  // Set the UINC and TXREQ bit
            }
            else
            {
                C4FIFOCON0SET = 0x0008;  // Set the TXREQ bit
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
 * @brief Read a can message from fifo
 * @param device CAN device number
 * @param fifo fifo number to read the message
 * @param header CAN message header struct (id, flags, data size)
 * @return 0 if message no readen, -1 in case of error, 1 if a message is readen
 */
int can_rec(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data)
{
    UDK_UNUSED(fifo);
#if CAN_COUNT >= 1
    int i;
    uint8_t can = MINOR(device);

    CAN_FLAGS flagValue = 0;
    CAN_RxMsgBuffer *buffer = NULL;

    switch (can)
    {
        case 0:
            if (C1FIFOINT1bits.RXNEMPTYIF != 1)
            {
                return 0;
            }
            buffer = PA_TO_KVA1(C1FIFOUA1);
            break;

#    if CAN_COUNT >= 2
        case 1:
            if (C2FIFOINT1bits.RXNEMPTYIF != 1)
            {
                return 0;
            }
            buffer = PA_TO_KVA1(C2FIFOUA1);
            break;
#    endif
#    if CAN_COUNT >= 3
        case 2:
            if (C3FIFOINT1bits.RXNEMPTYIF != 1)
            {
                return 0;
            }
            buffer = PA_TO_KVA1(C3FIFOUA1);
            break;
#    endif
#    if CAN_COUNT >= 4
        case 3:
            if (C4FIFOINT1bits.RXNEMPTYIF != 1)
            {
                return 0;
            }
            buffer = PA_TO_KVA1(C4FIFOUA1);
            break;
#    endif
        default:
            return 0;
    }

    // ID
    if (buffer->msgEID.IDE == 1)
    {
        flagValue = flagValue + CAN_VERS2BA;  // extended ID
        header->id = buffer->msgEID.EID + (buffer->msgSID.SID << 18);
    }
    else
    {
        header->id = buffer->msgSID.SID & 0x7FF;
    }

    // data read and copy
    header->size = buffer->msgEID.DLC;
    if (header->size > 8)
    {
        header->size = 0;
    }
    for (i = 0; i < header->size; i++)
    {
        data[i] = buffer->data[i];
    }

    // flags
    if (buffer->msgEID.SRR == 1)
    {
        flagValue += CAN_RTR;
    }
    header->flags = flagValue;

    switch (can)
    {
        case 0:
            C1FIFOCON1SET = 0x2000;  // mark as read
            break;

#    if CAN_COUNT >= 2
        case 1:
            C2FIFOCON1SET = 0x2000;  // mark as read
            break;

#    endif
#    if CAN_COUNT >= 3
        case 2:
            C3FIFOCON1SET = 0x2000;  // mark as read
            break;

#    endif
#    if CAN_COUNT >= 4
        case 3:
            C4FIFOCON1SET = 0x2000;  // mark as read
            break;

#    endif
    }

    // flags
    if (buffer->msgEID.RTR == 1)
    {
        flagValue += CAN_RTR;
    }
    header->flags = flagValue;

    return 1;
#else
    return -1;
#endif
}
