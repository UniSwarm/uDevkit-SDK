/**
 * @file can_pic32.h
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

#ifndef CAN_PIC32_H
#define CAN_PIC32_H

#if defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX534F064H)                       \
    || defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX550F256L)                    \
    || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H)                    \
    || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX570F512L)                    \
    || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H)                    \
    || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L)
#    define CAN_COUNT 1
#elif defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H)                     \
    || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)                    \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124)              \
    || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ0512EFK100)              \
    || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024ECH064)              \
    || defined(DEVICE_32MZ1024ECH100) || defined(DEVICE_32MZ1024ECH124) || defined(DEVICE_32MZ1024ECH144)              \
    || defined(DEVICE_32MZ1024ECM064) || defined(DEVICE_32MZ1024ECM100) || defined(DEVICE_32MZ1024ECM124)              \
    || defined(DEVICE_32MZ1024ECM144) || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100)              \
    || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFH064)              \
    || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)              \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124)              \
    || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ1024EFM100)              \
    || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ1025DAA169)              \
    || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)              \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169)              \
    || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176)              \
    || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176) || defined(DEVICE_32MZ1025DAL169)              \
    || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)              \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169)              \
    || defined(DEVICE_32MZ1064DAA176) || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169)              \
    || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169)              \
    || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)              \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169)              \
    || defined(DEVICE_32MZ1064DAL176) || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176)              \
    || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176) || defined(DEVICE_32MZ2025DAA169)              \
    || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)              \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169)              \
    || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176)              \
    || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176) || defined(DEVICE_32MZ2025DAL169)              \
    || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)              \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048ECH064)              \
    || defined(DEVICE_32MZ2048ECH100) || defined(DEVICE_32MZ2048ECH124) || defined(DEVICE_32MZ2048ECH144)              \
    || defined(DEVICE_32MZ2048ECM064) || defined(DEVICE_32MZ2048ECM100) || defined(DEVICE_32MZ2048ECM124)              \
    || defined(DEVICE_32MZ2048ECM144) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100)              \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM064)              \
    || defined(DEVICE_32MZ2048EFM100) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)              \
    || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176) || defined(DEVICE_32MZ2064DAA288)              \
    || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)              \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169)              \
    || defined(DEVICE_32MZ2064DAH176) || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176)              \
    || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176) || defined(DEVICE_32MZ2064DAR169)              \
    || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define CAN_COUNT 2
#elif defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512MCF064)               \
    || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100)              \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100)
#    define CAN_COUNT 4
#else
#    define CAN_COUNT 0
#endif

#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
// interrupt bits helpers for PIC32MZ
#    ifndef _CAN1IE
#        define _CAN1IE IEC4bits.CAN1IE
#        define _CAN1IF IFS4bits.CAN1IF
#        define _CAN1IP IPC37bits.CAN1IP
#        define _CAN1IS IPC37bits.CAN1IS
#        define _CAN2IE IEC4bits.CAN2IE
#        define _CAN2IF IFS4bits.CAN2IF
#        define _CAN2IP IPC38bits.CAN2IP
#        define _CAN2IS IPC38bits.CAN2IS
#    endif
#    define CANIPR IPL4SRS

#elif defined(ARCHI_pic32mk)
// interrupt bits helpers for PIC32MK
#    ifndef _CAN1IE
#        define _CAN1IE IEC5bits.CAN1IE
#        define _CAN1IF IFS5bits.CAN1IF
#        define _CAN1IP IPC41bits.CAN1IP
#        define _CAN1IS IPC41bits.CAN1IS
#        define _CAN2IE IEC5bits.CAN2IE
#        define _CAN2IF IFS5bits.CAN2IF
#        define _CAN2IP IPC42bits.CAN2IP
#        define _CAN2IS IPC42bits.CAN2IS
#        define _CAN3IE IEC5bits.CAN3IE
#        define _CAN3IF IFS5bits.CAN3IF
#        define _CAN3IP IPC46bits.CAN3IP
#        define _CAN3IS IPC46bits.CAN3IS
#        define _CAN4IE IEC5bits.CAN4IE
#        define _CAN4IF IFS5bits.CAN4IF
#        define _CAN4IP IPC47bits.CAN4IP
#        define _CAN4IS IPC47bits.CAN4IS
#    endif
#    define CANIPR IPL4SRS

#elif defined(ARCHI_pic32mx)
// interrupt bits helpers for PIC32MX
#    ifndef _CAN1IE
#        define _CAN1IE IEC1bits.CAN1IE
#        define _CAN1IF IFS1bits.CAN1IF
#        define _CAN1IP IPC11bits.CAN1IP
#        define _CAN1IS IPC11bits.CAN1IS
#        define _CAN2IE IEC1bits.CAN2IE
#        define _CAN2IF IFS1bits.CAN2IF
#        define _CAN2IP IPC11bits.CAN2IP
#        define _CAN2IS IPC11bits.CAN2IS
#    endif
#    define CANIPR IPL4SOFT
#endif

// ==== Transmit buffer memory (dedicated to PIC32) ====
typedef struct
{
    unsigned SID : 11;  ///< CAN TX Message Standard ID. This value should be between 0x0 - 0x7FF.
    unsigned : 21;
} CAN_TXMSG_SID;

typedef struct
{
    unsigned DLC : 4;  ///< Data Length Control. Specifies the size of the data payload section of the CAN packet
    unsigned RB0 : 1;  ///< Reserved bit. Should be always 0
    unsigned : 3;
    unsigned RB1 : 1;   ///< Reserved bit. Should be always 0
    unsigned RTR : 1;   ///< Remote Transmit Request bit. Should be set for RTR messages, clear otherwise.
    unsigned EID : 18;  ///< CAN TX and RX Extended ID field. Valid values are in range 0x0 - 0x3FFFF
    unsigned IDE : 1;   ///< Identifier bit. If 0 means that message is SID
    unsigned SRR : 1;   ///< Susbtitute Remote request bit. This bit should always be clear for an EID message
    unsigned : 2;
} CAN_MSGEID;

typedef union
{
    struct
    {
        CAN_TXMSG_SID msgSID;  ///< SID portion
        CAN_MSGEID msgEID;     ///< EID portion
        char data[8];          ///< data portion
    };
    uint32_t messageWord[4];  ///< CAN TX message organized as a set of 32 bit words
} CAN_TxMsgBuffer;

// ==== Receive buffer memory (dedicated to PIC32) =====
typedef struct
{
    unsigned SID : 11;     ///< CAN TX Message Standard ID. This value should be between 0x0 - 0x7FF
    unsigned FILHIT : 5;   ///< Filter which accepted this message
    unsigned CMSGTS : 16;  ///< Time stamp of the received message. This is valid only if the Timestamping is enabled
} CAN_RXMSG_SID;

typedef union
{
    struct
    {
        CAN_RXMSG_SID msgSID;  ///< SID portion
        CAN_MSGEID msgEID;     ///< EID portion
        char data[8];          ///< data portion
    };
    uint32_t messageWord[4];  ///< CAN TX message organized as a set of 32 bit words
} CAN_RxMsgBuffer;

#endif  // CAN_PIC32_H
