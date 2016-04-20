/**
 * @file rtboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 06:07 PM
 * 
 * @brief Definitions for RTboard from Robotips
 */

#ifndef RTBOARD_H
#define RTBOARD_H

#include <xc.h>

int init_board();

#define BOARD_NAME "rtboard"
#define SYSCLOCK_XTAL 8000000

// pins define
#define LED LATDbits.LATD11

#define M1A LATBbits.LATB14
#define M1B LATBbits.LATB15
#define M1en LATDbits.LATD0

#define M2A LATBbits.LATB12
#define M2B LATBbits.LATB13
#define M2en LATFbits.LATF3

#define M3A LATBbits.LATB8
#define M3B LATBbits.LATB9
#define M3en LATFbits.LATF5

#define M4A LATBbits.LATB10
#define M4B LATBbits.LATB11
#define M4en LATFbits.LATF4

#endif // RTBOARD_H