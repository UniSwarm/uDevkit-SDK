/**
 * @file gpio_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date March 20, 2017, 18:39 AM
 *
 * @brief GPIO support driver for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 *
 * Implementation based on Microchip document DS60001120F :
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/60001120F.pdf
 */

#ifndef GPIO_PIC32_H
#define GPIO_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

// compute PORT count and existance on device
#if defined(DEVICE_32MM0016GPL020) || defined(DEVICE_32MM0032GPL020) || defined(DEVICE_32MM0064GPL020) || defined(DEVICE_32MX110F016B)                         \
    || defined(DEVICE_32MX120F032B) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F256B) || defined(DEVICE_32MX150F128B)                            \
    || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX210F016B)                            \
    || defined(DEVICE_32MX220F032B) || defined(DEVICE_32MX230F064B) || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX250F128B)                            \
    || defined(DEVICE_32MX254F128B) || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX274F256B)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_PORT_COUNT 2
#    define GPIO_PORT_MAX   2
#elif defined(DEVICE_32MM0016GPL028) || defined(DEVICE_32MM0016GPL036) || defined(DEVICE_32MM0032GPL028) || defined(DEVICE_32MM0032GPL036)                     \
    || defined(DEVICE_32MM0064GPL028) || defined(DEVICE_32MM0064GPL036) || defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036)                    \
    || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) || defined(DEVICE_32MM0256GPM028) || defined(DEVICE_32MM0256GPM036)                    \
    || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032C) || defined(DEVICE_32MX120F032D)                            \
    || defined(DEVICE_32MX130F064C) || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128C)                            \
    || defined(DEVICE_32MX150F128D) || defined(DEVICE_32MX154F128D) || defined(DEVICE_32MX170F256D) || defined(DEVICE_32MX174F256D)                            \
    || defined(DEVICE_32MX210F016C) || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032C) || defined(DEVICE_32MX220F032D)                            \
    || defined(DEVICE_32MX230F064C) || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX230F256D) || defined(DEVICE_32MX250F128C)                            \
    || defined(DEVICE_32MX250F128D) || defined(DEVICE_32MX254F128D) || defined(DEVICE_32MX270F256D) || defined(DEVICE_32MX274F256D)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_PORT_COUNT 3
#    define GPIO_PORT_MAX   3
#elif defined(DEVICE_32MK0128MCA028) || defined(DEVICE_32MK0128MCA032) || defined(DEVICE_32MK0128MCA048) || defined(DEVICE_32MK0256GPG048)                     \
    || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0512GPG048) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MM0064GPM048)                    \
    || defined(DEVICE_32MM0064GPM064) || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064) || defined(DEVICE_32MM0256GPM048)                    \
    || defined(DEVICE_32MM0256GPM064)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_PORT_COUNT 4
#    define GPIO_PORT_MAX   4
#elif defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX170F512H)                             \
    || defined(DEVICE_32MX230F128H) || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX320F032H)                            \
    || defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) || defined(DEVICE_32MX330F064H) || defined(DEVICE_32MX340F128H)                            \
    || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H) || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F256H)                            \
    || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX420F032H) || defined(DEVICE_32MX430F064H) || defined(DEVICE_32MX440F128H)                            \
    || defined(DEVICE_32MX440F256H) || defined(DEVICE_32MX440F512H) || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F256H)                            \
    || defined(DEVICE_32MX470F512H) || defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX550F256H)                            \
    || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX575F256H)                            \
    || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX675F256H)                            \
    || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX775F256H)                            \
    || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFF064)                        \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ1024ECG064) || defined(DEVICE_32MZ1024ECH064) || defined(DEVICE_32MZ1024ECM064)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFH064)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ2048ECG064) || defined(DEVICE_32MZ2048ECH064)                    \
    || defined(DEVICE_32MZ2048ECM064) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFM064)
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 6
#    define GPIO_PORT_MAX   7
#elif defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100)                     \
    || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100) || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512GPK064)                    \
    || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100) || defined(DEVICE_32MK0512MCJ064)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)                    \
    || defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX170F512L) || defined(DEVICE_32MX230F128L)                            \
    || defined(DEVICE_32MX250F256L) || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX320F128L) || defined(DEVICE_32MX330F064L)                            \
    || defined(DEVICE_32MX340F128L) || defined(DEVICE_32MX350F128L) || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX360F256L)                            \
    || defined(DEVICE_32MX360F512L) || defined(DEVICE_32MX370F512L) || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX440F128L)                            \
    || defined(DEVICE_32MX450F128L) || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX460F256L) || defined(DEVICE_32MX460F512L)                            \
    || defined(DEVICE_32MX470F512L) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX550F256L)                            \
    || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX570F512L) || defined(DEVICE_32MX575F256L)                            \
    || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256L)                            \
    || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128L) || defined(DEVICE_32MX775F256L)                            \
    || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512L) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFF100)                        \
    || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ1024ECG100) || defined(DEVICE_32MZ1024ECH100) || defined(DEVICE_32MZ1024ECM100)                    \
    || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFF100) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFH100)                    \
    || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFM100) || defined(DEVICE_32MZ2048ECG100) || defined(DEVICE_32MZ2048ECH100)                    \
    || defined(DEVICE_32MZ2048ECM100) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFM100)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_PORT_COUNT 7
