/**
 * @file can_dspic33c.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2022
 *
 * @date September 8 2018, 09:05 AM
 *
 * @brief CAN communication support driver for dsPIC33CH, dsPIC33CK with CAN-Fd extension
 *
 * Implementation based on Microchip document DS70005340B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM,-CAN-Flexible-Data-Rate-(FD)-Protocol-Module-DS70005340B.pdf
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
uint32_t __attribute__((aligned(4))) CAN1FIFO[40 * 19];
#endif
#if CAN_COUNT >= 2
uint32_t __attribute__((aligned(4))) CAN2FIFO[40 * 19];
#endif

struct can_dev cans[] = {
#if CAN_COUNT >= 1
    {.bitRate = 0, .flags = {{.val = CAN_FLAG_UNUSED}}},
#endif
#if CAN_COUNT >= 2
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
            C1FIFOBAH = 0x0000;
            C1FIFOBAL = (uint16_t)(&CAN1FIFO);

            // Configure TEF to save 5 messages
            C1CONLbits.BRSDIS = 0x0;
            C1CONHbits.STEF = 0x0;   // Don't save transmitted messages in TEF
            C1CONHbits.TXQEN = 0x0;  // No TXQ

            // FIFO1 as transmiter (20 messages)
            C1FIFOCON1Hbits.FSIZE = 20 - 1;  // 20 messages deep
            C1FIFOCON1Hbits.PLSIZE = 0x0;    // 8 bytes of data
            C1FIFOCON1Lbits.TXEN = 1;        // Set TXEN bit, transmit fifo

            // FIFO2 as receiver (20 messages)
            C1FIFOCON2Hbits.FSIZE = 20 - 1;  // 20 messages deep
            C1FIFOCON2Hbits.PLSIZE = 0x0;    // 8 bytes of data
            C1FIFOCON2Lbits.TXEN = 0;        // Clear TXEN bit, receive fifo
            // filter 0
            C1FLTCON0Lbits.F0BP = 2;    // Store messages in FIFO2
            C1FLTOBJ0H = 0x0000;        // Filter 0 ID
            C1FLTOBJ0L = 0x0000;        // Filter 0 ID
            C1FLTOBJ0Hbits.EXIDE = 1;   // Filter only EID messages
            C1FLTCON0Lbits.FLTEN0 = 1;  // Enable the filter
            // mask 0
            C1MASK0H = 0x0000;      // Ignore all bits in comparison
            C1MASK0L = 0x0000;      // Ignore all bits in comparison
            C1MASK0Hbits.MIDE = 0;  // Match all message types
            break;
#    if CAN_COUNT >= 2
        case 1:
            C2FIFOBAH = 0x0000;
            C2FIFOBAL = (uint16_t)(&CAN2FIFO);

            // Configure TEF to save 5 messages
            C2CONLbits.BRSDIS = 0x0;
            C2CONHbits.STEF = 0x0;   // Don't save transmitted messages in TEF
            C2CONHbits.TXQEN = 0x0;  // No TXQ

            // FIFO1 as transmiter (20 messages)
            C2FIFOCON1Hbits.FSIZE = 20 - 1;  // 20 messages deep
            C2FIFOCON1Hbits.PLSIZE = 0x0;    // 8 bytes of data
            C2FIFOCON1Lbits.TXEN = 1;        // Set TXEN bit, transmit fifo

            // FIFO2 as receiver (20 messages)
            C2FIFOCON2Hbits.FSIZE = 20 - 1;  // 20 messages deep
            C2FIFOCON2Hbits.PLSIZE = 0x0;    // 8 bytes of data
            C2FIFOCON2Lbits.TXEN = 0;        // Clear TXEN bit, receive fifo
            // filter 0
            C2FLTCON0Lbits.F0BP = 2;    // Store messages in FIFO2
            C2FLTOBJ0H = 0x0000;        // Filter 0 ID
            C2FLTOBJ0L = 0x0000;        // Filter 0 ID
            C2FLTOBJ0Hbits.EXIDE = 1;   // Filter only EID messages
            C2FLTCON0Lbits.FLTEN0 = 1;  // Enable the filter
            // mask 0
            C2MASK0H = 0x0000;      // Ignore all bits in comparison
            C2MASK0L = 0x0000;      // Ignore all bits in comparison
            C2MASK0Hbits.MIDE = 0;  // Match all message types
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
            _C1IE = 0;  // disable can global interrupt
            C1CONHbits.REQOP = 4;
            while (C1CONHbits.OPMOD != 4)
                ;
            C1CONLbits.CON = 0;  // disable can
            while (C1CONLbits.BUSY == 1)
                ;
            break;
#    if CAN_COUNT >= 2
        case 1:
            _C2IE = 0;  // disable can global interrupt
            C2CONHbits.REQOP = 4;
            while (C2CONHbits.OPMOD != 4)
                ;
            C2CONLbits.CON = 0;  // disable can
            while (C2CONLbits.BUSY == 1)
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
            modeBits = 0b110;
            break;

        case CAN_MODE_NORMAL_FD:
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
            C1CONLbits.CON = 1;
            C1CONHbits.REQOP = modeBits;
            while (C1CONHbits.OPMOD != modeBits)
                ;
            break;
#    if CAN_COUNT >= 2
        case 1:
            C2CONLbits.CON = 1;
            C2CONHbits.REQOP = modeBits;
            while (C2CONHbits.OPMOD != modeBits)
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
    uint16_t bitRateDiv;
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
    quantum = propagSeg + s1Seg + s2Seg + (uint8_t)1;
    if (quantum < 8 || quantum > 25)
    {
        return -1;
    }
    cans[can].bitRate = bitRate;
    cans[can].propagSeg = propagSeg;
    cans[can].s1Seg = s1Seg;
    cans[can].s2Seg = s2Seg;

    bitRateDiv = sysclock_periphFreq(SYSCLOCK_CLOCK_CAN) / (bitRate * quantum * 2);
    if (bitRateDiv > 256)
    {
        bitRateDiv = 256;
    }
    switch (can)
    {
        case 0:
            C1CONLbits.CON = 1;
            C1CONHbits.REQOP = 4;
            while (C1CONHbits.OPMOD != 4)
                ;

            CANCLKCONbits.CANCLKSEL = 3;      // CAN Clock Source = VCO/2 = 640/2 = 320MHz
            CANCLKCONbits.CANCLKDIV = 4 - 1;  // divide by 4 i.e. 320/4 = 80MHz
            CANCLKCONbits.CANCLKEN = 1;       // enabled

            /*C1NBTCFGHbits.BRP = bitRateDiv - 1; // Baud Rate Prescaler bits (1-256)
            C1NBTCFGHbits.TSEG1 = s1Seg - 1; // Phase Buffer Segment 1 (1-256)
            C1NBTCFGLbits.TSEG2 = s2Seg - 1; // Phase Buffer Segment 2 (1-128)
            C1NBTCFGLbits.SJW = 0; // Synchronization Jump Width (1-128)

            C1DBTCFGHbits.BRP = bitRateDiv - 1; // Baud Rate Prescaler bits (1-256)
            C1DBTCFGHbits.TSEG1 = s1Seg - 1; // Phase Buffer Segment 1 (1-32)
            C1DBTCFGLbits.TSEG2 = s2Seg - 1; // Phase Buffer Segment 2 (1-16)
            C1DBTCFGLbits.SJW = 0; // Synchronization Jump Width (1-16)*/

            /* Set up the CANFD module for 1Mbps of Nominal bit rate speed and 2Mbps of Data bit rate. */
            // C1NBTCFGH = 0x003E;
            C1NBTCFGHbits.BRP = 0;         // Baud Rate Prescaler bits (1-256) div = 1
            C1NBTCFGHbits.TSEG1 = 63 - 1;  // Phase Buffer Segment 1 (1-256) Tseg = 63

            // C1NBTCFGL = 0x0F0F;
            C1NBTCFGLbits.TSEG2 = 16 - 1;  // Phase Buffer Segment 2 (1-128) Tseg2 = 16
            C1NBTCFGLbits.SJW = 16 - 1;    // SWJ = 16

            // CAN FD
            C1DBTCFGH = 0x001E;
            C1DBTCFGL = 0x0707;

            C1TDCH = 0x0002;  // TDCMOD is Auto
            C1TDCL = 0x1F00;

            break;
