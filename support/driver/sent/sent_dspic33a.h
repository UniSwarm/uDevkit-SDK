/**
 * @file sent_dspic33a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date August 3, 2024, 03:36 PM
 *
 * Implementation based on Microchip document DS70005539B:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 */

#ifndef SENT_DSPIC33A_H
#define SENT_DSPIC33A_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105) || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102)    \
    || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) || defined(DEVICE_33AK128MC102)                               \
    || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)
#    define SENT_COUNT 2
#else
#    define SENT_COUNT 0
#endif


#ifdef __cplusplus
}
#endif

#endif  // SENT_DSPIC33A_H
