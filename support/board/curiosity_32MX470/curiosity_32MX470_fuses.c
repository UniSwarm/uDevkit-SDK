/**
 * @file curiosity_32MX470_fuses.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date July 25, 2017, 11:20 AM
 *
 * @brief Fuses for Curiosity 32MX470 board (DM320103)
 */

// DEVCFG0
#pragma config DEBUG = OFF
#pragma config JTAGEN = OFF
#pragma config ICESEL = ICS_PGx2
#pragma config PWP = OFF
#pragma config BWP = OFF
#pragma config CP = OFF

// DEVCFG1
#pragma config FNOSC = PRI  // PRIPLL
#pragma config FSOSCEN = OFF
#pragma config IESO = ON
#pragma config POSCMOD = HS
#pragma config OSCIOFNC = OFF
#pragma config FPBDIV = DIV_2
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS1048576
#pragma config FWDTEN = OFF
#pragma config WINDIS = OFF
#pragma config FWDTWINSZ = WINSZ_25

// DEVCFG2
#pragma config FPLLIDIV = DIV_5
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1
#pragma config UPLLIDIV = DIV_5
#pragma config UPLLEN = ON

// DEVCFG3
#pragma config USERID = 0xFFFF
#pragma config FSRSSEL = PRIORITY_7
#pragma config PMDL1WAY = ON
#pragma config IOL1WAY = ON
#pragma config FUSBIDIO = ON
#pragma config FVBUSONIO = ON
