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

#include <stdint.h>

void ar1000_init(void);
// char ar1000_status_value(); //BULLSHIT

//TODO: a cacher dans .c
void ar1000_send(uint8_t cmd, uint8_t size);
void ar1000_received(uint8_t cmd, uint8_t size);
void ar1000_send_cmd(uint8_t cmd, uint8_t size, char* data);

void ar1000_get_version();
void ar1000_enable_touch();
void ar1000_disable_touch();


#endif //AR1000_H