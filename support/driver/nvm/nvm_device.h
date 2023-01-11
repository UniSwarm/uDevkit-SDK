/**
 * @file nvm_device.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 11, 2023, 10:52 AM
 *
 * @brief NVM support for specific devices
 */

#ifndef NVM_DEVICE_H
#define NVM_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) \
    || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
#    include "nvm_pic24_dspic30f_dspic33.h"
#else
#    error Unsuported ARCHI
#endif

#ifdef __cplusplus
}
#endif

#endif  // NVM_DEVICE_H
