/**
 * @file spi_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 06, 2016, 11:15 PM
 *
 * @brief SPI support for udevkit for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS61106G :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/61106G.pdf
 */

#ifndef SPI_PIC32_H
#define SPI_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(DEVICE_32MX420F032H) || defined(DEVICE_32MX440F128H) || defined(DEVICE_32MX440F256H) || defined(DEVICE_32MX440F512H)
#    define SPI_COUNT 1
#elif defined(DEVICE_32MK0128MCA028) || defined(DEVICE_32MK0128MCA032) || defined(DEVICE_32MK0128MCA048) || defined(DEVICE_32MK0256GPG048)                     \
    || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512GPG048)                    \
    || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064) || defined(DEVICE_32MM0016GPL020)                    \
    || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0032GPL028)                    \
    || defined(DEVICE_32MM0032GPL036) || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036)                    \
    || defined(DEVICE_32MX110F016B) || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032B)                            \
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
    || defined(DEVICE_32MX330F064H) || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX340F128H) || defined(DEVICE_32MX340F128L)                            \
    || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H) || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F128L)                            \
    || defined(DEVICE_32MX350F256H) || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX360F256L) || defined(DEVICE_32MX360F512L)                            \
    || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX370F512L) || defined(DEVICE_32MX430F064H) || defined(DEVICE_32MX430F064L)                            \
    || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F128L) || defined(DEVICE_32MX450F256H)                            \
    || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX460F256L) || defined(DEVICE_32MX460F512L) || defined(DEVICE_32MX470F512H)                            \
    || defined(DEVICE_32MX470F512L)
#    define SPI_COUNT 2
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) || defined(DEVICE_32MM0064GPM064)                     \
    || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064)                    \
    || defined(DEVICE_32MM0256GPM028) || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)                    \
    || defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX170F512H)                            \
    || defined(DEVICE_32MX230F128H) || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX530F128H)                            \
    || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F128H)                            \
    || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX664F064H)                            \
    || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX695F512H)                            \
    || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX795F512H)
#    define SPI_COUNT 3
#elif defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX230F128L)                             \
    || defined(DEVICE_32MX250F256L) || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX534F064L)                            \
    || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX570F512L)                            \
    || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128L)                            \
    || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128L)                            \
    || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512L) || defined(DEVICE_32MZ0512EFE064)                          \
    || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ1024ECG064) || defined(DEVICE_32MZ1024ECH064)                    \
    || defined(DEVICE_32MZ1024ECM064) || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFG064)                    \
    || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ2048ECG064)                    \
    || defined(DEVICE_32MZ2048ECH064) || defined(DEVICE_32MZ2048ECM064) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFH064)                    \
    || defined(DEVICE_32MZ2048EFM064)
#    define SPI_COUNT 4
#elif defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                     \
    || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)                    \
    || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF100)                    \
    || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124)                    \
    || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024ECG100) || defined(DEVICE_32MZ1024ECG124) || defined(DEVICE_32MZ1024ECG144)                    \
    || defined(DEVICE_32MZ1024ECH100) || defined(DEVICE_32MZ1024ECH124) || defined(DEVICE_32MZ1024ECH144) || defined(DEVICE_32MZ1024ECM100)                    \
    || defined(DEVICE_32MZ1024ECM124) || defined(DEVICE_32MZ1024ECM144) || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124)                    \
    || defined(DEVICE_32MZ1024EFE144) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFG144) || defined(DEVICE_32MZ1024EFH100)                    \
    || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124)                    \
    || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144)                    \
    || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176) || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169)                    \
    || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288) || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176)                    \
    || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176) || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176)                    \
    || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176) || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176)                    \
    || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176) || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176)                    \
    || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169) || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288)                    \
    || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176) || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176)                    \
    || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176) || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176)                    \
    || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176) || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176)                    \
    || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176) || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169)                    \
    || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288) || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176)                    \
    || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176) || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176)                    \
    || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176) || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176)                    \
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048ECG100) || defined(DEVICE_32MZ2048ECG124)                    \
    || defined(DEVICE_32MZ2048ECG144) || defined(DEVICE_32MZ2048ECH100) || defined(DEVICE_32MZ2048ECH124) || defined(DEVICE_32MZ2048ECH144)                    \
    || defined(DEVICE_32MZ2048ECM100) || defined(DEVICE_32MZ2048ECM124) || defined(DEVICE_32MZ2048ECM144) || defined(DEVICE_32MZ2048EFG100)                    \
    || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124)                    \
    || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM100) || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144)                    \
    || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176) || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169)                    \
    || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288) || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176)                    \
    || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176) || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176)                    \
    || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176) || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176)                    \
    || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define SPI_COUNT 6
