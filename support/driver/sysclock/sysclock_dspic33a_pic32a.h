/**
 * @file sysclock_dspic33a_pic32a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date May 3, 2025, 10:26 PM
 *
 * @brief System clock support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip document DS70005539B:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 */

#ifndef SYSCLOCK_DSPIC33A_PIC32A_H
#define SYSCLOCK_DSPIC33A_PIC32A_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_32AK1216GC41036) || defined(DEVICE_32AK1216GC41048) || defined(DEVICE_32AK1216GC41064) || defined(DEVICE_32AK3208GC41036)                   \
    || defined(DEVICE_32AK3208GC41048) || defined(DEVICE_32AK3208GC41064) || defined(DEVICE_32AK6416GC41036) || defined(DEVICE_32AK6416GC41048)                \
    || defined(DEVICE_32AK6416GC41064) || defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105)                            \
    || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102) || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) \
    || defined(DEVICE_33AK128MC102) || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)                            \
    || defined(DEVICE_33AK256MC205) || defined(DEVICE_33AK256MC206) || defined(DEVICE_33AK256MC208) || defined(DEVICE_33AK256MC210)                            \
    || defined(DEVICE_33AK256MPS205) || defined(DEVICE_33AK256MPS206) || defined(DEVICE_33AK256MPS208) || defined(DEVICE_33AK256MPS210)                        \
    || defined(DEVICE_33AK256MPS212) || defined(DEVICE_33AK512MC205) || defined(DEVICE_33AK512MC206) || defined(DEVICE_33AK512MC208)                           \
    || defined(DEVICE_33AK512MC210) || defined(DEVICE_33AK512MPS205) || defined(DEVICE_33AK512MPS206) || defined(DEVICE_33AK512MPS208)                         \
    || defined(DEVICE_33AK512MPS210) || defined(DEVICE_33AK512MPS212)
#    define SYSCLOCK_CLKGEN_COUNT 13

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0x0,  ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2,        ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3,        ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4,        ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5,        ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6,        ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7,        ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8,        ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9,        ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN10,       ///< CLKGEN10 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN11,       ///< CLKGEN11 Sources BiSS
    SYSCLOCK_CLOCK_CLKGEN12,       ///< CLKGEN12 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN13,       ///< CLKGEN13 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_FQST_PERIPH,    ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH,     ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH,    ///< Slow Speed Peripheral Clock FOSC/4
} SYSCLOCK_CLOCK;

// clock source
typedef enum
{
    SYSCLOCK_SRC_ICSP = 0b0000,          ///< ICSP clock (PGC)
    SYSCLOCK_SRC_FRC = 0b0001,           ///< Internal 8 MHz RC oscillator
    SYSCLOCK_SRC_BFRC = 0b0010,          ///< Internal Backup 8 MHz RC oscillator
    SYSCLOCK_SRC_POSC = 0b0011,          ///< Primary crystal oscillator (4-32 MHz)
    SYSCLOCK_SRC_LPRC = 0b0100,          ///< LPRC as BFRC/244
    SYSCLOCK_SRC_PLL1_FOUT = 0b0101,     ///< PLL1 output
    SYSCLOCK_SRC_PLL2_FOUT = 0b0110,     ///< PLL2 output
    SYSCLOCK_SRC_PLL1_VCO_DIV = 0b0111,  ///< PLL1 VCO DIV output
    SYSCLOCK_SRC_PLL2_VCO_DIV = 0b1000,  ///< PLL2 VCO DIV output
    SYSCLOCK_SRC_REFI2 = 0b1001,         ///< Device REFI2 pin through PPS
    SYSCLOCK_SRC_REFI1 = 0b1010,         ///< Device REFI1 pin through PPS
} SYSCLOCK_SOURCE;

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU   SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C   SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_UART  SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI   SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_TIMER SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_CCP   SYSCLOCK_CLOCK_STD_PERIPH  ///< CCP clock bus mapped toStandard Speed Peripheral

