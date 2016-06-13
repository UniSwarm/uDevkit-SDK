#include "ar.h"

/**
 * @brief Setup the device
 */
void ar1000_init(void)
{
	//set uart mode
	//set microcontroller M1 pin to 1... cf doc
}

void ar1000_send(uint8_t size, uint8_t cmd, char* data)
{
	char trame[20];
	trame[0]=0x55;
	trame[1]=size;
	trame[2]=cmd;

	// if(data !is_empty (mais c'est un pointer...))
		// trame[3 et plus] = data;

	//FAIRE UN TRUC POUR ENVOYER LA TRAME
}

void ar1000_receive(uint8_t size, uint8_t cmd)
{
	char trame[20];
	trame[0]=0x55;
	trame[1]=size;
	trame[2]=status_value(); //VALUE ?
	trame[3]=cmd;

	//FAIRE UN TRUC POUR ENVOYER LA TRAME
}

void ar1000_get_version()
{
	uint8_t size = 1;
	uint8_t cmd = 0x10;
	// set SpeedThreshold register: low value is often but noisy, hight value is good but slow
	// Recommended Values: <4, 8, 16>

	unit8_t type = 0x00001010;
	7-6bits: 00: 8bits; 01: 10bits; 10: 12bits

	ar1000_send(size, cmd);
	ar1000_receive(size, cmd);
}

void ar1000_enable_touch()
{
	uint8_t size = 1;
	uint8_t cmd = 0x12;
	ar1000_send(size, cmd);
	size = 2;
	ar1000_receive(size, cmd);
}

void ar1000_disable_touch()
{
	ar1000_send(0x13, 1, data_vide!);
	ar1000_receive();
}

//Status values
char ar1000_status_value()
{
	if(/*JE SAIS PAS QUOI*/)
		return 0x00; //Success
	else if(/*JE SAIS PAS QUOI*/)
		return 0x01; //Command Unrecognized
	else if(/*JE SAIS PAS QUOI*/)
		return 0x03; //Header Unrecognized
	else if(/*JE SAIS PAS QUOI*/)
		return 0x04; //Command Time Out (exceeded ~100ms)
	else if(/*JE SAIS PAS QUOI*/)
		return 0xFC; //Cancel Calibration mode
}

void ar1000_send_cmd(uint8_t size, uint8_t cmd, char* data)
{
	disable_touch();
	ar1000_send(size, cmd, data);
	// wait 50ms;
	ar1000_receive(size, cmd);
	enable_touch();
}
