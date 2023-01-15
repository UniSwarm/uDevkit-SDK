/**
 * @file UMC4D30CRU_fuses.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date March 21, 2018, 20:00 PM
 *
 * @brief Code for UMC4D30CRU board (or UMC4D30CRU-I)
 */

// DEVCFG0
#pragma config DEBUG = OFF
#pragma config JTAGEN = OFF
#pragma config ICESEL = ICS_PGx2
#pragma config TRCEN = OFF
#pragma config BOOTISA = MIPS32
#pragma config FSLEEP = OFF
#pragma config DBGPER = PG_ALL
#pragma config SMCLR = MCLR_NORM
#pragma config SOSCGAIN = GAIN_2X
#pragma config SOSCBOOST = OFF
#pragma config POSCGAIN = GAIN_LEVEL_3
#pragma config POSCBOOST = ON
#pragma config EJTAGBEN = NORMAL
#pragma config CP = OFF

// DEVCFG1
#pragma config FNOSC = FRC
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
#pragma config FPLLIDIV = DIV_1
#pragma config FPLLRNG = RANGE_8_16_MHZ
#pragma config FPLLICLK = PLL_POSC
#pragma config FPLLMULT = MUL_40
#pragma config FPLLODIV = DIV_4
#pragma config VBATBOREN = ON
#pragma config DSBOREN = ON
#pragma config DSWDTPS = DSPS32
#pragma config DSWDTOSC = LPRC
#pragma config DSWDTEN = OFF
#pragma config FDSEN = ON
#pragma config BORSEL = HIGH
#pragma config UPLLEN = OFF

// DEVCFG3
#pragma config USERID = 0xffff
#pragma config PWMLOCK = OFF
#pragma config FUSBIDIO2 = OFF
#pragma config FVBUSIO2 = OFF
#pragma config PGL1WAY = OFF
#pragma config PMDL1WAY = OFF
#pragma config IOL1WAY = OFF
#pragma config FUSBIDIO1 = OFF
#pragma config FVBUSIO1 = OFF

// BF1SEQ0
#pragma config TSEQ = 0x0000
#pragma config CSEQ = 0xffff
