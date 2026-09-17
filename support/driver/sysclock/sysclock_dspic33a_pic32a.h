/**
 * @file sysclock_dspic33a_pic32a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025-2026
 *
 * @date May 3, 2025, 10:26 PM
 *
 * @brief System clock support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip documents DS70005539C, DS70005629C, DS70005591D and DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK256MPS306-Family-Data-Sheet-DS70005629.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
 */

#ifndef SYSCLOCK_DSPIC33A_PIC32A_H
#define SYSCLOCK_DSPIC33A_PIC32A_H

#ifdef __cplusplus
extern "C" {
#endif

#define FRC_BASE_FREQ  8000000  //     8 MHz
#define OSCTUN_D       3760     // +/- 0.047%
#define LPRC_BASE_FREQ 32000    //    32 kHz
#define BFRC_BASE_FREQ 8000000  //     8 MHz

#define SYSCLOCK_PREDIV_MIN 1
#define SYSCLOCK_PREDIV_MAX 8
#define SYSCLOCK_FPLLI_MIN  5000000   //    5 MHz
#define SYSCLOCK_FPLLI_MAX  64000000  //   64 MHz

#define SYSCLOCK_FVCO_MIN 500000000   //  500 MHz
#define SYSCLOCK_FVCO_MAX 1600000000  // 1600 MHz

#define SYSCLOCK_POSTDIV1_MIN 1
#define SYSCLOCK_POSTDIV1_MAX 7
#define SYSCLOCK_POSTDIV2_MIN 1
#define SYSCLOCK_POSTDIV2_MAX 7
// POSTDIV1 >= POSTDIV2

#define SYSCLOCK_PLLM_MIN 16
#define SYSCLOCK_PLLM_MAX 320

#define SYSCLOCK_FOSC_MAX 200000000  //  200 MHz
#define SYSCLOCK_FPLL_MAX 800000000  //  800 MHz

#if defined(DEVICE_32AK1216GC41036) || defined(DEVICE_32AK1216GC41048) || defined(DEVICE_32AK1216GC41064) || defined(DEVICE_32AK3208GC41036)                   \
    || defined(DEVICE_32AK3208GC41048) || defined(DEVICE_32AK3208GC41064) || defined(DEVICE_32AK6416GC41036) || defined(DEVICE_32AK6416GC41048)                \
    || defined(DEVICE_32AK6416GC41064) || defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105)                            \
    || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102) || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) \
    || defined(DEVICE_33AK128MC102) || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)

