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
	// analog inputs
	ANSELB = 0x0000;	// all analog inputs of port B as digital buffer
	ANSELD = 0x0000;	// all analog inputs of port D as digital buffer
	ANSELE = 0x0007;	// all analog inputs of port E as digital buffer
	ANSELG = 0x0000;	// all analog inputs of port G as digital buffer
	
	ANSELBbits.ANSB2 = 1;		// BOARD_VOLT_IN as analog
	ANSELBbits.ANSB1 = 1;		// M1I as analog
	ANSELBbits.ANSB0 = 1;		// M2I as analog
	ANSELBbits.ANSB6 = 1;		// M3I as analog
	ANSELBbits.ANSB6 = 1;		// M4I as analog
	
	// digitals outputs
	TRISDbits.TRISD11 = 0;		// LED pin as output
	
	TRISBbits.TRISB14 = 0;		// M1A pin as output
	TRISBbits.TRISB15 = 0;		// M1B pin as output
	
	TRISBbits.TRISB12 = 0;		// M2A pin as output
	TRISBbits.TRISB13 = 0;		// M2B pin as output
	
	TRISBbits.TRISB8 = 0;		// M3A pin as output
	TRISBbits.TRISB9 = 0;		// M3B pin as output
	
	TRISBbits.TRISB10 = 0;		// M4A pin as output
	TRISBbits.TRISB11 = 0;		// M4B pin as output
	
	TRISBbits.TRISB3 = 0;		// AX12_TXEN pin as output
	
	// remappable pins
	// Unlock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;
		
		// UART1 pins (wifi)
		RPINR18bits.U1RXR = 71; // RX1 ==> RP71
		RPOR2bits.RP69R = 0b000001; // TX1 ==> RP69
		
		// UART2 pins (AX12)
		RPINR19bits.U2RXR = 97; // RX2 ==> RP97 AXrx
		RPOR14bits.RP120R = 0b000011; // TX2 ==> RP120 AXtx
		
		// UART3 pins (A6)
		RPINR27bits.U3RXR = 72; // RX3 ==> RPI72 A6rx
		RPOR1bits.RP66R = 0b011011; // TX3 ==> RP66 A6tx
		
		// UART4 pins (debug)
		RPINR28bits.U4RXR = 86; // RX4 ==> RPI86 AS7
		RPOR6bits.RP85R = 0b011101; // TX4 ==> RP85 AS6
		
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

