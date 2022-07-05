/**
 * @file can_pic32_fd.h
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

#ifndef CAN_PIC32_FD_H
#define CAN_PIC32_FD_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064)
#    define CAN_COUNT 1
#elif defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)
#    define CAN_COUNT 4
#else
#    define CAN_COUNT 0
#endif

typedef enum
{
    CAN_RXFIFO_NOT_EMPTY = 0x01,   ///<
    CAN_TXFIFO_NOT_FULL = 0x01,    ///<
    CAN_RXFIFO_HALF_FULL = 0x02,   ///<
    CAN_TXFIFO_HALF_EMPTY = 0x02,  ///<
    CAN_RXFIFO_FULL = 0x04,        ///<
    CAN_TXFIFO_EMPTY = 0x04,       ///<
    CAN_RXFIFO_OVERFLOW = 0x08,    ///<
} CAN_FIFO_EVENTS;

typedef enum
{
    CAN_FIFO_DATA64 = 0b111,
    CAN_FIFO_DATA48 = 0b110,
    CAN_FIFO_DATA32 = 0b101,
    CAN_FIFO_DATA24 = 0b100,
    CAN_FIFO_DATA20 = 0b011,
    CAN_FIFO_DATA16 = 0b010,
    CAN_FIFO_DATA12 = 0b001,
    CAN_FIFO_DATA8 = 0b000,
} CAN_FIFO_DATASIZE;

#define CAN_FILTER_COUNT 32
#define CAN_FIFO_COUNT   32

// interrupt bits helpers
#ifndef _CAN1IE
#    define _CAN1IE IEC5bits.CAN1IE
#    define _CAN1IF IFS5bits.CAN1IF
#    define _CAN1IP IPC41bits.CAN1IP
#    define _CAN1IS IPC41bits.CAN1IS
#    define _CAN2IE IEC5bits.CAN2IE
#    define _CAN2IF IFS5bits.CAN2IF
#    define _CAN2IP IPC42bits.CAN2IP
#    define _CAN2IS IPC42bits.CAN2IS
#    define _CAN3IE IEC5bits.CAN3IE
#    define _CAN3IF IFS5bits.CAN3IF
#    define _CAN3IP IPC46bits.CAN3IP
#    define _CAN3IS IPC46bits.CAN3IS
#    define _CAN4IE IEC5bits.CAN4IE
#    define _CAN4IF IFS5bits.CAN4IF
#    define _CAN4IP IPC47bits.CAN4IP
#    define _CAN4IS IPC47bits.CAN4IS
#endif
#define CANIPR IPL4SRS

// CANFD Message Time Stamp
typedef unsigned long CANFD_MSG_TIMESTAMP;

// CANFD TX / TX Message ID
typedef struct
{
    unsigned SID : 11;
    unsigned long EID : 18;
    unsigned SID11 : 1;
    unsigned _dummy2 : 2;
} CANFD_MSGOBJ_ID;

// CANFD RX Message Object Control
typedef struct
{
    unsigned DLC : 4;
    unsigned IDE : 1;
    unsigned RTR : 1;
    unsigned BRS : 1;
    unsigned FDF : 1;
    unsigned ESI : 1;
    unsigned _dummy2 : 2;
    unsigned FilterHit : 5;
    unsigned _dummy16 : 16;
} CANFD_RX_MSGOBJ_CTRL;

// CANFD RX Message Object
typedef union
{
    struct
    {
        CANFD_MSGOBJ_ID id;         ///< ID portion
        CANFD_RX_MSGOBJ_CTRL ctrl;  ///< Control portion
        char data[8];               ///< data portion
    };
    uint32_t messageWord[4];
} CAN_RxMsgBuffer;

// CAN TX Message Object Control
typedef struct
{
    unsigned DLC : 4;
    unsigned IDE : 1;
    unsigned RTR : 1;
    unsigned BRS : 1;
    unsigned FDF : 1;
    unsigned ESI : 1;
    unsigned SEQ : 7;
    unsigned _dummy1 : 16;
} CANFD_TX_MSGOBJ_CTRL;

// CAN TX Message Object
typedef union
{
    struct
    {
        CANFD_MSGOBJ_ID id;         ///< ID portion
        CANFD_TX_MSGOBJ_CTRL ctrl;  ///< Control portion
        char data[8];               ///< data portion
    };
    uint32_t messageWord[4];
} CAN_TxMsgBuffer;

#ifdef __cplusplus
}
#endif

#define CAN_MESSAGE_HEADER_SIZE 8U

#endif  // CAN_PIC32_FD_H
