/**
 * @file adc_dspic33_sar12.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2020
 *
 * @date December 13, 2018, 09:26 AM
 *
 * @brief ADC driver support for dsPIC33E GS, dsPIC33CK and dsPIC33CH
 *
 * Implementation based on Microchip document DS70005213F :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005213f.pdf
 */

#include "adc_dspic33_sar12.h"

#include <archi.h>
#include <stdint.h>

void adc_calib()
{
    ADCON5Hbits.WARMTIME = 15;          // Set initialization time to maximum

    ADCON1Lbits.ADON = 1;               // Turn on ADC module

#ifdef ADC_HAVE_DEDICATED_CORE0
    ADCON5Lbits.C0PWR = 1;              // Turn on analog power for dedicated core 0
    while (ADCON5Lbits.C0RDY == 0);     // Wait when the core 0 is ready for operation
    ADCON3Hbits.C0EN = 1;               // Turn on digital power to enable triggers to the core 0
#endif
#ifdef ADC_HAVE_DEDICATED_CORE1
    ADCON5Lbits.C1PWR = 1;              // Turn on analog power for dedicated core 1
    while (ADCON5Lbits.C1RDY == 0);     // Wait when the core 1 is ready for operation
    ADCON3Hbits.C1EN = 1;               // Turn on digital power to enable triggers to the core 1
#endif
#ifdef ADC_HAVE_DEDICATED_CORE2
    ADCON5Lbits.C2PWR = 1;              // Turn on analog power for dedicated core 1
    while (ADCON5Lbits.C2RDY == 0);     // Wait when the core 1 is ready for operation
    ADCON3Hbits.C2EN = 1;               // Turn on digital power to enable triggers to the core 1
#endif
#ifdef ADC_HAVE_DEDICATED_CORE3
    ADCON5Lbits.C3PWR = 1;              // Turn on analog power for dedicated core 1
    while (ADCON5Lbits.C3RDY == 0);     // Wait when the core 1 is ready for operation
    ADCON3Hbits.C3EN = 1;               // Turn on digital power to enable triggers to the core 1
#endif

    ADCON5Lbits.SHRPWR = 1;             // Turn on analog power for shared core
#ifndef __MPLAB_DEBUGGER_SIMULATOR
    while (ADCON5Lbits.SHRRDY == 0);    // Wait when the shared core is ready for operation
#endif
    ADCON3Hbits.SHREN = 1;              // Turn on digital power to enable triggers to the shared core

#ifdef ADC_HAVE_AUTOCALIB
  #ifdef ADC_HAVE_DEDICATED_CORE0
    ADCAL0Lbits.CAL0EN = 1;             // Enable calibration for the dedicated core 0
    ADCAL0Lbits.CAL0DIFF = 0;           // Single-ended input calibration
    ADCAL0Lbits.CAL0RUN = 1;            // Start calibration
    while (ADCAL0Lbits.CAL0RDY == 0);   // Poll for the calibration end
    ADCAL0Lbits.CAL0DIFF = 1;           // Differential input calibration
    ADCAL0Lbits.CAL0RUN = 1;            // Start calibration
    while (ADCAL0Lbits.CAL0RDY == 0);   // Poll for the calibration end
    ADCAL0Lbits.CAL0EN = 0;             // End the core 0 calibration
  #endif

  #ifdef ADC_HAVE_DEDICATED_CORE1
    ADCAL0Lbits.CAL1EN = 1;             // Enable calibration for the dedicated core 1
    ADCAL0Lbits.CAL1DIFF = 0;           // Single-ended input calibration
    ADCAL0Lbits.CAL1RUN = 1;            // Start calibration
    while (ADCAL0Lbits.CAL1RDY == 0);   // Poll for the calibration end
    ADCAL0Lbits.CAL1DIFF = 1;           // Differential input calibration
    ADCAL0Lbits.CAL1RUN = 1;            // Start calibration
    while (ADCAL0Lbits.CAL1RDY == 0);   // Poll for the calibration end
    ADCAL0Lbits.CAL1EN = 0;             // End the core 1 calibration
  #endif

  #ifdef ADC_HAVE_DEDICATED_CORE2
    ADCAL0Hbits.CAL2EN = 1;             // Enable calibration for the dedicated core 2
    ADCAL0Hbits.CAL2DIFF = 0;           // Single-ended input calibration
    ADCAL0Hbits.CAL2RUN = 1;            // Start calibration
    while (ADCAL0Hbits.CAL2RDY == 0);   // Poll for the calibration end
    ADCAL0Hbits.CAL2DIFF = 1;           // Differential input calibration
    ADCAL0Hbits.CAL2RUN = 1;            // Start calibration
    while (ADCAL0Hbits.CAL2RDY == 0);   // Poll for the calibration end
    ADCAL0Hbits.CAL2EN = 0;             // End the core 2 calibration
  #endif

  #ifdef ADC_HAVE_DEDICATED_CORE3
    ADCAL0Hbits.CAL3EN = 1;             // Enable calibration for the dedicated core 3
    ADCAL0Hbits.CAL3DIFF = 0;           // Single-ended input calibration
    ADCAL0Hbits.CAL3RUN = 1;            // Start calibration
    while (ADCAL0Hbits.CAL3RDY == 0);   // Poll for the calibration end
    ADCAL0Hbits.CAL3DIFF = 1;           // Differential input calibration
    ADCAL0Hbits.CAL3RUN = 1;            // Start calibration
    while (ADCAL0Hbits.CAL3RDY == 0);   // Poll for the calibration end
    ADCAL0Hbits.CAL3EN = 0;             // End the core 3 calibration
  #endif

    ADCAL1Hbits.CSHREN = 1;             // Enable calibration for the shared core
    ADCAL1Hbits.CSHRDIFF = 0;           // Single-ended input calibration
    ADCAL1Hbits.CSHRRUN = 1;            // Start calibration
    while (ADCAL1Hbits.CSHRRDY == 0);   // Poll for the calibration end
    ADCAL1Hbits.CSHRDIFF = 1;           // Differential input calibration
    ADCAL1Hbits.CSHRRUN = 1;            // Start calibration
    while (ADCAL1Hbits.CSHRRDY == 0);   // Poll for the calibration end
    ADCAL1Hbits.CSHREN = 0;             // End the shared core calibration
#endif
}