#    define GPIO_PORT_MAX   7
#elif defined(DEVICE_32MZ0512EFE124) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ1024ECG124)                     \
    || defined(DEVICE_32MZ1024ECH124) || defined(DEVICE_32MZ1024ECM124) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFF124)                    \
    || defined(DEVICE_32MZ1024EFG124) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFM124)                    \
    || defined(DEVICE_32MZ2048ECG124) || defined(DEVICE_32MZ2048ECH124) || defined(DEVICE_32MZ2048ECM124) || defined(DEVICE_32MZ2048EFG124)                    \
    || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFM124)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_HAVE_PORTH
#    define GPIO_HAVE_PORTJ
#    define GPIO_PORT_COUNT 9
#    define GPIO_PORT_MAX   10
#elif defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF144) || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024ECG144)                     \
    || defined(DEVICE_32MZ1024ECH144) || defined(DEVICE_32MZ1024ECM144) || defined(DEVICE_32MZ1024EFE144) || defined(DEVICE_32MZ1024EFF144)                    \
    || defined(DEVICE_32MZ1024EFG144) || defined(DEVICE_32MZ1024EFH144) || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM144)                    \
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
    || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176) || defined(DEVICE_32MZ2048ECG144) || defined(DEVICE_32MZ2048ECH144)                    \
    || defined(DEVICE_32MZ2048ECM144) || defined(DEVICE_32MZ2048EFG144) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM144)                    \
    || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176) || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169)                    \
    || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288) || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176)                    \
    || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176) || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176)                    \
    || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176) || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176)                    \
    || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define GPIO_HAVE_PORTA
#    define GPIO_HAVE_PORTB
#    define GPIO_HAVE_PORTC
#    define GPIO_HAVE_PORTD
#    define GPIO_HAVE_PORTE
#    define GPIO_HAVE_PORTF
#    define GPIO_HAVE_PORTG
#    define GPIO_HAVE_PORTH
#    define GPIO_HAVE_PORTJ
#    define GPIO_HAVE_PORTK
#    define GPIO_PORT_COUNT 10
#    define GPIO_PORT_MAX   11
#else
#    define GPIO_PORT_COUNT 0
#    define GPIO_PORT_MAX   0
#endif

#define GPIO_MAX_PORTWIDTH     16
#define GPIO_MAX_PORTWIDTHU    4
#define GPIO_MAX_PORTWIDTHMASK 0x0F

#define GPIO_HAVE_CHANGENOTIFICATION  // have change notification on pins
#define GPIO_HAVE_OPENDRAIN           // have open drain output config

#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
// interrupt bits helpers for PIC32MZ
#    ifndef _CNAIE
#        define _CNAIE IEC3bits.CNAIE
#        define _CNAIF IFS3bits.CNAIF
#        define _CNAIP IPC29bits.CNAIP
#        define _CNAIS IPC29bits.CNAIS
#        define _CNBIE IEC3bits.CNBIE
#        define _CNBIF IFS3bits.CNBIF
#        define _CNBIP IPC29bits.CNBIP
#        define _CNBIS IPC29bits.CNBIS
#        define _CNCIE IEC3bits.CNCIE
#        define _CNCIF IFS3bits.CNCIF
#        define _CNCIP IPC30bits.CNCIP
#        define _CNCIS IPC30bits.CNCIS
#        define _CNDIE IEC3bits.CNDIE
#        define _CNDIF IFS3bits.CNDIF
#        define _CNDIP IPC30bits.CNDIP
#        define _CNDIS IPC30bits.CNDIS
#        define _CNEIE IEC3bits.CNEIE
#        define _CNEIF IFS3bits.CNEIF
#        define _CNEIP IPC30bits.CNEIP
#        define _CNEIS IPC30bits.CNEIS
#        define _CNFIE IEC3bits.CNFIE
#        define _CNFIF IFS3bits.CNFIF
#        define _CNFIP IPC30bits.CNFIP
#        define _CNFIS IPC30bits.CNFIS
#        define _CNGIE IEC3bits.CNGIE
#        define _CNGIF IFS3bits.CNGIF
#        define _CNGIP IPC31bits.CNGIP
#        define _CNGIS IPC31bits.CNGIS
#        define _CNHIE IEC3bits.CNHIE
#        define _CNHIF IFS3bits.CNHIF
#        define _CNHIP IPC31bits.CNHIP
#        define _CNHIS IPC31bits.CNHIS
#        define _CNJIE IEC3bits.CNJIE
#        define _CNJIF IFS3bits.CNJIF
#        define _CNJIP IPC31bits.CNJIP
#        define _CNJIS IPC31bits.CNJIS
#        define _CNKIE IEC3bits.CNKIE
#        define _CNKIF IFS3bits.CNKIF
#        define _CNKIP IPC31bits.CNKIP
#        define _CNKIS IPC31bits.CNKIS
#    endif
#    define CNIPR IPL5SRS

