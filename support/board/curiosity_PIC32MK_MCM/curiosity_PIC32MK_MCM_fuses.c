/**
 * @file curiosity_PIC32MK_MCM_fuses.c
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
 *
 * @date December 5, 2022, 09:53 PM
 *
 * @brief Fuses for Curiosity PIC32MK MCM board (EV31E34A)
 */

// DEVCFG0
#pragma config DEBUG = OFF                                ///> Background Debugger Disabled (Debugger is disabled)
#pragma config JTAGEN = OFF                               ///> JTAG Enable (JTAG Port disabled)
#pragma config ICESEL = ICS_PGx3                          ///> ICE/ICD Comm Channel Select (Communicate on PGEC3/PGED3)
#pragma config TRCEN = OFF                                ///> Trace Disabled (Trace features in the CPU are disabled)
#pragma config BOOTISA = MIPS32                           ///> Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = ECC_DECC_DISABLE_ECCON_WRITABLE  ///> Dynamic Flash ECC Configuration Bits (ECC and Dynamic ECC are disabled)
#pragma config FSLEEP = OFF                               ///> Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = PG_ALL                            ///> Debug Mode CPU Access Permission (Allow CPU access to all permission regions)
#pragma config SMCLR = MCLR_NORM                          ///> Soft Master Clear Enable (MCLR pin generates a normal system Reset)
#pragma config SOSCGAIN = G3                              ///> Secondary Oscillator Gain Control bits (Gain is G3)
#pragma config SOSCBOOST = ON                             ///> Secondary Oscillator Boost Kick Start Enable bit (Boost the kick start of the oscillator)
#pragma config POSCGAIN = G3                              ///> Primary Oscillator Coarse Gain Control bits (Gain Level 3 (highest))
#pragma config POSCBOOST = ON                             ///> Primary Oscillator Boost Kick Start Enable bit (Boost the kick start of the oscillator)
#pragma config POSCFGAIN = G3                             ///> Primary Oscillator Fine Gain Control bits (Gain is G3)
#pragma config POSCAGCDLY = AGCRNG_x_25ms                 ///> AGC Gain Search Step Settling Time Control (Settling time = 25ms x AGCRNG)
#pragma config POSCAGCRNG = ONE_X                         ///> AGC Lock Range bit (Range 1x)
#pragma config POSCAGC = Automatic                        ///> Primary Oscillator Gain Control bit (Automatic Gain Control for Oscillator)
#pragma config EJTAGBEN = NORMAL                          ///> EJTAG Boot Enable (Normal EJTAG functionality)

// DEVCFG1
#pragma config FNOSC = FRC            ///> Oscillator Selection Bits (Internal Fast RC (FRC))
#pragma config DMTINTV = WIN_127_128  ///> DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = ON           ///> Secondary Oscillator Enable (Enable Secondary Oscillator)
#pragma config IESO = OFF             ///> Internal/External Switch Over (Disabled)
#pragma config POSCMOD = EC           ///> Primary Oscillator Configuration (External clock mode)
#pragma config OSCIOFNC = OFF         ///> CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSECME         ///> Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576      ///> Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP         ///> Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL        ///> Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF           ///> Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25   ///> Watchdog Timer Window Size (Window size is 25%)
#pragma config DMTCNT = DMT31         ///> Deadman Timer Count Selection (2^31 (2147483648))
#pragma config FDMTEN = OFF           ///> Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1          ///> System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ  ///> System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC        ///> System PLL Input Clock Selection (FRC is input to the System PLL)
#pragma config FPLLMULT = MUL_1          ///> System PLL Multiplier (PLL Multiply by 1)
#pragma config FPLLODIV = DIV_2          ///> System PLL Output Clock Divider (2x Divider)
#pragma config BORSEL = HIGH             ///> Brown-out trip voltage (BOR trip voltage 2.1v (Non-OPAMP deviced operation))
#pragma config UPLLEN = OFF              ///> USB PLL Enable (USB PLL Disabled)

// DEVCFG3
#pragma config USERID = 0xFFFF  ///> Enter Hexadecimal value (Enter Hexadecimal value)
#pragma config PWMLOCK = OFF    ///> PWM IOxCON lock (PWM IOxCON register writes accesses are not locked or protected)
#pragma config FUSBIDIO2 = OFF  ///> USB2 USBID Selection (USBID pin is controlled by the port function)
#pragma config FVBUSIO2 = OFF   ///> USB2 VBUSON Selection bit (VBUSON pin is controlled by the port function)
#pragma config PGL1WAY = OFF    ///> Permission Group Lock One Way Configuration bit (Allow multiple reconfigurations)
#pragma config PMDL1WAY = OFF   ///> Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = OFF    ///> Peripheral Pin Select Configuration (Allow multiple reconfigurations)
#pragma config FUSBIDIO1 = OFF  ///> USB1 USBID Selection (USBID pin is controlled by the port function)
#pragma config FVBUSIO1 = OFF   ///> USB2 VBUSON Selection bit (VBUSON pin is controlled by the port function)

// BF1SEQ
#pragma config TSEQ = 0x0
#pragma config CSEQ = 0xffff