int adc_init()
{
    #ifdef _ADC1MD
    _ADC1MD = 0;
    nop();
    #endif

    // Configure the common ADC clock.
    //ADCON3Hbits.CLKSEL = 0;     // clock from Fp oscillator
    ADCON3Hbits.CLKSEL = 0b11;    // clock from FVCO/4 oscillator
    ADCON3Hbits.CLKDIV = 3;       // no clock divider (1:4)

    // Configure the cores’ ADC clock.
#ifdef ADC_HAVE_DEDICATED_CORE0
    ADCORE0Hbits.ADCS = 1;      // clock divider (1:2)
    ADCORE0Hbits.RES = 0b11;    // 12 bits
    ADCORE0Lbits.SAMC = 11;     // 12 Tad
#endif
#ifdef ADC_HAVE_DEDICATED_CORE1
    ADCORE1Hbits.ADCS = 1;      // clock divider (1:2)
    ADCORE1Hbits.RES = 0b11;    // 12 bits
    ADCORE1Lbits.SAMC = 11;     // 12 Tad
#endif
#ifdef ADC_HAVE_DEDICATED_CORE2
    ADCORE2Hbits.ADCS = 1;      // clock divider (1:2)
    ADCORE2Hbits.RES = 0b11;    // 12 bits
    ADCORE2Lbits.SAMC = 11;     // 12 Tad
#endif
#ifdef ADC_HAVE_DEDICATED_CORE3
    ADCORE3Hbits.ADCS = 1;      // clock divider (1:2)
    ADCORE3Hbits.RES = 0b11;    // 12 bits
    ADCORE3Lbits.SAMC = 11;     // 12 Tad
#endif

    // Configure the ADC reference sources.
    ADCON3Lbits.REFSEL = 0;     // AVdd as voltage reference
    // Configure the integer of fractional output format.
    ADCON1Hbits.FORM = 0;       // integer format

    ADCON2Lbits.SHRADCS = 1;    // clock divider (1:2)
    ADCON2Hbits.SHRSAMC = 11;   // 12 Tad
    //ADCON1Lbits.NRE = 1; // Noise Reduction Enable bit, Holds conversion process for 1 T ADCORE when another core completes conversion to reduce noise between cores

    adc_calib();

    return 0;
}

int16_t adc_value(uint8_t channel)
{
    if (channel >= ADC_CHANNEL_COUNT)
    {
        return -1;
    }
    return *(&ADCBUF0 + channel);       // Read the ADC conversion result
}

int16_t adc_getValue(uint8_t channel)
{
    uint16_t bitMask;
    if (channel >= ADC_CHANNEL_COUNT)
    {
        return -1;
    }
    ADCON3Lbits.CNVCHSEL = channel;     // select channel to convert
    ADCON3Lbits.CNVRTCH = 1;            // Start sampling

    if (channel < 16)
    {
        bitMask = (0x0001 << channel);
        while ((ADSTATL & bitMask) == 0);
    }
    else
    {
        bitMask = (0x0001 << (channel - 16));
        while ((ADSTATH & bitMask) == 0);
    }

    return *(&ADCBUF0 + channel);       // Read the ADC conversion result
}
