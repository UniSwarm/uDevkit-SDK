/**
 * @file adc_pic32_sar12.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date May 07, 2017, 10:07 AM
 *
 * @brief ADC driver support for PIC32MZDA and PIC32MZEF
 *
 * Implementation based on Microchip document DS60001344B :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001344B.pdf
 */

#include "adc.h"

#include <archi.h>

static uint8_t _adc_sarFromChannel(uint8_t channel);

int adc_init(void)
{
    // initialize ADC calibration setting
    ADC0CFG = DEVADC0;
    ADC1CFG = DEVADC1;
    ADC2CFG = DEVADC2;
    ADC3CFG = DEVADC3;
    ADC4CFG = DEVADC4;
#ifdef ADC_HAVE_DEDICATED_CORE5
    ADC5CFG = DEVADC5;
#endif  // ADC_HAVE_DEDICATED_CORE5
    // ADC6CFG = DEVADC6;
    ADC7CFG = DEVADC7;

    // Configure ADCCON1
    ADCCON1 = 0;  // No ADCCON1 features are enabled including: Stop-in-Idle, turbo, CVD mode, Fractional mode and scan trigger source.

    // Configure ADCCON2
    ADCCON2 = 0;  // Since, we are using only the Class 1 inputs, no setting is required for ADCDIV

    // Initialize warm up time register
    ADCANCON = 0;
    ADCANCONbits.WKUPCLKCNT = 5;  // Wakeup exponent = 32 * TADx

    // Clock setting
    ADCCON3 = 0;
    ADCCON3bits.ADCSEL = 1;     // Select input clock source (FRC)
    ADCCON3bits.CONCLKDIV = 1;  // Control clock frequency is half of input clock
    ADCCON3bits.VREFSEL = 0;    // Select AVDD and AVSS as reference source

    // Select ADC sample time and conversion clock
    ADC0TIMEbits.ADCDIV = 1;  // ADC0 clock frequency is half of control clock = TAD0
    ADC0TIMEbits.SAMC = 5;    // ADC0 sampling time = 5 * TAD0
    ADC0TIMEbits.SELRES = 3;  // ADC0 resolution is 12 bits
    ADC1TIMEbits.ADCDIV = 1;  // ADC1 clock frequency is half of control clock = TAD1
    ADC1TIMEbits.SAMC = 5;    // ADC1 sampling time = 5 * TAD1
    ADC1TIMEbits.SELRES = 3;  // ADC1 resolution is 12 bits
    ADC2TIMEbits.ADCDIV = 1;  // ADC2 clock frequency is half of control clock = TAD2
    ADC2TIMEbits.SAMC = 5;    // ADC2 sampling time = 5 * TAD2
    ADC2TIMEbits.SELRES = 3;  // ADC2 resolution is 12 bits
    ADC3TIMEbits.ADCDIV = 1;  // ADC3 clock frequency is half of control clock = TAD3
    ADC3TIMEbits.SAMC = 5;    // ADC3 sampling time = 5 * TAD2
    ADC3TIMEbits.SELRES = 3;  // ADC3 resolution is 12 bits
    ADC4TIMEbits.ADCDIV = 1;  // ADC4 clock frequency is half of control clock = TAD4
    ADC4TIMEbits.SAMC = 5;    // ADC4 sampling time = 5 * TAD2
    ADC4TIMEbits.SELRES = 3;  // ADC4 resolution is 12 bits
    ADCCON2bits.ADCDIV = 1;   // ADC7 clock frequency is half of control clock = TAD7
    ADCCON2bits.SAMC = 5;     // ADC7 sampling time = 5 * TAD2
    ADCCON1bits.SELRES = 3;   // ADC7 resolution is 12 bits

    // Select ADC input mode
    ADCIMCON1 = 0;  // unsigned data format - Single ended mode
    ADCIMCON2 = 0;  // unsigned data format - Single ended mode
    ADCIMCON3 = 0;  // unsigned data format - Single ended mode

    // Configure ADCGIRQENx
    ADCGIRQEN1 = 0;  // No interrupts are used
    ADCGIRQEN2 = 0;

    // Configure ADCCSSx
    ADCCSS1 = 0;  // No scanning is used
    ADCCSS2 = 0;

    // Configure ADCCMPCONx
    ADCCMPCON1 = 0;  // No digital comparators are used. Setting the ADCCMPCONx
    ADCCMPCON2 = 0;  // register to '0' ensures that the comparator is disabled.
    ADCCMPCON3 = 0;  // Other registers are “don't care”.
    ADCCMPCON4 = 0;
#ifndef ARCHI_pic32mk
    ADCCMPCON5 = 0;
    ADCCMPCON6 = 0;
#endif

    // Configure ADCFLTRx
    ADCFLTR1 = 0;  // No oversampling filters are used.
    ADCFLTR2 = 0;
    ADCFLTR3 = 0;
    ADCFLTR4 = 0;
#ifndef ARCHI_pic32mk
    ADCFLTR5 = 0;
    ADCFLTR6 = 0;
#endif

    // Set up the trigger sources
    ADCTRGSNS = 0;         // Edge trigger
    ADCTRG1 = 0x01010101;  // Set triggers from software.
    ADCTRG2 = 0x01010101;  // Set triggers from software.
    ADCTRG3 = 0x01010101;  // Set triggers from software.
#ifdef ARCHI_pic32mk
#    if (defined(ADC_CHANNEL_HAVE_CH12) | defined(ADC_CHANNEL_HAVE_CH13) | defined(ADC_CHANNEL_HAVE_CH14) | defined(ADC_CHANNEL_HAVE_CH15))
    ADCTRG4 = 0x01010101;  // Set triggers from software.
#    endif
#    if (defined(ADC_CHANNEL_HAVE_CH16) | defined(ADC_CHANNEL_HAVE_CH17) | defined(ADC_CHANNEL_HAVE_CH18) | defined(ADC_CHANNEL_HAVE_CH19))
    ADCTRG5 = 0x01010101;  // Set triggers from software.
#    endif
#    if (defined(ADC_CHANNEL_HAVE_CH20) | defined(ADC_CHANNEL_HAVE_CH21) | defined(ADC_CHANNEL_HAVE_CH22) | defined(ADC_CHANNEL_HAVE_CH23))
    ADCTRG6 = 0x01010101;  // Set triggers from software.
#    endif
#    if (defined(ADC_CHANNEL_HAVE_CH24) | defined(ADC_CHANNEL_HAVE_CH25) | defined(ADC_CHANNEL_HAVE_CH26) | defined(ADC_CHANNEL_HAVE_CH27))
    ADCTRG7 = 0x01010101;  // Set triggers from software.
#    endif
#endif

    // Early interrupt
    ADCEIEN1 = 0;  // No early interrupt
    ADCEIEN2 = 0;

    // Turn the ADC on
    ADCCON1bits.ON = 1;

    // Wait for voltage reference to be stable
    while (!ADCCON2bits.BGVRRDY)
    {
        ;  // Wait until the reference voltage is ready
    }
    while (ADCCON2bits.REFFLT)
    {
        ;  // Wait if there is a fault with the reference voltage
    }

    // Enable clock to analog circuit
    ADCANCONbits.ANEN0 = 1;  // Enable the clock to analog bias
    ADCANCONbits.ANEN1 = 1;  // Enable the clock to analog bias
    ADCANCONbits.ANEN2 = 1;  // Enable the clock to analog bias
    ADCANCONbits.ANEN3 = 1;  // Enable the clock to analog bias
    ADCANCONbits.ANEN4 = 1;  // Enable the clock to analog bias
#ifdef ADC_HAVE_DEDICATED_CORE5
    ADCANCONbits.ANEN5 = 1;  // Enable the clock to analog bias
#endif                       // ADC_HAVE_DEDICATED_CORE5
    ADCANCONbits.ANEN7 = 1;  // Enable the clock to analog bias

    // Wait for ADC to be ready
    while (!ADCANCONbits.WKRDY0)
    {
        ;  // Wait until ADC0 is ready
    }
    while (!ADCANCONbits.WKRDY1)
    {
        ;  // Wait until ADC1 is ready
    }
#ifdef ADC_HAVE_DEDICATED_CORE2
    while (!ADCANCONbits.WKRDY2)
    {
        ;  // Wait until ADC2 is ready
    }
#endif  // ADC_HAVE_DEDICATED_CORE2
#ifdef ADC_HAVE_DEDICATED_CORE3
    while (!ADCANCONbits.WKRDY3)
    {
        ;  // Wait until ADC3 is ready
    }
#endif  // ADC_HAVE_DEDICATED_CORE3
#ifdef ADC_HAVE_DEDICATED_CORE4
    while (!ADCANCONbits.WKRDY4)
    {
        ;  // Wait until ADC4 is ready
    }
#endif  // ADC_HAVE_DEDICATED_CORE4
#ifdef ADC_HAVE_DEDICATED_CORE5
    while (!ADCANCONbits.WKRDY5)
    {
        ;  // Wait until ADC5 is ready
    }
#endif  // ADC_HAVE_DEDICATED_CORE5
#ifdef ADC_HAVE_DEDICATED_CORE6
    while (!ADCANCONbits.WKRDY6)
    {
        ;  // Wait until ADC6 is ready
    }
#endif  // ADC_HAVE_DEDICATED_CORE5
    while (!ADCANCONbits.WKRDY7)
    {
        ;  // Wait until ADC7 is ready
    }

    return 0;
}

