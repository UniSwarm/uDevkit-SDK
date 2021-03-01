/**
 * @file adc_dspic33_sar12.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2021
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
#include <stdlib.h>

void adc_calib(void);

#ifdef ADC_HAVE_CH0
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN0Interrupt(void);
#endif
#ifdef ADC_HAVE_CH1
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN1Interrupt(void);
#endif
#ifdef ADC_HAVE_CH2
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN2Interrupt(void);
#endif
#ifdef ADC_HAVE_CH3
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN3Interrupt(void);
#endif
#ifdef ADC_HAVE_CH4
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN4Interrupt(void);
#endif
#ifdef ADC_HAVE_CH5
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN5Interrupt(void);
#endif
#ifdef ADC_HAVE_CH6
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN6Interrupt(void);
#endif
#ifdef ADC_HAVE_CH7
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN7Interrupt(void);
#endif
#ifdef ADC_HAVE_CH8
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN8Interrupt(void);
#endif
#ifdef ADC_HAVE_CH9
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN9Interrupt(void);
#endif
#ifdef ADC_HAVE_CH10
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN10Interrupt(void);
#endif
#ifdef ADC_HAVE_CH11
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN11Interrupt(void);
#endif
#ifdef ADC_HAVE_CH12
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN12Interrupt(void);
#endif
#ifdef ADC_HAVE_CH13
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN13Interrupt(void);
#endif
#ifdef ADC_HAVE_CH14
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN14Interrupt(void);
#endif
#ifdef ADC_HAVE_CH15
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN15Interrupt(void);
#endif
#ifdef ADC_HAVE_CH16
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN16Interrupt(void);
#endif
#ifdef ADC_HAVE_CH17
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN17Interrupt(void);
#endif
#ifdef ADC_HAVE_CH18
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN18Interrupt(void);
#endif
#ifdef ADC_HAVE_CH19
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN19Interrupt(void);
#endif
#ifdef ADC_HAVE_CH20
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN20Interrupt(void);
#endif
#ifdef ADC_HAVE_CH21
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN21Interrupt(void);
#endif
#ifdef ADC_HAVE_CH22
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN22Interrupt(void);
#endif
#ifdef ADC_HAVE_CH23
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN23Interrupt(void);
#endif
#ifdef ADC_HAVE_CH24
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN24Interrupt(void);
#endif
#ifdef ADC_HAVE_CH25
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN25Interrupt(void);
#endif

struct adc_dev
{
    void (*handler)(int16_t);
};

struct adc_dev adcs[] = {
#if ADC_CHANNEL_MAX >= 1
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 2
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 3
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 4
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 5
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 6
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 7
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 8
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 9
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 10
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 11
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 12
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 13
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 14
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 15
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 16
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 17
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 18
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 19
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 20
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 21
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 22
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 23
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 24
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 25
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 26
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 27
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 28
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 29
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 30
    {
        .handler = NULL,
    },
#endif
#if ADC_CHANNEL_MAX >= 31
    {
        .handler = NULL,
    },
#endif
};

void adc_calib(void)
{
    ADCON5Hbits.WARMTIME = 15;  // Set initialization time to maximum

    ADCON1Lbits.ADON = 1;  // Turn on ADC module

#ifdef ADC_HAVE_DEDICATED_CORE0
    ADCON5Lbits.C0PWR = 1;  // Turn on analog power for dedicated core 0
    while (ADCON5Lbits.C0RDY == 0)
        ;                  // Wait when the core 0 is ready for operation
    ADCON3Hbits.C0EN = 1;  // Turn on digital power to enable triggers to the core 0
#endif
#ifdef ADC_HAVE_DEDICATED_CORE1
    ADCON5Lbits.C1PWR = 1;  // Turn on analog power for dedicated core 1
    while (ADCON5Lbits.C1RDY == 0)
        ;                  // Wait when the core 1 is ready for operation
    ADCON3Hbits.C1EN = 1;  // Turn on digital power to enable triggers to the core 1
#endif
#ifdef ADC_HAVE_DEDICATED_CORE2
    ADCON5Lbits.C2PWR = 1;  // Turn on analog power for dedicated core 1
    while (ADCON5Lbits.C2RDY == 0)
        ;                  // Wait when the core 1 is ready for operation
    ADCON3Hbits.C2EN = 1;  // Turn on digital power to enable triggers to the core 1
#endif
#ifdef ADC_HAVE_DEDICATED_CORE3
    ADCON5Lbits.C3PWR = 1;  // Turn on analog power for dedicated core 1
    while (ADCON5Lbits.C3RDY == 0)
        ;                  // Wait when the core 1 is ready for operation
    ADCON3Hbits.C3EN = 1;  // Turn on digital power to enable triggers to the core 1
#endif

    ADCON5Lbits.SHRPWR = 1;  // Turn on analog power for shared core
#ifndef __MPLAB_DEBUGGER_SIMULATOR
    while (ADCON5Lbits.SHRRDY == 0)
        ;  // Wait when the shared core is ready for operation
#endif
    ADCON3Hbits.SHREN = 1;  // Turn on digital power to enable triggers to the shared core

#ifdef ADC_HAVE_AUTOCALIB
#    ifdef ADC_HAVE_DEDICATED_CORE0
    ADCAL0Lbits.CAL0EN = 1;    // Enable calibration for the dedicated core 0
    ADCAL0Lbits.CAL0DIFF = 0;  // Single-ended input calibration
    ADCAL0Lbits.CAL0RUN = 1;   // Start calibration
    while (ADCAL0Lbits.CAL0RDY == 0)
        ;                      // Poll for the calibration end
    ADCAL0Lbits.CAL0DIFF = 1;  // Differential input calibration
    ADCAL0Lbits.CAL0RUN = 1;   // Start calibration
    while (ADCAL0Lbits.CAL0RDY == 0)
        ;                    // Poll for the calibration end
    ADCAL0Lbits.CAL0EN = 0;  // End the core 0 calibration
#    endif

#    ifdef ADC_HAVE_DEDICATED_CORE1
    ADCAL0Lbits.CAL1EN = 1;    // Enable calibration for the dedicated core 1
    ADCAL0Lbits.CAL1DIFF = 0;  // Single-ended input calibration
    ADCAL0Lbits.CAL1RUN = 1;   // Start calibration
    while (ADCAL0Lbits.CAL1RDY == 0)
        ;                      // Poll for the calibration end
    ADCAL0Lbits.CAL1DIFF = 1;  // Differential input calibration
    ADCAL0Lbits.CAL1RUN = 1;   // Start calibration
    while (ADCAL0Lbits.CAL1RDY == 0)
        ;                    // Poll for the calibration end
    ADCAL0Lbits.CAL1EN = 0;  // End the core 1 calibration
#    endif

#    ifdef ADC_HAVE_DEDICATED_CORE2
    ADCAL0Hbits.CAL2EN = 1;    // Enable calibration for the dedicated core 2
    ADCAL0Hbits.CAL2DIFF = 0;  // Single-ended input calibration
    ADCAL0Hbits.CAL2RUN = 1;   // Start calibration
    while (ADCAL0Hbits.CAL2RDY == 0)
        ;                      // Poll for the calibration end
    ADCAL0Hbits.CAL2DIFF = 1;  // Differential input calibration
    ADCAL0Hbits.CAL2RUN = 1;   // Start calibration
    while (ADCAL0Hbits.CAL2RDY == 0)
        ;                    // Poll for the calibration end
    ADCAL0Hbits.CAL2EN = 0;  // End the core 2 calibration
#    endif

#    ifdef ADC_HAVE_DEDICATED_CORE3
    ADCAL0Hbits.CAL3EN = 1;    // Enable calibration for the dedicated core 3
    ADCAL0Hbits.CAL3DIFF = 0;  // Single-ended input calibration
    ADCAL0Hbits.CAL3RUN = 1;   // Start calibration
    while (ADCAL0Hbits.CAL3RDY == 0)
        ;                      // Poll for the calibration end
    ADCAL0Hbits.CAL3DIFF = 1;  // Differential input calibration
    ADCAL0Hbits.CAL3RUN = 1;   // Start calibration
    while (ADCAL0Hbits.CAL3RDY == 0)
        ;                    // Poll for the calibration end
    ADCAL0Hbits.CAL3EN = 0;  // End the core 3 calibration
#    endif

    ADCAL1Hbits.CSHREN = 1;    // Enable calibration for the shared core
    ADCAL1Hbits.CSHRDIFF = 0;  // Single-ended input calibration
    ADCAL1Hbits.CSHRRUN = 1;   // Start calibration
    while (ADCAL1Hbits.CSHRRDY == 0)
        ;                      // Poll for the calibration end
    ADCAL1Hbits.CSHRDIFF = 1;  // Differential input calibration
    ADCAL1Hbits.CSHRRUN = 1;   // Start calibration
    while (ADCAL1Hbits.CSHRRDY == 0)
        ;                    // Poll for the calibration end
    ADCAL1Hbits.CSHREN = 0;  // End the shared core calibration
#endif
}

int adc_init(void)
{
#ifdef _ADC1MD
    _ADC1MD = 0;
    nop();
#endif

    // Configure the common ADC clock.
    // ADCON3Hbits.CLKSEL = 0b01;     // clock from Fp oscillator
    ADCON3Hbits.CLKSEL = 0b00;   // clock from FP (FOSC /2)
    ADCON3Hbits.CLKDIV = 1 - 1;  // 1/1 divider (1:1)

    // Configure the cores’ ADC clock.
#ifdef ADC_HAVE_DEDICATED_CORE0
    ADCORE0Hbits.ADCS = 2 - 1;  // clock divider (1:2)
    ADCORE0Hbits.RES = 0b11;    // 12 bits
    ADCORE0Lbits.SAMC = 0;      // 12 Tad delay before sampling
#endif
#ifdef ADC_HAVE_DEDICATED_CORE1
    ADCORE1Hbits.ADCS = 2 - 1;  // clock divider (1:2)
    ADCORE1Hbits.RES = 0b11;    // 12 bits
    ADCORE1Lbits.SAMC = 0;      // 12 Tad
#endif
#ifdef ADC_HAVE_DEDICATED_CORE2
    ADCORE2Hbits.ADCS = 2 - 1;  // clock divider (1:2)
    ADCORE2Hbits.RES = 0b11;    // 12 bits
    ADCORE2Lbits.SAMC = 0;      // 12 Tad
#endif
#ifdef ADC_HAVE_DEDICATED_CORE3
    ADCORE3Hbits.ADCS = 2 - 1;  // clock divider (1:2)
    ADCORE3Hbits.RES = 0b11;    // 12 bits
    ADCORE3Lbits.SAMC = 0;      // 12 Tad
#endif

    // Configure the ADC reference sources.
    ADCON3Lbits.REFSEL = 0;  // AVdd as voltage reference
    // Configure the integer of fractional output format.
    ADCON1Hbits.FORM = 0;  // integer format

    ADCON2Lbits.SHRADCS = 0b0000001;  // clock divider (1:2)
    ADCON1Hbits.SHRRES = 0b11;        // 12 bits
    ADCON2Hbits.SHRSAMC = 16 - 1;     // 16 Tad
    // ADCON1Lbits.NRE = 1; // Noise Reduction Enable bit, Holds conversion process for 1 T ADCORE when another core
    // completes conversion to reduce noise between cores

    adc_calib();

    return 0;
}

int16_t adc_value(uint8_t channel)
{
    if (channel >= ADC_CHANNEL_MAX)
    {
        return -1;
    }
    return *(&ADCBUF0 + channel);  // Read the ADC conversion result
}

int16_t adc_getValue(uint8_t channel)
{
    uint16_t bitMask;
    if (channel >= ADC_CHANNEL_MAX)
    {
        return -1;
    }
    ADCON3Lbits.CNVCHSEL = channel;  // select channel to convert
    ADCON3Lbits.CNVRTCH = 1;         // Start sampling

    if (channel < 16)
    {
        bitMask = (0x0001 << channel);
        while ((ADSTATL & bitMask) == 0)
            ;
    }
    else
    {
        bitMask = (0x0001 << (channel - 16));
        while ((ADSTATH & bitMask) == 0)
            ;
    }

    return *(&ADCBUF0 + channel);  // Read the ADC conversion result
}

int adc_setHandler(uint8_t channel, void (*handler)(int16_t))
{
    if (channel >= ADC_CHANNEL_MAX)
    {
        return -1;
    }
    adcs[channel].handler = handler;

    switch (channel)
    {
#ifdef ADC_HAVE_CH0
        case 0:
            _ADCAN0IF = 0;
            _ADCAN0IE = (handler != 0);
            _IE0 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH1
        case 1:
            _ADCAN1IF = 0;
            _ADCAN1IE = (handler != 0);
            _IE1 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH2
        case 2:
            _ADCAN2IF = 0;
            _ADCAN2IE = (handler != 0);
            _IE2 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH3
        case 3:
            _ADCAN3IF = 0;
            _ADCAN3IE = (handler != 0);
            _IE3 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH4
        case 4:
            _ADCAN4IF = 0;
            _ADCAN4IE = (handler != 0);
            _IE4 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH5
        case 5:
            _ADCAN5IF = 0;
            _ADCAN5IE = (handler != 0);
            _IE5 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH6
        case 6:
            _ADCAN6IF = 0;
            _ADCAN6IE = (handler != 0);
            _IE6 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH7
        case 7:
            _ADCAN7IF = 0;
            _ADCAN7IE = (handler != 0);
            _IE7 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH8
        case 8:
            _ADCAN8IF = 0;
            _ADCAN8IE = (handler != 0);
            _IE8 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH9
        case 9:
            _ADCAN9IF = 0;
            _ADCAN9IE = (handler != 0);
            _IE9 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH10
        case 10:
            _ADCAN10IF = 0;
            _ADCAN10IE = (handler != 0);
            _IE10 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH11
        case 11:
            _ADCAN11IF = 0;
            _ADCAN11IE = (handler != 0);
            _IE11 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH12
        case 12:
            _ADCAN12IF = 0;
            _ADCAN12IE = (handler != 0);
            _IE12 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH13
        case 13:
            _ADCAN13IF = 0;
            _ADCAN13IE = (handler != 0);
            _IE13 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH14
        case 14:
            _ADCAN14IF = 0;
            _ADCAN14IE = (handler != 0);
            _IE14 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH15
        case 15:
            _ADCAN15IF = 0;
            _ADCAN15IE = (handler != 0);
            _IE15 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH16
        case 16:
            _ADCAN16IF = 0;
            _ADCAN16IE = (handler != 0);
            _IE16 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH17
        case 17:
            _ADCAN17IF = 0;
            _ADCAN17IE = (handler != 0);
            _IE17 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH18
        case 18:
            _ADCAN18IF = 0;
            _ADCAN18IE = (handler != 0);
            _IE18 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH19
        case 19:
            _ADCAN19IF = 0;
            _ADCAN19IE = (handler != 0);
            _IE19 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH20
        case 20:
            _ADCAN20IF = 0;
            _ADCAN20IE = (handler != 0);
            _IE20 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH21
        case 21:
            _ADCAN21IF = 0;
            _ADCAN21IE = (handler != 0);
            _IE21 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH22
        case 22:
            _ADCAN22IF = 0;
            _ADCAN22IE = (handler != 0);
            _IE22 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH23
        case 23:
            _ADCAN23IF = 0;
            _ADCAN23IE = (handler != 0);
            _IE23 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH24
        case 24:
            _ADCAN24IF = 0;
            _ADCAN24IE = (handler != 0);
            _IE24 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH25
        case 25:
            _ADCAN25IF = 0;
            _ADCAN25IE = (handler != 0);
            _IE25 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH26
        case 26:
            _ADCAN26IF = 0;
            _ADCAN26IE = (handler != 0);
            _IE26 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH27
        case 27:
            _ADCAN27IF = 0;
            _ADCAN27IE = (handler != 0);
            _IE27 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH28
        case 28:
            _ADCAN28IF = 0;
            _ADCAN28IE = (handler != 0);
            _IE28 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH29
        case 29:
            _ADCAN29IF = 0;
            _ADCAN29IE = (handler != 0);
            _IE29 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH30
        case 30:
            _ADCAN30IF = 0;
            _ADCAN30IE = (handler != 0);
            _IE30 = 1;
            break;
#endif
#ifdef ADC_HAVE_CH31
        case 31:
            _ADCAN31IF = 0;
            _ADCAN31IE = (handler != 0);
            _IE31 = 1;
            break;
#endif
    }
    return 0;
}

#ifdef ADC_HAVE_CH0
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN0Interrupt(void)
{
    if (adcs[0].handler)
    {
        (*adcs[0].handler)(ADCBUF0);
    }
    _ADCAN0IF = 0;
}
#endif

#ifdef ADC_HAVE_CH1
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN1Interrupt(void)
{
    if (adcs[1].handler)
    {
        (*adcs[1].handler)(ADCBUF1);
    }
    _ADCAN1IF = 0;
}
#endif

#ifdef ADC_HAVE_CH2
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN2Interrupt(void)
{
    if (adcs[2].handler)
    {
        (*adcs[2].handler)(ADCBUF2);
    }
    _ADCAN2IF = 0;
}
#endif

#ifdef ADC_HAVE_CH3
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN3Interrupt(void)
{
    if (adcs[3].handler)
    {
        (*adcs[3].handler)(ADCBUF3);
    }
    _ADCAN3IF = 0;
}
#endif

#ifdef ADC_HAVE_CH4
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN4Interrupt(void)
{
    if (adcs[4].handler)
    {
        (*adcs[4].handler)(ADCBUF4);
    }
    _ADCAN4IF = 0;
}
#endif

#ifdef ADC_HAVE_CH5
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN5Interrupt(void)
{
    if (adcs[5].handler)
    {
        (*adcs[5].handler)(ADCBUF5);
    }
    _ADCAN5IF = 0;
}
#endif

#ifdef ADC_HAVE_CH6
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN6Interrupt(void)
{
    if (adcs[6].handler)
    {
        (*adcs[6].handler)(ADCBUF6);
    }
    _ADCAN6IF = 0;
}
#endif

#ifdef ADC_HAVE_CH7
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN7Interrupt(void)
{
    if (adcs[7].handler)
    {
        (*adcs[7].handler)(ADCBUF7);
    }
    _ADCAN7IF = 0;
}
#endif

#ifdef ADC_HAVE_CH8
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN8Interrupt(void)
{
    if (adcs[8].handler)
    {
        (*adcs[8].handler)(ADCBUF8);
    }
    _ADCAN8IF = 0;
}
#endif

#ifdef ADC_HAVE_CH9
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN9Interrupt(void)
{
    if (adcs[9].handler)
    {
        (*adcs[9].handler)(ADCBUF9);
    }
    _ADCAN9IF = 0;
}
#endif

#ifdef ADC_HAVE_CH10
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN10Interrupt(void)
{
    if (adcs[10].handler)
    {
        (*adcs[10].handler)(ADCBUF10);
    }
    _ADCAN10IF = 0;
}
#endif

#ifdef ADC_HAVE_CH11
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN11Interrupt(void)
{
    if (adcs[11].handler)
    {
        (*adcs[11].handler)(ADCBUF11);
    }
    _ADCAN11IF = 0;
}
#endif

#ifdef ADC_HAVE_CH12
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN12Interrupt(void)
{
    if (adcs[12].handler)
    {
        (*adcs[12].handler)(ADCBUF12);
    }
    _ADCAN12IF = 0;
}
#endif

#ifdef ADC_HAVE_CH13
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN13Interrupt(void)
{
    if (adcs[13].handler)
    {
        (*adcs[13].handler)(ADCBUF13);
    }
    _ADCAN13IF = 0;
}
#endif

#ifdef ADC_HAVE_CH14
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN14Interrupt(void)
{
    if (adcs[14].handler)
    {
        (*adcs[14].handler)(ADCBUF14);
    }
    _ADCAN14IF = 0;
}
#endif

#ifdef ADC_HAVE_CH15
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN15Interrupt(void)
{
    if (adcs[15].handler)
    {
        (*adcs[15].handler)(ADCBUF15);
    }
    _ADCAN15IF = 0;
}
#endif

#ifdef ADC_HAVE_CH16
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN16Interrupt(void)
{
    if (adcs[16].handler)
    {
        (*adcs[16].handler)(ADCBUF16);
    }
    _ADCAN16IF = 0;
}
#endif

#ifdef ADC_HAVE_CH17
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN17Interrupt(void)
{
    if (adcs[17].handler)
    {
        (*adcs[17].handler)(ADCBUF17);
    }
    _ADCAN17IF = 0;
}
#endif

#ifdef ADC_HAVE_CH18
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN18Interrupt(void)
{
    if (adcs[18].handler)
    {
        (*adcs[18].handler)(ADCBUF18);
    }
    _ADCAN18IF = 0;
}
#endif

#ifdef ADC_HAVE_CH19
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN19Interrupt(void)
{
    if (adcs[19].handler)
    {
        (*adcs[19].handler)(ADCBUF19);
    }
    _ADCAN19IF = 0;
}
#endif

#ifdef ADC_HAVE_CH20
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN20Interrupt(void)
{
    if (adcs[20].handler)
    {
        (*adcs[20].handler)(ADCBUF20);
    }
    _ADCAN20IF = 0;
}
#endif

#ifdef ADC_HAVE_CH21
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN21Interrupt(void)
{
    if (adcs[21].handler)
    {
        (*adcs[21].handler)(ADCBUF21);
    }
    _ADCAN21IF = 0;
}
#endif

#ifdef ADC_HAVE_CH22
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN22Interrupt(void)
{
    if (adcs[22].handler)
    {
        (*adcs[22].handler)(ADCBUF22);
    }
    _ADCAN22IF = 0;
}
#endif

#ifdef ADC_HAVE_CH23
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN23Interrupt(void)
{
    if (adcs[23].handler)
    {
        (*adcs[23].handler)(ADCBUF23);
    }
    _ADCAN23IF = 0;
}
#endif

#ifdef ADC_HAVE_CH24
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN24Interrupt(void)
{
    if (adcs[24].handler)
    {
        (*adcs[24].handler)(ADCBUF24);
    }
    _ADCAN24IF = 0;
}
#endif

#ifdef ADC_HAVE_CH25
void __attribute__((__interrupt__, no_auto_psv)) _ADCAN25Interrupt(void)
{
    if (adcs[25].handler)
    {
        (*adcs[25].handler)(ADCBUF25);
    }
    _ADCAN25IF = 0;
}
#endif
