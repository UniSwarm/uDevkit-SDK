/**
 * @file adc_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 19, 2016, 10:56 AM 
 * 
 * @brief ADC driver support
 */

#include "adc_dspic.h"

int adc_init()
{
	AD1CON1 = 0;
	AD1CON1bits.ASAM = 0;		// Manual sample
	AD1CON1bits.SIMSAM = 0;		// Simultaneous sample
	AD1CON1bits.FORM = 0b00;	// Output format (Integer)
	AD1CON1bits.AD12B = 0;		// 10 bits operation
	AD1CON1bits.SSRCG = 0;		// Normal group
	AD1CON1bits.SSRC = 0b111;	// Auto convert
	
	AD1CON2 = 0x0000;			// Scan mode register and DMA mode
	
	AD1CON3bits.ADRC = 0;		// Clock from periph clock
	AD1CON3bits.ADCS = 32;		// Conversion time tAD in number of tCY (max 255) +1
	AD1CON3bits.SAMC = 8;		// Auto sample time tS in number of tCY (max 31)  +1
	
	AD1CON4 = 0x0000;			// DMA allocation
	
	AD1CHS123 = 0x0000;			
	AD1CSSH = 0x0000;
	AD1CSSL = 0x0000;
	AD1CON1bits.ADON = 1;
	
	return 0;
}

uint16_t adc_getValue(uint8_t channel)
{
	AD1CHS0 = channel;			// select channel to convert
	AD1CON1bits.SAMP = 1;		// Start sampling
	while (!AD1CON1bits.DONE);	// Wait for the conversion to complete
	AD1CON1bits.DONE = 0;		// Clear conversion done status bit
	return ADC1BUF0;			// Read the ADC conversion result
}