#    define SYSCLOCK_CLKGEN_COUNT 13
#    define SYSCLOCK_CLKGEN_MAX   13

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0,       ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2 = 1,       ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3 = 2,       ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4 = 3,       ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5 = 4,       ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6 = 5,       ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7 = 6,       ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8 = 7,       ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9 = 8,       ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN10 = 9,      ///< CLKGEN10 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN11 = 10,     ///< CLKGEN11 Sources BiSS
    SYSCLOCK_CLOCK_CLKGEN12 = 11,     ///< CLKGEN12 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN13 = 12,     ///< CLKGEN13 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_FAST_PERIPH = 13,  ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH = 14,   ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH = 15,  ///< Slow Speed Peripheral Clock FOSC/4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_FRC = 0b0001,           ///< Internal 8 MHz RC oscillator
    SYSCLOCK_SRC_BFRC = 0b0010,          ///< Internal Backup 8 MHz RC oscillator
    SYSCLOCK_SRC_POSC = 0b0011,          ///< Primary crystal oscillator (4-32 MHz)
    SYSCLOCK_SRC_LPRC = 0b0100,          ///< LPRC as BFRC/244
    SYSCLOCK_SRC_PLL1_FOUT = 0b0101,     ///< PLL1 output
    SYSCLOCK_SRC_PLL2_FOUT = 0b0110,     ///< PLL2 output
    SYSCLOCK_SRC_PLL1_VCO_DIV = 0b0111,  ///< PLL1 VCO DIV output
    SYSCLOCK_SRC_PLL2_VCO_DIV = 0b1000,  ///< PLL2 VCO DIV output
    SYSCLOCK_SRC_REFI1 = 0b1010,         ///< Device REFI1 pin through PPS
    SYSCLOCK_SRC_REFI2 = 0b1001,         ///< Device REFI2 pin through PPS
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_MAX    10

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"", "FRC", "BFRC", "POSC", "LPRC", "PLL1", "PLL2", "VCO1", "VCO2", "", "REFI1", "REFI2"};
#endif

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU   SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C   SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_TIMER SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_PWM   SYSCLOCK_CLOCK_CLKGEN5     ///< PWM clock bus mapped to CLKGEN5
#    define SYSCLOCK_CLOCK_ADC   SYSCLOCK_CLOCK_CLKGEN6     ///< ADC clock bus mapped to CLKGEN6
#    define SYSCLOCK_CLOCK_DAC   SYSCLOCK_CLOCK_CLKGEN7     ///< DAC clock bus mapped to CLKGEN7
#    define SYSCLOCK_CLOCK_UART  SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI   SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_PTG   SYSCLOCK_CLOCK_CLKGEN10    ///< PTG clock bus mapped to CLKGEN10
#    define SYSCLOCK_CLOCK_BISS  SYSCLOCK_CLOCK_CLKGEN11    ///< BISS clock bus mapped to CLKGEN11
#    define SYSCLOCK_CLOCK_CCP   SYSCLOCK_CLOCK_CLKGEN12    ///< CCP clock bus mapped to CLKGEN12
#    define SYSCLOCK_CLOCK_REFO1 SYSCLOCK_CLOCK_CLKGEN12    ///< REFO1 clock bus mapped to CLKGEN12
#    define SYSCLOCK_CLOCK_REFO2 SYSCLOCK_CLOCK_CLKGEN13    ///< REFO2 clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_CLC   SYSCLOCK_CLOCK_CLKGEN13    ///< CLC clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_IOM   SYSCLOCK_CLOCK_CLKGEN13    ///< IOM clock bus mapped to CLKGEN13

#elif defined(DEVICE_33AK128MPS103) || defined(DEVICE_33AK128MPS105) || defined(DEVICE_33AK128MPS106) || defined(DEVICE_33AK256MPS103)                         \
    || defined(DEVICE_33AK256MPS105) || defined(DEVICE_33AK256MPS106)