#else
#    define SPI_COUNT 0
#endif

#ifndef _SPI1EIE
#    if defined(ARCHI_pic32mm)

#        if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) || defined(DEVICE_32MM0032GPL020)               \
            || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036) || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MM0064GPL028)            \
            || defined(DEVICE_32MM0064GPL036)
// interrupt bits helpers for MM GPL
#            define _SPI1EIE  IEC0bits.SPI1EIE
#            define _SPI1EIF  IFS0bits.SPI1EIF
#            define _SPI1EIP  IPC5bits.SPI1EIP
#            define _SPI1EIS  IPC5bits.SPI1EIS
#            define _SPI1RXIE IEC0bits.SPI1RXIE
#            define _SPI1RXIF IFS0bits.SPI1RXIF
#            define _SPI1RXIP IPC5bits.SPI1RXIP
#            define _SPI1RXIS IPC5bits.SPI1RXIS
#            define _SPI1TXIE IEC0bits.SPI1TXIE
#            define _SPI1TXIF IFS0bits.SPI1TXIF
#            define _SPI1TXIP IPC5bits.SPI1TXIP
#            define _SPI1TXIS IPC5bits.SPI1TXIS
#            define _SPI2EIE  IEC1bits.SPI2EIE
#            define _SPI2EIF  IFS1bits.SPI2EIF
#            define _SPI2EIP  IPC9bits.SPI2EIP
#            define _SPI2EIS  IPC9bits.SPI2EIS
#            define _SPI2RXIE IEC1bits.SPI2RXIE
#            define _SPI2RXIF IFS1bits.SPI2RXIF
#            define _SPI2RXIP IPC9bits.SPI2RXIP
#            define _SPI2RXIS IPC9bits.SPI2RXIS
#            define _SPI2TXIE IEC1bits.SPI2TXIE
#            define _SPI2TXIF IFS1bits.SPI2TXIF
#            define _SPI2TXIP IPC9bits.SPI2TXIP
#            define _SPI2TXIS IPC9bits.SPI2TXIS
#        else
// interrupt bits helpers for MM GPM
#            define _SPI1EIE  IEC1bits.SPI1EIE
#            define _SPI1EIF  IFS1bits.SPI1EIF
#            define _SPI1EIP  IPC10bits.SPI1EIP
#            define _SPI1EIS  IPC10bits.SPI1EIS
#            define _SPI1RXIE IEC1bits.SPI1RXIE
#            define _SPI1RXIF IFS1bits.SPI1RXIF
#            define _SPI1RXIP IPC10bits.SPI1RXIP
#            define _SPI1RXIS IPC10bits.SPI1RXIS
#            define _SPI1TXIE IEC1bits.SPI1TXIE
#            define _SPI1TXIF IFS1bits.SPI1TXIF
#            define _SPI1TXIP IPC10bits.SPI1TXIP
#            define _SPI1TXIS IPC10bits.SPI1TXIS
#            define _SPI2EIE  IEC1bits.SPI2EIE
#            define _SPI2EIF  IFS1bits.SPI2EIF
#            define _SPI2EIP  IPC11bits.SPI2EIP
#            define _SPI2EIS  IPC11bits.SPI2EIS
#            define _SPI2RXIE IEC1bits.SPI2RXIE
#            define _SPI2RXIF IFS1bits.SPI2RXIF
#            define _SPI2RXIP IPC11bits.SPI2RXIP
#            define _SPI2RXIS IPC11bits.SPI2RXIS
#            define _SPI2TXIE IEC1bits.SPI2TXIE
#            define _SPI2TXIF IFS1bits.SPI2TXIF
#            define _SPI2TXIP IPC11bits.SPI2TXIP
#            define _SPI2TXIS IPC11bits.SPI2TXIS
#            define _SPI3EIE  IEC1bits.SPI3EIE
#            define _SPI3EIF  IFS1bits.SPI3EIF
#            define _SPI3EIP  IPC11bits.SPI3EIP
#            define _SPI3EIS  IPC11bits.SPI3EIS
#            define _SPI3RXIE IEC1bits.SPI3RXIE
#            define _SPI3RXIF IFS1bits.SPI3RXIF
#            define _SPI3RXIP IPC12bits.SPI3RXIP
#            define _SPI3RXIS IPC12bits.SPI3RXIS
#            define _SPI3TXIE IEC1bits.SPI3TXIE
#            define _SPI3TXIF IFS1bits.SPI3TXIF
#            define _SPI3TXIP IPC12bits.SPI3TXIP
#            define _SPI3TXIS IPC12bits.SPI3TXIS
#        endif

