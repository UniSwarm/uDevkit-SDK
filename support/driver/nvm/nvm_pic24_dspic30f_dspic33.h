/**
 * @file nvm_pic24_dspic30f_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020
 *
 * @date march 20, 2020, 08:32
 *
 * @brief NVM (non volatile memory) support drivers for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#ifndef NVM_PIC24_DSPIC30F_DSPIC33_H
#define NVM_PIC24_DSPIC30F_DSPIC33_H

#if defined(ARCHI_dspic30f)
  #define NVM_FLASH_PAGE_BYTE     128
  #define NVM_FLASH_PAGE_MASK   0xFFFFFF00
  #define NVM_FLASH_PAGE_SHIFT    7
  #define NVM_FLASH_ROW_BYTE      128
  #define NVM_HAS_FLASH


  #define NVM_EE_WORD         2
  #define NVM_EE_ROW         32
  #define NVM_HAS_EPROM

#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) \
 || defined(ARCHI_dspic33fj)
  #define NVM_FLASH_PAGE_BYTE     2048
  #define NVM_FLASH_PAGE_MASK   0xFFFFF800
  #define NVM_FLASH_PAGE_SHIFT    11
  #define NVM_FLASH_ROW_BYTE      256
  #define NVM_HAS_FLASH


#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev) \
 || defined(ARCHI_dspic33ch) || defined(ARCHI_dspic33ck)
  #define NVM_FLASH_PAGE_BYTE     4096
  #define NVM_FLASH_PAGE_MASK   0xFFFFF000
  #define NVM_FLASH_PAGE_SHIFT    12
  #define NVM_FLASH_ROW_BYTE      512
  #define NVM_HAS_FLASH

#endif

#endif // NVM_PIC24_DSPIC30F_DSPIC33_H
