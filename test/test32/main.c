#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

char led=0;
void tt()
{
    board_setLed(1, led++);
}

int main(void)
{
    uint16_t i, j;
    rt_dev_t uartDbg, i2c_bus;
    uint16_t value;
    char buff[100];

    archi_init();
    //sysclock_setClock(200000000);
    sysclock_setClockDiv(SYSCLOCK_CLOCK_TIMER, 16);

    board_init();

    //board_setLed(1, 1);

    gui_init(0);

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1000);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    while(1)
    {
        value = uart_read(uartDbg, buff, 100);
        if(value>0)
            uart_write(uartDbg, buff, value);

        board_setLed(2, 1);
        for(j=0; j<20; j++) for(i=0; i<65000; i++);
        board_setLed(2, 0);
        for(j=0; j<20; j++) for(i=0; i<65000; i++);
    }

    return 0;
}
