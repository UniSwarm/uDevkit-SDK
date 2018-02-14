/**
 * @file qei_pic24e_dspic33e.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver for dsPIC33EP,
 * dsPIC33EV and PIC24EP
 * 
 * Implementation based on Microchip document DS70601B :
 *   http://ww1.microchip.com/downloads/en/DeviceDoc/S15.pdf
 */

#ifndef QEI_PIC24E_DSPIC33E_H
#define QEI_PIC24E_DSPIC33E_H

// calculate QEI count and version on the device
#if defined(DEVICE_33EDV64MC205) || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204) \
 || defined(DEVICE_33EP128MC206) || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) \
 || defined(DEVICE_33EP128MC506) || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) \
 || defined(DEVICE_33EP256MC206) || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) \
 || defined(DEVICE_33EP256MC506) || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) \
 || defined(DEVICE_33EP32MC204) || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) \
 || defined(DEVICE_33EP32MC504) || defined(DEVICE_33EP512MC202) || defined(DEVICE_33EP512MC204) \
 || defined(DEVICE_33EP512MC206) || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP512MC504) \
 || defined(DEVICE_33EP512MC506) || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) \
 || defined(DEVICE_33EP64MC204) || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) \
 || defined(DEVICE_33EP64MC503) || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) \
 || defined(DEVICE_24EP128MC202) || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) \
 || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206) \
 || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203) || defined(DEVICE_24EP32MC204) \
 || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) \
 || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) \
 || defined(DEVICE_24EP64MC206)
 #define QEI_COUNT 1
#elif defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) \
 || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) \
 || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) \
 || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) \
 || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) \
 || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) \
 || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) \
 || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
 #define QEI_COUNT 2
#else
 #define QEI_COUNT 0
#endif

#define QEI_32B

#endif // QEI_PIC24E_DSPIC33E_H
