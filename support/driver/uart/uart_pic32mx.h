/**
 * @file uart_pic32mx.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date June 07, 2017, 08:15 AM
 *
 * @brief Uart support for udevkit for PIC32MX
 *
 * Implementation based on Microchip document DS61107G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf
 */

#ifndef UART_PIC32MX_H
#define UART_PIC32MX_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032B)                               \
    || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C)                            \
    || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B)                            \
    || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX154F128D)                            \
    || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX170F256D) || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX174F256D)                            \
    || defined(DEVICE_32MX210F016B) || defined(DEVICE_32MX210F016C) || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032B)                            \
    || defined(DEVICE_32MX220F032C) || defined(DEVICE_32MX220F032D) || defined(DEVICE_32MX230F064B) || defined(DEVICE_32MX230F064C)                            \
    || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX230F256D) || defined(DEVICE_32MX250F128B)                            \
    || defined(DEVICE_32MX250F128C) || defined(DEVICE_32MX250F128D) || defined(DEVICE_32MX254F128B) || defined(DEVICE_32MX254F128D)                            \
    || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX270F256D) || defined(DEVICE_32MX274F256B) || defined(DEVICE_32MX274F256D)                            \
    || defined(DEVICE_32MX320F032H) || defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) || defined(DEVICE_32MX320F128L)                            \
    || defined(DEVICE_32MX340F128H) || defined(DEVICE_32MX340F128L) || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H)                            \
    || defined(DEVICE_32MX360F256L) || defined(DEVICE_32MX360F512L) || defined(DEVICE_32MX420F032H) || defined(DEVICE_32MX440F128H)                            \
    || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX440F256H) || defined(DEVICE_32MX440F512H) || defined(DEVICE_32MX460F256L)                            \
    || defined(DEVICE_32MX460F512L)
#    define UART_COUNT 2
#elif defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX170F512H)                             \
    || defined(DEVICE_32MX230F128H) || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX330F064H)                            \
    || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F256H) || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX430F064H)                            \
    || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F256H) || defined(DEVICE_32MX470F512H) || defined(DEVICE_32MX530F128H)                            \
    || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX570F512H)
#    define UART_COUNT 4
#elif defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX230F128L)                             \
    || defined(DEVICE_32MX250F256L) || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX350F128L)                            \
    || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX370F512L) || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX450F128L)                            \
    || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX470F512L) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX550F256L)                            \
    || defined(DEVICE_32MX570F512L)
#    define UART_COUNT 5
#elif defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L)                             \
    || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F256L)                            \
    || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L)                            \
    || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L)                            \
    || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX695F512L)                            \
    || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L) || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L)                            \
    || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)
#    define UART_COUNT 6
#else
#    define UART_COUNT 0
#endif

// interrupt bits helpers for MX (MX does not have IP interrupt priority)
#ifndef _U1RXIE
#    if defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX530F128L)                           \
        || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L)                        \
        || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L)                        \
        || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L)                        \
        || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX664F128L)                        \
        || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L)                        \
        || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L)                        \
        || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX775F512L)                        \
        || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)
#        define _U1EIE  IEC0bits.U1EIE
#        define _U1EIF  IFS0bits.U1EIF
#        define _U1RXIE IEC0bits.U1RXIE
#        define _U1RXIF IFS0bits.U1RXIF
#        define _U1TXIE IEC0bits.U1TXIE
#        define _U1TXIF IFS0bits.U1TXIF
#        define _U3TXIF IFS1bits.U3TXIF
#        define _U3TXIE IEC1bits.U3TXIE

#        define _U1IP IPC6bits.U1IP
#        define _U2IP IPC8bits.U2IP
#        define _U3IP IPC7bits.U3IP
#        define _U4IP IPC12bits.U4IP
#        define _U5IP IPC12bits.U5IP
#        define _U6IP IPC12bits.U6IP

#    else
#        define _U1EIE  IEC1bits.U1EIE
#        define _U1EIF  IFS1bits.U1EIF
#        define _U1RXIE IEC1bits.U1RXIE
#        define _U1RXIF IFS1bits.U1RXIF
#        define _U1TXIE IEC1bits.U1TXIE
#        define _U1TXIF IFS1bits.U1TXIF
#        define _U3TXIF IFS2bits.U3TXIF
#        define _U3TXIE IEC2bits.U3TXIE

#        define _U1IP IPC7bits.U1IP
#        define _U2IP IPC9bits.U2IP
#        define _U3IP IPC9bits.U3IP
#        define _U4IP IPC9bits.U4IP
#        define _U5IP IPC10bits.U5IP
#    endif

#    define _U2EIE  IEC1bits.U2EIE
#    define _U2EIF  IFS1bits.U2EIF
#    define _U2RXIE IEC1bits.U2RXIE
#    define _U2RXIF IFS1bits.U2RXIF
#    define _U2TXIE IEC1bits.U2TXIE
#    define _U2TXIF IFS1bits.U2TXIF
#    define _U3RXIE IEC1bits.U3RXIE
#    define _U3RXIF IFS1bits.U3RXIF
#    define _U4EIE  IEC2bits.U4EIE
#    define _U4EIF  IFS2bits.U4EIF
#    define _U4RXIE IEC2bits.U4RXIE
#    define _U4RXIF IFS2bits.U4RXIF
#    define _U4TXIE IEC2bits.U4TXIE
#    define _U4TXIF IFS2bits.U4TXIF
#    define _U5EIE  IEC2bits.U5EIE
#    define _U5EIF  IFS2bits.U5EIF
#    define _U5RXIE IEC2bits.U5RXIE
#    define _U5RXIF IFS2bits.U5RXIF
#    define _U5TXIE IEC2bits.U5TXIE
#    define _U5TXIF IFS2bits.U5TXIF
#    define _U6EIE  IEC2bits.U6EIE
#    define _U6EIF  IFS2bits.U6EIF
#    define _U6RXIE IEC2bits.U6RXIE
#    define _U6RXIF IFS2bits.U6RXIF
#    define _U6TXIE IEC2bits.U6TXIE
#    define _U6TXIF IFS2bits.U6TXIF
#endif

#define UART_MAXBRG 0x0000FFFF  // 16 bits divisor

#ifdef __cplusplus
}
#endif

#endif  // UART_PIC32MX_H