#elif defined(DEVICE_33AK256MC505) || defined(DEVICE_33AK256MC506) || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510)                             \
    || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506) || defined(DEVICE_33AK256MPS508) || defined(DEVICE_33AK256MPS510)                        \
    || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC505) || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508)                           \
    || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS505) || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508)                         \
    || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)
#    define SYSCLOCK_CLKGEN_COUNT 14

// bus clock
typedef enum
{
    SYSCLOCK_CLOCK_CLKGEN1 = 0x0,  ///< CLKGEN1 Sources System Clock and Peripheral Clock
    SYSCLOCK_CLOCK_CLKGEN2,        ///< CLKGEN2 Only FRC
    SYSCLOCK_CLOCK_CLKGEN3,        ///< CLKGEN3 Only BFRC
    SYSCLOCK_CLOCK_CLKGEN4,        ///< CLKGEN4 Sources RAM BIST and NVM BIST
    SYSCLOCK_CLOCK_CLKGEN5,        ///< CLKGEN5 Sources PWM
    SYSCLOCK_CLOCK_CLKGEN6,        ///< CLKGEN6 Sources ADC
    SYSCLOCK_CLOCK_CLKGEN7,        ///< CLKGEN7 Sources PDM DAC
    SYSCLOCK_CLOCK_CLKGEN8,        ///< CLKGEN8 Sources UART
    SYSCLOCK_CLOCK_CLKGEN9,        ///< CLKGEN9 Sources SPI
    SYSCLOCK_CLOCK_CLKGEN10,       ///< CLKGEN10 Sources CAN
    SYSCLOCK_CLOCK_CLKGEN11,       ///< CLKGEN11 Sources PTG
    SYSCLOCK_CLOCK_CLKGEN12,       ///< CLKGEN12 Sources BiSS
    SYSCLOCK_CLOCK_CLKGEN13,       ///< CLKGEN13 Sources CCP and REFO1
    SYSCLOCK_CLOCK_CLKGEN14,       ///< CLKGEN14 Sources CLC, IOIM and REFO2
    SYSCLOCK_CLOCK_FQST_PERIPH,    ///< Fast Speed Peripheral Clock FOSC
    SYSCLOCK_CLOCK_STD_PERIPH,     ///< Standard Speed Peripheral Clock FOSC/2
    SYSCLOCK_CLOCK_SLOW_PERIPH,    ///< Slow Speed Peripheral Clock FOSC/4
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
    SYSCLOCK_SRC_SOSC = 0b1011,          ///< Secondary crystal oscillator
    SYSCLOCK_SRC_AOSC = 0b1100,          ///< Auxiliary crystal oscillator
} SYSCLOCK_SOURCE;

// periph clock assoc
#    define SYSCLOCK_CLOCK_CPU    SYSCLOCK_CLOCK_CLKGEN1     ///< CPU clock bus
#    define SYSCLOCK_CLOCK_I2C    SYSCLOCK_CLOCK_STD_PERIPH  ///< I2C clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_UART   SYSCLOCK_CLOCK_CLKGEN8     ///< UART clock bus mapped to CLKGEN8
#    define SYSCLOCK_CLOCK_SPI    SYSCLOCK_CLOCK_CLKGEN9     ///< SPI clock bus mapped to CLKGEN9
#    define SYSCLOCK_CLOCK_CAN    SYSCLOCK_CLOCK_CLKGEN10    ///< UART clock bus mapped to CLKGEN10
#    define SYSCLOCK_CLOCK_TIMER  SYSCLOCK_CLOCK_STD_PERIPH  ///< TIMER clock bus mapped to Standard Speed Peripheral
#    define SYSCLOCK_CLOCK_CCP    SYSCLOCK_CLOCK_STD_PERIPH  ///< CCP clock bus mapped toStandard Speed Peripheral

#else
#    define SYSCLOCK_CLKGEN_COUNT 0
#endif

#ifdef __cplusplus
}
#endif

#endif  // SYSCLOCK_DSPIC33A_PIC32A_H
