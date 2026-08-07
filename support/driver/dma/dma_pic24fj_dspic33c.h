/**
 * @file dma_dspic33c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021-2026
 *
 * @date September 11, 2021, 03:50 PM
 *
 * @brief DMA support driver for PIC24FJ and dsPIC33C
 *
 * Implementation based on Microchip document DS30009742C:
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33-PIC24-FRM,-Direct-Memory-Access-Controller-(DMA)-DS30009742C.pdf
 */

#ifndef DMA_DSPIC33C_H
#define DMA_DSPIC33C_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIMULATOR
#    define _dma_space_ __attribute__((space(xmemory), aligned(2)))
#endif

#define DMA_ADDRMODE_NOCHANGE  0b00
#define DMA_ADDRMODE_INCREMENT 0b01
#define DMA_ADDRMODE_DECREMENT 0b10

#define DMA_MODE_ONESHOT            0b00
#define DMA_MODE_REPEATEDONESHOT    0b01
#define DMA_MODE_CONTINUOUS         0b10
#define DMA_MODE_REPEATEDCONTINUOUS 0b11

#define DMA_WORDSIZE_8  0b1
#define DMA_WORDSIZE_16 0b0

#define DMA_OPTION_RELOAD 0x1
#define DMA_OPTION_NULLW  0x2

#if defined(DEVICE_24FJ32GP202) || defined(DEVICE_24FJ32GP203) || defined(DEVICE_24FJ32GP205) || defined(DEVICE_24FJ32GU202) || defined(DEVICE_24FJ32GU203)    \
    || defined(DEVICE_24FJ32GU205) || defined(DEVICE_24FJ64GP202) || defined(DEVICE_24FJ64GP203) || defined(DEVICE_24FJ64GP205) || defined(DEVICE_24FJ64GU202) \
    || defined(DEVICE_24FJ64GU203) || defined(DEVICE_24FJ64GU205) || defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1)                            \
    || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1) || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1)                        \
    || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1) || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1)                        \
    || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1) || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1)                    \
    || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1) || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1)                    \
    || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1) || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1)                    \
    || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP218S1) || defined(DEVICE_33CH256MP505S1) || defined(DEVICE_33CH256MP506S1)                    \
    || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206S1) || defined(DEVICE_33CH512MP208S1)                    \
    || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)
#    define DMA_COUNT 2
#elif defined(DEVICE_33CDV64MC106) || defined(DEVICE_33CDV128MC106) || defined(DEVICE_33CDV128MC506) || defined(DEVICE_33CDV128MP206)                          \
    || defined(DEVICE_33CDV128MP506) || defined(DEVICE_33CDV256MC106) || defined(DEVICE_33CDV256MC506) || defined(DEVICE_33CDV256MP206)                        \
    || defined(DEVICE_33CDV256MP506) || defined(DEVICE_33CDVC128MP506) || defined(DEVICE_33CDVC256MP506) || defined(DEVICE_33CDVL64MC106)                      \
    || defined(DEVICE_33CDVL128MC106) || defined(DEVICE_33CDVL128MC506) || defined(DEVICE_33CDVL256MC106) || defined(DEVICE_33CDVL256MC506)                    \
    || defined(DEVICE_33CK32MC002) || defined(DEVICE_33CK32MC003) || defined(DEVICE_33CK32MC005) || defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) \
    || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) \
    || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) \
    || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC002) || defined(DEVICE_33CK64MC003) || defined(DEVICE_33CK64MC005) \
    || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) \
    || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) \
    || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) \
    || defined(DEVICE_33CK64MP508) || defined(DEVICE_33CK128MC002) || defined(DEVICE_33CK128MC003) || defined(DEVICE_33CK128MC005)                             \
    || defined(DEVICE_33CK128MC006) || defined(DEVICE_33CK128MC102) || defined(DEVICE_33CK128MC103) || defined(DEVICE_33CK128MC105)                            \
    || defined(DEVICE_33CK128MC106) || defined(DEVICE_33CK128MC502) || defined(DEVICE_33CK128MC503) || defined(DEVICE_33CK128MC505)                            \
    || defined(DEVICE_33CK128MC506) || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205)                            \
    || defined(DEVICE_33CK128MP206) || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503)                            \
    || defined(DEVICE_33CK128MP505) || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MC002)                            \
    || defined(DEVICE_33CK256MC003) || defined(DEVICE_33CK256MC005) || defined(DEVICE_33CK256MC006) || defined(DEVICE_33CK256MC102)                            \
    || defined(DEVICE_33CK256MC103) || defined(DEVICE_33CK256MC105) || defined(DEVICE_33CK256MC106) || defined(DEVICE_33CK256MC502)                            \
    || defined(DEVICE_33CK256MC503) || defined(DEVICE_33CK256MC505) || defined(DEVICE_33CK256MC506) || defined(DEVICE_33CK256MP202)                            \
    || defined(DEVICE_33CK256MP203) || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208)                            \
    || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506)                            \
    || defined(DEVICE_33CK256MP508)
