/**
 * @file can_pic32_fd.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
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
uint32_t __attribute__((coherent, aligned(16))) _can1_fifo_buffer[32 * 4];
#endif

struct can_dev cans[] = {
#if CAN_COUNT >= 1
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
            CFD1MASK0bits.MIDE = 0;        // Match all message types.
            break;
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
            CFD1CONbits.REQOP = 4;
            while (CFD1CONbits.OPMOD != 4)
                ;
            CFD1CONbits.ON = 0;  // disable can
            while (CFD1CONbits.BUSY == 1)
                ;
            break;
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
    cans[can].mode = mode;

    switch (can)
    {
        case 0:
            CFD1CONbits.ON = 1;
            CFD1CONbits.REQOP = modeBits;
            while (CFD1CONbits.OPMOD != modeBits)
                ;
            break;
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

    cans[can].bitRate = bitRate;
    cans[can].propagSeg = propagSeg;
    cans[can].s1Seg = s1Seg;
    cans[can].s2Seg = s2Seg;

    uint32_t can_freq = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN);
    uint16_t bitRateDiv = can_freq / (bitRate * quantum);
    if (bitRateDiv > 256)
    {
        bitRateDiv = 256;
    }

    switch (can)
    {
        case 0:
            CFD1CONbits.ON = 1;
            CFD1CONbits.CLKSEL0 = 0b1;  // REFCLK4 clock selected
            CFD1CONbits.REQOP = 4;
            while (CFD1CONbits.OPMOD != 4)
                ;

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
    uint8_t quantums = cans[can].propagSeg + cans[can].s1Seg + cans[can].s2Seg;

    switch (can)
    {
        case 0:
            bitRateDiv = (CFD1NBTCFGbits.BRP + 1);  // bit rate divisor (1-256)
            break;
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
            if (CFD1TXQSTAbits.TXQNIF == 0)
            {
                buffer = NULL;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)(PA_TO_KVA1(CFD1TXQUA));
            }
            break;
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
            buffer->id.SID = header->id;  // Message EID
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
                CFD1TXQCONSET = _CFD1TXQCON_TXREQ_MASK | _CFD1TEFCON_UINC_MASK;  // Set the UINC and TXREQ bit
            }
            else
            {
                CFD1TXQCONSET = _CFD1TXQCON_TXREQ_MASK;  // Set the TXREQ bit
            }
            break;
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
            if (CFD1FIFOSTA1bits.TFNRFNIF == 0)
            {
                return 0;
            }
            buffer = PA_TO_KVA1(CFD1FIFOUA1);
            break;

        default:
            return 0;
    }

    // ID
    if (buffer->ctrl.IDE == 1)
    {
        flagValue = flagValue + CAN_VERS2BA;  // extended ID
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
    for (i = 0; i < header->size; i++)
    {
        data[i] = buffer->data[i];
    }

    switch (can)
    {
        case 0:
            CFD1FIFOCON1SET = _CFD1TEFCON_UINC_MASK;  // mark as read
            break;
    }

    // flags
    if (buffer->ctrl.BRS == 1)
    {
        flagValue += CAN_RTR;
    }
    header->flags = flagValue;

    return 1;
#else
    return -1;
#endif
}
