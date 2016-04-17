// FGS
#pragma config GWRP = OFF           // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = OFF            // General Segment Code-Protect bit (General Segment Code protect is disabled)
#pragma config GSSK = OFF           // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)

// FOSCSEL
#pragma config FNOSC = PRIPLL        // Initial Oscillator Source Selection Bits (Internal Fast RC (FRC))
#pragma config IESO = OFF           // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#pragma config OSCIOFNC = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = OFF        // Peripheral pin select configuration (Allow multiple reconfigurations)
#pragma config FCKSM = CSECMD       // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPOST = PS32768    // Watchdog Timer Postscaler Bits (1:32,768)
#pragma config WDTPRE = PR128       // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN = ON          // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF         // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128           // Power-on Reset Timer Value Select bits (128ms)
#pragma config BOREN = ON              // Brown-out Reset (BOR) Detection Enable bit (BOR is disabled)
#pragma config ALTI2C1 = OFF            // Alternate I2C pins for I2C1 (SDA1/SCK1 pins are selected as the I/O pins for I2C1)

// FICD
#pragma config ICS = PGD2           // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config RSTPRI = PF          // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
#pragma config JTAGEN = OFF         // JTAG Enable bit (JTAG is disabled)

// FAS
#pragma config AWRP = OFF           // Auxiliary Segment Write-protect bit (Auxiliary program memory is not write-protected)
#pragma config APL = OFF            // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
#pragma config APLK = OFF           // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)

#include <stdio.h>
#include <stdint.h>
#include <xc.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

int main(void)
{
	unsigned int i,j;
	uint8_t uart;
	
	ANSELD = 0x0000;	// all analog inputs of port D as digital buffer
	TRISDbits.TRISD11 = 0;		// LED pin as output
	LED = 1;
	
	
	i = setSystemClock(60000000);
	
	ANSELB = 0x00C7;	// port B as digital buffer, but RB7-6 and RB2-0
	ANSELD = 0x0000;	// all analog inputs of port D as digital buffer
	ANSELG = 0x0000;	// all analog inputs of port G as digital buffer
	// Unlock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 0;
		
		// UART1 pins
		RPOR4bits.RP80R = 0b00001; // TX ==> RP80 AnP1
		RPINR18bits.U1RXR = 81; // RX ==> RP81 AnP2
		
	// Lock configuration pin
	OSCCONL = 0x46; OSCCONL = 0x57; OSCCONbits.IOLOCK = 1;
	
	// uart init
	uart = uart_getFreeDevice();
	uart_setBaudSpeed(uart, 115200);
	uart_setBitConfig(uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uart);
	
	while(1)
	{
		for(j=0;j<50;j++) for(i=0;i<65000;i++);
		LED = 0;
		uart_putc(uart, 'A');
		for(j=0;j<10;j++) for(i=0;i<65000;i++);
		LED = 1;
		uart_putc(uart, 'B');
	}
	
	return 0;
}
