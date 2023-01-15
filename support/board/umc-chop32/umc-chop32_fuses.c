/**
 * @file umc-chop32_fuses.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date August 22, 2022, 10:00 AM
 *
 * @brief Board support package fuses for UMC-CHOP32 board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc-chop32
 */

// FSEC
#pragma config BWRP = OFF      // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED  // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF      // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF      // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED  // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF      // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED  // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF   // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF  // Boot Segment Flash Page Address Limit bits (Enter Hexadecimal value)

// FOSCSEL
#pragma config FNOSC = FRCDIVN  // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = ON        // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE   // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON   // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config FCKSM = CSECMD  // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)
#pragma config PLLKEN = ON     // PLL Lock Enable (PLL clock output will be disabled if LOCK is lost)
#pragma config XTCFG = G3      // XT Config (24-32 MHz crystals)
#pragma config XTBST = ENABLE  // XT Boost (Boost the kick-start)

// FWDT
#pragma config RWDTPS = PS1048576  // Run Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config RCLKSEL = LPRC      // Watchdog Timer Clock Select bits (Always use LPRC)
#pragma config WINDIS = ON         // Watchdog Timer Window Enable bit (Watchdog Timer operates in Non-Window mode)
#pragma config WDTWIN = WIN25      // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config SWDTPS = PS1048576  // Sleep Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config FWDTEN = ON         // Watchdog Timer Enable bit (WDT enabled in hardware)

// FPOR
#pragma config BISTDIS = DISABLED  // Memory BIST Feature Disable (mBIST on reset feature disabled)

// FICD
#pragma config ICS = PGD2    // ICD Communication Channel Select bits (Communicate on PGC2 and PGD2)
#pragma config JTAGEN = OFF  // JTAG Enable bit (JTAG is disabled)

// FDMTIVTL
#pragma config DMTIVTL = 0xFFFF  // Dead Man Timer Interval low word (Enter Hexadecimal value)

// FDMTIVTH
#pragma config DMTIVTH = 0xFFFF  // Dead Man Timer Interval high word (Enter Hexadecimal value)

// FDMTCNTL
#pragma config DMTCNTL = 0xFFFF  // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMTCNTH
#pragma config DMTCNTH = 0xFFFF  // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF) (Enter Hexadecimal value)

// FDMT
#pragma config DMTDIS = OFF  // Dead Man Timer Disable bit (Dead Man Timer is Disabled and can be enabled by software)

// FDEVOPT
#pragma config ALTI2C1 = OFF    // Alternate I2C1 Pin bit (I2C1 mapped to SDA1/SCL1 pins)
#pragma config SMB3EN = SMBUS3  // SM Bus Enable (SMBus 3.0 input levels)
#pragma config SPI2PIN = PPS    // SPI2 Pin Select bit (SPI2 uses I/O remap (PPS) pins)

// FALTREG
#pragma config CTXT1 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits (Not Assigned)
#pragma config CTXT2 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits (Not Assigned)
#pragma config CTXT3 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits (Not Assigned)
#pragma config CTXT4 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits (Not Assigned)
