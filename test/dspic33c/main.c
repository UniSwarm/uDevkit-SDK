#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#ifdef SIMULATOR
    unsigned char *dspic33c_slave;
#else
    #include "dspic33c_slave.h"
    //extern __eds__ unsigned char *dspic33c_slave;
#endif

char led=0;
void tt()
{
    board_toggleLed(0);
}

int main(void)
{
    uint16_t i, j;
    rt_dev_t uartDbg;
    uint16_t value;
    char buff[100];

    sysclock_switchSourceTo(SYSCLOCK_SRC_POSC);
    board_init();
    sysclock_setPLLClock(80000000, SYSCLOCK_SRC_POSC);

#ifndef SIMULATOR
    _RP66R = 0b001110;
    REFOCONHbits.RODIV = 5; // /10
    REFOCONLbits.ROSEL = 0b0001; // Fp (FOSC/2)
    REFOCONLbits.ROEN = 1;
    REFOCONLbits.ROOUT = 1;
#endif

    msi_slave_program(1, dspic33c_slave);
    msi_slave_start(1);

    //T1CONbits.TECS = 0b10;
    //T1CONbits.TON = 1;
    //PR1 = 0xFFFF;

    //sysclock_setClock(200000000);
    //sysclock_setClockDiv(SYSCLOCK_CLOCK_TIMER, 16);
    //sysclock_setClockDiv(SYSCLOCK_CLOCK_UART, 16);

    // uart debug init
    uartDbg = uart(2);
    uart_open(uartDbg);
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    cmdline_init();
    cmdline_setDevice(uartDbg, uartDbg);

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 2);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    enable_interrupt();

    while(1)
    {
        #ifdef SIMULATOR
            usleep(1000);
        #endif

        cmdline_task();

        //board_setLed(0, 1);
        //uart_write(uartDbg, "Led ON", 6);
        for(j=0; j<5; j++) for(i=0; i<65000; i++);

        //board_setLed(0, 0);
        //uart_write(uartDbg, "Led OFF", 7);
        for(j=0; j<5; j++) for(i=0; i<65000; i++);
    }

    return 0;
}
