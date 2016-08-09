/**
 * @file ax12.h
 * @author Sebastien CAUX (sebcaux) / Charles-Antoine NOURY (CharlyBigoud)
 * @copyright Robotips 2016
 *
 * @date April 16, 2016, 14:41 PM 
 * 
 * @brief AX12 servomotor support
 */

#include "ax12.h"

#include "driver/uart.h"
//#include <xc.h>
#include "board.h"

//uint8_t idr=255;
//uint8_t buffr[30];
uint8_t trame[20];
rt_dev_t ax12_uart;

/**
 * @brief Set the device the send mode
 */
void ax12_sendMode()
{
    //AX12_TXEN = 0;
    //idr=0;
}

/**
 * @brief Set the device to receive mode
 */
void ax12_receiveMode()
{
    //idr = 0;
    //AX12_TXEN = 0;
}

/**
 * @brief Setup the device
 */
void ax12_init(void)
{
	ax12_uart = uart_getFreeDevice();
	uart_setBaudSpeed(ax12_uart, 1000000);
	uart_setBitConfig(ax12_uart, 8, UART_BIT_PARITY_NONE, 1);
	uart_enable(ax12_uart);
}

/**
 * @brief Send a char (8 bits) to the specified device
 * @param ax_id the device address
 * @param param
 * @param val
 */
void ax12_send_char(uint8_t ax_id, uint8_t param, uint8_t val)
{
	char trame[20];
    ax12_sendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=ax_id;
    trame[3]=4;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=val;
    trame[7]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]);
	
    uart_write(ax12_uart, trame, 8);
}

/**
 * @brief Send a short (16 bits) to the specified device
 * @param ax_id the device address
 */
void ax12_send_1_short(uint8_t ax_id, uint8_t param, uint16_t val)
{
	char trame[20];
    ax12_sendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=ax_id;
    trame[3]=5;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=(char)val;
    trame[7]=(char)((short)val>>8);
    trame[8]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]+trame[7]);

    uart_write(ax12_uart, trame, 9);
}

/**
 * @brief Send a two shorts (16 bits) to the specified device
 * @param ax_id the device address
 */
void ax12_send_2_short(uint8_t ax_id, uint8_t param, uint16_t val, uint16_t val2)
{
	char trame[20];
    ax12_sendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=ax_id;
    trame[3]=7;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=(char)val;
    trame[7]=(char)((short)val>>8);
    trame[8]=(char)val2;
    trame[9]=(char)((short)val2>>8);
    trame[10]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]+trame[7]+trame[8]+trame[9]);

    uart_write(ax12_uart, trame, 11);
}

/**
 * @brief Send three shorts (16 bits) to the specified device
 * @param ax_id the device address
 */
void ax12_send_3_short(uint8_t ax_id, uint8_t param, uint16_t val, uint16_t val2, uint16_t val3)
{
	char trame[20];
    ax12_sendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=ax_id;
    trame[3]=9;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=(char)val;
    trame[7]=(char)((short)val>>8);
    trame[8]=(char)val2;
    trame[9]=(char)((short)val2>>8);
    trame[10]=(char)val3;
    trame[11]=(char)((short)val3>>8);
    trame[12]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]+trame[7]+trame[8]+trame[9]+trame[10]+trame[11]);

    uart_write(ax12_uart, trame, 13);
}

/**
 * @brief Read parameters of the device
 * @param ax_id the device address
 */
/*void ax12_read_param_ax(uint8_t ax_id, uint8_t param, uint8_t nbParam)
{
    int p;
    axSendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=ax_id;
    trame[3]=4;
    trame[4]=INST_READ;
    trame[5]=param;
    trame[6]=nbParam;
    trame[7]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]);
    my_size=8;
    idax=0;
    U3TXREG = trame[0];
    IEC5bits.U3TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=my_size);
    //for(p=0;p<100;p++);
    //axRecMode();
}*/

/**
 * @brief foo
 * @return 1 if ok, 0 in case of error
 */
/*uint8_t parseResponse6(uint8_t ax_id, uint16_t *pos, uint16_t *speed, uint16_t *load)
{
    uint8_t sum,i;
    for(i=6;i<20;i++) if(buffr[i]==0xFF && buffr[i+1]==0xFF) break;
    if(buffr[i+1]!=0xFF) return 0;
    if(buffr[i+2]!=ax_id) return 0;
    sum=~(uint8_t)(buffr[i+2]+buffr[i+3]+buffr[i+4]+buffr[i+5]+buffr[i+6]+buffr[i+7]+buffr[i+8]+buffr[i+9]+buffr[i+10]);
    if(buffr[i+11]!=sum) return 0;
    *pos=(uint16_t)buffr[i+6]*256+buffr[i+5];
    *speed=(uint16_t)buffr[i+8]*256+buffr[i+7];
    *load=(uint16_t)buffr[i+10]*256+buffr[i+9];
    return 1;
}*/

/**
 * @brief foo
 */
/*void clearAxResponse(void)
{
    char i=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
    buffr[i++]=0;
}*/

/**
 * @brief foo
 */
/*void interrupt tx3_int(void) @ U3TX_VCTR
{
    int p;
    idax++;
    if(idax>=my_size)
    {
        IEC5bits.U3TXIE = 0;

        // axRecMode();                 //OLD NAME
        axReceiveMode();                //NEW NAME
        
        return;
    }
    //for(p=0;p<50;p++);
    U3TXREG = trame[idax];
    IFS5bits.U3TXIF = 0;
}*/

/**
 * @brief foo
 */
/*void interrupt rx3_int(void) @ U3RX_VCTR
{
    uint8_t rec;
    while(U3STAbits.URXDA==1)
    {
        if(U3STAbits.FERR==1)
        {
            rec=U3RXREG;
            IFS5bits.U3RXIF = 0;
            return;
        }
        if(U3STAbits.OERR==1)
        {
            rec=U3RXREG;
            U3STAbits.OERR=0;
            IFS5bits.U3RXIF = 0;
            return;
        }
        rec=U3RXREG;
        if(idr<30)
        {
            buffr[idr]=rec;
            idr++;
        }
    }
    IFS5bits.U3RXIF = 0;
}*/

void ax12_moveTo(uint8_t ax_id, uint16_t position, uint16_t speed, uint16_t torque)
{
	ax12_send_3_short(ax_id, P_GOAL_POSITION_L, position, speed, torque);
}

void ax12_setPosition(uint8_t ax_id, uint16_t position)
{
	ax12_send_1_short(ax_id, P_GOAL_POSITION_L, position);
}

void ax12_setSpeed(uint8_t ax_id, uint16_t speed)
{
	ax12_send_1_short(ax_id, P_GOAL_SPEED_L, speed);
}

void ax12_setTorque(uint8_t ax_id, uint16_t torque)
{
	ax12_send_1_short(ax_id, P_TORQUE_LIMIT_L, torque);
}

void ax12_setLed(uint8_t ax_id, uint8_t led)
{
	ax12_send_char(ax_id, P_LED, led);
}
