/**
 * @file motor_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date avril 28, 2016, 14:40  
 * 
 * @brief Support for motors control
 */
 
#include <xc.h>

#include "motor.h"
#include "driver/adc.h"
#include "board.h"

// <TODO replace theses functions by pwm support
void setup_PWM1(void)
{
	M1A=0;
	M1B=0;
	OC1CON1 = 0b0001110000000110;
	OC1CON2 = 0b0000000000011111;
	OC1R = 0;
	OC1RS = 1500;	// 20kz
}

void setup_PWM2(void)
{
	M2A=0;
	M2B=0;
	OC2CON1 = 0b0001110000000110;
	OC2CON2 = 0b0000000000011111;
	OC2R = 0;
	OC2RS = 1500;	// 20kz
}

void setup_PWM3(void)
{
	M3A=0;
	M3B=0;
	OC3CON1 = 0b0001110000000110;
	OC3CON2 = 0b0000000000011111;
	OC3R = 0;
	OC3RS = 1500;	// 20kz
}

void setup_PWM4(void)
{
	M4A=0;
	M4B=0;
	OC4CON1 = 0b0001110000000110;
	OC4CON2 = 0b0000000000011111;
	OC4R = 0;
	OC4RS = 1500;	// 20kz
}
// TODO/>

int motor_init()
{
	setup_PWM1();
	setup_PWM2();
	setup_PWM3();
	setup_PWM4();
	
	return 0;
}

int motor_setPower(uint8_t motor, int16_t power)
{
	int16_t pwm = power;
	if(pwm>1500)  pwm = 1500;
	if(pwm<-1500) pwm = -1500;
	
	switch(motor)
	{
	case 1:
		if(pwm>0)
		{
			M1A=0;
			M1B=1;
			OC1R = pwm;
		}
		else
		{
			M1A=1;
			M1B=0;
			OC1R = -pwm;
		}
		break;
	case 2:
		if(pwm>0)
		{
			M2A=0;
			M2B=1;
			OC2R = pwm;
		}
		else
		{
			M2A=1;
			M2B=0;
			OC2R = -pwm;
		}
		break;
	case 3:
		if(pwm>0)
		{
			M3A=0;
			M3B=1;
			OC3R = pwm;
		}
		else
		{
			M3A=1;
			M3B=0;
			OC3R = -pwm;
		}
		break;
	case 4:
		if(pwm>0)
		{
			M4A=0;
			M4B=1;
			OC4R = pwm;
		}
		else
		{
			M4A=1;
			M4B=0;
			OC4R = -pwm;
		}
		break;
	default:
		return -1;
	}
	
	return 0;
}

int16_t motor_getCurrent(uint8_t motor)
{
	int8_t channel;
	int16_t value;
	
	switch(motor)
	{
	case 1:
		channel = M1I;
		break;
	case 2:
		channel = M2I;
		break;
	case 3:
		channel = M3I;
		break;
	case 4:
		channel = M4I;
		break;
	default:
		return -1;
	}
	
	value = adc_getValue(channel);
	return (value * 13) >> 1;
}
