#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

char led=0;
void tt()
{
    board_toggleLed(1);
}

int main(void)
{
    uint16_t i, j;
    uint16_t value;
    char buff[100];

    sysclock_switchSourceTo(SYSCLOCK_SRC_POSC);
    board_init();
    //sysclock_setPLLClock(80000000, SYSCLOCK_SRC_POSC);

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    // Configure the source clock for the APLL
    ACLKCON1bits.FRCSEL = 0;
    // Select internal POSC as the clock source
    // Configure the APLL prescaler, APLL feedback divider, and both APLL postscalers.
    ACLKCON1bits.APLLPRE = 1;
    // N1 = 1
    APLLFBD1bits.APLLFBDIV = 125;
    // M = 125
    APLLDIV1bits.APOST1DIV = 2;
    // N2 = 2
    APLLDIV1bits.APOST2DIV = 1;
    // N3 = 1
    // Enable APLL
    ACLKCON1bits.APLLEN = 1;

    PCLKCONbits.DIVSEL = 0b00; // 1/2 clock div
    //PCLKCONbits.MCLKSEL = 0b00; // Clock sel = Fosc
    PCLKCONbits.MCLKSEL = 0b11; // AFPLL
    
    MPHASE = 0;      // Master phase
    MPER = 0xFFF8;   // Master period
    MDC = 0x8000;    // Master duty cycle

    // PG1
    PG1CONLbits.CLKSEL = 0b10;  // PWM Generator uses Master clock divided by clock divider circuit
    PG1CONLbits.MODSEL = 0b000; // Independent Edge PWM mode
    PG1CONLbits.HREN = 1; // High-Resolution Enable bit
    PG1CONHbits.MDCSEL = 0;     // 1 - Use  master duty cycle, own one
    PG1CONHbits.MPERSEL = 1;    // 1 - Use  master period, own one
    PG1CONHbits.MPHSEL = 0;     // 1 - Use  master phase, own one
    PG1DC = 0x4000;    // PG1 duty cycle, > 0x0020 /!!!!
    PG1PHASE = 0x0000; // PG1 phase
    //PG1DTL = 20; // 10ns
    //PG1DTH = 100;

    // IOs
    PG1IOCONLbits.SWAP = 0; // not swapped
    PG1IOCONLbits.OVRENH = 0; // PWM1H not overwritten
    PG1IOCONLbits.OVRENL = 0; // PWM1L not overwritten
    PG1IOCONLbits.OVRDAT = 0b00; // overwritten data
    PG1IOCONLbits.FLTDAT = 0b00; // fault data
    PG1IOCONLbits.CLDAT = 0b00;  // current limit data
    PG1IOCONLbits.FFDAT = 0b00;  // feed-forward data
    PG1IOCONLbits.DBDAT = 0b00;  // debug data
    PG1IOCONHbits.PMOD = 0b00; // Complementary mode
    PG1IOCONHbits.PENH = 1;    // PWMH active
    PG1IOCONHbits.PENL = 1;    // PWML active
    PG1IOCONHbits.POLH = 0;    // PWMH polarity non inversed
    PG1IOCONHbits.POLL = 0;    // PWML polarity non inversed

    PG1CONLbits.ON = 1;

    // PG2
    PG2CONLbits.CLKSEL = 0b10;  // PWM Generator uses Master clock divided by clock divider circuit
    PG2CONLbits.MODSEL = 0b000; // Independent Edge PWM mode
    PG2CONLbits.HREN = 1; // High-Resolution Enable bit
    PG2CONHbits.MDCSEL = 0;     // 1 - Use  master duty cycle, own one
    PG2CONHbits.MPERSEL = 1;    // 1 - Use  master period, own one
    PG2CONHbits.MPHSEL = 0;     // 1 - Use  master phase, own one
    PG2DC = 0x4001;    // PG2 duty cycle, > 0x0020 /!!!!
    PG2PHASE = 0x0000; // PG2 phase

    // IOs
    PG2IOCONLbits.SWAP = 0; // not swapped
    PG2IOCONLbits.OVRENH = 0; // PWM1H not overwritten
    PG2IOCONLbits.OVRENL = 0; // PWM1L not overwritten
    PG2IOCONLbits.OVRDAT = 0b00; // overwritten data
    PG2IOCONLbits.FLTDAT = 0b00; // fault data
    PG2IOCONLbits.CLDAT = 0b00;  // current limit data
    PG2IOCONLbits.FFDAT = 0b00;  // feed-forward data
    PG2IOCONLbits.DBDAT = 0b00;  // debug data
    PG2IOCONHbits.PMOD = 0b00; // Complementary mode
    PG2IOCONHbits.PENH = 1;    // PWMH active
    PG2IOCONHbits.PENL = 1;    // PWML active
    PG2IOCONHbits.POLH = 0;    // PWMH polarity non inversed
    PG2IOCONHbits.POLL = 0;    // PWML polarity non inversed

    PG2CONLbits.ON = 1;
    
    enable_interrupt();

    while(1)
    {
        #ifdef SIMULATOR
            usleep(1000);
        #endif

        //board_setLed(0, 1);
        //uart_write(uartDbg, "Led ON", 6);
        for(j=0; j<5; j++) for(i=0; i<65000; i++);

        //board_setLed(0, 0);
        //uart_write(uartDbg, "Led OFF", 7);
        for(j=0; j<5; j++) for(i=0; i<65000; i++);
    }

    return 0;
}
