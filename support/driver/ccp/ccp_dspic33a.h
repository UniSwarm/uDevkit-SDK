/**
 * @file ccp_dspic33a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2024
 *
 * @date August 3, 2024, 03:01 PM
 *
 * @brief .....
 */

#ifndef CCP_DSPIC33A_H
#define CCP_DSPIC33A_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105) || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102)    \
    || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) || defined(DEVICE_33AK128MC102)                               \
    || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)
#    define CCP_COUNT 4
#else
#    define CCP_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // CCP_DSPIC33A_H