#    define DMA_COUNT 4
#elif defined(DEVICE_24FJ64GA202) || defined(DEVICE_24FJ64GA204) || defined(DEVICE_24FJ64GA306) || defined(DEVICE_24FJ64GA308) || defined(DEVICE_24FJ64GA310)  \
    || defined(DEVICE_24FJ64GA406) || defined(DEVICE_24FJ64GA410) || defined(DEVICE_24FJ64GA412) || defined(DEVICE_24FJ64GA702) || defined(DEVICE_24FJ64GA704) \
    || defined(DEVICE_24FJ64GA705) || defined(DEVICE_24FJ64GB202) || defined(DEVICE_24FJ64GB204) || defined(DEVICE_24FJ64GB406) || defined(DEVICE_24FJ64GB410) \
    || defined(DEVICE_24FJ64GB412) || defined(DEVICE_24FJ64GC006) || defined(DEVICE_24FJ64GC010) || defined(DEVICE_24FJ64GL302) || defined(DEVICE_24FJ64GL303) \
    || defined(DEVICE_24FJ64GL305) || defined(DEVICE_24FJ64GL306) || defined(DEVICE_24FJ128GA202) || defined(DEVICE_24FJ128GA204)                              \
    || defined(DEVICE_24FJ128GA306) || defined(DEVICE_24FJ128GA308) || defined(DEVICE_24FJ128GA310) || defined(DEVICE_24FJ128GA406)                            \
    || defined(DEVICE_24FJ128GA410) || defined(DEVICE_24FJ128GA412) || defined(DEVICE_24FJ128GA702) || defined(DEVICE_24FJ128GA704)                            \
    || defined(DEVICE_24FJ128GA705) || defined(DEVICE_24FJ128GB202) || defined(DEVICE_24FJ128GB204) || defined(DEVICE_24FJ128GB406)                            \
    || defined(DEVICE_24FJ128GB410) || defined(DEVICE_24FJ128GB412) || defined(DEVICE_24FJ128GC006) || defined(DEVICE_24FJ128GC010)                            \
    || defined(DEVICE_24FJ128GL302) || defined(DEVICE_24FJ128GL303) || defined(DEVICE_24FJ128GL305) || defined(DEVICE_24FJ128GL306)                            \
    || defined(DEVICE_24FJ128GL405) || defined(DEVICE_24FJ128GL406) || defined(DEVICE_24FJ128GL408) || defined(DEVICE_24FJ128GL410)                            \
    || defined(DEVICE_24FJ128GU405) || defined(DEVICE_24FJ128GU406) || defined(DEVICE_24FJ128GU408) || defined(DEVICE_24FJ128GU410)                            \
    || defined(DEVICE_24FJ256GA406) || defined(DEVICE_24FJ256GA410) || defined(DEVICE_24FJ256GA412) || defined(DEVICE_24FJ256GA702)                            \
    || defined(DEVICE_24FJ256GA704) || defined(DEVICE_24FJ256GA705) || defined(DEVICE_24FJ256GB406) || defined(DEVICE_24FJ256GB410)                            \
    || defined(DEVICE_24FJ256GB412) || defined(DEVICE_24FJ256GL405) || defined(DEVICE_24FJ256GL406) || defined(DEVICE_24FJ256GL408)                            \
    || defined(DEVICE_24FJ256GL410) || defined(DEVICE_24FJ256GU405) || defined(DEVICE_24FJ256GU406) || defined(DEVICE_24FJ256GU408)                            \
    || defined(DEVICE_24FJ256GU410) || defined(DEVICE_24FJ512GL405) || defined(DEVICE_24FJ512GL406) || defined(DEVICE_24FJ512GL408)                            \
    || defined(DEVICE_24FJ512GL410) || defined(DEVICE_24FJ512GU405) || defined(DEVICE_24FJ512GU406) || defined(DEVICE_24FJ512GU408)                            \
    || defined(DEVICE_24FJ512GU410) || defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205)                               \
    || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208) || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) \
    || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203)                              \
    || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206) || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502)                            \
    || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505) || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508)                            \
    || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206) || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP218)                            \
    || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508) || defined(DEVICE_33CH512MP205)                            \
    || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505) || defined(DEVICE_33CH512MP506)                            \
    || defined(DEVICE_33CH512MP508)
