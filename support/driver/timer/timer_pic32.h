/**
 * @file timer_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 *
 * @date October 06, 2016, 11:15 PM
 *
 * @brief Timer support for rtprog for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61105F :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf
 */

#ifndef TIMER_PIC32_H
#define TIMER_PIC32_H

#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) \
 || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) \
 || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036)
 #define TIMER_COUNT 1
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) \
 || defined(DEVICE_32MM0064GPM064) || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) \
 || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064) || defined(DEVICE_32MM0256GPM028) \
 || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)
 #define TIMER_COUNT 3
#elif defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) \
 || defined(DEVICE_32MX120F032B) || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) \
 || defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C) \
 || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX130F128L) \
 || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B) \
 || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX150F256H) \
 || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX154F128D) \
 || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX170F256D) || defined(DEVICE_32MX170F512H) \
 || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX174F256D) \
 || defined(DEVICE_32MX175F256B) || defined(DEVICE_32MX175F256D) || defined(DEVICE_32MX210F016B) \
 || defined(DEVICE_32MX210F016C) || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032B) \
 || defined(DEVICE_32MX220F032C) || defined(DEVICE_32MX220F032D) || defined(DEVICE_32MX230F064B) \
 || defined(DEVICE_32MX230F064C) || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX230F128H) \
 || defined(DEVICE_32MX230F128L) || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX230F256D) \
 || defined(DEVICE_32MX250F128B) || defined(DEVICE_32MX250F128C) || defined(DEVICE_32MX250F128D) \
 || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX250F256L) || defined(DEVICE_32MX254F128B) \
 || defined(DEVICE_32MX254F128D) || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX270F256D) \
 || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX274F256B) \
 || defined(DEVICE_32MX274F256D) || defined(DEVICE_32MX275F256B) || defined(DEVICE_32MX320F032H) \
 || defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) || defined(DEVICE_32MX320F128L) \
 || defined(DEVICE_32MX330F064H) || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX340F128H) \
 || defined(DEVICE_32MX340F128L) || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H) \
 || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F128L) || defined(DEVICE_32MX350F256H) \
 || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX360F256L) || defined(DEVICE_32MX360F512L) \
 || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX370F512L) || defined(DEVICE_32MX420F032H) \
 || defined(DEVICE_32MX430F064H) || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX440F128H) \
 || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX440F256H) || defined(DEVICE_32MX440F512H) \
 || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F128L) || defined(DEVICE_32MX450F256H) \
 || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX460F256L) || defined(DEVICE_32MX460F512L) \
 || defined(DEVICE_32MX470F512H) || defined(DEVICE_32MX470F512L) || defined(DEVICE_32MX530F128H) \
 || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L) \
 || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX564F064H) \
 || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L) \
 || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX570F512L) || defined(DEVICE_32MX575F256H) \
 || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L) \
 || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) \
 || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L) \
 || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512H) \
 || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L) \
 || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) \
 || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)
 #define TIMER_COUNT 5
#elif defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) \
 || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) \
 || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100) || defined(DEVICE_32MK1024GPE064) \
 || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) \
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
 #define TIMER_COUNT 9
#else
 #define TIMER_COUNT 0
#endif

#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
 // interrupt bits helpers for PIC32MZ
 #ifndef _T1IE
  #define _T1IE   IEC0bits.T1IE
  #define _T1IF   IFS0bits.T1IF
  #define _T1IP   IPC1bits.T1IP
  #define _T1IS   IPC1bits.T1IS
  #define _T2IE   IEC0bits.T2IE
  #define _T2IF   IFS0bits.T2IF
  #define _T2IP   IPC2bits.T2IP
  #define _T2IS   IPC2bits.T2IS
  #define _T3IE   IEC0bits.T3IE
  #define _T3IF   IFS0bits.T3IF
  #define _T3IP   IPC3bits.T3IP
  #define _T3IS   IPC3bits.T3IS
  #define _T4IE   IEC0bits.T4IE
  #define _T4IF   IFS0bits.T4IF
  #define _T4IP   IPC4bits.T4IP
  #define _T4IS   IPC4bits.T4IS
  #define _T5IE   IEC0bits.T5IE
  #define _T5IF   IFS0bits.T5IF
  #define _T5IP   IPC6bits.T5IP
  #define _T5IS   IPC6bits.T5IS
  #define _T6IE   IEC0bits.T6IE
  #define _T6IF   IFS0bits.T6IF
  #define _T6IP   IPC7bits.T6IP
  #define _T6IS   IPC7bits.T6IS
  #define _T7IE   IEC1bits.T7IE
  #define _T7IF   IFS1bits.T7IF
  #define _T7IP   IPC8bits.T7IP
  #define _T7IS   IPC8bits.T7IS
  #define _T8IE   IEC1bits.T8IE
  #define _T8IF   IFS1bits.T8IF
  #define _T8IP   IPC9bits.T8IP
  #define _T8IS   IPC9bits.T8IS
  #define _T9IE   IEC1bits.T9IE
  #define _T9IF   IFS1bits.T9IF
  #define _T9IP   IPC10bits.T9IP
  #define _T9IS   IPC10bits.T9IS
 #endif
 #define TIPR IPL4SRS

