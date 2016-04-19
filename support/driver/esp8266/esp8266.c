#include "esp.h"

#include "setup.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// data/commands to send to esp
unsigned short idSend=0;
unsigned short sizeSend=0;
unsigned __attribute__((far)) char dataSend[2049];

// data receive from esp
unsigned char socket = 0;
unsigned short sizeRecPacket = 0;
unsigned short idRecPacket = 0;
unsigned char recPacketFlag = 0;
char __attribute__((far)) recPacket[2049];
volatile WIFIstatus wifistatus = FSM_UNKNOW;

volatile WIFI_STATE pendingState = WIFI_STATE_NONE;
volatile WIFI_STATE state = WIFI_STATE_NONE;

void esp_uart_init()
{
	// U2MODE bits configuration
	U1MODEbits.USIDL = 0;		// Continue operation in Idle mode
	U1MODEbits.IREN = 0;		// IrDA encoder and decoder are disabled
	U1MODEbits.RTSMD = 0;		// UxRTS is in Flow Control mode
	U1MODEbits.UEN = 0;			// UxTX and UxRX pins are enabled and used; UxCTS, UxRTS and BCLKx pins are controlled by port latches
	U1MODEbits.WAKE = 0;		// Wake-up is disabled
	U1MODEbits.LPBACK = 0;		// Loopback mode is disabled
	U1MODEbits.ABAUD = 0;		// Baud rate measurement disabled
	U1MODEbits.URXINV = 0;		// UxRX Idle state is ‘1’
	U1MODEbits.BRGH = 0;		// Low-speed mode
	U1MODEbits.PDSEL = 0b00;	// 9-bit data, no parity
	U1MODEbits.STSEL = 0;		// 1 Stop bit
	U1MODEbits.UARTEN = 1;		// UARTx is enabled
	
	// U2STA bits configuration
	U1STAbits.UTXISEL1 = 0;		// Interrupt is generated when the last transmission is over
	U1STAbits.UTXINV = 0;		// UxTX Idle state is ‘1’
	U1STAbits.UTXISEL0 = 1;		// Interrupt is generated when the last transmission is over
	U1STAbits.UTXBRK = 0;		// Sync Break transmission is disabled
	U1STAbits.UTXEN = 1;		// UARTx transmitter enabled
	U1STAbits.URXISEL = 0;		// Interrupt flag bit is set when a character is received
	
	// Baud rate generator
	U1BRG = 31;		// 115200 bds
	//U1BRG = 390;		// 9600 bds
	//                   FCY
	// baudRate = ------------------	(with BRGH=0)
	//             16 * (UXBRG + 1)
	
	// Uart Interrupt
	IPC2bits.U1RXIP = 6;		// Interrupt priority for receptor
	IPC3bits.U1TXIP = 5;		// Interrupt priority for transmitor
	IEC0bits.U1TXIE = 1;
    IEC0bits.U1RXIE = 1;
}

void esp_init()
{
	esp_uart_init();
}

void esp_send_cmd(char data[])
{
	unsigned short i=0;
	idSend=1;
	
	while(data[i]!=0)
	{
		dataSend[i]=data[i];
		i++;
	}
	dataSend[i++]='\r';
	dataSend[i++]='\n';
	sizeSend=i;
	
	U1TXREG = data[0];
	IEC0bits.U1TXIE = 1;
}

void __attribute__ ((interrupt,no_auto_psv)) _U1TXInterrupt(void)
{
	if(idSend<sizeSend)
	{
		U1TXREG = dataSend[idSend];
		idSend++;
	}
	else
	{
		IEC0bits.U1TXIE = 0;
	}	
	IFS0bits.U1TXIF = 0;
}

