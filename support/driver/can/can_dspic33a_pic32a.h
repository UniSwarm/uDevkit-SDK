/**
 * @file can_dspic33a_pic32a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025-2026
 *
 * @date May 3, 2025, 04:25 PM
 *
 * @brief CAN support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip documents DS70005629C and DS70005591D:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK256MPS306-Family-Data-Sheet-DS70005629.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 */

#ifndef CAN_DSPIC33A_PIC32A_H
#define CAN_DSPIC33A_PIC32A_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_33AK128MPS303) || defined(DEVICE_33AK128MPS305) || defined(DEVICE_33AK128MPS306) || defined(DEVICE_33AK256MPS303)                           \
    || defined(DEVICE_33AK256MPS305) || defined(DEVICE_33AK256MPS306)
#    define CAN_COUNT 1
#elif defined(DEVICE_33AK256MC505) || defined(DEVICE_33AK256MC506) || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510)                             \
    || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506) || defined(DEVICE_33AK256MPS508) || defined(DEVICE_33AK256MPS510)                        \
    || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC505) || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508)                           \
    || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS505) || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508)                         \
    || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)
#    define CAN_COUNT 2
#else
#    define CAN_COUNT 0
#endif

#if defined(DEVICE_33AK128MPS303) || defined(DEVICE_33AK128MPS305) || defined(DEVICE_33AK128MPS306) || defined(DEVICE_33AK256MC505)                            \
    || defined(DEVICE_33AK256MC506) || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510) || defined(DEVICE_33AK256MPS303)                           \
    || defined(DEVICE_33AK256MPS305) || defined(DEVICE_33AK256MPS306) || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506)                        \
    || defined(DEVICE_33AK256MPS508) || defined(DEVICE_33AK256MPS510) || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC505)                         \
    || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508) || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS505)                           \
    || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508) || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)
#    define CAN_FILTER_COUNT 16
#else
#    define CAN_FILTER_COUNT 0
#endif

#if defined(DEVICE_33AK128MPS303) || defined(DEVICE_33AK128MPS305) || defined(DEVICE_33AK128MPS306) || defined(DEVICE_33AK256MC505)                            \
    || defined(DEVICE_33AK256MC506) || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510) || defined(DEVICE_33AK256MPS303)                           \
    || defined(DEVICE_33AK256MPS305) || defined(DEVICE_33AK256MPS306) || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506)                        \
    || defined(DEVICE_33AK256MPS508) || defined(DEVICE_33AK256MPS510) || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC505)                         \
    || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508) || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS505)                           \
    || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508) || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)
#    define CAN_FIFO_COUNT 7
#else
#    define CAN_FIFO_COUNT 0
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

// CAN TX Message Object
typedef union
{
    struct
    {
        uint16_t sid;
        uint16_t eid;
        uint16_t flags;
        uint16_t unused;
    };
    uint16_t messageWord[4];
} CAN_TxMsgBuffer;
#define CAN_DSPIC33C_TX_SETDLC(txbuffer, dlc) (txbuffer)->flags |= (dlc & 0x0F)
#define CAN_DSPIC33C_TX_SETIDE(txbuffer)      (txbuffer)->flags |= 0x0010
#define CAN_DSPIC33C_TX_SETRTR(txbuffer)      (txbuffer)->flags |= 0x0020
#define CAN_DSPIC33C_TX_SETBRS(txbuffer)      (txbuffer)->flags |= 0x0040
#define CAN_DSPIC33C_TX_SETFDF(txbuffer)      (txbuffer)->flags |= 0x0080

// Can RX Message Object
typedef struct
{
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
#define CAN_DSPIC33C_RX_SID(rxbuffer)  ((uint32_t)(rxbuffer)->sid & 0x07FF)
#define CAN_DSPIC33C_RX_EIDL(rxbuffer) (((uint32_t)(rxbuffer)->sid & 0xF800) >> 11)
#define CAN_DSPIC33C_RX_EIDH(rxbuffer) ((uint32_t)(rxbuffer)->eid << 5)

// CAN filter Object
#define CAN_filter_SID(idFilter)  ((uint16_t)(idFilter >> 18) & 0x07FF)
#define CAN_filter_EIDL(idFilter) ((uint16_t)(idFilter << 11) & 0xF800)
#define CAN_filter_EIDH(idFilter) ((uint16_t)(idFilter >> 5) & 0x1FFF)

#define CAN_MESSAGE_HEADER_SIZE 8U

#ifdef __cplusplus
}
#endif

#endif  // CAN_DSPIC33A_PIC32A_H
