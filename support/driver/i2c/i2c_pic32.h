/**
 * @file i2c_pic32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2023
 *
 * @date October 06, 2016, 11:15 PM
 *
 * @brief I2C support for udevkit for PIC32MM, PIC32MK, PIC32MX,
 * PIC32MZDA, PIC32MZEC and PIC32MZEF
 */

#ifndef I2C_PIC32_H
#define I2C_PIC32_H

#ifdef __cplusplus
extern "C" {
#endif

// ========================= I2C module count ==========================
#if defined(DEVICE_32MK0128MCA028) || defined(DEVICE_32MK0128MCA032) || defined(DEVICE_32MK0128MCA048) || defined(DEVICE_32MK0256GPG048)                       \
    || defined(DEVICE_32MK0256GPG064) || defined(DEVICE_32MK0256MCJ048) || defined(DEVICE_32MK0256MCJ064) || defined(DEVICE_32MK0512GPG048)                    \
    || defined(DEVICE_32MK0512GPG064) || defined(DEVICE_32MK0512MCJ048) || defined(DEVICE_32MK0512MCJ064) || defined(DEVICE_32MX110F016B)                      \
    || defined(DEVICE_32MX110F016C) || defined(DEVICE_32MX110F016D) || defined(DEVICE_32MX120F032B) || defined(DEVICE_32MX120F032C)                            \
    || defined(DEVICE_32MX120F032D) || defined(DEVICE_32MX120F064H) || defined(DEVICE_32MX130F064B) || defined(DEVICE_32MX130F064C)                            \
    || defined(DEVICE_32MX130F064D) || defined(DEVICE_32MX130F128H) || defined(DEVICE_32MX130F128L) || defined(DEVICE_32MX130F256B)                            \
    || defined(DEVICE_32MX130F256D) || defined(DEVICE_32MX150F128B) || defined(DEVICE_32MX150F128C) || defined(DEVICE_32MX150F128D)                            \
    || defined(DEVICE_32MX150F256H) || defined(DEVICE_32MX150F256L) || defined(DEVICE_32MX154F128B) || defined(DEVICE_32MX154F128D)                            \
    || defined(DEVICE_32MX170F256B) || defined(DEVICE_32MX170F256D) || defined(DEVICE_32MX170F512H) || defined(DEVICE_32MX170F512L)                            \
    || defined(DEVICE_32MX174F256B) || defined(DEVICE_32MX174F256D) || defined(DEVICE_32MX210F016B) || defined(DEVICE_32MX210F016C)                            \
    || defined(DEVICE_32MX210F016D) || defined(DEVICE_32MX220F032B) || defined(DEVICE_32MX220F032C) || defined(DEVICE_32MX220F032D)                            \
    || defined(DEVICE_32MX230F064B) || defined(DEVICE_32MX230F064C) || defined(DEVICE_32MX230F064D) || defined(DEVICE_32MX230F128H)                            \
    || defined(DEVICE_32MX230F128L) || defined(DEVICE_32MX230F256B) || defined(DEVICE_32MX230F256D) || defined(DEVICE_32MX250F128B)                            \
    || defined(DEVICE_32MX250F128C) || defined(DEVICE_32MX250F128D) || defined(DEVICE_32MX250F256H) || defined(DEVICE_32MX250F256L)                            \
    || defined(DEVICE_32MX254F128B) || defined(DEVICE_32MX254F128D) || defined(DEVICE_32MX270F256B) || defined(DEVICE_32MX270F256D)                            \
    || defined(DEVICE_32MX270F512H) || defined(DEVICE_32MX270F512L) || defined(DEVICE_32MX274F256B) || defined(DEVICE_32MX274F256D)                            \
    || defined(DEVICE_32MX320F032H) || defined(DEVICE_32MX320F064H) || defined(DEVICE_32MX320F128H) || defined(DEVICE_32MX320F128L)                            \
    || defined(DEVICE_32MX330F064H) || defined(DEVICE_32MX330F064L) || defined(DEVICE_32MX340F128H) || defined(DEVICE_32MX340F128L)                            \
    || defined(DEVICE_32MX340F256H) || defined(DEVICE_32MX340F512H) || defined(DEVICE_32MX350F128H) || defined(DEVICE_32MX350F128L)                            \
    || defined(DEVICE_32MX350F256H) || defined(DEVICE_32MX350F256L) || defined(DEVICE_32MX360F256L) || defined(DEVICE_32MX360F512L)                            \
    || defined(DEVICE_32MX370F512H) || defined(DEVICE_32MX370F512L) || defined(DEVICE_32MX420F032H) || defined(DEVICE_32MX430F064H)                            \
    || defined(DEVICE_32MX430F064L) || defined(DEVICE_32MX440F128H) || defined(DEVICE_32MX440F128L) || defined(DEVICE_32MX440F256H)                            \
    || defined(DEVICE_32MX440F512H) || defined(DEVICE_32MX450F128H) || defined(DEVICE_32MX450F128L) || defined(DEVICE_32MX450F256H)                            \
    || defined(DEVICE_32MX450F256L) || defined(DEVICE_32MX460F256L) || defined(DEVICE_32MX460F512L) || defined(DEVICE_32MX470F512H)                            \
    || defined(DEVICE_32MX470F512L) || defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX530F128L) || defined(DEVICE_32MX550F256H)                            \
    || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX570F512L)
