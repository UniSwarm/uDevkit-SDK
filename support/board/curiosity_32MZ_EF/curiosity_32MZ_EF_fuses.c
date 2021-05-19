
/*** DEVCFG0 ***/

#pragma config DEBUG = OFF
#pragma config JTAGEN = OFF
#pragma config ICESEL = ICS_PGx2
#pragma config TRCEN = OFF
#pragma config BOOTISA = MIPS32
#pragma config FECCCON = OFF_UNLOCKED
#pragma config FSLEEP = OFF
#pragma config DBGPER = PG_ALL
#pragma config SMCLR = MCLR_NORM
#pragma config SOSCGAIN = GAIN_LEVEL_3
#pragma config SOSCBOOST = ON
#pragma config POSCGAIN = GAIN_LEVEL_3
#pragma config POSCBOOST = ON
#pragma config EJTAGBEN = NORMAL
#pragma config CP = OFF

/*** DEVCFG1 ***/

#pragma config FNOSC = POSC
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
/*** DEVCFG2 ***/

#pragma config FPLLIDIV = DIV_3
#pragma config FPLLRNG = RANGE_13_26_MHZ
#pragma config FPLLICLK = PLL_POSC
#pragma config FPLLMULT = MUL_25
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ
/*** DEVCFG3 ***/

#pragma config USERID = 0xFFFF
#pragma config FMIIEN = OFF
#pragma config FETHIO = ON
#pragma config PGL1WAY = ON
#pragma config PMDL1WAY = ON
#pragma config IOL1WAY = ON
#pragma config FUSBIDIO = ON

/*** BF1SEQ0 ***/

#pragma config TSEQ = 0x0000
#pragma config CSEQ = 0xFFFF