#elif defined(ARCHI_pic32mm)
 #if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) \
  || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) \
  || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036)
  // interrupt bits helpers for PIC32MM GPL
  #ifndef _T1IE
   #define _T1IE   IEC0bits.T1IE
   #define _T1IF   IFS0bits.T1IF
   #define _T1IP   IPC2bits.T1IP
   #define _T1IS   IPC2bits.T1IS
  #endif
 #else
  // interrupt bits helpers for PIC32MM GPM
  #ifndef _T1IE
   #define _T1IE   IEC0bits.T1IE
   #define _T1IF   IFS0bits.T1IF
   #define _T1IP   IPC4bits.T1IP
   #define _T1IS   IPC4bits.T1IS
   #define _T2IE   IEC0bits.T2IE
   #define _T2IF   IFS0bits.T2IF
   #define _T2IP   IPC4bits.T2IP
   #define _T2IS   IPC4bits.T2IS
   #define _T3IE   IEC0bits.T3IE
   #define _T3IF   IFS0bits.T3IF
   #define _T3IP   IPC4bits.T3IP
   #define _T3IS   IPC4bits.T3IS
  #endif
 #endif
 #define TIPR IPL4SRS
 
#elif defined(ARCHI_pic32mk)
  // interrupt bits helpers for PIC32MK
 #ifndef _T1IE
  #define _T1IE   IEC0bits.T1IE
  #define _T1IF   IFS0bits.T1IF
  #define _T1IP   IPC1bits.T1IP
  #define _T1IS   IPC1bits.T1IS
  #define _T2IE   IEC0bits.T2IE
  #define _T2IF   IFS0bits.T2IF
  #define _T2IP   IPC2bits.T2IP
  #define _T2IS   IPC2bits.T2IS
  #define _T3IE   IEC0bits.T3IE
  #define _T3IF   IFS0bits.T3IF
  #define _T3IP   IPC3bits.T3IP
  #define _T3IS   IPC3bits.T3IS
  #define _T4IE   IEC0bits.T4IE
  #define _T4IF   IFS0bits.T4IF
  #define _T4IP   IPC4bits.T4IP
  #define _T4IS   IPC4bits.T4IS
  #define _T5IE   IEC0bits.T5IE
  #define _T5IF   IFS0bits.T5IF
  #define _T5IP   IPC6bits.T5IP
  #define _T5IS   IPC6bits.T5IS
  #define _T6IE   IEC2bits.T6IE
  #define _T6IF   IFS2bits.T6IF
  #define _T6IP   IPC19bits.T6IP
  #define _T6IS   IPC19bits.T6IS
  #define _T7IE   IEC2bits.T7IE
  #define _T7IF   IFS2bits.T7IF
  #define _T7IP   IPC20bits.T7IP
  #define _T7IS   IPC20bits.T7IS
  #define _T8IE   IEC2bits.T8IE
  #define _T8IF   IFS2bits.T8IF
  #define _T8IP   IPC21bits.T8IP
  #define _T8IS   IPC21bits.T8IS
  #define _T9IE   IEC2bits.T9IE
  #define _T9IF   IFS2bits.T9IF
  #define _T9IP   IPC22bits.T9IP
  #define _T9IS   IPC22bits.T9IS
 #endif
 #define TIPR IPL4SRS
 
#elif defined(ARCHI_pic32mx)
  // interrupt bits helpers for PIC32MX
 #ifndef _T1IE
  #define _T1IE   IEC0bits.T1IE
  #define _T1IF   IFS0bits.T1IF
  #define _T1IP   IPC1bits.T1IP
  #define _T1IS   IPC1bits.T1IS
  #define _T2IE   IEC0bits.T2IE
  #define _T2IF   IFS0bits.T2IF
  #define _T2IP   IPC2bits.T2IP
  #define _T2IS   IPC2bits.T2IS
  #define _T3IE   IEC0bits.T3IE
  #define _T3IF   IFS0bits.T3IF
  #define _T3IP   IPC3bits.T3IP
  #define _T3IS   IPC3bits.T3IS
  #define _T4IE   IEC0bits.T4IE
  #define _T4IF   IFS0bits.T4IF
  #define _T4IP   IPC4bits.T4IP
  #define _T4IS   IPC4bits.T4IS
  #define _T5IE   IEC0bits.T5IE
  #define _T5IF   IFS0bits.T5IF
  #define _T5IP   IPC5bits.T5IP
  #define _T5IS   IPC5bits.T5IS
 #endif
 #define TIPR IPL4SOFT
#endif

#endif // TIMER_PIC32_H
