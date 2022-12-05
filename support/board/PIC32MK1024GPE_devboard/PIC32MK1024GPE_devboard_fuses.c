/**
 * @file PIC32MK1024GPE_devboard_fuses.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date October 25, 2017, 17:13 AM
 *
 * @brief Fuses for PIC32MK1024GPE dev board board (DM320106)
 */

// DEVCFG0
#pragma config DEBUG = OFF
#pragma config JTAGEN = OFF
#pragma config ICESEL = ICS_PGx1
#pragma config TRCEN = OFF
#pragma config BOOTISA = MIPS32
#pragma config FSLEEP = OFF
#pragma config DBGPER = PG_ALL
#pragma config SMCLR = MCLR_NORM
#pragma config SOSCGAIN = GAIN_2X
#pragma config SOSCBOOST = ON
#pragma config POSCGAIN = GAIN_LEVEL_3
#pragma config POSCBOOST = ON
#pragma config EJTAGBEN = NORMAL
#pragma config CP = OFF

// DEVCFGG1
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
#pragma config FUSBIDIO2 = ON
#pragma config FVBUSIO2 = ON
#pragma config PGL1WAY = ON
#pragma config PMDL1WAY = ON
#pragma config IOL1WAY = ON
#pragma config FUSBIDIO1 = ON
#pragma config FVBUSIO1 = ON

// BF1SEQ0
#pragma config TSEQ = 0x0000
#pragma config CSEQ = 0xffff