#    define SYSCLOCK_CLKGEN_COUNT 15
#    define SYSCLOCK_CLKGEN_MAX   16

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0,       ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2 = 1,       ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3 = 2,       ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4 = 3,       ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5 = 4,       ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6 = 5,       ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7 = 6,       ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8 = 7,       ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9 = 8,       ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN10 = 9,      ///< CLKGEN10 Sources CAN
    SYSCLOCK_CLOCK_CLKGEN11 = 10,     ///< CLKGEN11 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN12 = 11,     ///< CLKGEN12 Sources RDC
    SYSCLOCK_CLOCK_CLKGEN13 = 12,     ///< CLKGEN13 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN14 = 13,     ///< CLKGEN14 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_CLKGEN15 = 14,     ///< CLKGEN15 Sources TRACE
    SYSCLOCK_CLOCK_CLKGEN16 = 15,     ///< CLKGEN16 Sources I3C and BiSS
    SYSCLOCK_CLOCK_FAST_PERIPH = 16,  ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH = 17,   ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH = 18,  ///< Slow Speed Peripheral Clock FOSC/4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_FRC = 0b0001,           ///< Internal 8 MHz RC oscillator
    SYSCLOCK_SRC_BFRC = 0b0010,          ///< Internal Backup 8 MHz RC oscillator
    SYSCLOCK_SRC_POSC = 0b0011,          ///< Primary crystal oscillator (4-32 MHz)
    SYSCLOCK_SRC_LPRC = 0b0100,          ///< LPRC as BFRC/244
    SYSCLOCK_SRC_PLL1_FOUT = 0b0101,     ///< PLL1 output
    SYSCLOCK_SRC_PLL2_FOUT = 0b0110,     ///< PLL2 output
    SYSCLOCK_SRC_PLL1_VCO_DIV = 0b0111,  ///< PLL1 VCO DIV output
    SYSCLOCK_SRC_PLL2_VCO_DIV = 0b1000,  ///< PLL2 VCO DIV output
    SYSCLOCK_SRC_REFI1 = 0b1001,         ///< Device REFI1 pin through PPS
    SYSCLOCK_SRC_REFI2 = 0b1010,         ///< Device REFI2 pin through PPS
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_MAX    10

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"", "FRC", "BFRC", "POSC", "LPRC", "PLL1", "PLL2", "VCO1", "VCO2", "", "REFI1", "REFI2"};
#endif

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_PWM    SYSCLOCK_CLOCK_CLKGEN5     ///< PWM clock bus mapped to CLKGEN5
#    define SYSCLOCK_CLOCK_ADC    SYSCLOCK_CLOCK_CLKGEN6     ///< ADC clock bus mapped to CLKGEN6
#    define SYSCLOCK_CLOCK_DAC    SYSCLOCK_CLOCK_CLKGEN7     ///< DAC clock bus mapped to CLKGEN7
#    define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_PTG    SYSCLOCK_CLOCK_CLKGEN11    ///< PTG clock bus mapped to CLKGEN11
#    define SYSCLOCK_CLOCK_RDC    SYSCLOCK_CLOCK_CLKGEN12    ///< RDC clock bus mapped to CLKGEN12
#    define SYSCLOCK_CLOCK_CCP    SYSCLOCK_CLOCK_CLKGEN13    ///< CCP clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO1  SYSCLOCK_CLOCK_CLKGEN13    ///< REFO1 clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO2  SYSCLOCK_CLOCK_CLKGEN14    ///< REFO2 clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_CLC    SYSCLOCK_CLOCK_CLKGEN14    ///< CLC clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_IOM    SYSCLOCK_CLOCK_CLKGEN14    ///< IOM clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_TRACE  SYSCLOCK_CLOCK_CLKGEN15    ///< TRACE clock bus mapped to CLKGEN15
#    define SYSCLOCK_CLOCK_I3C    SYSCLOCK_CLOCK_CLKGEN16    ///< I3C clock bus mapped to CLKGEN16
#    define SYSCLOCK_CLOCK_BISS   SYSCLOCK_CLOCK_CLKGEN16    ///< BISS clock bus mapped to CLKGEN16

#elif defined(DEVICE_33AK128MPS303) || defined(DEVICE_33AK128MPS305) || defined(DEVICE_33AK128MPS306) || defined(DEVICE_33AK256MPS303)                         \
    || defined(DEVICE_33AK256MPS305) || defined(DEVICE_33AK256MPS306)