#    define I2C_COUNT 2
#elif defined(DEVICE_32MM0064GPM028) || defined(DEVICE_32MM0064GPM036) || defined(DEVICE_32MM0064GPM048) || defined(DEVICE_32MM0064GPM064)                     \
    || defined(DEVICE_32MM0128GPM028) || defined(DEVICE_32MM0128GPM036) || defined(DEVICE_32MM0128GPM048) || defined(DEVICE_32MM0128GPM064)                    \
    || defined(DEVICE_32MM0256GPM028) || defined(DEVICE_32MM0256GPM036) || defined(DEVICE_32MM0256GPM048) || defined(DEVICE_32MM0256GPM064)
#    define I2C_COUNT 3
#elif defined(DEVICE_32MK0512GPD064) || defined(DEVICE_32MK0512GPD100) || defined(DEVICE_32MK0512GPE064) || defined(DEVICE_32MK0512GPE100)                     \
    || defined(DEVICE_32MK0512GPK064) || defined(DEVICE_32MK0512GPK100) || defined(DEVICE_32MK0512MCF064) || defined(DEVICE_32MK0512MCF100)                    \
    || defined(DEVICE_32MK0512MCM064) || defined(DEVICE_32MK0512MCM100) || defined(DEVICE_32MK1024GPD064) || defined(DEVICE_32MK1024GPD100)                    \
    || defined(DEVICE_32MK1024GPE064) || defined(DEVICE_32MK1024GPE100) || defined(DEVICE_32MK1024GPK064) || defined(DEVICE_32MK1024GPK100)                    \
    || defined(DEVICE_32MK1024MCF064) || defined(DEVICE_32MK1024MCF100) || defined(DEVICE_32MK1024MCM064) || defined(DEVICE_32MK1024MCM100)                    \
    || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX575F256H)                            \
    || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX675F256H)                            \
    || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX775F256H)                            \
    || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFF064)                        \
    || defined(DEVICE_32MZ0512EFK064) || defined(DEVICE_32MZ1024ECG064) || defined(DEVICE_32MZ1024ECH064) || defined(DEVICE_32MZ1024ECM064)                    \
    || defined(DEVICE_32MZ1024EFE064) || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFH064)                    \
    || defined(DEVICE_32MZ1024EFK064) || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ2048ECG064) || defined(DEVICE_32MZ2048ECH064)                    \
    || defined(DEVICE_32MZ2048ECM064) || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MZ2048EFM064)
