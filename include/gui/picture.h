/**
 * @file picture.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date June 12, 2016, 11:28 PM
 *
 * @brief Picture structure for gui module
 */

#ifndef PICTURE_H
#define PICTURE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef XC16
#    define __space_prog__ __attribute__((space(prog)))
#else
#    define __prog__
#    define __space_prog__
#endif

/**
 * @brief Picture struct
 * contains data and metadata (width, height...)
 */
typedef struct
{
    // metadata
    uint16_t width;
    uint16_t height;

    // data
    __prog__ const uint16_t *data;

} Picture;

#ifdef __cplusplus
}
#endif

#endif  // PICTURE_H
