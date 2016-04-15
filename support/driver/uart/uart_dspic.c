/**
 * @file uart_dspic.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 13, 2016, 11:49 AM 
 * 
 * @brief Uart support for rtprog
 */

#include <stdint.h>

#include "uart_dspic.h"

#if UART_COUNT==1
 const struct UART *uarts[1]={U1MODE};
#elif UART_COUNT==2
 const struct UART *uarts[2]={U1MODE, U2MODE};
#elif UART_COUNT==3
 const struct UART *uarts[3]={U1MODE, U2MODE, U3MODE};
#elif UART_COUNT==4
 const struct UART *uarts[4]={U1MODE, U2MODE, U3MODE, U4MODE};
#else
 #error No device
#endif

int uart_enable(uint8_t device)
{
	if(device>UART_COUNT)
		return -1;
	
	uarts[device].uxmode.UARTEN = 1;
}
