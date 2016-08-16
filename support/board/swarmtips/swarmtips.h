/**
 * @file swarmtips.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date August 13, 2016, 12:04 PM
 * 
 * @brief Definitions for Swarmtips platform from Robotips
 */

#ifndef SWARMTIPS_H
#define SWARMTIPS_H

#ifndef SIMULATOR
 #include <xc.h>
#endif
 
int init_board();

#define BOARD_NAME "swarmtips"

// ==== pins define ====

// voltage measurement
#define BOARD_VOLT_IN 8 // RB8		// analog board voltage channel

// leds
#define LED LATBbits.LATB3
#define LED2 LATDbits.LATD11

// motors pins
#define M1A LATEbits.LATE4          // A pin direction
#define M1B LATEbits.LATE6          // B pin direction

#define M2A LATEbits.LATE1          // A pin direction
#define M2B LATEbits.LATE3          // B pin direction

// ==== motor config ====
#define MOTOR_COUNT 2


#endif // SWARMTIPS_H
