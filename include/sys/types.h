/**
 * @file types.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date June 25, 2016, 16:13 PM
 *
 * @brief Low level periph assignement handler
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#if !defined(_SIZE_T_DEFINED) &&  !defined(__SIZE_TYPE__) && !defined(_SIZE_T) && !defined(_SIZET)&& !defined(_BSD_SIZE_T_DEFINED_)
#define _SIZE_T_DEFINED
#define _SIZE_T
#define _SIZET
#define _BSD_SIZE_T_DEFINED_
 typedef uint16_t size_t;
#endif

#if !defined(_SSIZE_T_DEFINED) && !defined(_SSIZE_T) && !defined(_SSIZET)&& !defined(_BSD_SSIZE_T_DEFINED_)
#define _SSIZE_T_DEFINED
#define _SSIZE_T
#define _SSIZET
#define _BSD_SSIZE_T_DEFINED_
 typedef int16_t ssize_t;
#endif

#endif // TYPES_H