#    define DMA_COUNT 6
#elif defined(DEVICE_24FJ128GA606) || defined(DEVICE_24FJ128GA610) || defined(DEVICE_24FJ128GB606) || defined(DEVICE_24FJ128GB610)                             \
    || defined(DEVICE_24FJ256GA606) || defined(DEVICE_24FJ256GA610) || defined(DEVICE_24FJ256GB606) || defined(DEVICE_24FJ256GB610)                            \
    || defined(DEVICE_24FJ512GA606) || defined(DEVICE_24FJ512GA610) || defined(DEVICE_24FJ512GB606) || defined(DEVICE_24FJ512GB610)                            \
    || defined(DEVICE_24FJ1024GA606) || defined(DEVICE_24FJ1024GA610) || defined(DEVICE_24FJ1024GB606) || defined(DEVICE_24FJ1024GB610)                        \
    || defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP405)                            \
    || defined(DEVICE_33CK256MP406) || defined(DEVICE_33CK256MP408) || defined(DEVICE_33CK256MP410) || defined(DEVICE_33CK256MP605)                            \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK256MP705) || defined(DEVICE_33CK256MP706)                            \
    || defined(DEVICE_33CK256MP708) || defined(DEVICE_33CK256MP710) || defined(DEVICE_33CK256MPT608) || defined(DEVICE_33CK512MP305)                           \
    || defined(DEVICE_33CK512MP306) || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP405) || defined(DEVICE_33CK512MP406)                            \
    || defined(DEVICE_33CK512MP408) || defined(DEVICE_33CK512MP410) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606)                            \
    || defined(DEVICE_33CK512MP608) || defined(DEVICE_33CK512MP705) || defined(DEVICE_33CK512MP706) || defined(DEVICE_33CK512MP708)                            \
    || defined(DEVICE_33CK512MP710) || defined(DEVICE_33CK512MPT608) || defined(DEVICE_33CK1024MP405) || defined(DEVICE_33CK1024MP406)                         \
    || defined(DEVICE_33CK1024MP408) || defined(DEVICE_33CK1024MP410) || defined(DEVICE_33CK1024MP705) || defined(DEVICE_33CK1024MP706)                        \
    || defined(DEVICE_33CK1024MP708) || defined(DEVICE_33CK1024MP710)
#    define DMA_COUNT 8
#else
#    define DMA_COUNT 0
#endif

#if defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK64MC102) || defined(DEVICE_33CK64MC103)    \
    || defined(DEVICE_33CK64MC105)
