/**
 * @file can_dspic33a_pic32a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date May 3, 2025, 04:25 PM
 *
 * @brief CAN support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip document DS70005539B:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
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

#ifdef __cplusplus
}
#endif

#endif  // CAN_DSPIC33A_PIC32A_H
