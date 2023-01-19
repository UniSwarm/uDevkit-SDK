/**
 * @file nvm.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
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

// =================== byte manipulation ==================
ssize_t nvm_read(nvm_addr addr, char *data, size_t size);
ssize_t nvm_write(nvm_addr addr, const char *data, size_t size);

// =================== page manipulation ==================
ssize_t nvm_writePage(nvm_addr addr, const char *data);
ssize_t nvm_erasePage(nvm_addr addr);
ssize_t nvm_readPage(nvm_addr addr, char *data);

// =========  address and page number translation  ========
uint16_t nvm_pageNumber(nvm_addr addr);
nvm_addr nvm_pageAddress(uint16_t pageNum);

// ====================== NVM status ======================
bool nvm_ready(void);
void nvm_waitForReady(void);

#ifdef __cplusplus
}
#endif

#endif  // NVM_H