#    define SYSCLOCK_CLKGEN_COUNT 16
#    define SYSCLOCK_CLKGEN_MAX   16

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0,       ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2 = 1,       ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3 = 2,       ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4 = 3,       ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5 = 4,       ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6 = 5,       ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7 = 6,       ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8 = 7,       ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9 = 8,       ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN10 = 9,      ///< CLKGEN10 Sources CAN
    SYSCLOCK_CLOCK_CLKGEN11 = 10,     ///< CLKGEN11 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN12 = 11,     ///< CLKGEN12 Sources RDC
    SYSCLOCK_CLOCK_CLKGEN13 = 12,     ///< CLKGEN13 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN14 = 13,     ///< CLKGEN14 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_CLKGEN15 = 14,     ///< CLKGEN15 Sources TRACE
    SYSCLOCK_CLOCK_CLKGEN16 = 15,     ///< CLKGEN16 Sources I3C and BiSS
    SYSCLOCK_CLOCK_FAST_PERIPH = 16,  ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH = 17,   ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH = 18,  ///< Slow Speed Peripheral Clock FOSC/4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_FRC = 0b0001,           ///< Internal 8 MHz RC oscillator
    SYSCLOCK_SRC_BFRC = 0b0010,          ///< Internal Backup 8 MHz RC oscillator
    SYSCLOCK_SRC_POSC = 0b0011,          ///< Primary crystal oscillator (4-32 MHz)
    SYSCLOCK_SRC_LPRC = 0b0100,          ///< LPRC as BFRC/244
    SYSCLOCK_SRC_PLL1_FOUT = 0b0101,     ///< PLL1 output
    SYSCLOCK_SRC_PLL2_FOUT = 0b0110,     ///< PLL2 output
    SYSCLOCK_SRC_PLL1_VCO_DIV = 0b0111,  ///< PLL1 VCO DIV output
    SYSCLOCK_SRC_PLL2_VCO_DIV = 0b1000,  ///< PLL2 VCO DIV output
    SYSCLOCK_SRC_REFI1 = 0b1001,         ///< Device REFI1 pin through PPS
    SYSCLOCK_SRC_REFI2 = 0b1010,         ///< Device REFI2 pin through PPS
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_MAX    10

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"", "FRC", "BFRC", "POSC", "LPRC", "PLL1", "PLL2", "VCO1", "VCO2", "", "REFI1", "REFI2"};
#endif

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_PWM    SYSCLOCK_CLOCK_CLKGEN5     ///< PWM clock bus mapped to CLKGEN5
#    define SYSCLOCK_CLOCK_ADC    SYSCLOCK_CLOCK_CLKGEN6     ///< ADC clock bus mapped to CLKGEN6
#    define SYSCLOCK_CLOCK_DAC    SYSCLOCK_CLOCK_CLKGEN7     ///< DAC clock bus mapped to CLKGEN7
#    define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_CAN    SYSCLOCK_CLOCK_CLKGEN10    ///< CAN clock bus mapped to CLKGEN10
#    define SYSCLOCK_CLOCK_PTG    SYSCLOCK_CLOCK_CLKGEN11    ///< PTG clock bus mapped to CLKGEN11
#    define SYSCLOCK_CLOCK_RDC    SYSCLOCK_CLOCK_CLKGEN12    ///< RDC clock bus mapped to CLKGEN12
#    define SYSCLOCK_CLOCK_CCP    SYSCLOCK_CLOCK_CLKGEN13    ///< CCP clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO1  SYSCLOCK_CLOCK_CLKGEN13    ///< REFO1 clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO2  SYSCLOCK_CLOCK_CLKGEN14    ///< REFO2 clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_CLC    SYSCLOCK_CLOCK_CLKGEN14    ///< CLC clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_IOM    SYSCLOCK_CLOCK_CLKGEN14    ///< IOM clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_TRACE  SYSCLOCK_CLOCK_CLKGEN15    ///< TRACE clock bus mapped to CLKGEN15
#    define SYSCLOCK_CLOCK_I3C    SYSCLOCK_CLOCK_CLKGEN16    ///< I3C clock bus mapped to CLKGEN16
#    define SYSCLOCK_CLOCK_BISS   SYSCLOCK_CLOCK_CLKGEN16    ///< BISS clock bus mapped to CLKGEN16

#elif defined(DEVICE_33AK256MC205) || defined(DEVICE_33AK256MC206) || defined(DEVICE_33AK256MC208) || defined(DEVICE_33AK256MC210)                             \
    || defined(DEVICE_33AK256MPS205) || defined(DEVICE_33AK256MPS206) || defined(DEVICE_33AK256MPS208) || defined(DEVICE_33AK256MPS210)                        \
    || defined(DEVICE_33AK256MPS212) || defined(DEVICE_33AK512MC205) || defined(DEVICE_33AK512MC206) || defined(DEVICE_33AK512MC208)                           \
    || defined(DEVICE_33AK512MC210) || defined(DEVICE_33AK512MPS205) || defined(DEVICE_33AK512MPS206) || defined(DEVICE_33AK512MPS208)                         \
    || defined(DEVICE_33AK512MPS210) || defined(DEVICE_33AK512MPS212)

