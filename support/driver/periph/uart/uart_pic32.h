/**
 * @file uart_pic32.h
 * @author Sebastien CAUX (sebcaux) \
 * @copyright Robotips 2016-2017
 *
 * @date October 06, 2016, 11:15 PM
 *
 * @brief Uart support for rtprog for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61107G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf
 */

#ifndef UART_PIC32_H
#define UART_PIC32_H

#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) \
 || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) \
 || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036) \
 || defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) \
 || defined(DEVICE_32MX120F032B) || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) \
 || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C) || defined(DEVICE_32MX130F064D) \
 || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B) \
 || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX170F256B) \
 || defined(DEVICE_32MX170F256D) || defined(DEVICE_32MX210F016B) || defined(DEVICE_32MX210F016C) \
 || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032B) || defined(DEVICE_32MX220F032C) \
 || defined(DEVICE_32MX220F032D) || defined(DEVICE_32MX230F064B) || defined(DEVICE_32MX230F064C) \
 || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX230F256D) \
 || defined(DEVICE_32MX250F128B) || defined(DEVICE_32MX250F128C) || defined(DEVICE_32MX250F128D) \
 || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX270F256D) || defined(DEVICE_32MX270F256DB) \
 || defined(DEVICE_32MX320F032H) || defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) \
 || defined(DEVICE_32MX320F128L) || defined(DEVICE_32MX340F128H) || defined(DEVICE_32MX340F128L) \
 || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H) || defined(DEVICE_32MX360F256L) \
 || defined(DEVICE_32MX360F512L) || defined(DEVICE_32MX420F032H) || defined(DEVICE_32MX440F128H) \
 || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX440F256H) || defined(DEVICE_32MX440F512H) \
 || defined(DEVICE_32MX460F256L) || defined(DEVICE_32MX460F512L) || defined(DEVICE_32WK2057GPB132) \
 || defined(DEVICE_32WK2057GPD132)
 #define UART_COUNT 2
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) \
 || defined(DEVICE_32MM0064GPM064) || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) \
 || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064) || defined(DEVICE_32MM0256GPM028) \
 || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)
 #define UART_COUNT 3
#elif defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX150F256H) \
 || defined(DEVICE_32MX170F512H) || defined(DEVICE_32MX230F128H) || defined(DEVICE_32MX250F256H) \
 || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX550F256H) \
 || defined(DEVICE_32MX570F512H)
 #define UART_COUNT 4
#elif defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX170F512L) \
 || defined(DEVICE_32MX230F128L) || defined(DEVICE_32MX250F256L) || defined(DEVICE_32MX270F512L) \
 || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512L) \
 || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX350F128L) || defined(DEVICE_32MX350F256L) \
 || defined(DEVICE_32MX370F512L) || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX450F128L) \
 || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX470F512L) || defined(DEVICE_32MX470F512LB)
 #define UART_COUNT 5
#elif defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MX330F064H) \
 || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F256H) || defined(DEVICE_32MX370F512H) \
 || defined(DEVICE_32MX430F064H) || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F256H) \
 || defined(DEVICE_32MX450F256HB) || defined(DEVICE_32MX470F512H) || defined(DEVICE_32MX534F064H) \
 || defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L) \
 || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX575F256H) \
 || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L) \
 || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) \
 || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L) \
 || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512H) \
 || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L) \
 || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) \
 || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L) \
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
 || defined(DEVICE_32MZ2064DAH176) || defined(DEVICE_32PR0000DAD288) || defined(DEVICE_32PR0000DAD288EMU)
 #define UART_COUNT 6
#else
 #define UART_COUNT 0
#endif

// interrupt bits helpers for UART1
#ifndef _U1RXIP
 #define _U1RXIP  IPC28bits.U1RXIP
#endif
#ifndef _U1RXIF
 #define _U1RXIF  IFS3bits.U1RXIF
#endif
#ifndef _U1RXIE
 #define _U1RXIE  IEC3bits.U1RXIE
#endif
#ifndef _U1TXIP
 #define _U1TXIP  IPC28bits.U1TXIP
#endif
#ifndef _U1TXIF
 #define _U1TXIF  IFS3bits.U1TXIF
#endif
#ifndef _U1TXIE
 #define _U1TXIE  IEC3bits.U1TXIE
#endif
#ifndef _U1EIP
 #define _U1EIP   IPC28bits.U1EIP
#endif
#ifndef _U1EIF
 #define _U1EIF   IFS3bits.U1TXIF
#endif
#ifndef _U1EIE
 #define _U1EIE   IEC3bits.U1TXIE
#endif

// interrupt bits helpers for UART2
#ifndef _U2RXIP
 #define _U2RXIP  IPC36bits.U2RXIP