void __attribute__ ((interrupt,no_auto_psv)) _U1RXInterrupt(void)
{
	char rec = U1RXREG;
	
	switch(wifistatus)
	{
		case FSM_UNKNOW:
			if (rec == '\r')
				wifistatus = FSM_WAITING_VALIDATE;
			else
				wifistatus = FSM_UNKNOW;
			break;
		case FSM_WAITING_VALIDATE:
			if (rec == '\n')
			{
				//validate
				if(pendingState!=WIFI_STATE_NONE) state = pendingState;
				pendingState = WIFI_STATE_NONE;
				
				wifistatus = FSM_START;
			}	
			else
				wifistatus = FSM_UNKNOW;
			break;
		case FSM_START:
			if (rec == '\r')
				wifistatus = FSM_WAITING_VALIDATE;
			else if (rec == '+')
				wifistatus = FSM_PLUS;
			else if (rec == 'S')
				wifistatus = FSM_SENDOK_S;
			else if (rec == 'E')
				wifistatus = FSM_ERROR_E;
			else if (rec == '>')
			{
				state = WIFI_STATE_SEND_DATA;
				wifistatus = FSM_UNKNOW;
			}
			else if (rec == 'O')
				wifistatus = FSM_OK_O;
			else
				wifistatus = FSM_UNKNOW;
			break;
			
		case FSM_SENDOK_S:
			if (rec == 'E') wifistatus = FSM_SENDOK_E; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_SENDOK_E:
			if (rec == 'N') wifistatus = FSM_SENDOK_N; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_SENDOK_N:
			if (rec == 'D') wifistatus = FSM_SENDOK_D; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_SENDOK_D:
			if (rec == ' ') wifistatus = FSM_SENDOK_Sp; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_SENDOK_Sp:
			if (rec == 'O') wifistatus = FSM_SENDOK_O; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_SENDOK_O:
			if (rec == 'K') wifistatus = FSM_SENDOK_K; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_SENDOK_K:
			if (rec == '\r')
			{
				pendingState = WIFI_STATE_SEND_OK;
				wifistatus = FSM_WAITING_VALIDATE;
			}
			else
				wifistatus = FSM_UNKNOW;
			break;
			
		case FSM_ERROR_E:
			if (rec == 'R') wifistatus = FSM_ERROR_R1; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_ERROR_R1:
			if (rec == 'R') wifistatus = FSM_ERROR_R2; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_ERROR_R2:
			if (rec == 'O') wifistatus = FSM_ERROR_O; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_ERROR_O:
			if (rec == 'R') wifistatus = FSM_ERROR_R3; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_ERROR_R3:
			if (rec == '\r')
			{
				pendingState = WIFI_STATE_ERROR;
				wifistatus = FSM_WAITING_VALIDATE;
			}
			else
				wifistatus = FSM_UNKNOW;
			break;
			
		case FSM_OK_O:
			if (rec == 'K') wifistatus = FSM_OK_K; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_OK_K:
			if (rec == '\r')
			{
				pendingState = WIFI_STATE_OK;
				wifistatus = FSM_WAITING_VALIDATE;
			}
			else
				wifistatus = FSM_UNKNOW;
			break;
			
		case FSM_PLUS:
			if (rec == 'I') wifistatus = FSM_IPD_I; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_I:
			if (rec == 'P') wifistatus = FSM_IPD_P; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_P:
			if (rec == 'D') wifistatus = FSM_IPD_D; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_D:
			if (rec == ',') wifistatus = FSM_IPD_COMMA_1; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_COMMA_1:
			if (rec >= '0' && rec <= '9')
			{
				wifistatus = FSM_IPD_SOCKET_DIGIT;
				socket = rec - '0';
			}	
			else
				wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_SOCKET_DIGIT:
			if (rec == ',') wifistatus = FSM_IPD_COMMA_2; else wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_COMMA_2:
			if (rec >= '0' && rec <= '9')
			{
				wifistatus = FSM_IPD_SIZE_DIGITS;
				sizeRecPacket = (rec - '0');
			}	
			else
				wifistatus = FSM_UNKNOW;
			break;
		case FSM_IPD_SIZE_DIGITS:
			if (rec == ':')
			{
				idRecPacket = 0;
				wifistatus = FSM_PACKET_RX;
			}
			else
			{
				if (rec >= '0' && rec <= '9')
				{
					wifistatus = FSM_IPD_SIZE_DIGITS;
					sizeRecPacket = sizeRecPacket * 10 + (rec - '0');
				}	
				else
					wifistatus = FSM_UNKNOW;
			}
			break;
		case FSM_PACKET_RX:
			recPacket[idRecPacket++] = rec;
			if(idRecPacket >= sizeRecPacket)
			{
				recPacketFlag=1;
				state = WIFI_STATE_RECEIVE_DATA;
				wifistatus = FSM_UNKNOW;
			}
			break;
		default:
			wifistatus = FSM_UNKNOW;
	}
	
	IFS0bits.U1RXIF = 0;
}

void wait_ok()
{
	while(state != WIFI_STATE_OK);
	state = WIFI_STATE_NONE;
}

WIFI_STATE get_state()
{
	return state;
}

unsigned char getRecSocket()
{
	return socket;
}

char *getRecData()
{
	return recPacket;
}

unsigned short getRecSize()
{
	return sizeRecPacket;
}

unsigned char getRec()
{
	if(recPacketFlag==1)
	{
		recPacketFlag=0;
		return 1;
	}
	return 0;
}

unsigned char esp_open_tcp_socket(char ip_domain[], unsigned short port)
{
	esp_send_cmd("AT+CIPSTART=0,\"TCP\",\"robotips.fr\",80");
	wait_ok();
	return 0;
}

