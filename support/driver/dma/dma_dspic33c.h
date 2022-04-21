/**
 * @file dma_dspic33c.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021
 *
 * @date September 11, 2021, 03:50 PM
 *
 * @brief DMA support driver for PIC24 and dsPIC33C
 */

#ifndef DMA_DSPIC33C_H
#define DMA_DSPIC33C_H

#ifndef SIMULATOR
#    define _dma_space_ __attribute__((space(xmemory), aligned(2)))
#endif

#if defined(DEVICE_33CH64MP202S1) || defined(DEVICE_33CH64MP203S1) || defined(DEVICE_33CH64MP205S1) || defined(DEVICE_33CH64MP206S1)                           \
    || defined(DEVICE_33CH64MP208S1) || defined(DEVICE_33CH64MP502S1) || defined(DEVICE_33CH64MP503S1) || defined(DEVICE_33CH64MP505S1)                        \
    || defined(DEVICE_33CH64MP506S1) || defined(DEVICE_33CH64MP508S1) || defined(DEVICE_33CH128MP202S1) || defined(DEVICE_33CH128MP203S1)                      \
    || defined(DEVICE_33CH128MP205S1) || defined(DEVICE_33CH128MP206S1) || defined(DEVICE_33CH128MP208S1) || defined(DEVICE_33CH128MP502S1)                    \
    || defined(DEVICE_33CH128MP503S1) || defined(DEVICE_33CH128MP505S1) || defined(DEVICE_33CH128MP506S1) || defined(DEVICE_33CH128MP508S1)                    \
    || defined(DEVICE_33CH256MP205S1) || defined(DEVICE_33CH256MP206S1) || defined(DEVICE_33CH256MP208S1) || defined(DEVICE_33CH256MP505S1)                    \
    || defined(DEVICE_33CH256MP506S1) || defined(DEVICE_33CH256MP508S1) || defined(DEVICE_33CH512MP205S1) || defined(DEVICE_33CH512MP206S1)                    \
    || defined(DEVICE_33CH512MP208S1) || defined(DEVICE_33CH512MP505S1) || defined(DEVICE_33CH512MP506S1) || defined(DEVICE_33CH512MP508S1)
#    define DMA_COUNT 2
#elif defined(DEVICE_33CK32MC102) || defined(DEVICE_33CK32MC103) || defined(DEVICE_33CK32MC105) || defined(DEVICE_33CK32MP102) || defined(DEVICE_33CK32MP103)  \
    || defined(DEVICE_33CK32MP105) || defined(DEVICE_33CK32MP202) || defined(DEVICE_33CK32MP203) || defined(DEVICE_33CK32MP205) || defined(DEVICE_33CK32MP206) \
    || defined(DEVICE_33CK32MP502) || defined(DEVICE_33CK32MP503) || defined(DEVICE_33CK32MP505) || defined(DEVICE_33CK32MP506) || defined(DEVICE_33CK64MC102) \
    || defined(DEVICE_33CK64MC103) || defined(DEVICE_33CK64MC105) || defined(DEVICE_33CK64MP102) || defined(DEVICE_33CK64MP103) || defined(DEVICE_33CK64MP105) \
    || defined(DEVICE_33CK64MP202) || defined(DEVICE_33CK64MP203) || defined(DEVICE_33CK64MP205) || defined(DEVICE_33CK64MP206) || defined(DEVICE_33CK64MP208) \
    || defined(DEVICE_33CK64MP502) || defined(DEVICE_33CK64MP503) || defined(DEVICE_33CK64MP505) || defined(DEVICE_33CK64MP506) || defined(DEVICE_33CK64MP508) \
    || defined(DEVICE_33CK128MP202) || defined(DEVICE_33CK128MP203) || defined(DEVICE_33CK128MP205) || defined(DEVICE_33CK128MP206)                            \
    || defined(DEVICE_33CK128MP208) || defined(DEVICE_33CK128MP502) || defined(DEVICE_33CK128MP503) || defined(DEVICE_33CK128MP505)                            \
    || defined(DEVICE_33CK128MP506) || defined(DEVICE_33CK128MP508) || defined(DEVICE_33CK256MP202) || defined(DEVICE_33CK256MP203)                            \
    || defined(DEVICE_33CK256MP205) || defined(DEVICE_33CK256MP206) || defined(DEVICE_33CK256MP208) || defined(DEVICE_33CK256MP502)                            \
    || defined(DEVICE_33CK256MP503) || defined(DEVICE_33CK256MP505) || defined(DEVICE_33CK256MP506) || defined(DEVICE_33CK256MP508)
#    define DMA_COUNT 4
#elif defined(DEVICE_33CH64MP202) || defined(DEVICE_33CH64MP203) || defined(DEVICE_33CH64MP205) || defined(DEVICE_33CH64MP206) || defined(DEVICE_33CH64MP208)  \
    || defined(DEVICE_33CH64MP502) || defined(DEVICE_33CH64MP503) || defined(DEVICE_33CH64MP505) || defined(DEVICE_33CH64MP506) || defined(DEVICE_33CH64MP508) \
    || defined(DEVICE_33CH128MP202) || defined(DEVICE_33CH128MP203) || defined(DEVICE_33CH128MP205) || defined(DEVICE_33CH128MP206)                            \
    || defined(DEVICE_33CH128MP208) || defined(DEVICE_33CH128MP502) || defined(DEVICE_33CH128MP503) || defined(DEVICE_33CH128MP505)                            \
    || defined(DEVICE_33CH128MP506) || defined(DEVICE_33CH128MP508) || defined(DEVICE_33CH256MP205) || defined(DEVICE_33CH256MP206)                            \
    || defined(DEVICE_33CH256MP208) || defined(DEVICE_33CH256MP505) || defined(DEVICE_33CH256MP506) || defined(DEVICE_33CH256MP508)                            \
    || defined(DEVICE_33CH512MP205) || defined(DEVICE_33CH512MP206) || defined(DEVICE_33CH512MP208) || defined(DEVICE_33CH512MP505)                            \
    || defined(DEVICE_33CH512MP506) || defined(DEVICE_33CH512MP508)
#    define DMA_COUNT 6
#elif defined(DEVICE_33CK256MP305) || defined(DEVICE_33CK256MP306) || defined(DEVICE_33CK256MP308) || defined(DEVICE_33CK256MP605)                             \
    || defined(DEVICE_33CK256MP606) || defined(DEVICE_33CK256MP608) || defined(DEVICE_33CK512MP305) || defined(DEVICE_33CK512MP306)                            \
    || defined(DEVICE_33CK512MP308) || defined(DEVICE_33CK512MP605) || defined(DEVICE_33CK512MP606) || defined(DEVICE_33CK512MP608)
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

#endif  // DMA_DSPIC33C_H
