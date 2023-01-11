/**
 * @file nvm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date November 10, 2016, 06:01 PM
 *
 * @brief NVM (Non Volatile Memory) support drivers
 */

#ifndef NVM_H
#define NVM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nvm_device.h"

#include <driver/device.h>

// ========= byte manipulation ========
ssize_t nvm_read(uint32_t addr, char *data, size_t size);
ssize_t nvm_write(uint32_t addr, const char *data, size_t size);

// ========= page manipulation ========
ssize_t nvm_writePage(uint32_t addr, const char *data);
ssize_t nvm_erasePage(uint32_t addr);
ssize_t nvm_readPage(uint32_t addr, char *data);

// =========  address and page number translation  ========
uint16_t nvm_pageNumber(uint32_t addr);
uint32_t nvm_pageAddress(uint16_t pageNum);

// TODO temporary
void nvm_writeDoubleWord(uint32_t addrWord, const char *data);

#ifdef __cplusplus
}
#endif

#endif  // NVM_H