unsigned char esp_open_udp_socket(char ip_domain[], unsigned short port, unsigned short localPort, unsigned char mode)
{
	return 0;
}

void esp_set_mode(ESP_MODE mode)
{
	char buff[20];
	char *ptbuff=buff;
	
	(*(ptbuff++))='A';
	(*(ptbuff++))='T';
	(*(ptbuff++))='+';
	(*(ptbuff++))='C';
	(*(ptbuff++))='W';
	(*(ptbuff++))='M';
	(*(ptbuff++))='O';
	(*(ptbuff++))='D';
	(*(ptbuff++))='E';
	(*(ptbuff++))='=';
	
	if(mode==ESP_MODE_AP) (*(ptbuff++))='2';
	else if(mode==ESP_MODE_STA_AP) (*(ptbuff++))='3';
	else (*(ptbuff++))='1';
	
	(*(ptbuff++))='\0';
	esp_send_cmd(buff);
	wait_ok();
}

unsigned char esp_connect_ap(char ssid[], char pw[])		// warning, be careful to special car, protect with backslash
{
	char buff[100];
	char *ptbuff=buff;
	char *ptssid=ssid;
	char *ptpw=pw;
	
	(*(ptbuff++))='A';
	(*(ptbuff++))='T';
	(*(ptbuff++))='+';
	(*(ptbuff++))='C';
	(*(ptbuff++))='W';
	(*(ptbuff++))='J';
	(*(ptbuff++))='A';
	(*(ptbuff++))='P';
	(*(ptbuff++))='=';
	
	(*(ptbuff++))='"';
	while(*ptssid!=0)
	{
		if(*ptssid=='"' || *ptssid==',' || *ptssid=='\\') (*(ptbuff++))='\\';
		(*(ptbuff++))=*ptssid;
		ptssid++;
	}
	(*(ptbuff++))='"';
	(*(ptbuff++))=',';
	
	(*(ptbuff++))='"';
	while(*ptpw!=0)
	{
		if(*ptpw=='"' || *ptpw==',' || *ptpw=='\\') (*(ptbuff++))='\\';
		(*(ptbuff++))=*ptpw;
		ptpw++;
	}
	(*(ptbuff++))='"';
	
	(*(ptbuff++))='\0';
	esp_send_cmd(buff);
	wait_ok();
	
	return 0;
}

unsigned char esp_disconnect_ap()
{
	esp_send_cmd("AT+CWQAP");
	wait_ok();
	return 0;
}

void esp_close_socket(unsigned char sock)
{
	char buff[20];
	char *ptbuff=buff;
	
	(*(ptbuff++))='A';
	(*(ptbuff++))='T';
	(*(ptbuff++))='+';
	(*(ptbuff++))='C';
	(*(ptbuff++))='I';
	(*(ptbuff++))='P';
	(*(ptbuff++))='C';
	(*(ptbuff++))='L';
	(*(ptbuff++))='O';
	(*(ptbuff++))='S';
	(*(ptbuff++))='E';
	(*(ptbuff++))='=';
	(*(ptbuff++))=sock+'0';
	(*(ptbuff++))='\0';
	esp_send_cmd(buff);
	wait_ok();
}

void esp_write_socket(unsigned char sock, char data[], unsigned short size)
{
	char buff[20];
	char *ptbuff=buff;
	
	(*(ptbuff++))='A';
	(*(ptbuff++))='T';
	(*(ptbuff++))='+';
	(*(ptbuff++))='C';
	(*(ptbuff++))='I';
	(*(ptbuff++))='P';
	(*(ptbuff++))='S';
	(*(ptbuff++))='E';
	(*(ptbuff++))='N';
	(*(ptbuff++))='D';
	(*(ptbuff++))='=';
	(*(ptbuff++))=sock+'0';
	(*(ptbuff++))=',';
	
	itoa(ptbuff, size, 10);
	
	esp_send_cmd(buff);
	
	while(state != WIFI_STATE_SEND_DATA);
	state = WIFI_STATE_NONE;
	
	esp_write(data, size);
	while(state != WIFI_STATE_SEND_OK);
}

void esp_write_socket_string(unsigned char sock, char str[])
{
	unsigned short size=0;
	
	while(str[size]!=0) size++;
	esp_write_socket(sock, str, size);
}

void esp_write(char data[], unsigned short size)
{
	unsigned short i=0;
	idSend=1;
	
	while(i<size)
	{
		dataSend[i]=data[i];
		i++;
	}
	sizeSend=size;
	
	U1TXREG = data[0];
	IEC0bits.U1TXIE = 1;
}
