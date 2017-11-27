#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "steppers.h"

extern void rest_api_exec(char *restUrl, HTTP_QUERRY_TYPE querry_type, char *buffer);
extern const Fs_FilesList file_list;

rt_dev_t uartLed;

void sendLed(uint8_t r, uint8_t g, uint8_t b, char *bufLed)
{
    uint32_t grb;
    uint8_t idLed;
    grb = (((uint32_t)g)<<16) + (((uint32_t)r)<<8) + b;

    for(idLed=0; idLed<12; idLed++)
    {
        bufLed[idLed] = 0x00;
        if((grb & 0x800000) == 0)
            bufLed[idLed] |= 0x07;
        if((grb & 0x400000) == 0)
            bufLed[idLed] |= 0xF0;
        grb = grb << 2;
    }
}

int main(void)
{
	unsigned int i,j;
	int16_t value;
	char buff[100];

	sysclock_setClock(60000000);
	board_init();

	// warning keep this init order before remap support
	network_init();
    web_server_setRestApi(rest_api_exec);
    web_server_setRootFS(&file_list);

    // uart debug init
    /*uartLed = uart_getFreeDevice();
    uart_setBaudSpeed(uartLed, 4000000);
    uart_setBitConfig(uartLed, 8, UART_BIT_PARITY_NONE, 1);
    U2STAbits.UTXINV = 1;
    uart_enable(uartLed);*/

    board_setLed(0, 1);
    for(j=0;j<2;j++) for(i=0;i<65000;i++);
    /*sendLed(64, 0, 128, buff);
    sendLed(0, 128, 64, buff+12);
    uart_write(uartLed, buff, 24);*/

	adc_init();
    steppers_init();

	for(j=0;j<2;j++) for(i=0;i<65000;i++);

	while(1)
	{
        network_task();

        value = VL6180X_getDistance(board_i2c_tof(), 0x52);
        if(value > 50)
        {
            board_setLed(1, 1);
            steppers_start();

            /*sendLed(128, 0, 0, buff);
            sendLed(0, 0, 0, buff+12);
            uart_write(uartLed, buff, 24);*/
        }
        else
        {
            board_setLed(1, 0);
            steppers_stop();

            /*sendLed(0, 0, 0, buff);
            sendLed(0, 0, 128, buff+12);
            uart_write(uartLed, buff, 24);*/
        }

		value = adc_getValue(BOARD_VOLT_IN);	// BOARD_VOLT_IN
	}

	return 0;
}
