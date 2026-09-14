/**
 * @file curiosity_dsPIC33AK128MC106_fuses.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date September 13, 2026, 02:51 PM
 *
 * @brief Fuses for uDSP board
 */

// FCP
#pragma config FCP_CP = OFF     // Memory protection enable bit. (Memory protection is disabled.)
#pragma config FCP_CRC = OFF    // CRC enable bit. (CRC is disabled.)
#pragma config FCP_WPUCA = OFF  // User configuration areas write protection enable bits. (Protection is disabled.)

// FICD
#pragma config FICD_JTAGEN = OFF              // JTAG enable bit. (JTAG is disabled.)
#pragma config FICD_NOBTSWP = BTSWP_DISABLED  // BOOTSWP instruction disable bit (BOOTSWP instruction is disabled)

// FDEVOPT
#pragma config FDEVOPT_BISTDIS = OFF  // Hardware RAM test disable bit. (RAM test is disabled)

// FWDT
#pragma config FWDT_WINDIS = ON             // Watchdog Timer Window Disable bit (Watchdog Timer operates in Non-Window mode)
#pragma config FWDT_SWDTMPS = PS2147483648  // Sleep Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config FWDT_RCLKSEL = BFRC244       // Watchdog Timer Clock Select bits (WDT Run Mode uses 32.78kHz clock from BFRC/244)
#pragma config FWDT_RWDTPS = PS2147483648   // Run Mode Watchdog Timer Post Scaler select bits (1:2147483648)
#pragma config FWDT_WDTWIN = WIN25          // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config FWDT_WDTEN = SW              // Watchdog Timer Enable bit (WDT is controlled by software, use WDTCON.ON bit)
#pragma config FWDT_WDTRSTEN = ON           // Watchdog Timer Reset Enable bit (WDT Event Generates a Reset)
#pragma config FWDT_WDTNVMSTL = ON          // WDT Stall During NVM Operation (Stall WDT During NVM Operation)

// FPR0CTRL
#pragma config FPR0CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR0CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR0CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR0CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR0CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR0CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR0CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR0CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR0ST
#pragma config FPR0ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR0END
#pragma config FPR0END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR1CTRL
#pragma config FPR1CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR1CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR1CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR1CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR1CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR1CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR1CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR1CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR1ST
#pragma config FPR1ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR1END
#pragma config FPR1END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR2CTRL
#pragma config FPR2CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR2CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR2CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR2CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR2CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR2CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR2CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR2CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR2ST
#pragma config FPR2ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR2END
#pragma config FPR2END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR3CTRL
#pragma config FPR3CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR3CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR3CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR3CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR3CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR3CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR3CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR3CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR3ST
#pragma config FPR3ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR3END
#pragma config FPR3END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR4CTRL
#pragma config FPR4CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR4CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR4CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR4CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR4CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR4CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR4CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR4CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR4ST
#pragma config FPR4ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR4END
#pragma config FPR4END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR5CTRL
#pragma config FPR5CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR5CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR5CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR5CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR5CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR5CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR5CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR5CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR5ST
#pragma config FPR5ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR5END
#pragma config FPR5END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR6CTRL
#pragma config FPR6CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR6CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR6CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR6CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR6CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR6CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR6CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR6CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR6ST
#pragma config FPR6ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR6END
#pragma config FPR6END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FPR7CTRL
#pragma config FPR7CTRL_RDIS = ON         // Region protection disable bit (Protection is disabled)
#pragma config FPR7CTRL_ERAO = ON         // Error Report Address Only (ECC error reporting information restricted to address only)
#pragma config FPR7CTRL_EX = ON           // Execute permission bit. (Code execution is enabled.)
#pragma config FPR7CTRL_RD = ON           // Read permission bit. (Read operation is enabled.)
#pragma config FPR7CTRL_WR = ON           // Write permission bit. (Write and erase operation is enabled.)
#pragma config FPR7CTRL_CRC = ON          // CRC enable bit. (NVM controller CRC calculation is enabled.)
#pragma config FPR7CTRL_RTYPE = FIRMWARE  // Region type selection bits. (Firmware configurable region.)
#pragma config FPR7CTRL_PSEL = BOTH       // Partition Select (Both Panels)

// FPR7ST
#pragma config FPR7ST_START = 0x7FF  // Region start address bits. (Enter Hexadecimal value)

// FPR7END
#pragma config FPR7END_END = 0x7FF  // Region end address bits. (Enter Hexadecimal value)

// FIRT
#pragma config FIRT_IRT = OFF  // Immutable Root of Trust Enable bit (Immutable root of trust (IRT) regions are disabled)

// FSECDBG
#pragma config FSECDBG_SECDBG = OFF  // Secure Debug Enable bit (Secure Debug is Disabled)

// FPED
#pragma config FPED_ICSPPED = OFF  // ICSP Program and Erase disable bit (ICSP can program and erase)

// FEPUCB
#pragma config FEPUCB_EPUCB = 0xFFFFFFFF  // User Config B Page Erase Protect bits (Enter Hexadecimal value)

// FWPUCB
#pragma config FWPUCB_WPUCB = 0xFFFFFFFF  // UCB Write Protection bits (Enter Hexadecimal value)