#    elif defined(ARCHI_pic32mk)
// interrupt bits helpers for MK
#        define _SPI1EIE  IEC1bits.SPI1EIE
#        define _SPI1EIF  IFS1bits.SPI1EIF
#        define _SPI1EIP  IPC8bits.SPI1EIP
#        define _SPI1EIS  IPC8bits.SPI1EIS
#        define _SPI1RXIE IEC1bits.SPI1RXIE
#        define _SPI1RXIF IFS1bits.SPI1RXIF
#        define _SPI1RXIP IPC9bits.SPI1RXIP
#        define _SPI1RXIS IPC9bits.SPI1RXIS
#        define _SPI1TXIE IEC1bits.SPI1TXIE
#        define _SPI1TXIF IFS1bits.SPI1TXIF
#        define _SPI1TXIP IPC9bits.SPI1TXIP
#        define _SPI1TXIS IPC9bits.SPI1TXIS
#        define _SPI2EIE  IEC1bits.SPI2EIE
#        define _SPI2EIF  IFS1bits.SPI2EIF
#        define _SPI2EIP  IPC13bits.SPI2EIP
#        define _SPI2EIS  IPC13bits.SPI2EIS
#        define _SPI2RXIE IEC1bits.SPI2RXIE
#        define _SPI2RXIF IFS1bits.SPI2RXIF
#        define _SPI2RXIP IPC13bits.SPI2RXIP
#        define _SPI2RXIS IPC13bits.SPI2RXIS
#        define _SPI2TXIE IEC1bits.SPI2TXIE
#        define _SPI2TXIF IFS1bits.SPI2TXIF
#        define _SPI2TXIP IPC13bits.SPI2TXIP
#        define _SPI2TXIS IPC13bits.SPI2TXIS
#        define _SPI3EIE  IEC6bits.SPI3EIE
#        define _SPI3EIF  IFS6bits.SPI3EIF
#        define _SPI3EIP  IPC54bits.SPI3EIP
#        define _SPI3EIS  IPC54bits.SPI3EIS
#        define _SPI3RXIE IEC6bits.SPI3RXIE
#        define _SPI3RXIF IFS6bits.SPI3RXIF
#        define _SPI3RXIP IPC54bits.SPI3RXIP
#        define _SPI3RXIS IPC54bits.SPI3RXIS
#        define _SPI3TXIE IEC6bits.SPI3TXIE
#        define _SPI3TXIF IFS6bits.SPI3TXIF
#        define _SPI3TXIP IPC55bits.SPI3TXIP
#        define _SPI3TXIS IPC55bits.SPI3TXIS
#        define _SPI4EIE  IEC6bits.SPI4EIE
#        define _SPI4EIF  IFS6bits.SPI4EIF
#        define _SPI4EIP  IPC55bits.SPI4EIP
#        define _SPI4EIS  IPC55bits.SPI4EIS
#        define _SPI4RXIE IEC6bits.SPI4RXIE
#        define _SPI4RXIF IFS6bits.SPI4RXIF
#        define _SPI4RXIP IPC55bits.SPI4RXIP
#        define _SPI4RXIS IPC55bits.SPI4RXIS
#        define _SPI4TXIE IEC6bits.SPI4TXIE
#        define _SPI4TXIF IFS6bits.SPI4TXIF
#        define _SPI4TXIP IPC55bits.SPI4TXIP
#        define _SPI4TXIS IPC55bits.SPI4TXIS
#        define _SPI5EIE  IEC7bits.SPI5EIE
#        define _SPI5EIF  IFS7bits.SPI5EIF
#        define _SPI5EIP  IPC56bits.SPI5EIP
#        define _SPI5EIS  IPC56bits.SPI5EIS
#        define _SPI5RXIE IEC7bits.SPI5RXIE
#        define _SPI5RXIF IFS7bits.SPI5RXIF
#        define _SPI5RXIP IPC56bits.SPI5RXIP
#        define _SPI5RXIS IPC56bits.SPI5RXIS
#        define _SPI5TXIE IEC7bits.SPI5TXIE
#        define _SPI5TXIF IFS7bits.SPI5TXIF
#        define _SPI5TXIP IPC56bits.SPI5TXIP
#        define _SPI5TXIS IPC56bits.SPI5TXIS
#        define _SPI6EIE  IEC7bits.SPI6EIE
#        define _SPI6EIF  IFS7bits.SPI6EIF
#        define _SPI6EIP  IPC56bits.SPI6EIP
#        define _SPI6EIS  IPC56bits.SPI6EIS
#        define _SPI6RXIE IEC7bits.SPI6RXIE
#        define _SPI6RXIF IFS7bits.SPI6RXIF
#        define _SPI6RXIP IPC57bits.SPI6RXIP
#        define _SPI6RXIS IPC57bits.SPI6RXIS
#        define _SPI6TXIE IEC7bits.SPI6TXIE
#        define _SPI6TXIF IFS7bits.SPI6TXIF
#        define _SPI6TXIP IPC57bits.SPI6TXIP
#        define _SPI6TXIS IPC57bits.SPI6TXIS

