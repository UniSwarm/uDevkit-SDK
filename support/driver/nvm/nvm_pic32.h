/**
 * @file nvm_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2023
 *
 * @date January 11, 2023, 10:56 AM
 *
 * @brief NVM (Non Volatile Memory) support drivers for PIC32MK,
 * PIC32MX, PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS60001121G :
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/60001121g.pdf
 */

#ifndef NVM_PIC32_H
#define NVM_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

#define NVM_FLASH_PAGE_BYTE  4096
#define NVM_FLASH_PAGE_MASK  0xFFFFF000
#define NVM_FLASH_PAGE_SHIFT 12
#define NVM_FLASH_ROW_BYTE   512
#define NVM_HAS_FLASH

#ifdef __cplusplus
}
#endif

#endif  // NVM_PIC32_H
