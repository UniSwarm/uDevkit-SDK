/**
 * @file ar1000.c
 * @author Charles-Antoine NOURY (CharlyBigoud)
 * @copyright Robotips 2016
 *
 * @date June 6, 2016, 9:10 PM 
 * 
 * @brief AR driver support
 */
 
#include "ar1000.h"

#include <xc.h>
#include <string.h>

#include "driver/uart.h"
#include "board.h"

#if AR1021_MODE == AR1021_UART
 rt_dev_t ar1000_uart;
#endif

#if AR1021_MODE == AR1021_I2C
 rt_dev_t ar1000_i2c;
#endif

#if AR1021_MODE == AR1021_SPI
 rt_dev_t ar1000_spi;
#endif

#define AR1000_CMD_ENABLE  0x12
#define AR1000_CMD_DISABLE 0x13

//PROTECTED FUNCTIONS
/**
 * @Brief ar1000_send
 */
ssize_t ar1000_send(uint8_t cmd, const char *data, size_t size)
{
    char trame[20];
    trame[0]=0x55;
    trame[1]=size+1;
    trame[2]=cmd;
    if(data != NULL)
        memcpy(trame+3, data, size);

    //set uart mode
    #if AR1021_MODE == AR1021_UART
    return uart_write(ar1000_uart, trame, size+3);
    #endif

    //TODO: set i2c mode
    #if AR1021_MODE == AR1021_I2C
    return 0;
    #endif
    
    //TODO: set spi mode
    #if AR1021_MODE == AR1021_SPI
    return 0;
    #endif
}

/**
 * @Brief ar1000_receive
 */
ssize_t ar1000_receive(uint8_t cmd, char *data, uint8_t size)
{
    return uart_read(ar1000_uart, data, size);
}

/**
 * @Brief ar1000_send_cmd
 */
void ar1000_send_cmd(uint8_t cmd, uint8_t size, char* data)
{
    ar1000_disable_touch();
    ar1000_send(cmd, data, size);

    //TODO: evaluate "status" value ??
    //TODO: wait 50ms; (cf doc)

    ar1000_receive(cmd, data, size);
    ar1000_enable_touch();
}


//PUBLIC FUNCTIONS

/**
 * @brief ar1000_init Setup the device
 */
int ar1000_init()
{
    int status = -1;

    //set uart mode
    //TODO a degade car ne devrait pas exister (au moins pour AR1021)
    #if AR1021_MODE == AR1021_UART
        AR1000_M1 = 1;
        AR1000_SDO = 0;
        ar1000_uart = uart_getFreeDevice();
        uart_setBaudSpeed(ar1000_uart, 9600);
        status = uart_enable(ar1000_uart);
    #endif

    //TODO: set i2c mode
    #if AR1021_MODE == AR1021_I2C
        // AR1000_M1 = 1;
        // AR1000_INT = ???
        // AR1000_SDO = 0;
        ar1000_i2c = i2c_getFreeDevice();
        i2c_setBaudSpeed(ar1000_i2c, 9600);
        status = i2c_enable(ar1000_i2c);
    #endif

    //TODO: set spi mode
    #if AR1021_MODE == AR1021_SPI
        return -1;
    #endif

    return status;
}

/**
 * @Brief ar1000_get_version
 */
// ssize_t ar1000_get_version()
// {
//     uint8_t cmd = 0x10;
//     uint8_t size = 1;
//     // set SpeedThreshold register: low value is often but noisy, hight value is good but slow
//     // Recommended Values: <4, 8, 16>

//     uint8_t type = 0x00001010;
//     // 7-6bits: 00: 8bits; 01: 10bits; 10: 12bits

//     char data[20];
//     ar1000_send(cmd, data, size);
//     return ar1000_receive(cmd, data, size);

//     // return uart_read(ar1000_uart, data, 20);
// }

/**
 * @Brief enable the touch screen
 */
ssize_t ar1000_enable_touch()
{
    char data[20];
    ar1000_send(AR1000_CMD_ENABLE, NULL, 0);
    return uart_read(ar1000_uart, data, 20);
}

/**
 * @Brief disable the touch screen
 */
ssize_t ar1000_disable_touch()
{
    char data[20];
    ar1000_send(AR1000_CMD_DISABLE, NULL, 0);
    return uart_read(ar1000_uart, data, 20);
}

// /**
//  * @Brief ar1000_calibrate_mode
//  */
// void ar1000_calibrate_mode()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x14;

// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_register_read
//  */
// void ar1000_register_read()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x20;

// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_register_write
//  */
// void ar1000_register_write()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x21;
	
// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_register_start_address_request
//  */
// void ar1000_register_start_address_request()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x22;
	
// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_registers_write_to_eeprom
//  */
// void ar1000_registers_write_to_eeprom()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x23;
	
// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_eeprom_read
//  */
// void ar1000_eeprom_read()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x28;
	
// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_eeprom_write
//  */
// void ar1000_eeprom_write()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x29;
	
// 	ar1000_send(cmd, data_vide, size);
// }

// /**
//  * @Brief ar1000_eeprom_write_to_regiters
//  */
// void ar1000_eeprom_write_to_regiters()
// {
// 	uint8_t size = 1;
// 	uint8_t cmd = 0x2B;
	
// 	ar1000_send(cmd, data_vide, size);
// }
