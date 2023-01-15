/**
 * @file pic32mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 12, 2017, 11:35 AM
 *
 * @brief Architecture low level definitions for PIC32MK
 */

#ifndef PIC32MK_H
#define PIC32MK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../pic32/pic32.h"

void archi_prefetch_enable(void);
void archi_prefetch_disable(void);

#ifdef __cplusplus
}
#endif

#endif  // PIC32MK_H
