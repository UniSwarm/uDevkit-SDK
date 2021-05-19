
// FDEVOPT
#pragma config SOSCHP = OFF     // Secondary Oscillator High Power Enable bit (SOSC oprerates in normal power mode.)
#pragma config ALTI2C = ON      // Alternate I2C1 Pins Location Enable bit (Alternate I2C1 pins are used)
#pragma config FUSBIDIO = ON    // USBID pin control (USBID pin is controlled by the port function)
#pragma config FVBUSIO = ON     // VBUS Pin Control (VBUS pin is controlled by port function)
#pragma config USERID = 0xFFFF  // User ID bits (User ID bits)

// FICD
#pragma config JTAGEN = OFF  // JTAG Enable bit (JTAG is disabled)
#pragma config ICS = PGx2    // ICE/ICD Communication Channel Selection bits (Communicate on PGEC2/PGED2)

// FPOR
#pragma config BOREN = BOR3  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config RETVR = OFF   // Retention Voltage Regulator Enable bit (Retention regulator is disabled)
#pragma config LPBOREN =                                                                                               \
    ON  // Downside Voltage Protection Enable bit (Low power BOR is enabled, when main BOR is disabled)

// FWDT
#pragma config SWDTPS = PS1048576  // Sleep Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config FWDTWINSZ = PS25_0  // Watchdog Timer Window Size bits (Watchdog timer window size is 25%)
#pragma config WINDIS = OFF        // Windowed Watchdog Timer Disable bit (Watchdog timer is in non-window mode)
#pragma config RWDTPS = PS1048576  // Run Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config RCLKSEL =                                                                                               \
    LPRC  // Run Mode Watchdog Timer Clock Source Selection bits (Clock source is LPRC (same as for sleep mode))
#pragma config FWDTEN = OFF  // Watchdog Timer Enable bit (WDT is disabled)

// FOSCSEL
#pragma config FNOSC = FRCDIV  // Oscillator Selection bits (Fast RC oscillator (FRC) with divide-by-N)
#pragma config PLLSRC =                                                                                                \
    FRC  // System PLL Input Clock Selection bit (FRC oscillator is selected as PLL reference input on device reset)
#pragma config SOSCEN = ON     // Secondary Oscillator Enable bit (Secondary oscillator (SOSC) is enabled)
#pragma config IESO = OFF      // Two Speed Startup Enable bit (Two speed startup is disabled)
#pragma config POSCMOD = OFF   // Primary Oscillator Selection bit (Primary oscillator is disabled)
#pragma config OSCIOFNC = OFF  // System Clock on CLKO Pin Enable bit (OSCO pin operates as a normal I/O)
#pragma config SOSCSEL =                                                                                               \
    ON  // Secondary Oscillator External Clock Enable bit (Crystal is used (RA4 and RB4 are controlled by SOSC))
#pragma config FCKSM = CSECME  // Clock Switching and Fail-Safe Clock Monitor Enable bits (Clock switching is enabled;
                               // Fail-safe clock monitor is enabled)
