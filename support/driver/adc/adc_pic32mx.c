/**
 * @file adc_pic32mx.c
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2023
 *
 * @date May 15, 2023, 07:06 PM
 *
 * @brief ADC driver support for PIC32MX
 *
 * Implementation based on Microchip document DS60001156K :
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU32/ProductDocuments/DataSheets/PIC32MX5XX6XX7XX_Family%29Datasheet_DS60001156K.pdf
 */

#include "adc.h"

#include <archi.h>

int adc_init(void)
{
    // Clock from peripheral clock TPB
    AD1CON3bits.ADRC = 0;
    // ADC clock TAD = 8 peripheral clock TPB
    AD1CON3bits.ADCS = 8;
    // Set sample time to 15 TAD
    AD1CON3bits.SAMC = 15;
    // Set auto conversion trigger
    AD1CON1bits.SSRC = 0b111;

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
        return 0;
    }

    AD1CHSbits.CH0SA = channel;

    // Start sampling
    AD1CON1bits.SAMP = 1;

    // Wait for the result
    while (AD1CON1bits.DONE == 0)
    {
        nop();
    }

    // Get ADC value
    return ADC1BUF0;
}