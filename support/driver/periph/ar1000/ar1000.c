#include "ar.h"

rt_dev_t ar1000_uart;
//PROTECTED FUNCTIONS

/**
 * @Brief ar1000_send
 */
void ar1000_send(uint8_t cmd, uint8_t size, char* data)
{
	char trame[20];
	trame[0]=0x55;
	trame[1]=size;
	trame[2]=cmd;

	// if(data !is_empty (mais c'est un pointer...))
		// trame[3 et plus] = data;

	//FAIRE UN TRUC POUR ENVOYER LA TRAME
}

/**
 * @Brief ar1000_receive
 */
void ar1000_receive(uint8_t cmd, uint8_t size)
{
	char trame[20];
	trame[0]=0x55;
	trame[1]=size;
	trame[2]= ???; //VALUE ?
	trame[3]=cmd;

	//FAIRE UN TRUC POUR ENVOYER LA TRAME
}

/**
 * @Brief ar1000_send_cmd
 */
void ar1000_send_cmd(uint8_t cmd, uint8_t size, char* data)
{
	ar1000_disable_touch();
	ar1000_send(cmd, size, data);
	// wait 50ms; (cf doc)
	ar1000_receive(cmd, size);
	ar1000_enable_touch();
}


//PUBLIC FUNCTIONS

/**
 * @brief ar1000_init Setup the device
 */
void ar1000_init()
{
	//set uart mode
	//set microcontroller M1 pin to 1... cf doc
	ar1000_uart = uart_getFreeDevice(); //WARNING: remapable pin ?
	uart_setBaudSpeed(ar1000_uart, 9600); //WARNING: baud rate unit ??? 
	//some other stuff ??
	uart_enable(ar1000_uart); //connected to pin 1 ????

	//TODO: set i2c mode
	//TODO: set spi mode
}

/**
 * @Brief ar1000_get_version
 */
void ar1000_get_version()
{
	uint8_t cmd = 0x10;
	uint8_t size = 1;
	// set SpeedThreshold register: low value is often but noisy, hight value is good but slow
	// Recommended Values: <4, 8, 16>

	uint8_t type = 0x00001010;
	// 7-6bits: 00: 8bits; 01: 10bits; 10: 12bits

	ar1000_send(cmd, size, data_vide!);
	ar1000_receive(cmd, size, data_vide!);
}

/**
 * @Brief ar1000_enable_touch
 */
void ar1000_enable_touch()
{
	uint8_t size = 1;
	uint8_t cmd = 0x12;
	ar1000_send(cmd, size, data_vide!);
	size = 2;
	ar1000_receive(cmd, size, data_vide!);
}

/**
 * @Brief ar1000_disable_touch
 */
void ar1000_disable_touch()
{
	ar1000_send(0x13, 1, data_vide!);
	ar1000_receive();
}

/**
 * @Brief ar1000_calibrate_mode
 */
void ar1000_calibrate_mode()
{
	ar1000_send(0x14, 1, data_vide!);
}

/**
 * @Brief ar1000_register_read
 */
void ar1000_register_read()
{
	ar1000_send(0x20, 1, data_vide!);
}

/**
 * @Brief ar1000_register_write
 */
void ar1000_register_write()
{
	ar1000_send(0x21, 1, data_vide!);

}

/**
 * @Brief ar1000_register_start_address_request
 */
void ar1000_register_start_address_request()
{
	ar1000_send(0x22, 1, data_vide!);

}

/**
 * @Brief ar1000_registers_write_to_eeprom
 */
void ar1000_registers_write_to_eeprom()
{
	ar1000_send(0x23, 1, data_vide!);

}

/**
 * @Brief ar1000_eeprom_read
 */
void ar1000_eeprom_read()
{
	ar1000_send(0x28, 1, data_vide!);

}

/**
 * @Brief ar1000_eeprom_write
 */
void ar1000_eeprom_write()
{
	ar1000_send(0x29, 1, data_vide!);

}

/**
 * @Brief ar1000_eeprom_write_to_regiters
 */
void ar1000_eeprom_write_to_regiters()
{
	ar1000_send(0x2B, 1, data_vide!);

}
