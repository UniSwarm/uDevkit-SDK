/**
 * @file can_pic24_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2021
 *
 * @date May 06, 2016, 11:34 AM
 *
 * @brief CAN communication support driver for dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 *
 * Implementation based on Microchip document DS70185C and DS70353C :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70185C.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70353C.pdf
 */

#ifndef CAN_PIC24_DSPIC33_H
#define CAN_PIC24_DSPIC33_H

#if defined(DEVICE_33EP128GP502) || defined(DEVICE_33EP128GP504) || defined(DEVICE_33EP128GP506)                       \
    || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506)                    \
    || defined(DEVICE_33EP256GP502) || defined(DEVICE_33EP256GP504) || defined(DEVICE_33EP256GP506)                    \
    || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506)                    \
    || defined(DEVICE_33EP32GP502) || defined(DEVICE_33EP32GP503) || defined(DEVICE_33EP32GP504)                       \
    || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504)                       \
    || defined(DEVICE_33EP512GP502) || defined(DEVICE_33EP512GP504) || defined(DEVICE_33EP512GP506)                    \
    || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506)                    \
    || defined(DEVICE_33EP64GP502) || defined(DEVICE_33EP64GP503) || defined(DEVICE_33EP64GP504)                       \
    || defined(DEVICE_33EP64GP506) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503)                       \
    || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) || defined(DEVICE_33EV128GM102)                      \
    || defined(DEVICE_33EV128GM103) || defined(DEVICE_33EV128GM104) || defined(DEVICE_33EV128GM106)                    \
    || defined(DEVICE_33EV256GM102) || defined(DEVICE_33EV256GM103) || defined(DEVICE_33EV256GM104)                    \
    || defined(DEVICE_33EV256GM106) || defined(DEVICE_33EV32GM102) || defined(DEVICE_33EV32GM103)                      \
    || defined(DEVICE_33EV32GM104) || defined(DEVICE_33EV32GM106) || defined(DEVICE_33EV64GM102)                       \
    || defined(DEVICE_33EV64GM103) || defined(DEVICE_33EV64GM104) || defined(DEVICE_33EV64GM106)                       \
    || defined(DEVICE_33FJ128GP802) || defined(DEVICE_33FJ128GP804) || defined(DEVICE_33FJ128MC506)                    \
    || defined(DEVICE_33FJ128MC506A) || defined(DEVICE_33FJ128MC510) || defined(DEVICE_33FJ128MC510A)                  \
    || defined(DEVICE_33FJ128MC706) || defined(DEVICE_33FJ128MC706A) || defined(DEVICE_33FJ128MC802)                   \
    || defined(DEVICE_33FJ128MC804) || defined(DEVICE_33FJ256GP506) || defined(DEVICE_33FJ256GP506A)                   \
    || defined(DEVICE_33FJ256GP510) || defined(DEVICE_33FJ256GP510A) || defined(DEVICE_33FJ256MC510)                   \
    || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ64GP802) || defined(DEVICE_33FJ64GP804)                     \
    || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64GS608) || defined(DEVICE_33FJ64GS610)                       \
    || defined(DEVICE_33FJ64MC506) || defined(DEVICE_33FJ64MC506A) || defined(DEVICE_33FJ64MC508)                      \
    || defined(DEVICE_33FJ64MC508A) || defined(DEVICE_33FJ64MC510) || defined(DEVICE_33FJ64MC510A)                     \
    || defined(DEVICE_33FJ64MC706) || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC802)                      \
    || defined(DEVICE_33FJ64MC804) || defined(DEVICE_24HJ128GP502) || defined(DEVICE_24HJ128GP504)                     \
    || defined(DEVICE_24HJ128GP506) || defined(DEVICE_24HJ128GP506A) || defined(DEVICE_24HJ128GP510)                   \
    || defined(DEVICE_24HJ128GP510A) || defined(DEVICE_24HJ64GP502) || defined(DEVICE_24HJ64GP504)                     \
    || defined(DEVICE_24HJ64GP506) || defined(DEVICE_24HJ64GP506A) || defined(DEVICE_24HJ64GP510)                      \
    || defined(DEVICE_24HJ64GP510A)
#    define CAN_COUNT 1
#elif defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710)                     \
    || defined(DEVICE_33EP128GS804) || defined(DEVICE_33EP128GS805) || defined(DEVICE_33EP128GS806)                    \
    || defined(DEVICE_33EP128GS808) || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706)                    \
    || defined(DEVICE_33EP256GM710) || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810)                    \
    || defined(DEVICE_33EP256MU814) || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706)                    \
    || defined(DEVICE_33EP512GM710) || defined(DEVICE_33EP512GP806) || defined(DEVICE_33EP512MC806)                    \
    || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814) || defined(DEVICE_33EP64GS804)                     \
    || defined(DEVICE_33EP64GS805) || defined(DEVICE_33EP64GS806) || defined(DEVICE_33EP64GS808)                       \
    || defined(DEVICE_33FJ128GP706) || defined(DEVICE_33FJ128GP706A) || defined(DEVICE_33FJ128GP708)                   \
    || defined(DEVICE_33FJ128GP708A) || defined(DEVICE_33FJ128GP710) || defined(DEVICE_33FJ128GP710A)                  \
    || defined(DEVICE_33FJ128MC708) || defined(DEVICE_33FJ128MC708A) || defined(DEVICE_33FJ128MC710)                   \
    || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ256GP710) || defined(DEVICE_33FJ256GP710A)                  \
    || defined(DEVICE_33FJ256MC710) || defined(DEVICE_33FJ256MC710A) || defined(DEVICE_33FJ64GP706)                    \
    || defined(DEVICE_33FJ64GP706A) || defined(DEVICE_33FJ64GP708) || defined(DEVICE_33FJ64GP708A)                     \
    || defined(DEVICE_33FJ64GP710) || defined(DEVICE_33FJ64GP710A) || defined(DEVICE_33FJ64MC710)                      \
    || defined(DEVICE_33FJ64MC710A) || defined(DEVICE_24EP256GU810) || defined(DEVICE_24EP256GU814)                    \
    || defined(DEVICE_24EP512GP806) || defined(DEVICE_24EP512GU810) || defined(DEVICE_24EP512GU814)                    \
    || defined(DEVICE_24HJ256GP610) || defined(DEVICE_24HJ256GP610A)
#    define CAN_COUNT 2
#else
#    define CAN_COUNT 0
#endif

#if CAN_COUNT > 0
#    define CAN_FIFO_COUNT 32
#else
#    define CAN_FIFO_COUNT 0
#endif

#endif  // CAN_PIC24_DSPIC33_H
