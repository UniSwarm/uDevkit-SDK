/**
 * @file can_dspic33c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date September 4 2018, 15:05 PM
 *
 * @brief CAN communication support driver for dsPIC33CH, dsPIC33CK with CAN-Fd extension
 *
 * Implementation based on Microchip document DS70005340A :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM-CAN-Flexible-Data-Rate-FD-Protocol-Module-70005340a.pdf
 */

#ifndef CAN_DSPIC33C_H
#define CAN_DSPIC33C_H

#if defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505) \
 || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH64MP502) \
 || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) \
 || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) \
 || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) \
 || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) \
 || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK32MP502) \
 || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) \
 || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) \
 || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)
 #define CAN_COUNT 1
#elif defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508) \
 || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
 #define CAN_COUNT 2
#else
 #define CAN_COUNT 0
#endif

#if defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505) \
 || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP505) \
 || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP505) \
 || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508) || defined(DEVICE_33CH64MP502) \
 || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) \
 || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) \
 || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) \
 || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) \
 || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK32MP502) \
 || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) \
 || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) \
 || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)
 #define CAN_FILTER_COUNT 16
 #define CAN_FIFO_COUNT 7
#else
 #define CAN_FIFO_COUNT 0
 #define CAN_FILTER_COUNT 0
#endif

typedef struct {
    unsigned DLC:4;
    unsigned IDE:1;
    unsigned RTR:1;
    unsigned BRS:1;
    unsigned FDF:1;
    unsigned ESI:1;
    unsigned SEQ:7;
    unsigned unimplemented1:16;
} CAN_TX_MSGOBJ_CTRL;

// CANFD TX Message ID
    typedef struct {
    unsigned SID:11;
    unsigned long EID:18;
    unsigned SID11:1;
    unsigned unimplemented1:2;
} CAN_MSGOBJ_ID;

// CAN TX Message Object
typedef union {
    struct {
        uint16_t sid;
        uint16_t eid;
        uint16_t flags;
        uint16_t unused;
    };
    uint16_t messageWord[4];
} CAN_TxMsgBuffer;
#define CAN_DSPIC33C_TX_SETDLC(txbuffer, dlc) (txbuffer)->flags |= (dlc & 0x0F)
#define CAN_DSPIC33C_TX_SETIDE(txbuffer) (txbuffer)->flags |= 0x0010
#define CAN_DSPIC33C_TX_SETRTR(txbuffer) (txbuffer)->flags |= 0x0020
#define CAN_DSPIC33C_TX_SETBRS(txbuffer) (txbuffer)->flags |= 0x0040
#define CAN_DSPIC33C_TX_SETFDF(txbuffer) (txbuffer)->flags |= 0x0080

typedef struct {
    uint16_t sid;
    uint16_t eid;
    uint16_t flags;
    uint16_t unused;
    uint16_t timeStampL;
    uint16_t timeStampH;
} CAN_RxMsgBuffer;
#define CAN_DSPIC33C_RX_DLC(rxbuffer)  ((rxbuffer)->flags & 0x000F)
#define CAN_DSPIC33C_RX_IDE(rxbuffer)  ((rxbuffer)->flags & 0x0010)
#define CAN_DSPIC33C_RX_RTR(rxbuffer)  ((rxbuffer)->flags & 0x0020)
#define CAN_DSPIC33C_RX_BRS(rxbuffer)  ((rxbuffer)->flags & 0x0040)
#define CAN_DSPIC33C_RX_FDF(rxbuffer)  ((rxbuffer)->flags & 0x0080)
#define CAN_DSPIC33C_RX_SID(rxbuffer)  ((uint32_t)(rxbuffer)->sid   & 0x03FF)
#define CAN_DSPIC33C_RX_EIDL(rxbuffer) (((uint32_t)(rxbuffer)->sid  & 0xF800) >> 11)
#define CAN_DSPIC33C_RX_EIDH(rxbuffer) ((uint32_t)(rxbuffer)->eid << 5)

#endif // CAN_DSPIC33C_H