#endif
#ifndef _U2RXIF
 #define _U2RXIF  IFS4bits.U2RXIF
#endif
#ifndef _U2RXIE
 #define _U2RXIE  IEC4bits.U2RXIE
#endif
#ifndef _U2TXIP
 #define _U2TXIP  IPC36bits.U2TXIP
#endif
#ifndef _U2TXIF
 #define _U2TXIF  IFS4bits.U2TXIF
#endif
#ifndef _U2TXIE
 #define _U2TXIE  IEC4bits.U2TXIE
#endif
#ifndef _U2EIP
 #define _U2EIP   IPC36bits.U2EIP
#endif
#ifndef _U2EIF
 #define _U2EIF   IFS4bits.U2TXIF
#endif
#ifndef _U2EIE
 #define _U2EIE   IEC4bits.U2TXIE
#endif

// interrupt bits helpers for UART3
#ifndef _U3RXIP
 #define _U3RXIP  IPC39bits.U3RXIP
#endif
#ifndef _U3RXIF
 #define _U3RXIF  IFS4bits.U3RXIF
#endif
#ifndef _U3RXIE
 #define _U3RXIE  IEC4bits.U3RXIE
#endif
#ifndef _U3TXIP
 #define _U3TXIP  IPC39bits.U3TXIP
#endif
#ifndef _U3TXIF
 #define _U3TXIF  IFS4bits.U3TXIF
#endif
#ifndef _U3TXIE
 #define _U3TXIE  IEC4bits.U3TXIE
#endif
#ifndef _U3EIP
 #define _U3EIP   IPC39bits.U3EIP
#endif
#ifndef _U3EIF
 #define _U3EIF   IFS4bits.U3TXIF
#endif
#ifndef _U3EIE
 #define _U3EIE   IEC4bits.U3TXIE
#endif

// interrupt bits helpers for UART4
#ifndef _U4RXIP
 #define _U4RXIP  IPC42bits.U4RXIP
#endif
#ifndef _U4RXIF
 #define _U4RXIF  IFS5bits.U4RXIF
#endif
#ifndef _U4RXIE
 #define _U4RXIE  IEC5bits.U4RXIE
#endif
#ifndef _U4TXIP
 #define _U4TXIP  IPC43bits.U4TXIP
#endif
#ifndef _U4TXIF
 #define _U4TXIF  IFS5bits.U4TXIF
#endif
#ifndef _U4TXIE
 #define _U4TXIE  IEC5bits.U4TXIE
#endif
#ifndef _U4EIP
 #define _U4EIP   IPC42bits.U4EIP
#endif
#ifndef _U4EIF
 #define _U4EIF   IFS5bits.U4TXIF
#endif
#ifndef _U4EIE
 #define _U4EIE   IEC5bits.U4TXIE
#endif

// interrupt bits helpers for UART5
#ifndef _U5RXIP
 #define _U5RXIP  IPC45bits.U5RXIP
#endif
#ifndef _U5RXIF
 #define _U5RXIF  IFS5bits.U5RXIF
#endif
#ifndef _U5RXIE
 #define _U5RXIE  IEC5bits.U5RXIE
#endif
#ifndef _U5TXIP
 #define _U5TXIP  IPC45bits.U5TXIP
#endif
#ifndef _U5TXIF
 #define _U5TXIF  IFS5bits.U5TXIF
#endif
#ifndef _U5TXIE
 #define _U5TXIE  IEC5bits.U5TXIE
#endif
#ifndef _U5EIP
 #define _U5EIP   IPC44bits.U5EIP
#endif
#ifndef _U5EIF
 #define _U5EIF   IFS5bits.U5TXIF
#endif
#ifndef _U5EIE
 #define _U5EIE   IEC5bits.U5TXIE
#endif

// interrupt bits helpers for UART6
#ifndef _U6RXIP
 #define _U6RXIP  IPC47bits.U6RXIP
#endif
#ifndef _U6RXIF
 #define _U6RXIF  IFS5bits.U6RXIF
#endif
#ifndef _U6RXIE
 #define _U6RXIE  IEC5bits.U6RXIE
#endif
#ifndef _U6TXIP
 #define _U6TXIP  IPC47bits.U6TXIP
#endif
#ifndef _U6TXIF
 #define _U6TXIF  IFS5bits.U6TXIF
#endif
#ifndef _U6TXIE
 #define _U6TXIE  IEC5bits.U6TXIE
#endif
#ifndef _U6EIP
 #define _U6EIP   IPC47bits.U6EIP
#endif
#ifndef _U6EIF
 #define _U6EIF   IFS5bits.U6TXIF
#endif
#ifndef _U6EIE
 #define _U6EIE   IEC5bits.U6TXIE
#endif

#endif // UART_PIC32_H
