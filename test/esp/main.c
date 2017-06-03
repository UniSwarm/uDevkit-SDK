#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "archi.h"
#include "board.h"

extern void rest_api_exec(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer);

int main(void)
{
#ifndef SIMULATOR
    unsigned int i;
#endif
    rt_dev_t uartDbg;

    sysclock_setClock(120000000);
    board_init();

    // warning keep this init order before remap support
    network_init();
    web_server_setRestApi(rest_api_exec);

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    while(1)
    {
        network_task();
        
        #ifdef SIMULATOR
            usleep(1000);
        #else
            for(i=0;i<65000;i++);
        #endif
    }

    return 0;
}