#elif defined(ARCHI_pic32mm)
#    ifndef _CNAIE
#        define _CNAIE IEC0bits.CNAIE
#        define _CNAIF IFS0bits.CNAIF
#        define _CNAIP IPC2bits.CNAIP
#        define _CNAIS IPC2bits.CNAIS
#        define _CNBIE IEC0bits.CNBIE
#        define _CNBIF IFS0bits.CNBIF
#        define _CNBIP IPC2bits.CNBIP
#        define _CNBIS IPC2bits.CNBIS
#        define _CNCIE IEC0bits.CNCIE
#        define _CNCIF IFS0bits.CNCIF
#        define _CNCIP IPC2bits.CNCIP
#        define _CNCIS IPC2bits.CNCIS
#        define _CNDIE IEC0bits.CNDIE
#        define _CNDIF IFS0bits.CNDIF
#        define _CNDIP IPC2bits.CNDIP
#        define _CNDIS IPC2bits.CNDIS
#    endif
#    define CNIPR IPL5SRS
#    define GPIO_CN_NOEDGEDETECT

#elif defined(ARCHI_pic32mk)
#    ifndef _CNAIE
#        define _CNAIE IEC1bits.CNAIE
#        define _CNAIF IFS1bits.CNAIF
#        define _CNAIP IPC11bits.CNAIP
#        define _CNAIS IPC11bits.CNAIS
#        define _CNBIE IEC1bits.CNBIE
#        define _CNBIF IFS1bits.CNBIF
#        define _CNBIP IPC11bits.CNBIP
#        define _CNBIS IPC11bits.CNBIS
#        define _CNCIE IEC1bits.CNCIE
#        define _CNCIF IFS1bits.CNCIF
#        define _CNCIP IPC11bits.CNCIP
#        define _CNCIS IPC11bits.CNCIS
#        define _CNDIE IEC1bits.CNDIE
#        define _CNDIF IFS1bits.CNDIF
#        define _CNDIP IPC11bits.CNDIP
#        define _CNDIS IPC11bits.CNDIS
#        define _CNEIE IEC1bits.CNEIE
#        define _CNEIF IFS1bits.CNEIF
#        define _CNEIP IPC12bits.CNEIP
#        define _CNEIS IPC12bits.CNEIS
#        define _CNFIE IEC1bits.CNFIE
#        define _CNFIF IFS1bits.CNFIF
#        define _CNFIP IPC12bits.CNFIP
#        define _CNFIS IPC12bits.CNFIS
#        define _CNGIE IEC1bits.CNGIE
#        define _CNGIF IFS1bits.CNGIF
#        define _CNGIP IPC12bits.CNGIP
#        define _CNGIS IPC12bits.CNGIS
#    endif
#    define CNIPR IPL5SRS

#elif defined(ARCHI_pic32mx)
#    ifndef _CNAIE
#        if defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX530F128L)                       \
            || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L)                    \
            || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L)                    \
            || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L)                    \
            || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX664F128L)                    \
            || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L)                    \
            || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L)                    \
            || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX775F512L)                    \
            || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)
//           PIC32MX5xx / 7xx
#            define _CNIE IEC1bits.CNIE
#            define _CNIF IFS1bits.CNIF
#            define _CNIP IPC6bits.CNIP
#            define _CNIS IPC6bits.CNIS
#        else
#            define _CNAIE IEC1bits.CNAIE
#            define _CNAIF IFS1bits.CNAIF
#            define _CNAIP IPC8bits.CNIP
#            define _CNAIS IPC8bits.CNIS
#            define _CNBIE IEC1bits.CNBIE
#            define _CNBIF IFS1bits.CNBIF
#            define _CNBIP IPC8bits.CNIP
#            define _CNBIS IPC8bits.CNIS
#            define _CNCIE IEC1bits.CNCIE
#            define _CNCIF IFS1bits.CNCIF
#            define _CNCIP IPC8bits.CNIP
#            define _CNCIS IPC8bits.CNIS
#            define _CNDIE IEC1bits.CNDIE
#            define _CNDIF IFS1bits.CNDIF
#            define _CNDIP IPC8bits.CNIP
#            define _CNDIS IPC8bits.CNIS
#            define _CNEIE IEC1bits.CNEIE
#            define _CNEIF IFS1bits.CNEIF
#            define _CNEIP IPC8bits.CNIP
#            define _CNEIS IPC8bits.CNIS
#            define _CNFIE IEC1bits.CNFIE
#            define _CNFIF IFS1bits.CNFIF
#            define _CNFIP IPC8bits.CNIP
#            define _CNFIS IPC8bits.CNIS
#            define _CNGIE IEC1bits.CNGIE
#            define _CNGIF IFS1bits.CNGIF
#            define _CNGIP IPC8bits.CNIP
#            define _CNGIS IPC8bits.CNIS
#        endif
#    endif
#    define CNIPR IPL5SRS
#    define GPIO_CN_NOEDGEDETECT
#    define GPIO_CN_SINGLEINTERRUPT
#endif

#ifdef __cplusplus
}
#endif

#endif  // GPIO_PIC32_H
