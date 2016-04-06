#include "setup.h"

void setup_clock()
{
	CLKDIVbits.PLLPRE = 0;	// PLL pre div = 1
	CLKDIVbits.PLLPOST = 0;	// PLL pre div = 1
	PLLFBD = 58;			// * 15 ==> 120MHz
	//                         (PLLFBD + 2)
	// Fosc = Fin * ----------------------------------
	//              ((PLLPRE + 2) * 2 * (PLLPOST + 1))
	//while(OSCCONbits.LOCK!=1); // Wait for PLL to lock
	
    __builtin_write_OSCCONH(0x03);
    __builtin_write_OSCCONL(0x01);

    while (OSCCONbits.COSC != 0x3);
}

void setup_io()
{
	ANSELB = 0x00C7;	// port B as digital buffer, but RB7-6 and RB2-0
	ANSELD = 0x0000;	// all analog inputs of port D as digital buffer
	ANSELG = 0x0000;	// all analog inputs of port G as digital buffer
	TRISDbits.TRISD11 = 0;		// LED pin as output
	//TRISBbits.TRISB14 = 0;
	
	// Unlock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;
		
		// UART1 pins
		RPINR18bits.U1RXR = 71; // RX ==> RP71
		RPOR2bits.RP69R = 0b00001; // TX ==> RP69
		
		// QEI1 pins
		RPINR14bits.QEA1R = 119; // C1A ==> RPI119
		RPINR14bits.QEB1R = 118; // C1B ==> RPI118
		
		// QEI2 pins
		RPINR16bits.QEA2R = 37; // C2A ==> RPI37
		RPINR16bits.QEB2R = 121; // C2B ==> RPI121
		
		// OC PWM motors
		RPOR0bits.RP64R = 0b010000; // OC1 ==> RP64
		RPOR8bits.RP99R = 0b010001; // OC2 ==> RP99
		
	// Lock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 1;
	
	// M1
	TRISBbits.TRISB14 = 0;	// M1A
	TRISBbits.TRISB15 = 0;	// M1B
	//TRISDbits.TRISD0 = 0;	// M1en
}