#    define SYSCLOCK_CLKGEN_COUNT 13
#    define SYSCLOCK_CLKGEN_MAX   14

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0,       ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2 = 1,       ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3 = 2,       ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4 = 3,       ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5 = 4,       ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6 = 5,       ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7 = 6,       ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8 = 7,       ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9 = 8,       ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN11 = 10,     ///< CLKGEN11 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN12 = 11,     ///< CLKGEN12 Sources BiSS
    SYSCLOCK_CLOCK_CLKGEN13 = 12,     ///< CLKGEN13 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN14 = 13,     ///< CLKGEN14 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_FAST_PERIPH = 14,  ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH = 15,   ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH = 16,  ///< Slow Speed Peripheral Clock FOSC/4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_FRC = 0b0001,           ///< Internal 8 MHz RC oscillator
    SYSCLOCK_SRC_BFRC = 0b0010,          ///< Internal Backup 8 MHz RC oscillator
    SYSCLOCK_SRC_POSC = 0b0011,          ///< Primary crystal oscillator (4-32 MHz)
    SYSCLOCK_SRC_LPRC = 0b0100,          ///< LPRC as BFRC/244
    SYSCLOCK_SRC_PLL1_FOUT = 0b0101,     ///< PLL1 output
    SYSCLOCK_SRC_PLL2_FOUT = 0b0110,     ///< PLL2 output
    SYSCLOCK_SRC_PLL1_VCO_DIV = 0b0111,  ///< PLL1 VCO DIV output
    SYSCLOCK_SRC_PLL2_VCO_DIV = 0b1000,  ///< PLL2 VCO DIV output
    SYSCLOCK_SRC_REFI1 = 0b1001,         ///< Device REFI1 pin through PPS
    SYSCLOCK_SRC_REFI2 = 0b1010,         ///< Device REFI2 pin through PPS
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_MAX    10

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"", "FRC", "BFRC", "POSC", "LPRC", "PLL1", "PLL2", "VCO1", "VCO2", "", "REFI1", "REFI2"};
#endif

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_PWM    SYSCLOCK_CLOCK_CLKGEN5     ///< PWM clock bus mapped to CLKGEN5
#    define SYSCLOCK_CLOCK_ADC    SYSCLOCK_CLOCK_CLKGEN6     ///< ADC clock bus mapped to CLKGEN6
#    define SYSCLOCK_CLOCK_DAC    SYSCLOCK_CLOCK_CLKGEN7     ///< DAC clock bus mapped to CLKGEN7
#    define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_PTG    SYSCLOCK_CLOCK_CLKGEN11    ///< PTG clock bus mapped to CLKGEN11
#    define SYSCLOCK_CLOCK_BISS   SYSCLOCK_CLOCK_CLKGEN12    ///< BISS clock bus mapped to CLKGEN12
#    define SYSCLOCK_CLOCK_CCP    SYSCLOCK_CLOCK_CLKGEN13    ///< CCP clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO1  SYSCLOCK_CLOCK_CLKGEN13    ///< REFO1 clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO2  SYSCLOCK_CLOCK_CLKGEN14    ///< REFO2 clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_CLC    SYSCLOCK_CLOCK_CLKGEN14    ///< CLC clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_IOM    SYSCLOCK_CLOCK_CLKGEN14    ///< IOM clock bus mapped to CLKGEN14

#elif defined(DEVICE_33AK256MC505) || defined(DEVICE_33AK256MC506) || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510)                             \
    || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506) || defined(DEVICE_33AK256MPS508) || defined(DEVICE_33AK256MPS510)                        \
    || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC505) || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508)                           \
    || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS505) || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508)                         \
    || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)

