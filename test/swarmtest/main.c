#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "modules.h"
#include "board.h"
#include "archi.h"

#include "driver/motor.h"

#define MMAX  1200
#define MMAX2 800

void setup_PWM(void)
{
	OC1CON1 = 0b0001110000000110;
	OC1CON2 = 0b0000000000011111;
	OC1R = 0;
	OC1RS = 1500;	// 20kz

	OC2CON1 = 0b0001110000000110;
	OC2CON2 = 0b0000000000011111;
	OC2R = 0;
	OC2RS = 1500;	// 20kz

	OC3CON1 = 0b0001110000000110;
	OC3CON2 = 0b0000000000011111;
	OC3R = 0;
	OC3RS = 1500;	// 20kz

	OC4CON1 = 0b0001110000000110;
	OC4CON2 = 0b0000000000011111;
	OC4R = 0;
	OC4RS = 1500;	// 20kz
}

void setM1A(short v)
{
    if(v >= 0)
    {
        OC1R = v;
        OC1CON2bits.OCINV = 0;
        M1A = 0;
    }
    else
    {
        OC1R = -v;
        OC1CON2bits.OCINV = 1;
        M1A = 1;
    }
}
void setM1B(short v)
{
    if(v >= 0)
    {
        OC2R = v;
        OC2CON2bits.OCINV = 0;
        M1B = 0;
    }
    else
    {
        OC2R = -v;
        OC2CON2bits.OCINV = 1;
        M1B = 1;
    }
}

void setM2A(short v)
{
    if(v >= 0)
    {
        OC3R = v;
        OC3CON2bits.OCINV = 0;
        M2A = 0;
    }
    else
    {
        OC3R = -v;
        OC3CON2bits.OCINV = 1;
        M2A = 1;
    }
}
void setM2B(short v)
{
    if(v >= 0)
    {
        OC4R = v;
        OC4CON2bits.OCINV = 0;
        M2B = 0;
    }
    else
    {
        OC4R = -v;
        OC4CON2bits.OCINV = 1;
        M2B = 1;
    }
}

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

void stepper_handler()
{
    static uint8_t step = 0;
    switch(step)
    {
    case 0:
        board_setLed(0, 0);
        setM1A(MMAX2);
        setM1B(MMAX2);
        setM2A(MMAX2);
        setM2B(MMAX2);
        break;

    case 1:
        setM1A(0);
        setM1B(MMAX);
        setM2A(0);
        setM2B(MMAX);
        break;

    case 2:
        setM1A(-MMAX2);
        setM1B(MMAX2);
        setM2A(-MMAX2);
        setM2B(MMAX2);
        break;

    case 3:
        setM1A(-MMAX);
        setM1B(0);
        setM2A(-MMAX);
        setM2B(0);
        break;

    case 4:
        board_setLed(0, 1);
        setM1A(-MMAX2);
        setM1B(-MMAX2);
        setM2A(-MMAX2);
        setM2B(-MMAX2);
        break;

    case 5:
        setM1A(0);
        setM1B(-MMAX);
        setM2A(0);
        setM2B(-MMAX);
        break;

    case 6:
        setM1A(MMAX2);
        setM1B(-MMAX2);
        setM2A(MMAX2);
        setM2B(-MMAX2);
        break;

    case 7:
        setM1A(MMAX);
        setM1B(0);
        setM2A(MMAX);
        setM2B(0);
        break;
    }

    step++;
    if(step>=8)
        step=0;
}

int main(void)
{
	unsigned int i,j;
	uint16_t value;
	char buff[100];
    rt_dev_t stepper_timer;
    rt_dev_t i2c, vlx;

	sysclock_setClock(120000000);
	board_init();

	// warning keep this init order before remap support
	esp_init();

    // uart debug init
    uartLed = uart_getFreeDevice();
    uart_setBaudSpeed(uartLed, 4000000);
    uart_setBitConfig(uartLed, 8, UART_BIT_PARITY_NONE, 1);
    U2STAbits.UTXINV = 1;
    uart_enable(uartLed);

    board_setLed(1, 1);
    for(j=0;j<2;j++) for(i=0;i<65000;i++);
    /*sendLed(64, 0, 128, buff);
    sendLed(0, 128, 64, buff+12);
    uart_write(uartLed, buff, 24);*/

	adc_init();

    setup_PWM();

    // stepper
    stepper_timer = timer_getFreeDevice();
    timer_setPeriodMs(stepper_timer, 1000);
    timer_setHandler(stepper_timer, stepper_handler);
    timer_enable(stepper_timer);

    i2c = i2c_getFreeDevice();
    i2c_setBaudSpeed(i2c, I2C_BAUD_400K);
    i2c_enable(i2c);

	for(j=0;j<2;j++) for(i=0;i<65000;i++);
    // setup VL6180X
    vlx = VL6180X_init(i2c, 0x52);

	for(j=0;j<2;j++) for(i=0;i<65000;i++);

	// uart debug init
	uartLed = uart_getFreeDevice();
	uart_setBaudSpeed(uartLed, 115200);
	uart_setBitConfig(uartLed, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartLed);

	while(1)
	{
        value = VL6180X_getDistance(i2c, 0x52);
        if(value > 50)
        {
            board_setLed(1, 1);
            timer_enable(stepper_timer);

            sendLed(128, 0, 0, buff);
            sendLed(0, 0, 0, buff+12);
            uart_write(uartLed, buff, 24);
        }
        else
        {
            board_setLed(1, 0);
            timer_disable(stepper_timer);

            sendLed(0, 0, 0, buff);
            sendLed(0, 0, 128, buff+12);
            uart_write(uartLed, buff, 24);
        }

		value = adc_getValue(BOARD_VOLT_IN);	// BOARD_VOLT_IN
		sprintf(buff, "value: %dv", value);

		uart_write(uartLed, buff, strlen(buff)+1);

		value = uart_read(uartLed, buff, 100);
		if(value>0)
			uart_write(uartLed, buff, value);
	}

	return 0;
}
