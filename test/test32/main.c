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

    // Prefetch-cache: Enable prefetch for PFM (any PFM instructions or data)
    PRECONbits.PREFEN = 3;
    // Flash PM Wait States: MZ Flash runs at 2 wait states @ 200 MHz
    PRECONbits.PFMWS = 2;
    //sysclock_setClock(120000000);
    board_init();

    //board_setLed(1, 1);

    gui_init();

    // uart debug init
    /*uartDbg = uart_getFreeDevice();
    uart_setBaudSpeed(uartDbg, 115200);
    uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(uartDbg);*/

    for(j=0; j<10; j++)
    {
        memset(buff, 0, 16);
        i2c_writeregs(i2c_bus, OLED_I2C_ADDR, 0x40, buff, 16, 0);
        memset(buff, 255, 16);
        i2c_writeregs(i2c_bus, OLED_I2C_ADDR, 0x40, buff, 16, 0);
    }
    for(j=0; j<32; j++)
    {
        memset(buff, 0, 16);
        i2c_writeregs(i2c_bus, OLED_I2C_ADDR, 0x40, buff, 16, 0);
    }

    // init timer
    rt_dev_t timer;
    timer = timer_getFreeDevice();
    timer_setPeriodMs(timer, 1000);
    timer_setHandler(timer, tt);
    timer_enable(timer);

    INTCONSET = _INTCON_MVEC_MASK;
    PRISS = 0x76543210;
    enable_interrupt();

    while(1)
    {
        /*value = uart_read(uartDbg, buff, 100);
        if(value>0)
            uart_write(uartDbg, buff, value);*/

        board_setLed(2, 1);
        for(j=0; j<20; j++) for(i=0; i<65000; i++);
        board_setLed(2, 0);
        for(j=0; j<20; j++) for(i=0; i<65000; i++);
    }

    return 0;
}
