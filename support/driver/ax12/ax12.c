/**
 * @file ax12.h
 * @author Sebastien CAUX (sebcaux) / Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2016
 *
 * @date April 16, 2016, 14:41 PM
 *
 * @brief AX12 servomotor support
 */

#include "ax12.h"

//uint8_t idr = 255;
//uint8_t buffr[30];
uint8_t ax12_trame[20];
rt_dev_t ax12_uart;
rt_dev_t ax12_txen;
uint8_t ax12_inverted;

/**
 * @brief Set the device the send mode
 */
void ax12_sendMode()
{
    if (ax12_txen != NULLDEV)
    {
        if (ax12_inverted == 0)
            gpio_setBit(ax12_txen);
        else
            gpio_clearBit(ax12_txen);
    }
    //idr = 0;
}

/**
 * @brief Set the device to receive mode
 */
void ax12_receiveMode()
{
    //idr = 0;
    if (ax12_txen != NULLDEV)
    {
        if (ax12_inverted == 0)
            gpio_clearBit(ax12_txen);
        else
            gpio_setBit(ax12_txen);
    }
}

/**
 * @brief Setup the ax bus
 * @param uart uart dev to transmit data
 * @param txen optional gpio to enable transmitter, NULLDEV if not used
 * @param inverted 0 to invert txen signal (txen 0 for send mode, 1 for receive)
 */
void ax12_init(rt_dev_t uart, rt_dev_t txen, uint8_t inverted)
{
    ax12_uart = uart;
    uart_setBaudSpeed(ax12_uart, 1000000);
    uart_setBitConfig(ax12_uart, 8, UART_BIT_PARITY_NONE, 1);
    uart_enable(ax12_uart);
    
    ax12_txen = txen;
    ax12_inverted = inverted;
    if (ax12_txen != NULLDEV)
        gpio_setBitConfig(ax12_txen, GPIO_OUTPUT);
}

/**
 * @brief Send a char (8 bits) to the specified ax
 * @param ax_id the device address
 * @param param addr of the parameter to set
 * @param val value to write
 */
void ax12_send_char(uint8_t ax_id, uint8_t param, uint8_t val)
{
    char ax12_trame[20];
    ax12_sendMode();
    ax12_trame[0] = 0xFF;
    ax12_trame[1] = 0xFF;
    ax12_trame[2] = ax_id;
    ax12_trame[3] = 4;
    ax12_trame[4] = INST_WRITE;
    ax12_trame[5] = param;
    ax12_trame[6] = val;
    ax12_trame[7] = ~(uint8_t)(ax12_trame[2]+ax12_trame[3]+ax12_trame[4]+ax12_trame[5]+ax12_trame[6]);

    uart_write(ax12_uart, ax12_trame, 8);
}

/**
 * @brief Send a short (16 bits) to the specified ax
 * @param ax_id the device address
 * @param param addr of the parameter to set
 * @param val value to write
 */
void ax12_send_1_short(uint8_t ax_id, uint8_t param, uint16_t val)
{
    char ax12_trame[20];
    ax12_sendMode();
    ax12_trame[0] = 0xFF;
    ax12_trame[1] = 0xFF;
    ax12_trame[2] = ax_id;
    ax12_trame[3] = 5;
    ax12_trame[4] = INST_WRITE;
    ax12_trame[5] = param;
    ax12_trame[6] = (char)val;
    ax12_trame[7] = (char)((short)val>>8);
    ax12_trame[8] = ~(uint8_t)(ax12_trame[2]+ax12_trame[3]+ax12_trame[4]+ax12_trame[5]+ax12_trame[6]+ax12_trame[7]);

    uart_write(ax12_uart, ax12_trame, 9);
}

/**
 * @brief Send a two shorts (16 bits) to the specified ax
 * @param ax_id the device address
 * @param param addr of the parameter to set
 * @param val value to write
 * @param val2 second value to write at `param` + 2
 */
void ax12_send_2_short(uint8_t ax_id, uint8_t param, uint16_t val, uint16_t val2)
{
    char ax12_trame[20];
    ax12_sendMode();
    ax12_trame[0] = 0xFF;
    ax12_trame[1] = 0xFF;
    ax12_trame[2] = ax_id;
    ax12_trame[3] = 7;
    ax12_trame[4] = INST_WRITE;
    ax12_trame[5] = param;
    ax12_trame[6] = (char)val;
    ax12_trame[7] = (char)((short)val>>8);
    ax12_trame[8] = (char)val2;
    ax12_trame[9] = (char)((short)val2>>8);
    ax12_trame[10] = ~(uint8_t)(ax12_trame[2]+ax12_trame[3]+ax12_trame[4]+ax12_trame[5]+ax12_trame[6]+ax12_trame[7]+ax12_trame[8]+ax12_trame[9]);

    uart_write(ax12_uart, ax12_trame, 11);
}

/**
 * @brief Send three shorts (16 bits) to the specified ax
 * @param ax_id the device address
 * @param param addr of the parameter to set
 * @param val first value to write
 * @param val2 second value to write at `param` + 2
 * @param val3 third value to write at `param` + 4
 */