#    define SYSCLOCK_CLKGEN_COUNT 14
#    define SYSCLOCK_CLKGEN_MAX   14

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0,       ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2 = 1,       ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3 = 2,       ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4 = 3,       ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5 = 4,       ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6 = 5,       ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7 = 6,       ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8 = 7,       ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9 = 8,       ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN10 = 9,      ///< CLKGEN10 Sources CAN
    SYSCLOCK_CLOCK_CLKGEN11 = 10,     ///< CLKGEN11 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN12 = 11,     ///< CLKGEN12 Sources BiSS
    SYSCLOCK_CLOCK_CLKGEN13 = 12,     ///< CLKGEN13 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN14 = 13,     ///< CLKGEN14 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_FAST_PERIPH = 14,  ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH = 15,   ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH = 16,  ///< Slow Speed Peripheral Clock FOSC/4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_FRC = 0b0001,           ///< Internal 8 MHz RC oscillator
    SYSCLOCK_SRC_BFRC = 0b0010,          ///< Internal Backup 8 MHz RC oscillator
    SYSCLOCK_SRC_POSC = 0b0011,          ///< Primary crystal oscillator (4-32 MHz)
    SYSCLOCK_SRC_LPRC = 0b0100,          ///< LPRC as BFRC/244
    SYSCLOCK_SRC_PLL1_FOUT = 0b0101,     ///< PLL1 output
    SYSCLOCK_SRC_PLL2_FOUT = 0b0110,     ///< PLL2 output
    SYSCLOCK_SRC_PLL1_VCO_DIV = 0b0111,  ///< PLL1 VCO DIV output
    SYSCLOCK_SRC_PLL2_VCO_DIV = 0b1000,  ///< PLL2 VCO DIV output
    SYSCLOCK_SRC_REFI1 = 0b1001,         ///< Device REFI1 pin through PPS
    SYSCLOCK_SRC_REFI2 = 0b1010,         ///< Device REFI2 pin through PPS
} SYSCLOCK_SOURCE;
#define SYSCLOCK_SRC_MAX    10

#ifdef SYSCLOCK_DEBUG
static const char *sysclock_sources_str[] = {"", "FRC", "BFRC", "POSC", "LPRC", "PLL1", "PLL2", "VCO1", "VCO2", "", "REFI1", "REFI2"};
#endif

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_PWM    SYSCLOCK_CLOCK_CLKGEN5     ///< PWM clock bus mapped to CLKGEN5
#    define SYSCLOCK_CLOCK_ADC    SYSCLOCK_CLOCK_CLKGEN6     ///< ADC clock bus mapped to CLKGEN6
#    define SYSCLOCK_CLOCK_DAC    SYSCLOCK_CLOCK_CLKGEN7     ///< DAC clock bus mapped to CLKGEN7
#    define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_CAN    SYSCLOCK_CLOCK_CLKGEN10    ///< CAN clock bus mapped to CLKGEN10
#    define SYSCLOCK_CLOCK_PTG    SYSCLOCK_CLOCK_CLKGEN11    ///< PTG clock bus mapped to CLKGEN11
#    define SYSCLOCK_CLOCK_BISS   SYSCLOCK_CLOCK_CLKGEN12    ///< BISS clock bus mapped to CLKGEN12
#    define SYSCLOCK_CLOCK_CCP    SYSCLOCK_CLOCK_CLKGEN13    ///< CCP clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO1  SYSCLOCK_CLOCK_CLKGEN13    ///< REFO1 clock bus mapped to CLKGEN13
#    define SYSCLOCK_CLOCK_REFO2  SYSCLOCK_CLOCK_CLKGEN14    ///< REFO2 clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_CLC    SYSCLOCK_CLOCK_CLKGEN14    ///< CLC clock bus mapped to CLKGEN14
#    define SYSCLOCK_CLOCK_IOM    SYSCLOCK_CLOCK_CLKGEN14    ///< IOM clock bus mapped to CLKGEN14

#else
#    define SYSCLOCK_CLKGEN_COUNT 0
#endif

uint32_t sysclock_clkgenFreq(uint8_t clkgen);
uint32_t sysclock_getPLLClock(uint8_t pllId);

#ifdef __cplusplus
}
#endif

#endif  // SYSCLOCK_DSPIC33A_PIC32A_H
