/**
 * @file rtboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 11, 2016, 06:07 PM
 * 
 * @brief Code for RTboard from Robotips
 */

#include "rtboard.h"

int init_io()
{
	ANSELB = 0x0000;	// all analog inputs of port B as digital buffer
	ANSELD = 0x0000;	// all analog inputs of port D as digital buffer
	ANSELG = 0x0000;	// all analog inputs of port G as digital buffer
	
	TRISDbits.TRISD11 = 0;		// LED pin as output
	
	TRISBbits.TRISB14 = 0;		// M1A pin as output
	TRISBbits.TRISB15 = 0;		// M1B pin as output
	
	TRISBbits.TRISB12 = 0;		// M2A pin as output
	TRISBbits.TRISB13 = 0;		// M2B pin as output
	
	TRISBbits.TRISB8 = 0;		// M3A pin as output
	TRISBbits.TRISB9 = 0;		// M3B pin as output
	
	TRISBbits.TRISB10 = 0;		// M4A pin as output
	TRISBbits.TRISB11 = 0;		// M4B pin as output
	
	// Unlock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;
		
		// UART1 pins (wifi)
		RPINR18bits.U1RXR = 71; // RX ==> RP71
		RPOR2bits.RP69R = 0b00001; // TX ==> RP69
		
		// uart debug
		RPOR4bits.RP80R = 0b00011; // TX ==> RP80 AnP1
		RPINR19bits.U2RXR = 81; // RX ==> RP81 AnP2
		
		// QEI1 pins (coder 1)
		RPINR14bits.QEA1R = 119; // C1A ==> RPI119
		RPINR14bits.QEB1R = 118; // C1B ==> RPI118
		
		// QEI2 pins (coder 2)
		RPINR16bits.QEA2R = 37; // C2A ==> RPI37
		RPINR16bits.QEB2R = 121; // C2B ==> RPI121
		
		// OC PWM motors (motor 1-4)
		RPOR0bits.RP64R = 0b010000; // OC1 ==> RP64
		RPOR8bits.RP99R = 0b010001; // OC2 ==> RP99
		RPOR9bits.RP101R = 0b010010; // OC3 ==> RP101
		RPOR9bits.RP100R = 0b010011; // OC4 ==> RP100
		
	// Lock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 1;
	
	return 0;
}

int init_board()
{
	init_io();
	
	return 0;
}

