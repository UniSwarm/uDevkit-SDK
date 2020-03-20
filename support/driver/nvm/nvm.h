/**
 * @file nvm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date novembre 10, 2016, 18:01
 *
 * @brief NVM (non volatile memory) support drivers
 */

#ifndef NVM_H
#define NVM_H

#include <driver/device.h>


void nvm_read(uint32_t address, char *data, size_t size);

void nvm_erase_page(uint32_t address);

void nvm_write(uint32_t address, char *data, size_t size);

void nvm_write_double_word(uint32_t address, char *data);


#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ch) \
 || defined(ARCHI_dspic33ck)
 #include "nvm_pic24_dspic30f_dspic33.h"
#else
 #error Unsuported ARCHI
#endif

#endif // NVM_H
