/**
 * @file curiosity_nano_dsPIC33CK_fuses.c
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2025
 *
 * @date February 11, 2025, 03:27 PM
 *
 * @brief Fuses for Curiosity dsPIC33CK nano board (EV88G73A)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/EV88G73A
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/dsPIC33CK64MC105-Curiosity-Nano-Users-Guide-DS70005517.pdf
 */

// FSEC
#pragma config BWRP = OFF      // Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED  // Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF      // Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF      // General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED  // General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF      // Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED  // Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF   // Alternate Interrupt Vector Table bit->Disabled AIVT

// FBSLIM
#pragma config BSLIM = 8191  // Boot Segment Flash Page Address Limit bits->8191

// FOSCSEL
#pragma config FNOSC = FRC  // Oscillator Source Selection (Internal Fast RC (FRC) Oscillator with postscaler)
#pragma config IESO = ON    // Two-speed Oscillator Start-up Enable bit (Start up device with FRC, then switch to user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE   // Primary Oscillator Mode Select bits (Primary Oscillator disabled)
#pragma config OSCIOFNC = ON   // OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config FCKSM = CSECME  // Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are enabled
#pragma config PLLKEN = ON     // PLL Lock Status Control->PLL lock signal will be used to disable PLL clock output if lock is lost
#pragma config XTCFG = G3      // XT Config->24-32 MHz crystals
#pragma config XTBST = ENABLE  // XT Boost->Boost the kick-start

// FWDT
#pragma config RCLKSEL = LPRC  // Watchdog Timer Clock Select bits->Always use LPRC
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable bit->Watchdog Timer in Window mode
#pragma config WDTWIN = WIN25  // Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config FWDTEN = ON_SW  // Watchdog Timer Enable bit->WDT controlled via SW, use WDTCON.ON bit

// FPOR
#pragma config BISTDIS = DISABLED  // Memory BIST Feature Disable->mBIST on reset feature disabled

// FICD
#pragma config ICS = PGD3    // ICD Communication Channel Select bits->Communicate on PGC3 and PGD3
#pragma config JTAGEN = OFF  // JTAG Enable bit->JTAG is disabled

// FDMTIVTL
#pragma config DMTIVTL = 0  // Dead Man Timer Interval low word->0

// FDMTIVTH
#pragma config DMTIVTH = 0  // Dead Man Timer Interval high word->0

// FDMTCNTL
#pragma config DMTCNTL = 0  // Lower 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->0

// FDMTCNTH
#pragma config DMTCNTH = 0  // Upper 16 bits of 32 bit DMT instruction count time-out value (0-0xFFFF)->0

// FDMT
#pragma config DMTDIS = OFF  // Dead Man Timer Disable bit->Dead Man Timer is Disabled and can be enabled by software

// FDEVOPT
#pragma config ALTI2C1 = OFF  // Alternate I2C1 Pin bit->I2C1 mapped to SDA1/SCL1 pins
#pragma config ALTI2C2 = OFF  // Alternate I2C2 Pin bit->I2C2 mapped to SDA2/SCL2 pins
#pragma config SPI2PIN = PPS  // SPI2 Pin Select bit->SPI2 uses I/O remap (PPS) pins

// FALTREG
#pragma config CTXT1 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 1 bits->Not Assigned
#pragma config CTXT2 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 2 bits->Not Assigned
#pragma config CTXT3 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 3 bits->Not Assigned
#pragma config CTXT4 = OFF  // Specifies Interrupt Priority Level (IPL) Associated to Alternate Working Register 4 bits->Not Assigned
