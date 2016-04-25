/**
 * @file a6screenboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 49, 2016, 08:49 AM
 * 
 * @brief Code for A6screenboard from Robotips
 */

#include "a6screenboard.h"

#include <xc.h>

int init_io()
{
	ANSELB = 0x0000;	// all analog inputs of port B as digital buffer
	ANSELD = 0x0000;	// all analog inputs of port D as digital buffer
	ANSELG = 0x0000;	// all analog inputs of port G as digital buffer
	
	TRISDbits.TRISD3 = 0;		// SCREEN_RD pin as output
	TRISDbits.TRISD2 = 0;		// SCREEN_RW pin as output
	TRISDbits.TRISD1 = 0;		// SCREEN_RS pin as output
	TRISDbits.TRISD0 = 0;		// SCREEN_CS pin as output
	TRISDbits.TRISD4 = 0;		// SCREEN_RST pin as output
	TRISEbits.TRISE4 = 0;		// SCREEN_LEDBL pin as output
	
	TRISFbits.TRISF1 = 0;		// A6_RW pin as output
	
	// Unlock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;
		
		// UART1 pins (A6)
		RPINR18bits.U1RXR = 80; // RX ==> RP80
		RPOR7bits.RP96R = 0b00001; // TX ==> RP96
		
		// OC PWM luminosity
		RPOR0bits.RP64R = 0b010000; // OC1 ==> RP64
		
	// Lock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 1;
	
	return 0;
}

int init_board()
{
	init_io();
	
	return 0;
}