#    elif defined(ARCHI_pic32mx)
// interrupt bits helpers for MX
#        if defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX530F128L)                       \
            || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L)                    \
            || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L)                    \
            || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L)                    \
            || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX664F128L)                    \
            || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L)                    \
            || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L)                    \
            || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX775F512L)                    \
            || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)
#            define _SPI1EIE  IEC0bits.SPI1EIE
#            define _SPI1EIF  IFS0bits.SPI1EIF
#            define _SPI1RXIE IEC0bits.SPI1RXIE
#            define _SPI1RXIF IFS0bits.SPI1RXIF
#            define _SPI1TXIE IEC0bits.SPI1TXIE
#            define _SPI1TXIF IFS0bits.SPI1TXIF
#        else
#            define _SPI1EIE  IEC1bits.SPI1EIE
#            define _SPI1EIF  IFS1bits.SPI1EIF
#            define _SPI1RXIE IEC1bits.SPI1RXIE
#            define _SPI1RXIF IFS1bits.SPI1RXIF
#            define _SPI1TXIE IEC1bits.SPI1TXIE
#            define _SPI1TXIF IFS1bits.SPI1TXIF
#        endif
#        define _SPI2EIE  IEC1bits.SPI2EIE
#        define _SPI2EIF  IFS1bits.SPI2EIF
#        define _SPI2RXIE IEC1bits.SPI2RXIE
#        define _SPI2RXIF IFS1bits.SPI2RXIF
#        define _SPI2TXIE IEC1bits.SPI2TXIE
#        define _SPI2TXIF IFS1bits.SPI2TXIF
#        define _SPI3EIE  IEC0bits.SPI3EIE
#        define _SPI3EIF  IFS0bits.SPI3EIF
#        define _SPI3RXIE IEC0bits.SPI3RXIE
#        define _SPI3RXIF IFS0bits.SPI3RXIF
#        define _SPI3TXIE IEC0bits.SPI3TXIE
#        define _SPI3TXIF IFS0bits.SPI3TXIF
#        define _SPI4EIE  IEC1bits.SPI4EIE
#        define _SPI4EIF  IFS1bits.SPI4EIF
#        define _SPI4RXIE IEC1bits.SPI4RXIE
#        define _SPI4RXIF IFS1bits.SPI4RXIF
#        define _SPI4TXIE IEC1bits.SPI4TXIE
#        define _SPI4TXIF IFS1bits.SPI4TXIF

