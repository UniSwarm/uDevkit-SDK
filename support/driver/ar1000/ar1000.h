/**
 * @file ar1000.h
 * @author Charles-Antoine NOURY (CharlyBigoud)
 * @copyright Robotips 2016
 *
 * @date June 6, 2016, 9:10 PM 
 * 
 * @brief AR driver support
 */

#ifndef AR1000_H
#define AR1000_H

#include "driver/device.h"

#define AR1000_UART 1
#define AR1000_SPI  2
#define AR1000_I2C  2

void ar1000_init(void);

//AR1000 Commands
ssize_t ar1000_get_version();
void ar1000_enable_touch();
void ar1000_disable_touch();
void ar1000_calibrate_mode();
void ar1000_register_read();
void ar1000_register_write();
void ar1000_register_start_address_request();
void ar1000_registers_write_to_eeprom();
void ar1000_eeprom_read();
void ar1000_eeprom_write();
void ar1000_eeprom_write_to_regiters();

#endif //AR1000_H