void ax12_send_3_short(uint8_t ax_id, uint8_t param, uint16_t val, uint16_t val2, uint16_t val3)
{
    char ax12_trame[20];
    ax12_sendMode();
    ax12_trame[0] = 0xFF;
    ax12_trame[1] = 0xFF;
    ax12_trame[2] = ax_id;
    ax12_trame[3] = 9;
    ax12_trame[4] = INST_WRITE;
    ax12_trame[5] = param;
    ax12_trame[6] = (char)val;
    ax12_trame[7] = (char)((short)val>>8);
    ax12_trame[8] = (char)val2;
    ax12_trame[9] = (char)((short)val2>>8);
    ax12_trame[10] = (char)val3;
    ax12_trame[11] = (char)((short)val3>>8);
    ax12_trame[12] = ~(uint8_t)(ax12_trame[2]+ax12_trame[3]+ax12_trame[4]+ax12_trame[5]+ax12_trame[6]+ax12_trame[7]+ax12_trame[8]+ax12_trame[9]+ax12_trame[10]+ax12_trame[11]);

    uart_write(ax12_uart, ax12_trame, 13);
}

/**
 * @brief Read parameters of the device
 * @param ax_id the device address
 */
/*void ax12_read_param_ax(uint8_t ax_id, uint8_t param, uint8_t nbParam)
{
    int p;
    axSendMode();
    ax12_trame[0] = 0xFF;
    ax12_trame[1] = 0xFF;
    ax12_trame[2] = ax_id;
    ax12_trame[3] = 4;
    ax12_trame[4] = INST_READ;
    ax12_trame[5] = param;
    ax12_trame[6] = nbParam;
    ax12_trame[7] = ~(uint8_t)(ax12_trame[2]+ax12_trame[3]+ax12_trame[4]+ax12_trame[5]+ax12_trame[6]);
    my_size = 8;
    idax = 0;
    U3TXREG = ax12_trame[0];
    IEC5bits.U3TXIE = 1;
    //for(p = 0;p<100;p++);
    //while(idax! = my_size);
    //for(p = 0;p<100;p++);
    //axRecMode();
}*/

/**
 * @brief foo
 * @return 1 if ok, 0 in case of error
 */
/*uint8_t parseResponse6(uint8_t ax_id, uint16_t *pos, uint16_t *speed, uint16_t *load)
{
    uint8_t sum, i;
    for(i = 6;i<20;i++) if(buffr[i] = =0xFF && buffr[i+1] = =0xFF) break;
    if(buffr[i+1]! = 0xFF) return 0;
    if(buffr[i+2]! = ax_id) return 0;
    sum = ~(uint8_t)(buffr[i+2]+buffr[i+3]+buffr[i+4]+buffr[i+5]+buffr[i+6]+buffr[i+7]+buffr[i+8]+buffr[i+9]+buffr[i+10]);
    if(buffr[i+11]! = sum) return 0;
    *pos = (uint16_t)buffr[i+6]*256+buffr[i+5];
    *speed = (uint16_t)buffr[i+8]*256+buffr[i+7];
    *load = (uint16_t)buffr[i+10]*256+buffr[i+9];
    return 1;
}*/

/**
 * @brief clear internal respond buffer
 */
/*void clearAxResponse(void)
{
    uint8_t i;
    for (i = 0; i<30; i++)
    	buffr[i] = 0;
}*/

/**
 * @brief foo
 */
/*void interrupt rx3_int(void) @ U3RX_VCTR
{
    uint8_t rec;
    while(U3STAbits.URXDA = =1)
    {
        if(U3STAbits.FERR = =1)
        {
            rec = U3RXREG;
            IFS5bits.U3RXIF = 0;
            return;
        }
        if(U3STAbits.OERR = =1)
        {
            rec = U3RXREG;
            U3STAbits.OERR = 0;
            IFS5bits.U3RXIF = 0;
            return;
        }
        rec = U3RXREG;
        if(idr<30)
        {
            buffr[idr] = rec;
            idr++;
        }
    }
    IFS5bits.U3RXIF = 0;
}*/

/**
 * @brief Move an ax to the specified position with the specified speed and torque
 * @param ax_id the device address
 * @param position destination position. 0-1023, 511 is the center of a 270° movement
 * @param speed speed limit for this movement. 0-1023
 * @param torque torque limit for this movement. 0-1023
 */
void ax12_moveTo(uint8_t ax_id, uint16_t position, uint16_t speed, uint16_t torque)
{
    ax12_send_3_short(ax_id, P_GOAL_POSITION_L, position, speed, torque);
}

/**
 * @brief Move an ax to the specified position
 * @param ax_id the device address
 * @param position destination position. 0-1023, 511 is the center of a 270° movement
 */
void ax12_setPosition(uint8_t ax_id, uint16_t position)
{
    ax12_send_1_short(ax_id, P_GOAL_POSITION_L, position);
}

/**
 * @brief Set limit speed
 * @param ax_id the device address
 * @param speed speed limit for this movement. 0-1023
 */
void ax12_setSpeed(uint8_t ax_id, uint16_t speed)
{
    ax12_send_1_short(ax_id, P_GOAL_SPEED_L, speed);
}

/**
 * @brief Set limit torque
 * @param ax_id the device address
 * @param torque torque limit for this movement. 0-1023
 */
void ax12_setTorque(uint8_t ax_id, uint16_t torque)
{
    ax12_send_1_short(ax_id, P_TORQUE_LIMIT_L, torque);
}

/**
 * @brief Light on/off the ax led
 * @param ax_id the device address
 * @param led value of the led 0(Off)/1(On)
 */
void ax12_setLed(uint8_t ax_id, uint8_t led)
{
    ax12_send_char(ax_id, P_LED, led);
}

/**
 * @brief CHange id of an ax motor
 * @param ax_id actual id of the motor
 * @param newId future id to set
 */
void ax12_setId(uint8_t ax_id, uint8_t newId)
{
    ax12_send_char(ax_id, P_ID, newId);
}