#    elif defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
// interrupt bits helpers for MZ
#        define _SPI1EIE  IEC3bits.SPI1EIE
#        define _SPI1EIF  IFS3bits.SPI1EIF
#        define _SPI1EIP  IPC27bits.SPI1EIP
#        define _SPI1EIS  IPC27bits.SPI1EIS
#        define _SPI1RXIE IEC3bits.SPI1RXIE
#        define _SPI1RXIF IFS3bits.SPI1RXIF
#        define _SPI1RXIP IPC27bits.SPI1RXIP
#        define _SPI1RXIS IPC27bits.SPI1RXIS
#        define _SPI1TXIE IEC3bits.SPI1TXIE
#        define _SPI1TXIF IFS3bits.SPI1TXIF
#        define _SPI1TXIP IPC27bits.SPI1TXIP
#        define _SPI1TXIS IPC27bits.SPI1TXIS
#        define _SPI2EIE  IEC4bits.SPI2EIE
#        define _SPI2EIF  IFS4bits.SPI2EIF
#        define _SPI2EIP  IPC35bits.SPI2EIP
#        define _SPI2EIS  IPC35bits.SPI2EIS
#        define _SPI2RXIE IEC4bits.SPI2RXIE
#        define _SPI2RXIF IFS4bits.SPI2RXIF
#        define _SPI2RXIP IPC35bits.SPI2RXIP
#        define _SPI2RXIS IPC35bits.SPI2RXIS
#        define _SPI2TXIE IEC4bits.SPI2TXIE
#        define _SPI2TXIF IFS4bits.SPI2TXIF
#        define _SPI2TXIP IPC36bits.SPI2TXIP
#        define _SPI2TXIS IPC36bits.SPI2TXIS
#        define _SPI3EIE  IEC4bits.SPI3EIE
#        define _SPI3EIF  IFS4bits.SPI3EIF
#        define _SPI3EIP  IPC38bits.SPI3EIP
#        define _SPI3EIS  IPC38bits.SPI3EIS
#        define _SPI3RXIE IEC4bits.SPI3RXIE
#        define _SPI3RXIF IFS4bits.SPI3RXIF
#        define _SPI3RXIP IPC38bits.SPI3RXIP
#        define _SPI3RXIS IPC38bits.SPI3RXIS
#        define _SPI3TXIE IEC4bits.SPI3TXIE
#        define _SPI3TXIF IFS4bits.SPI3TXIF
#        define _SPI3TXIP IPC39bits.SPI3TXIP
#        define _SPI3TXIS IPC39bits.SPI3TXIS
#        define _SPI4EIE  IEC5bits.SPI4EIE
#        define _SPI4EIF  IFS5bits.SPI4EIF
#        define _SPI4EIP  IPC40bits.SPI4EIP
#        define _SPI4EIS  IPC40bits.SPI4EIS
#        define _SPI4RXIE IEC5bits.SPI4RXIE
#        define _SPI4RXIF IFS5bits.SPI4RXIF
#        define _SPI4RXIP IPC41bits.SPI4RXIP
#        define _SPI4RXIS IPC41bits.SPI4RXIS
#        define _SPI4TXIE IEC5bits.SPI4TXIE
#        define _SPI4TXIF IFS5bits.SPI4TXIF
#        define _SPI4TXIP IPC41bits.SPI4TXIP
#        define _SPI4TXIS IPC41bits.SPI4TXIS
#        define _SPI5EIE  IEC5bits.SPI5EIE
#        define _SPI5EIF  IFS5bits.SPI5EIF
#        define _SPI5EIP  IPC44bits.SPI5EIP
#        define _SPI5EIS  IPC44bits.SPI5EIS
#        define _SPI5RXIE IEC5bits.SPI5RXIE
#        define _SPI5RXIF IFS5bits.SPI5RXIF
#        define _SPI5RXIP IPC44bits.SPI5RXIP
#        define _SPI5RXIS IPC44bits.SPI5RXIS
#        define _SPI5TXIE IEC5bits.SPI5TXIE
#        define _SPI5TXIF IFS5bits.SPI5TXIF
#        define _SPI5TXIP IPC44bits.SPI5TXIP
#        define _SPI5TXIS IPC44bits.SPI5TXIS
#        define _SPI6EIP  IPC46bits.SPI6EIP
#        define _SPI6EIS  IPC46bits.SPI6EIS
#        define _SPI6RXIE IEC5bits.SPI6RXIE
#        define _SPI6RXIF IFS5bits.SPI6RXIF
#        define _SPI6RXIP IPC46bits.SPI6RXIP
#        define _SPI6RXIS IPC46bits.SPI6RXIS
#        define _SPI6TXIE IEC5bits.SPI6TXIE
#        define _SPI6TXIP IPC46bits.SPI6TXIP
#        define _SPI6TXIS IPC46bits.SPI6TXIS
#    endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // SPI_PIC32_H