#    define I2C_COUNT 4
#elif defined(DEVICE_32MX534F064L) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128L) || defined(DEVICE_32MX575F256L)                             \
    || defined(DEVICE_32MX575F512L) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128L) || defined(DEVICE_32MX675F256L)                            \
    || defined(DEVICE_32MX675F512L) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128L) || defined(DEVICE_32MX775F256L)                            \
    || defined(DEVICE_32MX775F512L) || defined(DEVICE_32MX795F512L) || defined(DEVICE_32MZ0512EFE100) || defined(DEVICE_32MZ0512EFE124)                        \
    || defined(DEVICE_32MZ0512EFE144) || defined(DEVICE_32MZ0512EFF100) || defined(DEVICE_32MZ0512EFF124) || defined(DEVICE_32MZ0512EFF144)                    \
    || defined(DEVICE_32MZ0512EFK100) || defined(DEVICE_32MZ0512EFK124) || defined(DEVICE_32MZ0512EFK144) || defined(DEVICE_32MZ1024ECG100)                    \
    || defined(DEVICE_32MZ1024ECG124) || defined(DEVICE_32MZ1024ECG144) || defined(DEVICE_32MZ1024ECH100) || defined(DEVICE_32MZ1024ECH124)                    \
    || defined(DEVICE_32MZ1024ECH144) || defined(DEVICE_32MZ1024ECM100) || defined(DEVICE_32MZ1024ECM124) || defined(DEVICE_32MZ1024ECM144)                    \
    || defined(DEVICE_32MZ1024EFE100) || defined(DEVICE_32MZ1024EFE124) || defined(DEVICE_32MZ1024EFE144) || defined(DEVICE_32MZ1024EFF100)                    \
    || defined(DEVICE_32MZ1024EFF124) || defined(DEVICE_32MZ1024EFF144) || defined(DEVICE_32MZ1024EFG100) || defined(DEVICE_32MZ1024EFG124)                    \
    || defined(DEVICE_32MZ1024EFG144) || defined(DEVICE_32MZ1024EFH100) || defined(DEVICE_32MZ1024EFH124) || defined(DEVICE_32MZ1024EFH144)                    \
    || defined(DEVICE_32MZ1024EFK100) || defined(DEVICE_32MZ1024EFK124) || defined(DEVICE_32MZ1024EFK144) || defined(DEVICE_32MZ1024EFM100)                    \
    || defined(DEVICE_32MZ1024EFM124) || defined(DEVICE_32MZ1024EFM144) || defined(DEVICE_32MZ1025DAA169) || defined(DEVICE_32MZ1025DAA176)                    \
    || defined(DEVICE_32MZ1025DAA288) || defined(DEVICE_32MZ1025DAB169) || defined(DEVICE_32MZ1025DAB176) || defined(DEVICE_32MZ1025DAB288)                    \
    || defined(DEVICE_32MZ1025DAG169) || defined(DEVICE_32MZ1025DAG176) || defined(DEVICE_32MZ1025DAH169) || defined(DEVICE_32MZ1025DAH176)                    \
    || defined(DEVICE_32MZ1025DAK169) || defined(DEVICE_32MZ1025DAK176) || defined(DEVICE_32MZ1025DAL169) || defined(DEVICE_32MZ1025DAL176)                    \
    || defined(DEVICE_32MZ1025DAR169) || defined(DEVICE_32MZ1025DAR176) || defined(DEVICE_32MZ1025DAS169) || defined(DEVICE_32MZ1025DAS176)                    \
    || defined(DEVICE_32MZ1064DAA169) || defined(DEVICE_32MZ1064DAA176) || defined(DEVICE_32MZ1064DAA288) || defined(DEVICE_32MZ1064DAB169)                    \
    || defined(DEVICE_32MZ1064DAB176) || defined(DEVICE_32MZ1064DAB288) || defined(DEVICE_32MZ1064DAG169) || defined(DEVICE_32MZ1064DAG176)                    \
    || defined(DEVICE_32MZ1064DAH169) || defined(DEVICE_32MZ1064DAH176) || defined(DEVICE_32MZ1064DAK169) || defined(DEVICE_32MZ1064DAK176)                    \
    || defined(DEVICE_32MZ1064DAL169) || defined(DEVICE_32MZ1064DAL176) || defined(DEVICE_32MZ1064DAR169) || defined(DEVICE_32MZ1064DAR176)                    \
    || defined(DEVICE_32MZ1064DAS169) || defined(DEVICE_32MZ1064DAS176) || defined(DEVICE_32MZ2025DAA169) || defined(DEVICE_32MZ2025DAA176)                    \
    || defined(DEVICE_32MZ2025DAA288) || defined(DEVICE_32MZ2025DAB169) || defined(DEVICE_32MZ2025DAB176) || defined(DEVICE_32MZ2025DAB288)                    \
    || defined(DEVICE_32MZ2025DAG169) || defined(DEVICE_32MZ2025DAG176) || defined(DEVICE_32MZ2025DAH169) || defined(DEVICE_32MZ2025DAH176)                    \
    || defined(DEVICE_32MZ2025DAK169) || defined(DEVICE_32MZ2025DAK176) || defined(DEVICE_32MZ2025DAL169) || defined(DEVICE_32MZ2025DAL176)                    \
    || defined(DEVICE_32MZ2025DAR169) || defined(DEVICE_32MZ2025DAR176) || defined(DEVICE_32MZ2025DAS169) || defined(DEVICE_32MZ2025DAS176)                    \
    || defined(DEVICE_32MZ2048ECG100) || defined(DEVICE_32MZ2048ECG124) || defined(DEVICE_32MZ2048ECG144) || defined(DEVICE_32MZ2048ECH100)                    \
    || defined(DEVICE_32MZ2048ECH124) || defined(DEVICE_32MZ2048ECH144) || defined(DEVICE_32MZ2048ECM100) || defined(DEVICE_32MZ2048ECM124)                    \
    || defined(DEVICE_32MZ2048ECM144) || defined(DEVICE_32MZ2048EFG100) || defined(DEVICE_32MZ2048EFG124) || defined(DEVICE_32MZ2048EFG144)                    \
    || defined(DEVICE_32MZ2048EFH100) || defined(DEVICE_32MZ2048EFH124) || defined(DEVICE_32MZ2048EFH144) || defined(DEVICE_32MZ2048EFM100)                    \
    || defined(DEVICE_32MZ2048EFM124) || defined(DEVICE_32MZ2048EFM144) || defined(DEVICE_32MZ2064DAA169) || defined(DEVICE_32MZ2064DAA176)                    \
    || defined(DEVICE_32MZ2064DAA288) || defined(DEVICE_32MZ2064DAB169) || defined(DEVICE_32MZ2064DAB176) || defined(DEVICE_32MZ2064DAB288)                    \
    || defined(DEVICE_32MZ2064DAG169) || defined(DEVICE_32MZ2064DAG176) || defined(DEVICE_32MZ2064DAH169) || defined(DEVICE_32MZ2064DAH176)                    \
    || defined(DEVICE_32MZ2064DAK169) || defined(DEVICE_32MZ2064DAK176) || defined(DEVICE_32MZ2064DAL169) || defined(DEVICE_32MZ2064DAL176)                    \
    || defined(DEVICE_32MZ2064DAR169) || defined(DEVICE_32MZ2064DAR176) || defined(DEVICE_32MZ2064DAS169) || defined(DEVICE_32MZ2064DAS176)