#    define DMA_TRIGGER_INT0_External_Interrupt_0    0x00
#    define DMA_TRIGGER_SCCP1_IC_OC                  0x01
#    define DMA_TRIGGER_SPI1_Receiver                0x02
#    define DMA_TRIGGER_SPI1_Transmitter             0x03
#    define DMA_TRIGGER_UART1_Receiver               0x04
#    define DMA_TRIGGER_UART1_Transmitter            0x05
#    define DMA_TRIGGER_ECC_Single_Bit_Error         0x06
#    define DMA_TRIGGER_NVM_Write_Complete           0x07
#    define DMA_TRIGGER_INT1_External_Interrupt_1    0x08
#    define DMA_TRIGGER_SI2C1_I2C1_Client_Event      0x09
#    define DMA_TRIGGER_MI2C1_I2C1_Host_Event        0x0A
#    define DMA_TRIGGER_INT2_External_Interrupt_2    0x0B
#    define DMA_TRIGGER_SCCP2_Interrupt              0x0C
#    define DMA_TRIGGER_INT3_External_Interrupt_3    0x0D
#    define DMA_TRIGGER_UART2_Receiver               0x0E
#    define DMA_TRIGGER_UART2_Transmitter            0x0F
#    define DMA_TRIGGER_SPI2_Receiver                0x10
#    define DMA_TRIGGER_SPI2_Transmitter             0x11
#    define DMA_TRIGGER_SCCP3_Interrupt              0x12
#    define DMA_TRIGGER_SCCP4_Interrupt              0x15
#    define DMA_TRIGGER_CRC_Generator_Interrupt      0x18
#    define DMA_TRIGGER_PWM_Event_A                  0x19
#    define DMA_TRIGGER_PWM_Event_B                  0x1B
#    define DMA_TRIGGER_PWM_Generator_1              0x1C
#    define DMA_TRIGGER_PWM_Generator_2              0x1D
#    define DMA_TRIGGER_PWM_Generator_3              0x1E
#    define DMA_TRIGGER_PWM_Generator_4              0x1F
#    define DMA_TRIGGER_PWM_Event_C                  0x24
#    define DMA_TRIGGER_SENT1_TX_RX                  0x25
#    define DMA_TRIGGER_ADC_Common_Interrupt         0x27
#    define DMA_TRIGGER_ADC_Done_AN0                 0x28
#    define DMA_TRIGGER_ADC_Done_AN1                 0x29
#    define DMA_TRIGGER_ADC_Done_AN2                 0x2A
#    define DMA_TRIGGER_ADC_Done_AN3                 0x2B
#    define DMA_TRIGGER_ADC_Done_AN4                 0x2C
#    define DMA_TRIGGER_ADC_Done_AN5                 0x2D
#    define DMA_TRIGGER_ADC_Done_AN6                 0x2E
#    define DMA_TRIGGER_ADC_Done_AN7                 0x2F
#    define DMA_TRIGGER_ADC_Done_AN8                 0x30
#    define DMA_TRIGGER_ADC_Done_AN9                 0x31
#    define DMA_TRIGGER_ADC_Done_AN10                0x32
#    define DMA_TRIGGER_ADC_Done_AN11                0x33
#    define DMA_TRIGGER_ADC_Done_AN12                0x34
#    define DMA_TRIGGER_ADC_Done_AN13                0x35
#    define DMA_TRIGGER_ADC_Done_AN14                0x36
#    define DMA_TRIGGER_ADC_Done_AN15                0x37
#    define DMA_TRIGGER_ADC_Done_AN16                0x38
#    define DMA_TRIGGER_ADC_Done_AN17                0x39
#    define DMA_TRIGGER_AD1FLTR1_Oversample_Filter_1 0x40
#    define DMA_TRIGGER_AD1FLTR2_Oversample_Filter_2 0x41
#    define DMA_TRIGGER_AD1FLTR3_Oversample_Filter_3 0x42
#    define DMA_TRIGGER_AD1FLTR4_Oversample_Filter_4 0x43
#    define DMA_TRIGGER_CLC1_Positive_Edge_Interrupt 0x44
#    define DMA_TRIGGER_CLC2_Positive_Edge_Interrupt 0x45
#    define DMA_TRIGGER_SPI1_Fault_Interrupt         0x46
#    define DMA_TRIGGER_SPI2_Fault_Interrupt         0x47
#    define DMA_TRIGGER_PWM_Event_D                  0x57
#    define DMA_TRIGGER_PWM_Event_E                  0x58
#    define DMA_TRIGGER_PWM_Event_F                  0x59
#    define DMA_TRIGGER_CLC3_Positive_Edge_Interrupt 0x60
#    define DMA_TRIGGER_CLC4_Positive_Edge_Interrupt 0x61
#    define DMA_TRIGGER_UART3_Receiver               0x68
#    define DMA_TRIGGER_UART3_Transmitter            0x69
#elif defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103) || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203)  \
    || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) \
    || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) || defined(DEVICE_33CK64MP202) \
    || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) || defined(DEVICE_33CK64MP502) \
    || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508)                                \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206)                            \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                            \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                            \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP305)                            \
    || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP502) || defined(DEVICE_33CK256MP503)                            \
    || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508) || defined(DEVICE_33CK256MP605)                            \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306)                            \
    || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)