int adc_setMasterClock(uint8_t source, uint16_t divider)
{
    UDK_UNUSED(source);
    UDK_UNUSED(divider);

    // TODO implement

    return 0;
}

int adc_setCoreClockDivider(uint8_t core, uint16_t divider)
{
    UDK_UNUSED(core);
    UDK_UNUSED(divider);

    // TODO implement

    return 0;
}

int adc_setCoreResolution(uint8_t core, uint16_t resolution)
{
    UDK_UNUSED(core);
    UDK_UNUSED(resolution);

    // TODO implement

    return 0;
}

int adc_setSamplingCycles(uint8_t core, uint16_t cycles)
{
    UDK_UNUSED(core);
    UDK_UNUSED(cycles);

    // TODO implement

    return 0;
}

int adc_startSampling(uint8_t channel)
{
    uint32_t mask;
    uint8_t sar;

    if (channel <= 31)
    {
        mask = 1U << channel;
    }
    else
    {
        mask = 1U << (channel - 32);
    }

    sar = _adc_sarFromChannel(channel);
    switch (sar)
    {
        case 0:
            ADCTRGMODEbits.SH0ALT = 0;  // ADC0 = AN0
            ADCCON3bits.DIGEN0 = 1;     // Enable ADC0
            break;

        case 1:
            ADCTRGMODEbits.SH1ALT = 0;  // ADC1 = AN1
            ADCCON3bits.DIGEN1 = 1;     // Enable ADC1
            break;

        case 2:
            ADCTRGMODEbits.SH2ALT = 0;  // ADC2 = AN2
            ADCCON3bits.DIGEN2 = 1;     // Enable ADC2
            break;

        case 3:
            ADCTRGMODEbits.SH3ALT = 0;  // ADC3 = AN3
            ADCCON3bits.DIGEN3 = 1;     // Enable ADC3
            break;

        case 4:
            ADCTRGMODEbits.SH4ALT = 0;  // ADC4 = AN4
            ADCCON3bits.DIGEN4 = 1;     // Enable ADC4
            break;

#ifdef ADC_HAVE_DEDICATED_CORE5
        case 5:
            ADCTRGMODEbits.SH5ALT = 0;  // ADC5 = AN5
            ADCCON3bits.DIGEN5 = 1;     // Enable ADC5
            break;
#endif  // ADC_HAVE_DEDICATED_CORE5

        case 7:
            if (channel <= 31)
            {
                ADCCSS1 |= mask;
            }
            else
            {
                ADCCSS2 |= mask;
            }
            ADCCON3bits.DIGEN7 = 1;  // Enable ADC7
            break;
    }

    if (adc_setTriggerSource(channel, ADC_TRGSRC_SOFTWARE_EDGE_TRIGGER) < 0)
    {
        return -1;
    }

    // Trigger a conversion
    ADCCON3bits.GSWTRG = 1;
    return 0;
}

