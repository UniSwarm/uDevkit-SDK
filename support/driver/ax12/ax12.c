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
#include <xc.h>

uint8_t idr=255;
uint8_t buffr[30];
uint8_t trame[20], idax,
// size,
my_size //compiler said there is a redefinition... STAY CALM
;

/**
 * @brief Set the device the send mode
 */
void axSendMode()
{
    U3MODEbits.STSEL=1;
    RWB=1;
    idr=0;
}

/**
 * @brief Set the device to receive mode
 */
// void axRecMode()                             //OLD NAME
void axReceiveMode()                            //NEW NAME
{
    uint8_t rec;
    U3MODEbits.STSEL = 0;
    RWB = 0;
    //idr = 0;
    // if(U3STAbits.OERR==1)
    // {
    //     rec=U3RXREG;
    //     U3STAbits.OERR=0;
    // }
}

/**
 * @brief Setup the device
 */
void setup_AX(void)
{
    setup_uart_AX();
}

/**
 * @brief foo
 */
void setup_uart_AX(void)
{
    // U1MODE bits configuration
    U3MODEbits.STSEL = 0;   // 1 Stop bit
    U3MODEbits.PDSEL = 0b00;   // 8-bit data, no parity
    U3MODEbits.BRGH = 1;     // Low-speed mode
    U3MODEbits.URXINV = 0;     // UxRX Idle state is ‘1’
    U3MODEbits.ABAUD = 0;   // Baud rate measurement disabled
    U3MODEbits.LPBACK = 0;     // Loopback mode is disabled
    U3MODEbits.WAKE = 0;     // Wake-up is disabled
    U3MODEbits.UEN = 0;         // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches
    U3MODEbits.RTSMD = 0;   // UxRTS is in Flow Control mode
    U3MODEbits.IREN = 0;     // IrDA encoder and decoder are disabled
    U3MODEbits.USIDL = 0;   // Continue operation in Idle mode
    U3MODEbits.UARTEN = 1;     // UARTx is enabled

    // U1STA bits configuration
    U3STAbits.URXISEL = 0;     // Interrupt flag bit is set when a character is received
    U3STAbits.UTXEN = 1;     // UARTx transmitter enabled
    U3STAbits.UTXBRK = 0;   // Sync Break transmission is disabled
    U3STAbits.UTXISEL0 = 1;       // Interrupt is generated when the last transmission is over
    U3STAbits.UTXINV = 0;   // UxTX Idle state is ‘1’
    U3STAbits.UTXISEL1 = 0;       // Interrupt is generated when the last transmission is over

    // Baud rate generator
    U3BRG = 9;
    //                   FCY
    // baudRate = -----------------       (with BRGH=1)
    //             4 * (UXBRG + 1)
    
    // Uart Interrupt
    IPC20bits.U3RXIP = 5;     // Interrupt priority for receptor
    IPC20bits.U3TXIP = 6;     // Interrupt priority for transmitor
    IEC5bits.U3TXIE = 0;
    IEC5bits.U3RXIE = 1;
}

/**
 * @brief Send a char (8 bits) to the specified device
 * @param addr the device address
 * @param param
 * @param val
 */
void send_char_ax(uint8_t addr, uint8_t param, uint8_t val)
{
    int p;
    axSendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=addr;
    trame[3]=4;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=val;
    trame[7]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]);
    my_size=8;
    idax=0;
    U3TXREG = trame[0];
    IEC5bits.U3TXIE = 1;
    //for(p=0;p<100;p++);
    //while(IEC5bits.U3TXIE==1);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief Send a short (16 bits) to the specified device
 * @param addr the device address
 */
void send_1_short_ax(uint8_t addr, uint8_t param, uint16_t val)
{
    int p;
    axSendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=addr;
    trame[3]=5;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=val;
    trame[7]=*((char*)(&val)+1);
    trame[8]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]+trame[7]);
    my_size=9;
    idax=0;
    U3TXREG = trame[0];
    IEC5bits.U3TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=my_size);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief Send a two shorts (16 bits) to the specified device
 * @param addr the device address
 */
void send_2_short_ax(uint8_t addr, uint8_t param, uint16_t val, uint16_t val2)
{
    int p;
    axSendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=addr;
    trame[3]=7;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=val;
    trame[7]=*((char*)(&val)+1);
    trame[8]=val2;
    trame[9]=*((char*)(&val2)+1);
    trame[10]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]+trame[7]+trame[8]+trame[9]);
    my_size=11;
    idax=0;
    U3TXREG = trame[0];
    IEC5bits.U3TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=my_size);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief Send three shorts (16 bits) to the specified device
 * @param addr the device address
 */
void send_3_short_ax(uint8_t addr, uint8_t param, uint16_t val, uint16_t val2, uint16_t val3)
{
    int p;
    axSendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=addr;
    trame[3]=9;
    trame[4]=INST_WRITE;
    trame[5]=param;
    trame[6]=val;
    trame[7]=*((char*)(&val)+1);
    trame[8]=val2;
    trame[9]=*((char*)(&val2)+1);
    trame[10]=val3;
    trame[11]=*((char*)(&val3)+1);
    trame[12]=~(uint8_t)(trame[2]+trame[3]+trame[4]+trame[5]+trame[6]+trame[7]+trame[8]+trame[9]+trame[10]+trame[11]);
    my_size=13;
    idax=0;
    U3TXREG = trame[0];
    IEC5bits.U3TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=my_size);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief Read parameters of the device
 * @param addr the device address
 */
void read_param_ax(uint8_t addr, uint8_t param, uint8_t nbParam)
{
    int p;
    axSendMode();
    trame[0]=0xFF;
    trame[1]=0xFF;
    trame[2]=addr;
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
}

/**
 * @brief foo
 * @return 1 if ok, 0 in case of error
 */
uint8_t parseResponse6(uint8_t addr, uint16_t *pos, uint16_t *speed, uint16_t *load)
{
    uint8_t sum,i;
    for(i=6;i<20;i++) if(buffr[i]==0xFF && buffr[i+1]==0xFF) break;
    if(buffr[i+1]!=0xFF) return 0;
    if(buffr[i+2]!=addr) return 0;
    sum=~(uint8_t)(buffr[i+2]+buffr[i+3]+buffr[i+4]+buffr[i+5]+buffr[i+6]+buffr[i+7]+buffr[i+8]+buffr[i+9]+buffr[i+10]);
    if(buffr[i+11]!=sum) return 0;
    *pos=(uint16_t)buffr[i+6]*256+buffr[i+5];
    *speed=(uint16_t)buffr[i+8]*256+buffr[i+7];
    *load=(uint16_t)buffr[i+10]*256+buffr[i+9];
    return 1;
}

/**
 * @brief foo
 */
void clearAxResponse(void)
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
}

/**
 * @brief foo
 */
void interrupt tx3_int(void) @ U3TX_VCTR
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
}

/**
 * @brief foo
 */
void interrupt rx3_int(void) @ U3RX_VCTR
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
}