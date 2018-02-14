/**
 * @file sent_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2017
 *
 * @date November 17, 2017, 16:10 PM
 *
 * @brief SAE J2716 SENT (Single Edge Nibble Transmission) support driver for dsPIC33EV, dsPIC33CH
 * and dsPIC33CK
 *
 * Implementation based on Microchip document DS70005145B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005145b.pdf
 */

#ifndef SENT_DSPIC33_H
#define SENT_DSPIC33_H

#if defined(DEVICE_33EV128GM002) || defined(DEVICE_33EV128GM003) || defined(DEVICE_33EV128GM004) \
 || defined(DEVICE_33EV128GM006) || defined(DEVICE_33EV128GM102) || defined(DEVICE_33EV128GM103) \
 || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106) || defined(DEVICE_33EV256GM002) \
 || defined(DEVICE_33EV256GM003) || defined(DEVICE_33EV256GM004) || defined(DEVICE_33EV256GM006) \
 || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104) \
 || defined(DEVICE_33EV256GM106) || defined(DEVICE_33EV32GM002) || defined(DEVICE_33EV32GM003) \
 || defined(DEVICE_33EV32GM004) || defined(DEVICE_33EV32GM006) || defined(DEVICE_33EV32GM102) \
 || defined(DEVICE_33EV32GM103) || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) \
 || defined(DEVICE_33EV64GM002) || defined(DEVICE_33EV64GM003) || defined(DEVICE_33EV64GM004) \
 || defined(DEVICE_33EV64GM006) || defined(DEVICE_33EV64GM102) || defined(DEVICE_33EV64GM103) \
 || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106)
 #define SENT_COUNT 2
#else
 #define SENT_COUNT 0
#endif

#endif // SENT_DSPIC33_H
