/**
 * @file udt1cr-i.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date November 26, 2018, 18:00 PM
 *
 * @brief Fuses configuration for UDT1FR from UniSwarm
 *
 * product page:
 *  https://uniswarm.fr/uboards/udt/udt1fr
 */

// DEVCFG0
#pragma config DEBUG = OFF
#pragma config JTAGEN = OFF
#pragma config ICESEL = ICS_PGx1
#pragma config TRCEN = OFF
#pragma config BOOTISA = MIPS32
#pragma config FECCCON = OFF_UNLOCKED
#pragma config FSLEEP = OFF
#pragma config DBGPER = PG_ALL
#pragma config SMCLR = MCLR_NORM
#pragma config SOSCGAIN = GAIN_1X
#pragma config SOSCBOOST = OFF
#pragma config POSCGAIN = GAIN_1X
#pragma config POSCBOOST = ON
#pragma config EJTAGBEN = NORMAL
#pragma config CP = ON

// DEVCFG1
#pragma config FNOSC = SPLL
#pragma config DMTINTV = WIN_127_128
#pragma config FSOSCEN = OFF
#pragma config IESO = OFF
#pragma config POSCMOD = EC
#pragma config OSCIOFNC = OFF
#pragma config FCKSM = CSECME
#pragma config WDTPS = PS1048576
#pragma config WDTSPGM = STOP
#pragma config FWDTEN = OFF
#pragma config WINDIS = NORMAL
#pragma config FWDTWINSZ = WINSZ_25
#pragma config DMTCNT = DMT31
#pragma config FDMTEN = OFF

// DEVCFG2
#pragma config FPLLIDIV = DIV_3
#pragma config FPLLRNG = RANGE_5_10_MHZ
#pragma config FPLLICLK = PLL_POSC
#pragma config FPLLMULT = MUL_50
#pragma config FPLLODIV = DIV_4
#pragma config UPLLFSEL = FREQ_24MHZ

// DEVCFG3
#pragma config USERID = 0xffff
#pragma config FMIIEN = OFF
#if BOARD_VERSION < 110
#    pragma config FETHIO = OFF
#else
#    pragma config FETHIO = ON
#endif
#pragma config PGL1WAY = OFF
#pragma config PMDL1WAY = OFF
#pragma config IOL1WAY = OFF
#pragma config FUSBIDIO = OFF

// BF1SEQ0
#pragma config TSEQ = 0x0000
#pragma config CSEQ = 0xffff
