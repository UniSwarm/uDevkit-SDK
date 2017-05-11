#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "archi.h"
//#include "board.h"

int main(void)
{
	unsigned int i, j;
    rt_dev_t uartDbg;
    char buff[200];

    sysclock_setClock(120000000);
    board_init();

    // warning keep this init order before remap support
    network_init();

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    j=0;
    while(1)
    {
        network_task();
        for(i=0;i<65000;i++);
    }

    return 0;
}