#    define DMA_TRIGGER_INT0_External_Interrupt_0    0x00
#    define DMA_TRIGGER_SCCP1_Interrupt              0x01
#    define DMA_TRIGGER_SPI1_Receiver                0x02
#    define DMA_TRIGGER_SPI1_Transmitter             0x03
#    define DMA_TRIGGER_UART1_Receiver               0x04
#    define DMA_TRIGGER_UART1_Transmitter            0x05
#    define DMA_TRIGGER_ECC_Single_Bit_Error         0x06
#    define DMA_TRIGGER_NVM_Write_Complete           0x07
#    define DMA_TRIGGER_INT1_External_Interrupt_1    0x08
#    define DMA_TRIGGER_SI2C1_I2C1_Client_Event      0x09
#    define DMA_TRIGGER_MI2C1_I2C1_Host_Event        0x0A
#    define DMA_TRIGGER_INT2_External_Interrupt_2    0x0B
#    define DMA_TRIGGER_SCCP2_Interrupt              0x0C
#    define DMA_TRIGGER_INT3_External_Interrupt_3    0x0D
#    define DMA_TRIGGER_UART2_Receiver               0x0E
#    define DMA_TRIGGER_UART2_Transmitter            0x0F
#    define DMA_TRIGGER_SPI2_Receiver                0x10
#    define DMA_TRIGGER_SPI2_Transmitter             0x11
#    define DMA_TRIGGER_SCCP3_Interrupt              0x12
#    define DMA_TRIGGER_SI2C2_I2C2_Client_Event      0x13
#    define DMA_TRIGGER_MI2C2_I2C1_Host_Event        0x14
#    define DMA_TRIGGER_SCCP4_Interrupt              0x15
#    define DMA_TRIGGER_SCCP5_Interrupt              0x16
#    define DMA_TRIGGER_SCCP6_Interrupt              0x17
#    define DMA_TRIGGER_CRC_Generator_Interrupt      0x18
#    define DMA_TRIGGER_PWM_Event_A                  0x19
#    define DMA_TRIGGER_PWM_Event_B                  0x1B
#    define DMA_TRIGGER_PWM_Generator_1              0x1C
#    define DMA_TRIGGER_PWM_Generator_2              0x1D
#    define DMA_TRIGGER_PWM_Generator_3              0x1E
#    define DMA_TRIGGER_PWM_Generator_4              0x1F
#    define DMA_TRIGGER_PWM_Generator_5              0x20
#    define DMA_TRIGGER_PWM_Generator_6              0x21
#    define DMA_TRIGGER_PWM_Generator_7              0x22
#    define DMA_TRIGGER_PWM_Generator_8              0x23
#    define DMA_TRIGGER_PWM_Event_C                  0x24
#    define DMA_TRIGGER_SENT1_TX_RX                  0x25
#    define DMA_TRIGGER_SENT2_TX_RX                  0x26
#    define DMA_TRIGGER_ADC1_Group_Convert_Done      0x27
#    define DMA_TRIGGER_ADC_Done_AN0                 0x28
#    define DMA_TRIGGER_ADC_Done_AN1                 0x29
#    define DMA_TRIGGER_ADC_Done_AN2                 0x2A
#    define DMA_TRIGGER_ADC_Done_AN3                 0x2B
#    define DMA_TRIGGER_ADC_Done_AN4                 0x2C
#    define DMA_TRIGGER_ADC_Done_AN5                 0x2D
#    define DMA_TRIGGER_ADC_Done_AN6                 0x2E
#    define DMA_TRIGGER_ADC_Done_AN7                 0x2F
#    define DMA_TRIGGER_ADC_Done_AN8                 0x30
#    define DMA_TRIGGER_ADC_Done_AN9                 0x31
#    define DMA_TRIGGER_ADC_Done_AN10                0x32
#    define DMA_TRIGGER_ADC_Done_AN11                0x33
#    define DMA_TRIGGER_ADC_Done_AN12                0x34
#    define DMA_TRIGGER_ADC_Done_AN13                0x35
#    define DMA_TRIGGER_ADC_Done_AN14                0x36
#    define DMA_TRIGGER_ADC_Done_AN15                0x37
#    define DMA_TRIGGER_ADC_Done_AN16                0x38
#    define DMA_TRIGGER_ADC_Done_AN17                0x39
#    define DMA_TRIGGER_ADC_Done_AN18                0x3A
#    define DMA_TRIGGER_ADC_Done_AN19                0x3B
#    define DMA_TRIGGER_ADC_Done_AN20                0x3C
#    define DMA_TRIGGER_ADC_Done_AN21                0x3D
#    define DMA_TRIGGER_ADC_Done_AN22                0x3E
#    define DMA_TRIGGER_ADC_Done_AN23                0x3F
#    define DMA_TRIGGER_AD1FLTR1_Oversample_Filter_1 0x40
#    define DMA_TRIGGER_AD1FLTR2_Oversample_Filter_2 0x41
#    define DMA_TRIGGER_AD1FLTR3_Oversample_Filter_3 0x42
#    define DMA_TRIGGER_AD1FLTR4_Oversample_Filter_4 0x43
#    define DMA_TRIGGER_CLC1_Positive_Edge_Interrupt 0x44
#    define DMA_TRIGGER_CLC2_Positive_Edge_Interrupt 0x45
#    define DMA_TRIGGER_SPI1_Fault_Interrupt         0x46
#    define DMA_TRIGGER_SPI2_Fault_Interrupt         0x47
#    define DMA_TRIGGER_PWM_Event_D                  0x57
#    define DMA_TRIGGER_PWM_Event_E                  0x58
#    define DMA_TRIGGER_PWM_Event_F                  0x59
#    define DMA_TRIGGER_SCCP7_Interrupt              0x5C
#    define DMA_TRIGGER_SCCP8_Interrupt              0x5D
#    define DMA_TRIGGER_CLC3_Positive_Edge_Interrupt 0x60
#    define DMA_TRIGGER_CLC4_Positive_Edge_Interrupt 0x61
#    define DMA_TRIGGER_SPI3_Receiver                0x62
#    define DMA_TRIGGER_SPI3_Transmitter             0x63
#    define DMA_TRIGGER_SI2C3_I2C3_Client_Event      0x64
#    define DMA_TRIGGER_MI2C3_I2C3_Host_Event        0x65
#    define DMA_TRIGGER_SPI3_Fault                   0x66
#    define DMA_TRIGGER_MCCP9                        0x67
#    define DMA_TRIGGER_UART3_Receiver               0x68
#    define DMA_TRIGGER_UART3_Transmitter            0x69
#    define DMA_TRIGGER_ADC_Done_AN24                0x6A
#    define DMA_TRIGGER_ADC_Done_AN25                0x6B
#    define DMA_TRIGGER_PMP_Event                    0x6C
#    define DMA_TRIGGER_PMP_Error_Event              0x6D
#elif defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208)  \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                            \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                            \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206)                            \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508)                            \
    || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505)                            \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
