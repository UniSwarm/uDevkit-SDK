/**
 * @file rtboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 25, 2016, 08:49 AM
 * 
 * @brief Definitions for RTboard from Robotips
 */

#ifndef A6SCREENBOARD_H
#define A6SCREENBOARD_H

int init_board();

#define BOARD_NAME "a6screenboard"

// pins define
#define SCREEN_PORT		LATB
#define SCREEN_PORT_INPUT		(TRISB = 1)
#define SCREEN_PORT_OUTPUT		(TRISB = 0)
#define SCREEN_RD		LATDbits.LATD3
#define SCREEN_RW		LATDbits.LATD2
#define SCREEN_RS		LATDbits.LATD1
#define SCREEN_CS		LATDbits.LATD0
#define SCREEN_RST		LATDbits.LATD4
#define SCREEN_LEDBL	LATEbits.LATE4

#define A6_RW			LATFbits.LATF1

#endif // A6SCREENBOARD_H
