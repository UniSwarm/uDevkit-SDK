#ifndef __SETUP_HEADER__
#define __SETUP_HEADER__

#include <xc.h>

void setup_clock();
void setup_io();

#define LED PORTDbits.RD11

#define M1A LATBbits.LATB14
#define M1B LATBbits.LATB15
#define M1en LATDbits.LATD0

#define M2A LATBbits.LATB12
#define M2B LATBbits.LATB13
#define M2en LATFbits.LATF3

#define M3A LATBbits.LATB8
#define M3B LATBbits.LATB9
#define M3en LATFbits.LATF4

#define M4A LATBbits.LATB10
#define M4B LATBbits.LATB11
#define M4en LATFbits.LATF5

#endif   //__SETUP_HEADER__