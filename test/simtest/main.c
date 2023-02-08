#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "archi.h"
#include "board.h"
#include "modules.h"

void tt()
{
    puts("tt");
}

int main(void)
{
    unsigned int i, j;
    rt_dev_t uartDbg;
    float f = 0.23;
    uint16_t value;
    char buff[100];

    rt_dev_t asserv_timer;

    sysclock_setClock(120000000);
    board_init();

    // uart debug init
    uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

    // timer
    asserv_timer = timer_getFreeDevice();
    timer_setPeriodMs(asserv_timer, 1000);
    timer_setHandler(asserv_timer, tt);
    timer_enable(asserv_timer);

    // gui
    gui_init(0);
    gui_drawRect(20, 20, 50, 100);

    while (1)
    {
        for (j = 0; j < 100; j++)
        {
            for (i = 0; i < 65000; i++)
            {
                f = sqrt(f);
            }
        }
        // LED = 0;
        printf("LED 0\n");
        fflush(stdout);
        uart_write(uartDbg, "LED 0\n", 6);

        for (j = 0; j < 100; j++)
        {
            for (i = 0; i < 65000; i++)
            {
                f = sqrt(f);
            }
        }
        // LED = 1;
        printf("LED 1\n");
        fflush(stdout);
        uart_write(uartDbg, "LED 1\n", 6);

        value = uart_read(uartDbg, buff, 100);
        if (value > 0)
        {
            uart_write(uartDbg, buff, value);
        }
    }

    return 0;
}
