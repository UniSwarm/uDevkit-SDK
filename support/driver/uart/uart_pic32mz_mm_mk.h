/**
 * @file uart_pic32mz_mm_mk.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2019
 *
 * @date October 06, 2016, 11:15 PM
 *
 * @brief Uart support for udevkit for PIC32MM, PIC32MK, PIC32MZDA,
 * PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61107G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf
 */

#ifndef UART_PIC32MZ_MM_MK_H
#define UART_PIC32MZ_MM_MK_H

#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) \
 || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) \
 || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036)
 #define UART_COUNT 2
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) \
 || defined(DEVICE_32MM0064GPM064) || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) \
 || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064) || defined(DEVICE_32MM0256GPM028) \
 || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)
 #define UART_COUNT 3
#elif defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) \
 || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100) \
 || defined(DEVICE_32MK0512GPL064) || defined(DEVICE_32MK0512GPL100) || defined(DEVICE_32MK0512MCF064) \
 || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) \
 || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100) || defined(DEVICE_32MK1024GPE064) \
 || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100) \
 || defined(DEVICE_32MK1024GPL064) || defined(DEVICE_32MK1024GPL100) || defined(DEVICE_32MK1024MCF064) \
 || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100) \
 || defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) \
 || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFF100) \
 || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK064) \
 || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144) \
 || defined(DEVICE_32MZ1024ECG064) || defined(DEVICE_32MZ1024ECG100) || defined(DEVICE_32MZ1024ECG124) \
 || defined(DEVICE_32MZ1024ECG144) || defined(DEVICE_32MZ1024ECH064) || defined(DEVICE_32MZ1024ECH100) \
 || defined(DEVICE_32MZ1024ECH124) || defined(DEVICE_32MZ1024ECH144) || defined(DEVICE_32MZ1024ECM064) \
 || defined(DEVICE_32MZ1024ECM100) || defined(DEVICE_32MZ1024ECM124) || defined(DEVICE_32MZ1024ECM144) \
 || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) \
 || defined(DEVICE_32MZ1024EFE144) || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFF100) \
 || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG064) \
 || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144) \
 || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) \
 || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFK100) \
 || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM064) \
 || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) \
 || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) \
 || defined(DEVICE_32MZ1025DAB169) || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) \
 || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169) \
 || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176) \
 || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) \
 || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) \
 || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176) || defined(DEVICE_32MZ2025DAA169) \
 || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169) \
 || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) \
 || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) \
 || defined(DEVICE_32MZ2048ECG064) || defined(DEVICE_32MZ2048ECG100) || defined(DEVICE_32MZ2048ECG124) \
 || defined(DEVICE_32MZ2048ECG144) || defined(DEVICE_32MZ2048ECH064) || defined(DEVICE_32MZ2048ECH100) \
 || defined(DEVICE_32MZ2048ECH124) || defined(DEVICE_32MZ2048ECH144) || defined(DEVICE_32MZ2048ECM064) \
 || defined(DEVICE_32MZ2048ECM100) || defined(DEVICE_32MZ2048ECM124) || defined(DEVICE_32MZ2048ECM144) \
 || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFG124) \
 || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFH100) \
 || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM064) \
 || defined(DEVICE_32MZ2048EFM100) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) \
 || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176) || defined(DEVICE_32MZ2064DAA288) \
 || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288) \
 || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) \
 || defined(DEVICE_32MZ2064DAH176)
 #define UART_COUNT 6
#else
 #define UART_COUNT 0
#endif

// Maximum baud rate generator divisor
#if defined(ARCHI_pic32mk)
 #define UART_MAXBRG 0x000FFFFF    // 20 bits divisor
#else
 #define UART_MAXBRG 0x0000FFFF    // 16 bits divisor
#endif

#if defined(ARCHI_pic32mm) || defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) \
 || defined(ARCHI_pic32mzda)
 #define uart_getClock(d) sysclock_periphFreq(SYSCLOCK_CLOCK_UART)
#else
 uint32_t uart_getClock(rt_dev_t device);
#endif

