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

// BE CAREFUL : this code is awful but... it works

uint8_t idr=255;
uint8_t buffr[30];
uint8_t trame[20],idax,size;

#define axSendMode() U1MODEbits.STSEL = 1; RWB=1; idr = 0

/**
 * @brief foo
 * @return bar
 */
void axRecMode()
{
    uint8_t rec;
    U1MODEbits.STSEL = 0;
    RWB = 0;
    //idr = 0;
    // if(U1STAbits.OERR==1)
    // {
    //     rec=U1RXREG;
    //     U1STAbits.OERR=0;
    // }
}

/**
 * @brief foo
 * @return bar
 */
void setup_AX(void)
{
    setup_uart_AX();
}

/**
 * @brief foo
 * @return bar
 */
void setup_uart_AX(void)
{
    // U1MODE bits configuration
    U1MODEbits.USIDL = 0;   // Continue operation in Idle mode
    U1MODEbits.IREN = 0;     // IrDA encoder and decoder are disabled
    U1MODEbits.RTSMD = 0;   // UxRTS is in Flow Control mode
    U1MODEbits.UEN = 0;         // UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches
    U1MODEbits.WAKE = 0;     // Wake-up is disabled
    U1MODEbits.LPBACK = 0;     // Loopback mode is disabled
    U1MODEbits.ABAUD = 0;   // Baud rate measurement disabled
    U1MODEbits.URXINV = 0;     // UxRX Idle state is ‘1’
    U1MODEbits.BRGH = 1;     // Low-speed mode
    U1MODEbits.PDSEL = 0b00;   // 8-bit data, no parity
    U1MODEbits.STSEL = 0;   // 1 Stop bit
    U1MODEbits.UARTEN = 1;     // UARTx is enabled
    
    // U1STA bits configuration
    U1STAbits.UTXISEL1 = 0;       // Interrupt is generated when the last transmission is over
    U1STAbits.UTXINV = 0;   // UxTX Idle state is ‘1’
    U1STAbits.UTXISEL0 = 1;       // Interrupt is generated when the last transmission is over
    U1STAbits.UTXBRK = 0;   // Sync Break transmission is disabled
    U1STAbits.UTXEN = 1;     // UARTx transmitter enabled
    U1STAbits.URXISEL = 0;     // Interrupt flag bit is set when a character is received

    // Baud rate generator
    U1BRG = 9;
    //                   FCY
    // baudRate = -----------------       (with BRGH=1)
    //             4 * (UXBRG + 1)
    
    // Uart Interrupt
    IPC2bits.U1RXIP = 5;     // Interrupt priority for receptor
    IPC3bits.U1TXIP = 6;     // Interrupt priority for transmitor
    U1TXIE = 0;
    U1RXIE = 1;
}

/**
 * @brief foo
 * @return bar
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
    size=8;
    idax=0;
    U1TXREG = trame[0];
    U1TXIE = 1;
    //for(p=0;p<100;p++);
    //while(U1TXIE==1);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief foo
 * @return bar
 */
void send_short_ax(uint8_t addr, uint8_t param, uint16_t val)
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
    size=9;
    idax=0;
    U1TXREG = trame[0];
    U1TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=size);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief foo
 * @return bar
 */
void send_dbshort_ax(uint8_t addr, uint8_t param, uint16_t val, uint16_t val2)
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
    size=11;
    idax=0;
    U1TXREG = trame[0];
    U1TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=size);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief foo
 * @return bar
 */
void send_trishort_ax(uint8_t addr, uint8_t param, uint16_t val, uint16_t val2, uint16_t val3)
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
    size=13;
    idax=0;
    U1TXREG = trame[0];
    U1TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=size);
    //for(p=0;p<100;p++);
    //idr=0;
    //axRecMode();
}

/**
 * @brief foo
 * @return bar
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
    size=8;
    idax=0;
    U1TXREG = trame[0];
    U1TXIE = 1;
    //for(p=0;p<100;p++);
    //while(idax!=size);
    //for(p=0;p<100;p++);
    //axRecMode();
}

/**
 * @brief foo
 * @return bar
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
 * @return bar
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
 * @return bar
 */
void interrupt tx1_int(void) @ U1TX_VCTR
{
    int p;
    idax++;
    if(idax>=size)
    {
        U1TXIE = 0;
        axRecMode();
        return;
    }
    //for(p=0;p<50;p++);
    U1TXREG = trame[idax];
    U1TXIF = 0;
}

/**
 * @brief foo
 * @return bar
 */
void interrupt rx1_int(void) @ U1RX_VCTR
{
    uint8_t rec;
    while(U1STAbits.URXDA==1)
    {
        if(U1STAbits.FERR==1)
        {
            rec=U1RXREG;
            U1RXIF = 0;
            return;
        }
        if(U1STAbits.OERR==1)
        {
            rec=U1RXREG;
            U1STAbits.OERR=0;
            U1RXIF = 0;
            return;
        }
        rec=U1RXREG;
        if(idr<30)
        {
            buffr[idr]=rec;
            idr++;
        }
    }
    U1RXIF = 0;
}