/**
 * @file qei_.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 18, 2016, 22:33 PM
 *
 * @brief Quadrature Encoder Interface support driver
 */

#ifndef QEI__H
#define QEI__H

// calculate QEI count and version on the device
#if defined(DEVICE_30F2010) || defined(DEVICE_30F3010) || defined(DEVICE_30F3011) \
 || defined(DEVICE_30F4011) || defined(DEVICE_30F4012) || defined(DEVICE_30F5015) \
 || defined(DEVICE_30F5016) || defined(DEVICE_30F6010A) || defined(DEVICE_30F6015) \
 || defined(DEVICE_33FJ128MC510A) || defined(DEVICE_33FJ128MC706A) || defined(DEVICE_33FJ128MC708A) \
 || defined(DEVICE_33FJ128MC710A) || defined(DEVICE_33FJ12MC201) || defined(DEVICE_33FJ12MC202) \
 || defined(DEVICE_33FJ16MC304) || defined(DEVICE_33FJ256MC510A) || defined(DEVICE_33FJ256MC710A) \
 || defined(DEVICE_33FJ32GS406) || defined(DEVICE_33FJ32MC202) || defined(DEVICE_33FJ32MC204) \
 || defined(DEVICE_33FJ64GS406) || defined(DEVICE_33FJ64MC506A) || defined(DEVICE_33FJ64MC508A) \
 || defined(DEVICE_33FJ64MC510A) || defined(DEVICE_33FJ64MC706A) || defined(DEVICE_33FJ64MC710A) \
 || defined(DEVICE_33FJ128MC506A)
  #define QEI_COUNT 1
  #define QEI_V1
  #define QEI_16B
#elif defined(DEVICE_24EP128MC202) || defined(DEVICE_24EP128MC204) || defined(DEVICE_24EP128MC206) \
 || defined(DEVICE_24EP256MC202) || defined(DEVICE_24EP256MC204) || defined(DEVICE_24EP256MC206) \
 || defined(DEVICE_24EP32MC202) || defined(DEVICE_24EP32MC203) || defined(DEVICE_24EP32MC204) \
 || defined(DEVICE_24EP512MC202) || defined(DEVICE_24EP512MC204) || defined(DEVICE_24EP512MC206) \
 || defined(DEVICE_24EP64MC202) || defined(DEVICE_24EP64MC203) || defined(DEVICE_24EP64MC204) \
 || defined(DEVICE_33EP128MC202) || defined(DEVICE_33EP128MC204) || defined(DEVICE_33EP128MC206) \
 || defined(DEVICE_33EP128MC502) || defined(DEVICE_33EP128MC504) || defined(DEVICE_33EP128MC506) \
 || defined(DEVICE_33EP256MC202) || defined(DEVICE_33EP256MC204) || defined(DEVICE_33EP256MC206) \
 || defined(DEVICE_33EP256MC502) || defined(DEVICE_33EP256MC504) || defined(DEVICE_33EP256MC506) \
 || defined(DEVICE_33EP32MC202) || defined(DEVICE_33EP32MC203) || defined(DEVICE_33EP32MC204) \
 || defined(DEVICE_33EP32MC502) || defined(DEVICE_33EP32MC503) || defined(DEVICE_33EP32MC504) \
 || defined(DEVICE_33EP512MC502) || defined(DEVICE_33EP512MC504) || defined(DEVICE_33EP512MC506) \
 || defined(DEVICE_33EP64MC202) || defined(DEVICE_33EP64MC203) || defined(DEVICE_33EP64MC204) \
 || defined(DEVICE_33EP64MC206) || defined(DEVICE_33EP64MC502) || defined(DEVICE_33EP64MC503) \
 || defined(DEVICE_33EP64MC504) || defined(DEVICE_33EP64MC506) || defined(DEVICE_24EP64MC206)
  #define QEI_COUNT 1
  #define QEI_V2
  #define QEI_32B
#elif defined(DEVICE_33FJ128MC202) || defined(DEVICE_33FJ128MC204) || defined(DEVICE_33FJ128MC802) \
 || defined(DEVICE_33FJ128MC804) || defined(DEVICE_33FJ32GS606) || defined(DEVICE_33FJ32GS608) \
 || defined(DEVICE_33FJ32GS610) || defined(DEVICE_33FJ32MC302) || defined(DEVICE_33FJ32MC304) \
 || defined(DEVICE_33FJ64GS606) || defined(DEVICE_33FJ64GS608) || defined(DEVICE_33FJ64GS610) \
 || defined(DEVICE_33FJ64MC202) || defined(DEVICE_33FJ64MC204) || defined(DEVICE_33FJ64MC802) \
 || defined(DEVICE_33FJ64MC804)
  #define QEI_COUNT 2
  #define QEI_V1
  #define QEI_16B
#elif defined(DEVICE_33EP128GM304) || defined(DEVICE_33EP128GM306) || defined(DEVICE_33EP128GM310) \
 || defined(DEVICE_33EP128GM604) || defined(DEVICE_33EP128GM706) || defined(DEVICE_33EP128GM710) \
 || defined(DEVICE_33EP256GM304) || defined(DEVICE_33EP256GM306) || defined(DEVICE_33EP256GM310) \
 || defined(DEVICE_33EP256GM604) || defined(DEVICE_33EP256GM706) || defined(DEVICE_33EP256GM710) \
 || defined(DEVICE_33EP256MU806) || defined(DEVICE_33EP256MU810) || defined(DEVICE_33EP256MU814) \
 || defined(DEVICE_33EP512GM304) || defined(DEVICE_33EP512GM306) || defined(DEVICE_33EP512GM310) \
 || defined(DEVICE_33EP512GM604) || defined(DEVICE_33EP512GM706) || defined(DEVICE_33EP512GM710) \
 || defined(DEVICE_33EP512MC806) || defined(DEVICE_33EP512MU810) || defined(DEVICE_33EP512MU814)
  #define QEI_COUNT 2
  #define QEI_V2
  #define QEI_32B
#else
  #define QEI_COUNT 0
#endif

#endif // QEI__H