#    define DMA_TRIGGER_INT0_External_Interrupt_0      0x00
#    define DMA_TRIGGER_SCCP1_IC_OC                    0x01
#    define DMA_TRIGGER_SPI1_Receiver                  0x02
#    define DMA_TRIGGER_SPI1_Transmitter               0x03
#    define DMA_TRIGGER_UART1_Receiver                 0x04
#    define DMA_TRIGGER_UART1_Transmitter              0x05
#    define DMA_TRIGGER_ECC_Single_Bit_Error           0x06
#    define DMA_TRIGGER_NVM_Write_Complete             0x07
#    define DMA_TRIGGER_INT1_External_Interrupt_1      0x08
#    define DMA_TRIGGER_SI2C1_I2C1_Slave_Event         0x09
#    define DMA_TRIGGER_MI2C1_I2C1_Master_Event        0x0A
#    define DMA_TRIGGER_INT2_External_Interrupt_2      0x0B
#    define DMA_TRIGGER_SCCP2_IC_OC                    0x0C
#    define DMA_TRIGGER_INT3_External_Interrupt_3      0x0D
#    define DMA_TRIGGER_UART2_Receiver                 0x0E
#    define DMA_TRIGGER_UART2_Transmitter              0x0F
#    define DMA_TRIGGER_SPI2_Receiver                  0x10
#    define DMA_TRIGGER_SPI2_Transmitter               0x11
#    define DMA_TRIGGER_SCCP3_IC_OC                    0x12
#    define DMA_TRIGGER_SI2C2_I2C2_Slave_Event         0x13
#    define DMA_TRIGGER_MI2C2_I2C1_Master_Event        0x14
#    define DMA_TRIGGER_SCCP4_IC_OC                    0x15
#    define DMA_TRIGGER_SCCP5_IC_OC                    0x16
#    define DMA_TRIGGER_SCCP6_IC_OC                    0x17
#    define DMA_TRIGGER_CRC_Generator_Interrupt        0x18
#    define DMA_TRIGGER_PWM_Event_A                    0x19
#    define DMA_TRIGGER_PWM_Event_B                    0x1B
#    define DMA_TRIGGER_PWM_Generator_1                0x1C
#    define DMA_TRIGGER_PWM_Generator_2                0x1D
#    define DMA_TRIGGER_PWM_Generator_3                0x1E
#    define DMA_TRIGGER_PWM_Generator_4                0x1F
#    define DMA_TRIGGER_PWM_Event_C                    0x24
#    define DMA_TRIGGER_SENT1_TX_RX                    0x25
#    define DMA_TRIGGER_SENT2_TX_RX                    0x26
#    define DMA_TRIGGER_ADC1_Group_Convert_Done        0x27
#    define DMA_TRIGGER_ADC_Done_AN0                   0x28
#    define DMA_TRIGGER_ADC_Done_AN1                   0x29
#    define DMA_TRIGGER_ADC_Done_AN2                   0x2A
#    define DMA_TRIGGER_ADC_Done_AN3                   0x2B
#    define DMA_TRIGGER_ADC_Done_AN4                   0x2C
#    define DMA_TRIGGER_ADC_Done_AN5                   0x2D
#    define DMA_TRIGGER_ADC_Done_AN6                   0x2E
#    define DMA_TRIGGER_ADC_Done_AN7                   0x2F
#    define DMA_TRIGGER_ADC_Done_AN8                   0x30
#    define DMA_TRIGGER_ADC_Done_AN9                   0x31
#    define DMA_TRIGGER_ADC_Done_AN10                  0x32
#    define DMA_TRIGGER_ADC_Done_AN11                  0x33
#    define DMA_TRIGGER_ADC_Done_AN12                  0x34
#    define DMA_TRIGGER_ADC_Done_AN13                  0x35
#    define DMA_TRIGGER_ADC_Done_AN14                  0x36
#    define DMA_TRIGGER_ADC_Done_AN15                  0x37
#    define DMA_TRIGGER_ADC_Done_AN16                  0x38
#    define DMA_TRIGGER_ADC_Done_AN17                  0x39
#    define DMA_TRIGGER_AD1FLTR1_Oversample_Filter_1   0x40
#    define DMA_TRIGGER_AD1FLTR2_Oversample_Filter_2   0x41
#    define DMA_TRIGGER_AD1FLTR3_Oversample_Filter_3   0x42
#    define DMA_TRIGGER_AD1FLTR4_Oversample_Filter_4   0x43
#    define DMA_TRIGGER_CLC1_Interrupt                 0x44
#    define DMA_TRIGGER_CLC2_Interrupt                 0x45
#    define DMA_TRIGGER_SPI1_Fault_Interrupt           0x46
#    define DMA_TRIGGER_SPI2_Fault_Interrupt           0x47
#    define DMA_TRIGGER_MSI_Slave_Initiated_Slave_IRQ  0x4A
#    define DMA_TRIGGER_MSI_Protocol_A                 0x4B
#    define DMA_TRIGGER_MSI_Protocol_B                 0x4C
#    define DMA_TRIGGER_MSI_Protocol_C                 0x4D
#    define DMA_TRIGGER_MSI_Protocol_D                 0x4E
#    define DMA_TRIGGER_MSI_Protocol_E                 0x4F
#    define DMA_TRIGGER_MSI_Protocol_F                 0x50
#    define DMA_TRIGGER_MSI_Protocol_G                 0x51
#    define DMA_TRIGGER_MSI_Protocol_H                 0x52
#    define DMA_TRIGGER_MSI_Master_Read_FIFO_Data      0x53
#    define DMA_TRIGGER_MSI_Master_Write_FIFO          0x54
#    define DMA_TRIGGER_MSI_Fault                      0x55
#    define DMA_TRIGGER_MSI_Master_Reset_IRQ           0x56
#    define DMA_TRIGGER_PWM_Event_D                    0x57
#    define DMA_TRIGGER_PWM_Event_E                    0x58
#    define DMA_TRIGGER_PWM_Event_F                    0x59
#    define DMA_TRIGGER_Slave_ICD_Breakpoint_Interrupt 0x5A
#    define DMA_TRIGGER_SCCP7_Interrupt                0x5C
#    define DMA_TRIGGER_SCCP8_Interrupt                0x5D
#    define DMA_TRIGGER_Slave_Clock_Fail_Interrupt     0x5E
#    define DMA_TRIGGER_ADC_FIFO_Ready_Interrupt       0x5F
#    define DMA_TRIGGER_CLC3_Positive_Edge_Interrupt   0x60
#    define DMA_TRIGGER_CLC4_Positive_Edge_Interrupt   0x61
#elif defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                         \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505S1)                    \
    || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206S1)                    \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)