#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 // interrupt bits helpers for MZ
 #ifndef _U1RXIE
  #define _U1EIE  IEC3bits.U1EIE
  #define _U1EIF  IFS3bits.U1EIF
  #define _U1EIP  IPC28bits.U1EIP
  #define _U1RXIE IEC3bits.U1RXIE
  #define _U1RXIF IFS3bits.U1RXIF
  #define _U1RXIP IPC28bits.U1RXIP
  #define _U1TXIE IEC3bits.U1TXIE
  #define _U1TXIF IFS3bits.U1TXIF
  #define _U1TXIP IPC28bits.U1TXIP
  #define _U2EIE  IEC4bits.U2EIE
  #define _U2EIF  IFS4bits.U2EIF
  #define _U2EIP  IPC36bits.U2EIP
  #define _U2RXIE IEC4bits.U2RXIE
  #define _U2RXIF IFS4bits.U2RXIF
  #define _U2RXIP IPC36bits.U2RXIP
  #define _U2TXIE IEC4bits.U2TXIE
  #define _U2TXIF IFS4bits.U2TXIF
  #define _U2TXIP IPC36bits.U2TXIP
  #define _U3EIE  IEC4bits.U3EIE
  #define _U3EIF  IFS4bits.U3EIF
  #define _U3EIP  IPC39bits.U3EIP
  #define _U3RXIE IEC4bits.U3RXIE
  #define _U3RXIF IFS4bits.U3RXIF
  #define _U3RXIP IPC39bits.U3RXIP
  #define _U3TXIE IEC4bits.U3TXIE
  #define _U3TXIF IFS4bits.U3TXIF
  #define _U3TXIP IPC39bits.U3TXIP
  #define _U4EIE  IEC5bits.U4EIE
  #define _U4EIF  IFS5bits.U4EIF
  #define _U4EIP  IPC42bits.U4EIP
  #define _U4RXIE IEC5bits.U4RXIE
  #define _U4RXIF IFS5bits.U4RXIF
  #define _U4RXIP IPC42bits.U4RXIP
  #define _U4TXIE IEC5bits.U4TXIE
  #define _U4TXIF IFS5bits.U4TXIF
  #define _U4TXIP IPC43bits.U4TXIP
  #define _U5EIE  IEC5bits.U5EIE
  #define _U5EIF  IFS5bits.U5EIF
  #define _U5EIP  IPC44bits.U5EIP
  #define _U5RXIE IEC5bits.U5RXIE
  #define _U5RXIF IFS5bits.U5RXIF
  #define _U5RXIP IPC45bits.U5RXIP
  #define _U5TXIE IEC5bits.U5TXIE
  #define _U5TXIF IFS5bits.U5TXIF
  #define _U5TXIP IPC45bits.U5TXIP
  #define _U6EIE  IEC5bits.U6EIE
  #define _U6EIF  IFS5bits.U6EIF
  #define _U6EIP  IPC47bits.U6EIP
  #define _U6RXIE IEC5bits.U6RXIE
  #define _U6RXIF IFS5bits.U6RXIF
  #define _U6RXIP IPC47bits.U6RXIP
  #define _U6TXIE IEC5bits.U6TXIE
  #define _U6TXIF IFS5bits.U6TXIF
  #define _U6TXIP IPC47bits.U6TXIP
 #endif
 #define UIPR IPL3SRS

#elif defined(ARCHI_pic32mm)

 #if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) \
  || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) \
  || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036)
  // interrupt bits helpers for MM GPL
  #ifndef _U1RXIE
   #define _U1EIE  IEC0bits.U1EIE
   #define _U1EIF  IFS0bits.U1EIF
   #define _U1EIP  IPC6bits.U1EIP
   #define _U1RXIE IEC0bits.U1RXIE
   #define _U1RXIF IFS0bits.U1RXIF
   #define _U1RXIP IPC5bits.U1RXIP
   #define _U1TXIE IEC0bits.U1TXIE
   #define _U1TXIF IFS0bits.U1TXIF
   #define _U1TXIP IPC6bits.U1TXIP
   #define _U2EIE  IEC1bits.U2EIE
   #define _U2EIF  IFS1bits.U2EIF
   #define _U2EIP  IPC10bits.U2EIP
   #define _U2RXIE IEC1bits.U2RXIE
   #define _U2RXIF IFS1bits.U2RXIF
   #define _U2RXIP IPC10bits.U2RXIP
   #define _U2TXIE IEC1bits.U2TXIE
   #define _U2TXIF IFS1bits.U2TXIF
   #define _U2TXIP IPC10bits.U2TXIP
  #endif
 #define UIPR IPL3SRS
 #else
  // interrupt bits helpers for MM GPM
  #ifndef _U1RXIE
   #define _U1EIE  IEC1bits.U1EIE
   #define _U1EIF  IFS1bits.U1EIF
   #define _U1EIP  IPC13bits.U1EIP
   #define _U1RXIE IEC1bits.U1RXIE
   #define _U1RXIF IFS1bits.U1RXIF
   #define _U1RXIP IPC13bits.U1RXIP
   #define _U1TXIE IEC1bits.U1TXIE
   #define _U1TXIF IFS1bits.U1TXIF
   #define _U1TXIP IPC13bits.U1TXIP
   #define _U2EIE  IEC1bits.U2EIE
   #define _U2EIF  IFS1bits.U2EIF
   #define _U2EIP  IPC14bits.U2EIP
   #define _U2RXIE IEC1bits.U2RXIE
   #define _U2RXIF IFS1bits.U2RXIF
   #define _U2RXIP IPC14bits.U2RXIP
   #define _U2TXIE IEC1bits.U2TXIE
   #define _U2TXIF IFS1bits.U2TXIF
   #define _U2TXIP IPC14bits.U2TXIP
   #define _U3EIE  IEC1bits.U3EIE
   #define _U3EIF  IFS1bits.U3EIF
   #define _U3EIP  IPC15bits.U3EIP
   #define _U3RXIE IEC1bits.U3RXIE
   #define _U3RXIF IFS1bits.U3RXIF
   #define _U3RXIP IPC14bits.U3RXIP
   #define _U3TXIE IEC1bits.U3TXIE
   #define _U3TXIF IFS1bits.U3TXIF
   #define _U3TXIP IPC15bits.U3TXIP
  #endif
 #define UIPR IPL3SRS
 #endif