#    define I2C_COUNT 5
#else
#    define I2C_COUNT 0
#endif

// ======================= I2C module existance =======================
#if defined(DEVICE_32MZ0512EFE064) || defined(DEVICE_32MZ0512EFF064) || defined(DEVICE_32MZ2048EFM064) || defined(DEVICE_32MZ0512EFK064)                       \
    || defined(DEVICE_32MZ1024ECG064) || defined(DEVICE_32MZ1024ECH064) || defined(DEVICE_32MZ1024ECM064) || defined(DEVICE_32MZ1024EFE064)                    \
    || defined(DEVICE_32MZ1024EFF064) || defined(DEVICE_32MZ1024EFG064) || defined(DEVICE_32MZ1024EFH064) || defined(DEVICE_32MZ1024EFK064)                    \
    || defined(DEVICE_32MZ1024EFM064) || defined(DEVICE_32MZ2048ECG064) || defined(DEVICE_32MZ2048ECH064) || defined(DEVICE_32MZ2048ECM064)                    \
    || defined(DEVICE_32MZ2048EFG064) || defined(DEVICE_32MZ2048EFH064) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX564F064H)                        \
    || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX664F064H)                            \
    || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX695F512H)                            \
    || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX795F512H)

#    define I2C_NOI2C2  // I2C 2 does not exist on 64 pins MZ/MX device, but they have I2C 5 with I2C_COUNT=4 ...