#    if CAN_COUNT >= 2
        case 1:
            // TODO
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
    uint8_t quantums = cans[can].propagSeg + cans[can].s1Seg + cans[can].s2Seg + (uint8_t)1;

    switch (can)
    {
        case 0:
            // bitRateDiv = (C1CFGbits.BRP + 1) << 1;      // bit rate divisor (1-64) * 2
            break;
#    if CAN_COUNT >= 2
        case 1:
            // TODO
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
    uint8_t size;
    uint8_t dlc;

    uint8_t can = MINOR(device);
    if (can >= CAN_COUNT)
    {
        return -1;
    }
    CAN_TxMsgBuffer *buffer = NULL;

    switch (can)
    {
        case 0:
            // while (C1FIFOCON1Lbits.TXREQ == 1);
            if (C1FIFOSTA1bits.TFNRFNIF == 0)  // fifo full
            {
                return -1;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)C1FIFOUA1L;
            }
            break;
#    if CAN_COUNT >= 2
        case 1:
            if (C2FIFOSTA1bits.TFNRFNIF == 0)  // fifo full
            {
                return -1;
            }
            else
            {
                buffer = (CAN_TxMsgBuffer *)C2FIFOUA1L;
            }
            break;
#    endif
    }

    // clear the message header
    buffer->messageWord[0] = 0;
    buffer->messageWord[1] = 0;
    buffer->messageWord[2] = 0;
    buffer->messageWord[3] = 0;

    // set can id
    if ((header->flags & CAN_VERS2BA) == CAN_VERS2BA)
    {
        CAN_DSPIC33C_TX_SETIDE(buffer);                                    // extended id
        buffer->eid = (header->id >> 5) & 0x1FFF;                          // Message EID
        buffer->sid = (header->id >> 18) + ((header->id & 0x001F) << 11);  // Message SID
    }
    else
    {
        buffer->sid = header->id & 0x07FF;  // Message SID
    }

    if (header->flags & CAN_RTR)
    {
        CAN_DSPIC33C_TX_SETRTR(buffer);
    }
    // set data and data size
    size = header->size;
    if (header->flags & CAN_FDF)
    {
        if (size > 64)
        {
            size = 64;
        }

        // compute CAN Fd DLC
        if (size <= 8)
        {
            dlc = size;
        }
        else if (size <= 12)
        {
            dlc = 9;
        }
        else if (size <= 16)
        {
            dlc = 10;
        }
        else if (size <= 20)
        {
            dlc = 11;
        }
        else if (size <= 24)
        {
            dlc = 12;
        }
        else if (size <= 32)
        {
            dlc = 13;
        }
        else if (size <= 48)
        {
            dlc = 14;
        }
        else
        {
            dlc = 15;
        }
    }
    else
    {
        if (size > 8)
        {
            size = 8;
        }
        dlc = size;
    }
    CAN_DSPIC33C_TX_SETDLC(buffer, dlc);  // Data Length

    // data
    char *bufferData = (char *)buffer + 8;
    for (i = 0; i < header->size; i++)
    {
        bufferData[i] = data[i];
    }
    switch (can)
    {
        case 0:
            C1FIFOCON1Lbits.UINC = 1;
            C1FIFOCON1Lbits.TXREQ = 1;
            break;
#    if CAN_COUNT >= 2
        case 1:
            C2FIFOCON1Lbits.UINC = 1;
            C2FIFOCON1Lbits.TXREQ = 1;
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
    if (can >= CAN_COUNT)
    {
        return 0;
    }
    CAN_FLAGS flagValue = 0;
    CAN_RxMsgBuffer *buffer = NULL;

    switch (can)
    {
        case 0:
            if (C1FIFOSTA2bits.TFNRFNIF == 0)  // fifo empty
            {
                return 0;
            }
            buffer = (CAN_RxMsgBuffer *)C1FIFOUA2L;
            break;
#    if CAN_COUNT >= 2
        case 1:
            if (C2FIFOSTA2bits.TFNRFNIF == 0)  // fifo empty
            {
                return 0;
            }
            buffer = (CAN_RxMsgBuffer *)C2FIFOUA2L;
            break;
#    endif
    }

    // ID
    uint32_t canId;
    if (CAN_DSPIC33C_RX_IDE(buffer))
    {
        flagValue += CAN_VERS2BA;  // extended ID
        canId = (((uint32_t)CAN_DSPIC33C_RX_SID(buffer)) << 18) + CAN_DSPIC33C_RX_EIDH(buffer) + CAN_DSPIC33C_RX_EIDL(buffer);
    }
    else
    {
        canId = CAN_DSPIC33C_RX_SID(buffer);
    }
    header->id = canId;

    // data read and copy
    uint8_t size = CAN_DSPIC33C_RX_DLC(buffer);
    if (CAN_DSPIC33C_RX_FDF(buffer))
    {
        flagValue += CAN_FDF;  // CAN Fd
        switch (size)
        {
            case 9:
                size = 12;
                break;

            case 10:
                size = 16;
                break;

            case 11:
                size = 20;
                break;

            case 12:
                size = 24;
                break;

            case 13:
                size = 32;
                break;

            case 14:
                size = 48;
                break;

            case 15:
                size = 64;
                break;
        }
    }
    else
    {
        if (size > 8)
        {
            size = 8;
        }
    }
    char *bufferData = (char *)buffer + 8;
    for (i = 0; i < size; i++)
    {
        data[i] = bufferData[i];
    }
    header->size = size;

    switch (can)
    {
        case 0:
            C1FIFOCON2Lbits.UINC = 1;  // mark as read
            break;
#    if CAN_COUNT >= 2
        case 1:
            C2FIFOCON2Lbits.UINC = 1;  // mark as read
            break;
#    endif
    }

    // flags
    if (CAN_DSPIC33C_RX_RTR(buffer))
    {
        flagValue += CAN_RTR;
    }

    header->flags = flagValue;

    return 1;
#else
    return -1;
#endif
}

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
int can_filterConfiguration(rt_dev_t device, uint8_t nFilter, uint8_t fifo, uint32_t idFilter, uint32_t mask, CAN_FRAME_FORMAT_FLAGS frame)
{
#if CAN_COUNT >= 1
    uint8_t can = MINOR(device);
    volatile uint8_t *con = NULL;
    volatile uint16_t *reg = NULL;

    uint16_t mide, exide;
    if (can >= CAN_COUNT || nFilter >= CAN_FILTER_COUNT || fifo > CAN_FIFO_COUNT)
    {
        return -1;
    }

    if (frame == CAN_FRAME_STD)
    {
        mide = 0x4000;
        exide = 0;
    }
    else if (frame == CAN_FRAME_EXT)
    {
        mide = 0x4000;
        exide = 0x4000;
    }
    else if (frame == CAN_FRAME_BOTH)
    {
        mide = 0;
        exide = 0x4000;
    }
    else
    {
        return -1;
    }

    switch (can)
    {
        case 0:
            con = (volatile uint8_t *)&C1FLTCON0L;
            reg = (volatile uint16_t *)&C1FLTOBJ0L;
            break;
#    if CAN_COUNT >= 2
        case 1:
            con = (volatile uint8_t *)&C2FLTCON0L;
            reg = (volatile uint16_t *)&C2FLTOBJ0L;
            break;
#    endif
    }
    // filter disabled
    con[nFilter] = con[nFilter] & 0x7F;
    // filter configured
    nFilter = nFilter << 2;
    reg[nFilter] = (CAN_filter_SID(idFilter) + CAN_filter_EIDL(idFilter));
    nFilter++;
    reg[nFilter] = (CAN_filter_EIDH(idFilter) + exide);
    nFilter++;
    reg[nFilter] = (CAN_filter_SID(mask) + CAN_filter_EIDL(mask));
    nFilter++;
    reg[nFilter] = (CAN_filter_EIDH(mask) + mide);
    // filter enabled
    nFilter = nFilter >> 2;
    con[nFilter] = fifo | (1 << 7);
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
    volatile uint8_t *con = NULL;
    if (can >= CAN_COUNT || nFilter >= CAN_FILTER_COUNT)
    {
        return -1;
    }

    switch (can)
    {
        case 0:
            con = (volatile uint8_t *)&C1FLTCON0L;
            break;
#    if CAN_COUNT >= 2
        case 1:
            con = (volatile uint8_t *)&C2FLTCON0L;
            break;
#    endif
            con[nFilter] = con[nFilter] | (1 << 7);  // Enable the filter
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
    volatile uint8_t *con = NULL;
    if (can >= CAN_COUNT || nFilter >= CAN_FILTER_COUNT)
    {
        return -1;
    }

    switch (can)
    {
        case 0:
            con = (volatile uint8_t *)&C1FLTCON0L;
            break;
#    if CAN_COUNT >= 2
        case 1:
            con = (volatile uint8_t *)&C2FLTCON0L;
            break;
#    endif
            con[nFilter] = con[nFilter] & 0x7F;  // Disable the filter
    }
#else
    return -1;
#endif
    return 0;
}
