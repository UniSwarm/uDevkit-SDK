#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "modules.h"
#include <archi.h>

#include <board.h>

#include <module/cmdline.h>

void timer_handler(void)
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
    // sysclock_setClock(20000000);
    // sysclock_setClockDiv(SYSCLOCK_CLOCK_TIMER, 32);
    // sysclock_setPLLClock(40000000, SYSCLOCK_SRC_POSC);
    // sysclock_setPLLClock(160000000, SYSCLOCK_SRC_POSC);
    // sysclock_setPLLClock(120000000, SYSCLOCK_SRC_POSC);
    // sysclock_setPLLClock(40000000, SYSCLOCK_SRC_POSC);
    // sysclock_switchSourceTo(SYSCLOCK_SRC_SPLL);
    sysclock_setClock(20000000);

#if defined(USE_adc) & ADC_CHANNEL_COUNT >= 1
    adc_init();
#endif

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 500);
    timer_setHandler(timer, timer_handler);
    timer_enable(timer);

    // uart debug init
    uartDbg = uart(UART_DGB_ID);
    uart_open(uartDbg);
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);

#if QEI_COUNT >= 1
    rt_dev_t qei1 = qei(1);
    qei_open(qei1);
    qei_enable(qei1);
#endif

#ifdef USE_MODULE_cmdline
    // console init
    cmdline_setDevice(uartDbg, uartDbg);
    cmdline_init();
#endif  // USE_MODULE_cmdline
    uart_write(uartDbg, "TEST\n", 5);

    enable_interrupt();

    while (1)
    {
#ifdef USE_MODULE_cmdline
        cmdline_task();
#endif  // USE_MODULE_cmdline

#ifdef BOARD
        board_setLed(1, board_getButton(0));
#endif
    }

    return 0;
}