#    if I2C_COUNT >= 1
#        define I2C_NUM1 0
#    endif
// no I2C2
#    if I2C_COUNT >= 2
#        define I2C_NUM3 1
#    endif
#    if I2C_COUNT >= 3
#        define I2C_NUM4 2
#    endif
#    if I2C_COUNT >= 4
#        define I2C_NUM5 3
#    endif

rt_dev_t i2c(uint8_t d);

#else  // in normal case ...
#    if I2C_COUNT >= 1
#        define I2C_NUM1 0
#    endif
#    if I2C_COUNT >= 2
#        define I2C_NUM2 1
#    endif
#    if I2C_COUNT >= 3
#        define I2C_NUM3 2
#    endif
#    if I2C_COUNT >= 4
#        define I2C_NUM4 3
#    endif
#    if I2C_COUNT >= 5
#        define I2C_NUM5 4
#    endif

#    define i2c(d) MKDEV(DEV_CLASS_I2C, (d)-1);
#endif

#define I2C_FPGD 9615384  // 104ns

#if defined(ARCHI_pic32mk)
uint32_t i2c_clock(rt_dev_t device);
#else
#    define i2c_clock(d) sysclock_periphFreq(SYSCLOCK_CLOCK_I2C)
#endif

// ======================= Interrupt bits helper =======================
#if defined(ARCHI_pic32mzec) || defined(ARCHI_pic32mzef) || defined(ARCHI_pic32mzda)
// interrupt bits helpers for MZ
#    ifndef _I2C1SIE
#        define _I2C1MIE IEC3bits.I2C1MIE
#        define _I2C1MIF IFS3bits.I2C1MIF
#        define _I2C1MIP IPC29bits.I2C1MIP
#        define _I2C1MIS IPC29bits.I2C1MIS
#        define _I2C1SIE IEC3bits.I2C1SIE
#        define _I2C1SIF IFS3bits.I2C1SIF
#        define _I2C1SIP IPC29bits.I2C1SIP
#        define _I2C1SIS IPC29bits.I2C1SIS
#        define _I2C2MIE IEC4bits.I2C2MIE
#        define _I2C2MIF IFS4bits.I2C2MIF
#        define _I2C2MIP IPC37bits.I2C2MIP
#        define _I2C2MIS IPC37bits.I2C2MIS
#        define _I2C2SIE IEC4bits.I2C2SIE
#        define _I2C2SIF IFS4bits.I2C2SIF
#        define _I2C2SIP IPC37bits.I2C2SIP
#        define _I2C2SIS IPC37bits.I2C2SIS
#        define _I2C3MIE IEC5bits.I2C3MIE
#        define _I2C3MIF IFS5bits.I2C3MIF
#        define _I2C3MIP IPC40bits.I2C3MIP
#        define _I2C3MIS IPC40bits.I2C3MIS
#        define _I2C3SIE IEC5bits.I2C3SIE
#        define _I2C3SIF IFS5bits.I2C3SIF
#        define _I2C3SIP IPC40bits.I2C3SIP
#        define _I2C3SIS IPC40bits.I2C3SIS
#        define _I2C4MIE IEC5bits.I2C4MIE
#        define _I2C4MIF IFS5bits.I2C4MIF
#        define _I2C4MIP IPC43bits.I2C4MIP
#        define _I2C4MIS IPC43bits.I2C4MIS
#        define _I2C4SIE IEC5bits.I2C4SIE
#        define _I2C4SIF IFS5bits.I2C4SIF
#        define _I2C4SIP IPC43bits.I2C4SIP
#        define _I2C4SIS IPC43bits.I2C4SIS
#        define _I2C5MIE IEC5bits.I2C5MIE
#        define _I2C5MIF IFS5bits.I2C5MIF
#        define _I2C5MIP IPC46bits.I2C5MIP
#        define _I2C5MIS IPC46bits.I2C5MIS
#        define _I2C5SIE IEC5bits.I2C5SIE
#        define _I2C5SIF IFS5bits.I2C5SIF
#        define _I2C5SIP IPC45bits.I2C5SIP
#        define _I2C5SIS IPC45bits.I2C5SIS
#    endif

