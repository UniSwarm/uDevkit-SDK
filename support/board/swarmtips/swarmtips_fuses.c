
// FGS
#pragma config GWRP = OFF  // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = OFF   // General Segment Code-Protect bit (General Segment Code protect is disabled)
#pragma config GSSK =                                                                                                  \
    OFF  // General Segment Key bits (General Segment Write Protection and Code Protection is Disabled)

// FOSCSEL
#pragma config FNOSC = FRCPLL  // Initial Oscillator Source Selection Bits (Internal Fast RC (FRC))
#pragma config IESO = ON  // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
#pragma config POSCMD = NONE   // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#pragma config OSCIOFNC = OFF  // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config IOL1WAY = ON    // Peripheral pin select configuration (Allow multiple reconfigurations)
#pragma config FCKSM =                                                                                                 \
    CSDCMD  // Clock Switching Mode bits (Clock switching is enabled,Fail-safe Clock Monitor is disabled)

// FWDT
#pragma config WDTPOST = PS32768  // Watchdog Timer Postscaler Bits (1:32,768)
#pragma config WDTPRE = PR128     // Watchdog Timer Prescaler bit (1:128)
#pragma config PLLKEN =                                                                                                \
    ON  // PLL Lock Wait Enable bit (Clock switch to PLL source will wait until the PLL lock signal is valid.)
#pragma config WINDIS = OFF  // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config FWDTEN = OFF  // Watchdog Timer Enable bit (Watchdog timer enabled/disabled by user software)

// FPOR
#pragma config FPWRT = PWR128  // Power-on Reset Timer Value Select bits (128ms)
#pragma config BOREN = ON      // Brown-out Reset (BOR) Detection Enable bit (BOR is enabled)
#pragma config ALTI2C1 = ON    // Alternate I2C pins for I2C1 (ASDA1/ASCK1 pins are selected as the I/O pins for I2C1)

// FICD
#pragma config ICS = PGD2    // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config RSTPRI = PF   // Reset Target Vector Select bit (Device will obtain reset instruction from Primary flash)
#pragma config JTAGEN = OFF  // JTAG Enable bit (JTAG is disabled)

// FAS
#pragma config AWRP = OFF  // Auxiliary Segment Write-protect bit (Auxiliary program memory is not write-protected)
#pragma config APL = OFF   // Auxiliary Segment Code-protect bit (Aux Flash Code protect is disabled)
#pragma config APLK = OFF  // Auxiliary Segment Key bits (Aux Flash Write Protection and Code Protection is Disabled)