int adc_dataReady(uint8_t channel)
{
    uint32_t mask;

    if (channel > ADC_CHANNEL_MAX)
    {
        return -1;
    }

    if (channel <= 31)
    {
        mask = 1U << channel;
        return ((ADCDSTAT1 & mask) == 0) ? 0 : 1;
    }

    mask = 1U << (channel - 32);
    return ((ADCDSTAT2 & mask) == 0) ? 0 : 1;
}

int16_t adc_value(uint8_t channel)
{
    if (channel > ADC_CHANNEL_MAX)
    {
        return 0;
    }
    return (int16_t) * (volatile int32_t *)((&ADCDATA0) + (channel << 2));
}

volatile int32_t *adc_buffAddr(uint8_t channel)
{
    if (channel > ADC_CHANNEL_MAX)
    {
        return NULL;
    }
    return (volatile int32_t *)((&ADCDATA0) + (channel << 2));
}

uint8_t _adc_sarFromChannel(uint8_t channel)
{
#ifdef ADC_HAVE_DEDICATED_CORE5
    if (channel <= 5)
    {
        return channel;
    }
#else
    if (channel <= 4)
    {
        return channel;
    }
#endif  // ADC_HAVE_DEDICATED_CORE5
    if (channel >= 45 && channel <= 49)
    {
        return channel - 45;
    }
    return 7;
}

int16_t adc_getValue(uint8_t channel)
{
    volatile uint32_t *result;
    uint32_t mask;

    ADCCON3 &= 0xFF00FFFF;  // disable all ADC*

    if (channel <= 31)
    {
        mask = 1U << channel;
    }
    else
    {
        mask = 1U << (channel - 32);
    }

    if (adc_startSampling(channel) < 0)
    {
        return 0;
    }

    // Wait the conversions to complete
    if (channel <= 31)
    {
        while ((ADCDSTAT1 & mask) == 0)
        {
            ;
        }
    }
    else
    {
        while ((ADCDSTAT2 & mask) == 0)
        {
            ;
        }
    }

    // return result
    result = &ADCDATA0 + (channel << 2);
    return (int16_t)*result;
}

#define ADCTRG(channel) ((volatile uint8_t *)(&ADCTRG1) + (((uint8_t)(channel)&0xFC) * 4 + ((uint8_t)(channel)&0x03)))
int adc_setTriggerSource(uint8_t channel, uint8_t triggerSource)
{
    if (channel > ADC_CHANNEL_MAX)
    {
        return -1;
    }
    if (channel >= 32)  // no trigger for channel > 32
    {
        return -1;
    }

    (*ADCTRG(channel)) = triggerSource;

    return 0;
}