#elif defined(ARCHI_pic32mm)
// interrupt bits helpers for MM
#    ifndef _I2C1SIE
#        define _I2C1MIE IEC2bits.I2C1MIE
#        define _I2C1MIF IFS2bits.I2C1MIF
#        define _I2C1MIP IPC16bits.I2C1MIP
#        define _I2C1MIS IPC16bits.I2C1MIS
#        define _I2C1SIE IEC2bits.I2C1SIE
#        define _I2C1SIF IFS2bits.I2C1SIF
#        define _I2C1SIP IPC16bits.I2C1SIP
#        define _I2C1SIS IPC16bits.I2C1SIS
#        define _I2C2MIE IEC2bits.I2C2MIE
#        define _I2C2MIF IFS2bits.I2C2MIF
#        define _I2C2MIP IPC17bits.I2C2MIP
#        define _I2C2MIS IPC17bits.I2C2MIS
#        define _I2C2SIE IEC2bits.I2C2SIE
#        define _I2C2SIF IFS2bits.I2C2SIF
#        define _I2C2SIP IPC17bits.I2C2SIP
#        define _I2C2SIS IPC17bits.I2C2SIS
#        define _I2C3MIE IEC2bits.I2C3MIE
#        define _I2C3MIF IFS2bits.I2C3MIF
#        define _I2C3MIP IPC18bits.I2C3MIP
#        define _I2C3MIS IPC18bits.I2C3MIS
#        define _I2C3SIE IEC2bits.I2C3SIE
#        define _I2C3SIF IFS2bits.I2C3SIF
#        define _I2C3SIP IPC17bits.I2C3SIP
#        define _I2C3SIS IPC17bits.I2C3SIS
#    endif

#elif defined(ARCHI_pic32mk)
// interrupt bits helpers for MK
#    ifndef _I2C1SIE
#        define _I2C1MIE IEC1bits.I2C1MIE
#        define _I2C1MIF IFS1bits.I2C1MIF
#        define _I2C1MIP IPC10bits.I2C1MIP
#        define _I2C1MIS IPC10bits.I2C1MIS
#        define _I2C1SIE IEC1bits.I2C1SIE
#        define _I2C1SIF IFS1bits.I2C1SIF
#        define _I2C1SIP IPC10bits.I2C1SIP
#        define _I2C1SIS IPC10bits.I2C1SIS
#        define _I2C2MIE IEC1bits.I2C2MIE
#        define _I2C2MIF IFS1bits.I2C2MIF
#        define _I2C2MIP IPC15bits.I2C2MIP
#        define _I2C2MIS IPC15bits.I2C2MIS
#        define _I2C2SIE IEC1bits.I2C2SIE
#        define _I2C2SIF IFS1bits.I2C2SIF
#        define _I2C2SIP IPC15bits.I2C2SIP
#        define _I2C2SIS IPC15bits.I2C2SIS
#        define _I2C3MIE IEC5bits.I2C3MIE
#        define _I2C3MIF IFS5bits.I2C3MIF
#        define _I2C3MIP IPC45bits.I2C3MIP
#        define _I2C3MIS IPC45bits.I2C3MIS
#        define _I2C3SIE IEC5bits.I2C3SIE
#        define _I2C3SIF IFS5bits.I2C3SIF
#        define _I2C3SIP IPC45bits.I2C3SIP
#        define _I2C3SIS IPC45bits.I2C3SIS
#        define _I2C4MIE IEC6bits.I2C4MIE
#        define _I2C4MIF IFS6bits.I2C4MIF
#        define _I2C4MIP IPC49bits.I2C4MIP
#        define _I2C4MIS IPC49bits.I2C4MIS
#        define _I2C4SIE IEC6bits.I2C4SIE
#        define _I2C4SIF IFS6bits.I2C4SIF
#        define _I2C4SIP IPC48bits.I2C4SIP
#        define _I2C4SIS IPC48bits.I2C4SIS
#    endif