#    define DMA_TRIGGER_INT0_External_Interrupt_0       0x00
#    define DMA_TRIGGER_SCCP1_IC_OC                     0x01
#    define DMA_TRIGGER_SPI1_Receiver                   0x02
#    define DMA_TRIGGER_SPI1_Transmitter                0x03
#    define DMA_TRIGGER_UART1_Receiver                  0x04
#    define DMA_TRIGGER_UART1_Transmitter               0x05
#    define DMA_TRIGGER_ECC_Single_Bit_Error            0x06
#    define DMA_TRIGGER_NVM_Write_Complete              0x07
#    define DMA_TRIGGER_INT1_External_Interrupt_1       0x08
#    define DMA_TRIGGER_SI2C1_I2C1_Slave_Event          0x09
#    define DMA_TRIGGER_MI2C1_I2C1_Master_Event         0x0A
#    define DMA_TRIGGER_INT2_External_Interrupt_2       0x0B
#    define DMA_TRIGGER_SCCP2_IC_OC                     0x0C
#    define DMA_TRIGGER_INT3_External_Interrupt_3       0x0D
#    define DMA_TRIGGER_SCCP3_IC_OC                     0x12
#    define DMA_TRIGGER_SCCP4_IC_OC                     0x15
#    define DMA_TRIGGER_PWM_Event_A                     0x19
#    define DMA_TRIGGER_PWM_Event_B                     0x1B
#    define DMA_TRIGGER_PWM_Generator_1                 0x1C
#    define DMA_TRIGGER_PWM_Generator_2                 0x1D
#    define DMA_TRIGGER_PWM_Generator_3                 0x1E
#    define DMA_TRIGGER_PWM_Generator_4                 0x1F
#    define DMA_TRIGGER_PWM_Generator_5                 0x20
#    define DMA_TRIGGER_PWM_Generator_6                 0x21
#    define DMA_TRIGGER_PWM_Generator_7                 0x22
#    define DMA_TRIGGER_PWM_Generator_8                 0x23
#    define DMA_TRIGGER_PWM_Event_C                     0x24
#    define DMA_TRIGGER_ADC1_Group_Convert_Done         0x27
#    define DMA_TRIGGER_ADC_Done_AN0                    0x28
#    define DMA_TRIGGER_ADC_Done_AN1                    0x29
#    define DMA_TRIGGER_ADC_Done_AN2                    0x2A
#    define DMA_TRIGGER_ADC_Done_AN3                    0x2B
#    define DMA_TRIGGER_ADC_Done_AN4                    0x2C
#    define DMA_TRIGGER_ADC_Done_AN5                    0x2D
#    define DMA_TRIGGER_ADC_Done_AN6                    0x2E
#    define DMA_TRIGGER_ADC_Done_AN7                    0x2F
#    define DMA_TRIGGER_ADC_Done_AN8                    0x30
#    define DMA_TRIGGER_ADC_Done_AN9                    0x31
#    define DMA_TRIGGER_ADC_Done_AN10                   0x32
#    define DMA_TRIGGER_ADC_Done_AN11                   0x33
#    define DMA_TRIGGER_ADC_Done_AN12                   0x34
#    define DMA_TRIGGER_ADC_Done_AN13                   0x35
#    define DMA_TRIGGER_ADC_Done_AN14                   0x36
#    define DMA_TRIGGER_ADC_Done_AN15                   0x37
#    define DMA_TRIGGER_ADC_Done_AN16                   0x38
#    define DMA_TRIGGER_ADC_Done_AN17                   0x39
#    define DMA_TRIGGER_ADC_Done_AN19                   0x3B
#    define DMA_TRIGGER_AD1FLTR1_Oversample_Filter_1    0x40
#    define DMA_TRIGGER_AD1FLTR2_Oversample_Filter_2    0x41
#    define DMA_TRIGGER_AD1FLTR3_Oversample_Filter_3    0x42
#    define DMA_TRIGGER_AD1FLTR4_Oversample_Filter_4    0x43
#    define DMA_TRIGGER_CLC1_Interrupt                  0x44
#    define DMA_TRIGGER_CLC2_Interrupt                  0x45
#    define DMA_TRIGGER_SPI1_Fault_Interrupt            0x46
#    define DMA_TRIGGER_MSI_Master_Initiated_Slave_IRQ  0x4A
#    define DMA_TRIGGER_MSI_Protocol_A                  0x4B
#    define DMA_TRIGGER_MSI_Protocol_B                  0x4C
#    define DMA_TRIGGER_MSI_Protocol_C                  0x4D
#    define DMA_TRIGGER_MSI_Protocol_D                  0x4E
#    define DMA_TRIGGER_MSI_Protocol_E                  0x4F
#    define DMA_TRIGGER_MSI_Protocol_F                  0x50
#    define DMA_TRIGGER_MSI_Protocol_G                  0x51
#    define DMA_TRIGGER_MSI_Protocol_H                  0x52
#    define DMA_TRIGGER_MSI_Slave_Read_FIFO_Data        0x53
#    define DMA_TRIGGER_MSI_Slave_Write_FIFO_Empty      0x54
#    define DMA_TRIGGER_MSI_FIFO_Fault                  0x55
#    define DMA_TRIGGER_MSI_Master_Reset_IRQ            0x56
#    define DMA_TRIGGER_PWM_Event_D                     0x57
#    define DMA_TRIGGER_PWM_Event_E                     0x58
#    define DMA_TRIGGER_PWM_Event_F                     0x59
#    define DMA_TRIGGER_Master_ICD_Breakpoint_Interrupt 0x5A
#    define DMA_TRIGGER_Master_Clock_Fail_Interrupt     0x5E
#    define DMA_TRIGGER_ADC_FIFO_Ready_Interrupt        0x5F
#    define DMA_TRIGGER_CLC3_Positive_Edge_Interrupt    0x60
#    define DMA_TRIGGER_CLC4_Positive_Edge_Interrupt    0x61
#endif

#ifdef __cplusplus
}
#endif

#endif  // DMA_DSPIC33C_H
