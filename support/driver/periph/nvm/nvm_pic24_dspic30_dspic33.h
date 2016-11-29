/**
 * @file nvm_pic24_dspic30_dspic33.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date novembre 10, 2016, 18:01
 *
 * @brief NVM (non volatile memory) support drivers for dsPIC30F, dsPIC33FJ, dsPIC33EP, dsPIC33EV,
 * PIC24F, PIC24FJ, PIC24EP and PIC24HJ
 */

#ifndef NVM_PIC24_DSPIC30_DSPIC33_H
#define NVM_PIC24_DSPIC30_DSPIC33_H

typedef unsigned long prog_ptr;

#if defined(ARCHI_dspic30f)
  #define NVM_FLASH_PAGE     32
  #define NVM_FLASH_ROW      32
  #define NVM_HAS_FLASH

  #define NVM_EE_WORD         2
  #define NVM_EE_ROW         32
  #define NVM_HAS_EPROM

#elif defined(ARCHI_pic24f) || defined(ARCHI_pic24fj) || defined(ARCHI_pic24hj) || defined(ARCHI_dspic33fj)
  #define NVM_FLASH_PAGE     512
  #define NVM_FLASH_ROW      64
  #define NVM_HAS_FLASH

#elif defined(ARCHI_pic24ep) || defined(ARCHI_dspic33ep) || defined(ARCHI_dspic33ev)
  #define NVM_FLASH_PAGE     1024
  #define NVM_FLASH_ROW      128
  #define NVM_HAS_FLASH

#endif

#endif // NVM_PIC24_DSPIC30_DSPIC33_H
