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