#elif defined(ARCHI_pic32mk)
 #ifndef _U1RXIE
  #define _U1EIE  IEC1bits.U1EIE
  #define _U1EIF  IFS1bits.U1EIF
  #define _U1EIP  IPC9bits.U1EIP
  #define _U1RXIE IEC1bits.U1RXIE
  #define _U1RXIF IFS1bits.U1RXIF
  #define _U1RXIP IPC9bits.U1RXIP
  #define _U1TXIE IEC1bits.U1TXIE
  #define _U1TXIF IFS1bits.U1TXIF
  #define _U1TXIP IPC10bits.U1TXIP
  #define _U2EIE  IEC1bits.U2EIE
  #define _U2EIF  IFS1bits.U2EIF
  #define _U2EIP  IPC14bits.U2EIP
  #define _U2RXIE IEC1bits.U2RXIE
  #define _U2RXIF IFS1bits.U2RXIF
  #define _U2RXIP IPC14bits.U2RXIP
  #define _U2TXIE IEC1bits.U2TXIE
  #define _U2TXIF IFS1bits.U2TXIF
  #define _U2TXIP IPC14bits.U2TXIP
  #define _U3EIE  IEC1bits.U3EIE
  #define _U3EIF  IFS1bits.U3EIF
  #define _U3EIP  IPC15bits.U3EIP
  #define _U3RXIE IEC1bits.U3RXIE
  #define _U3RXIF IFS1bits.U3RXIF
  #define _U3RXIP IPC15bits.U3RXIP
  #define _U3TXIE IEC2bits.U3TXIE
  #define _U3TXIF IFS2bits.U3TXIF
  #define _U3TXIP IPC16bits.U3TXIP
  #define _U4EIE  IEC2bits.U4EIE
  #define _U4EIF  IFS2bits.U4EIF
  #define _U4EIP  IPC16bits.U4EIP
  #define _U4RXIE IEC2bits.U4RXIE
  #define _U4RXIF IFS2bits.U4RXIF
  #define _U4RXIP IPC16bits.U4RXIP
  #define _U4TXIE IEC2bits.U4TXIE
  #define _U4TXIF IFS2bits.U4TXIF
  #define _U4TXIP IPC16bits.U4TXIP
  #define _U5EIE  IEC2bits.U5EIE
  #define _U5EIF  IFS2bits.U5EIF
  #define _U5EIP  IPC17bits.U5EIP
  #define _U5RXIE IEC2bits.U5RXIE
  #define _U5RXIF IFS2bits.U5RXIF
  #define _U5RXIP IPC17bits.U5RXIP
  #define _U5TXIE IEC2bits.U5TXIE
  #define _U5TXIF IFS2bits.U5TXIF
  #define _U5TXIP IPC17bits.U5TXIP
  #define _U6EIE  IEC5bits.U6EIE
  #define _U6EIF  IFS5bits.U6EIF
  #define _U6EIP  IPC41bits.U6EIP
  #define _U6RXIE IEC5bits.U6RXIE
  #define _U6RXIF IFS5bits.U6RXIF
  #define _U6RXIP IPC41bits.U6RXIP
  #define _U6TXIE IEC5bits.U6TXIE
  #define _U6TXIF IFS5bits.U6TXIF
  #define _U6TXIP IPC41bits.U6TXIP
 #endif
 #define UIPR IPL3AUTO
#endif

#endif // UART_PIC32MZ_MM_MK_H
