/**
 * @file adc_pic32mm.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 2, 2023, 05:24 PM
 *
 * @brief ADC driver support for PIC32MM GPL/GPM
 *
 * Implementation based on Microchip document DS60001344B :
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/60001359b.pdf
 */

#include "adc.h"

#include <archi.h>

int adc_init(void)
{
    // Select RB12/AN7 input
    AD1CHSbits.CH0SA = 7;

    // Clock from peripheral clock TPB
    AD1CON3bits.ADRC = 0;
    // ADC clock TAD = 8 peripheral clock TPB
    AD1CON3bits.ADCS = 8;
    // Set sample time to 5 TAD
    AD1CON3bits.SAMC = 5;
    // Set auto conversion trigger
    AD1CON1bits.SSRC = 7;
    // Turn on the ADC
    AD1CON1bits.ON = 1;

    return 0;
}

int16_t adc_value(uint8_t channel)
{
    return 0;
}

int16_t adc_getValue(uint8_t channel)
{
    if (channel > ADC_CHANNEL_MAX)
    {
        return -1;
    }

    // Reset ADC interrupt flag
    _AD1IF = 0;
    // Start sampling and after 5 TAD go to conversion
    AD1CON1bits.SAMP = 1;
    // Wait for the result
    while (_AD1IF == 0)
    {
        ;
    }
    // Get ADC value
    return ADC1BUF0;
}
