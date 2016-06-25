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

// ==== pins define ====
// leds
#define LED LATDbits.LATD11

// voltage measurement
#define BOARD_VOLT_IN 2 // RB2		// analog board voltage channel

// motors pins
#define M1A LATBbits.LATB14			// A pin direction
#define M1B LATBbits.LATB15			// B pin direction
#define M1en LATDbits.LATD0			// pwm/en pin
#define M1I 1	// RB1				// analog current channel

#define M2A LATBbits.LATB12			// A pin direction
#define M2B LATBbits.LATB13			// B pin direction
#define M2en LATFbits.LATF3			// pwm/en pin
#define M2I 0	// RB0				// analog current channel

#define M3A LATBbits.LATB8			// A pin direction
#define M3B LATBbits.LATB9			// B pin direction
#define M3en LATFbits.LATF5			// pwm/en pin
#define M3I 6	// RB6				// analog current channel

#define M4A LATBbits.LATB10			// A pin direction
#define M4B LATBbits.LATB11			// B pin direction
#define M4en LATFbits.LATF4			// pwm/en pin
#define M4I 7	// RB7				// analog current channel

// AX12
#define AX12_TXEN LATBbits.LATB3	// AX12 buffer direction

// A6
#define A6_RW LATDbits.LATD1		// A6 trancever direction
#define A6_WRITE 1
#define A6_READ 0

#endif // RTBOARD_H
