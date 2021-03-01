/**
 * @file nvm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date novembre 10, 2016, 18:01
 *
 * @brief NVM (non volatile memory) support drivers
 */

#ifndef NVM_H
#define NVM_H

#include <driver/device.h>

// ========= byte manipulation ========
ssize_t nvm_read(uint32_t addr, char *data, size_t size);
ssize_t nvm_write(uint32_t addr, char *data, size_t size);

// ========= page manipulation ========
ssize_t nvm_writePage(uint32_t addr, char *data);
ssize_t nvm_erasePage(uint32_t addr);
ssize_t nvm_readPage(uint32_t addr, char *data);

// =========  address and page number translation  ========
uint16_t nvm_pageNumber(uint32_t addr);
uint32_t nvm_pageAddress(uint16_t pageNum);

#if defined(ARCHI_pic24ep) || defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) \
 || defined(ARCHI_pic24hj) || defined(ARCHI_dspic30f) || defined(ARCHI_dspic33ep) \
 || defined(ARCHI_dspic33ev) || defined(ARCHI_dspic33fj) || defined(ARCHI_dspic33ch) \
 || defined(ARCHI_dspic33ck)
 #include "nvm_pic24_dspic30f_dspic33.h"
#else
 #error Unsuported ARCHI
#endif

#endif // NVM_H
