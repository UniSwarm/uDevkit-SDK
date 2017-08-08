#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include <archi.h>

#include "board.h"

char led=0;
void tt()
{
}

int main(void)
{
#ifdef BOARD
    board_init();
#else
    archi_init();
#endif

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1000);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    while(1);

    return 0;
}