#elif defined(ARCHI_pic32mx)
// interrupt bits helpers for MX
#    if defined(DEVICE_32MX530F128H) || defined(DEVICE_32MX550F256H) || defined(DEVICE_32MX570F512H) || defined(DEVICE_32MX530F128L)                           \
        || defined(DEVICE_32MX550F256L) || defined(DEVICE_32MX570F512L) || defined(DEVICE_32MX534F064H) || defined(DEVICE_32MX534F064L)                        \
        || defined(DEVICE_32MX564F064H) || defined(DEVICE_32MX564F064L) || defined(DEVICE_32MX564F128H) || defined(DEVICE_32MX564F128L)                        \
        || defined(DEVICE_32MX575F256H) || defined(DEVICE_32MX575F256L) || defined(DEVICE_32MX575F512H) || defined(DEVICE_32MX575F512L)                        \
        || defined(DEVICE_32MX664F064H) || defined(DEVICE_32MX664F064L) || defined(DEVICE_32MX664F128H) || defined(DEVICE_32MX664F128L)                        \
        || defined(DEVICE_32MX675F256H) || defined(DEVICE_32MX675F256L) || defined(DEVICE_32MX675F512H) || defined(DEVICE_32MX675F512L)                        \
        || defined(DEVICE_32MX695F512H) || defined(DEVICE_32MX695F512L) || defined(DEVICE_32MX764F128H) || defined(DEVICE_32MX764F128L)                        \
        || defined(DEVICE_32MX775F256H) || defined(DEVICE_32MX775F256L) || defined(DEVICE_32MX775F512H) || defined(DEVICE_32MX775F512L)                        \
        || defined(DEVICE_32MX795F512H) || defined(DEVICE_32MX795F512L)
#        ifndef _I2C1SIE
#            define _I2C1IP  IPC6bits.I2C1IP
#            define _I2C1IS  IPC6bits.I2C1IS
#            define _I2C1MIE IEC0bits.I2C1MIE
#            define _I2C1MIF IFS0bits.I2C1MIF
#            define _I2C1SIE IEC0bits.I2C1SIE
#            define _I2C1SIF IFS0bits.I2C1SIF
#            define _I2C2IP  IPC8bits.I2C2IP
#            define _I2C2IS  IPC8bits.I2C2IS
#            define _I2C2MIE IEC1bits.I2C2MIE
#            define _I2C2MIF IFS1bits.I2C2MIF
#            define _I2C2SIE IEC1bits.I2C2SIE
#            define _I2C2SIF IFS1bits.I2C2SIF
#            define _I2C3IP  IPC6bits.I2C3IP
#            define _I2C3IS  IPC6bits.I2C3IS
#            define _I2C3MIE IEC0bits.I2C3MIE
#            define _I2C3MIF IFS0bits.I2C3MIF
#            define _I2C3SIE IEC0bits.I2C3SIE
#            define _I2C3SIF IFS0bits.I2C3SIF
#            define _I2C4IP  IPC7bits.I2C4IP
#            define _I2C4IS  IPC7bits.I2C4IS
#            define _I2C4MIE IEC1bits.I2C4MIE
#            define _I2C4MIF IFS1bits.I2C4MIF
#            define _I2C4SIE IEC1bits.I2C4SIE
#            define _I2C4SIF IFS1bits.I2C4SIF
#            define _I2C5IP  IPC8bits.I2C5IP
#            define _I2C5IS  IPC8bits.I2C5IS
#            define _I2C5MIE IEC1bits.I2C5MIE
#            define _I2C5MIF IFS1bits.I2C5MIF
#            define _I2C5SIE IEC1bits.I2C5SIE
#            define _I2C5SIF IFS1bits.I2C5SIF
#        endif

#    else
#        ifndef _I2C1SIE
#            define _I2C1IP  IPC8bits.I2C1IP
#            define _I2C1IS  IPC8bits.I2C1IS
#            define _I2C1MIE IEC1bits.I2C1MIE
#            define _I2C1MIF IFS1bits.I2C1MIF
#            define _I2C1SIE IEC1bits.I2C1SIE
#            define _I2C1SIF IFS1bits.I2C1SIF
#            define _I2C2IP  IPC9bits.I2C2IP
#            define _I2C2IS  IPC9bits.I2C2IS
#            define _I2C2MIE IEC1bits.I2C2MIE
#            define _I2C2MIF IFS1bits.I2C2MIF
#            define _I2C2SIE IEC1bits.I2C2SIE
#            define _I2C2SIF IFS1bits.I2C2SIF
#        endif
#    endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // I2C_PIC32_H
