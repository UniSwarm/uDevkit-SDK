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

int main(void)
{
	unsigned int i,j;
	rt_dev_t uartDbg;
	uint16_t value;
	char buff[100];
	
	setSystemClock(120000000);
	init_board();
	
	// warning keep this init order before remap support
	esp_init();
    LED2 = 1;
    
	adc_init();
    
    setup_PWM();
	
	// uart debug init
	uartDbg = uart_getFreeDevice();
	uart_setBaudSpeed(uartDbg, 115200);
	uart_setBitConfig(uartDbg, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(uartDbg);
	
	while(1)
	{
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
		LED = 0;
        setM1A(MMAX2);
        setM1B(MMAX2);
        setM2A(MMAX2);
        setM2B(MMAX2);
        
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        setM1A(0);
        setM1B(MMAX);
        setM2A(0);
        setM2B(MMAX);
        
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        setM1A(-MMAX2);
        setM1B(MMAX2);
        setM2A(-MMAX2);
        setM2B(MMAX2);
        
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        setM1A(-MMAX);
        setM1B(0);
        setM2A(-MMAX);
        setM2B(0);
        
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
		LED = 1;
        setM1A(-MMAX2);
        setM1B(-MMAX2);
        setM2A(-MMAX2);
        setM2B(-MMAX2);
        
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        setM1A(0);
        setM1B(-MMAX);
        setM2A(0);
        setM2B(-MMAX);
		
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        setM1A(MMAX2);
        setM1B(-MMAX2);
        setM2A(MMAX2);
        setM2B(-MMAX2);
        
		for(j=0;j<5;j++) for(i=0;i<65000;i++);
        setM1A(MMAX);
        setM1B(0);
        setM2A(MMAX);
        setM2B(0);
        
		value = adc_getValue(BOARD_VOLT_IN);	// BOARD_VOLT_IN
		sprintf(buff, "value: %dv", value);

		uart_write(uartDbg, buff, strlen(buff)+1);
		
		value = uart_read(uartDbg, buff, 100);
		if(value>0)
			uart_write(uartDbg, buff, value);
	}
	
	return 0;
}
