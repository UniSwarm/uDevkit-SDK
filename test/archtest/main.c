#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include <archi.h>

#include "board.h"

char led=0;
void tt()
{
#ifdef BOARD
    board_toggleLed(0);
#endif
}

int main(void)
{
    rt_dev_t uartDbg;

#ifdef BOARD
    board_init();
#else
    archi_init();
#endif
    enable_interrupt();
    //sysclock_setClock(20000000);
    //sysclock_setClockDiv(SYSCLOCK_CLOCK_TIMER, 32);

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 500);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    // uart debug init
    uartDbg = uart(2);
    uart_open(uartDbg);
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);
    
    
#if QEI_COUNT>=1
    rt_dev_t qei1 = qei(0);
    qei_open(qei1);
    qei_enable(qei1);
#endif

    // console init
    //cmdline_init();
    //cmdline_setDevice(uartDbg, uartDbg);

    while(1)
    {
        //cmdline_task();
    #ifdef BOARD
        board_setLed(1, board_getButton(0));
    #endif
    }

    return 0;
}
