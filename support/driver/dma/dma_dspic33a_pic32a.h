/**
 * @file dma_dspic33a_pic32a.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2026
 *
 * @date August 30, 2026, 08:30 PM
 *
 * @brief DMA support driver for dsPIC33A and PIC32A
 *
 * Implementation based on Microchip documents DS70005539C, DS70005629C, DS70005591D and DS70005592A:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK128MC106-Family-Data-Sheet-DS70005539.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK256MPS306-Family-Data-Sheet-DS70005629.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/dsPIC33AK512MPS512-Family-Data-Sheet-DS70005591.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/DataSheets/PIC32AK1216GC41064-Family-Data-Sheet-DS70005592.pdf
 */

#ifndef DMA_DSPIC33A_PIC32A_H
#define DMA_DSPIC33A_PIC32A_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SIMULATOR
#    define _dma_space_ __attribute__((space(xmemory), aligned(4)))
#endif

#define DMA_ADDRMODE_NOCHANGE  0b00
#define DMA_ADDRMODE_INCREMENT 0b01
#define DMA_ADDRMODE_DECREMENT 0b10

#define DMA_MODE_ONESHOT            0b00
#define DMA_MODE_REPEATEDONESHOT    0b01
#define DMA_MODE_CONTINUOUS         0b10
#define DMA_MODE_REPEATEDCONTINUOUS 0b11

#define DMA_WORDSIZE_8  0b00
#define DMA_WORDSIZE_16 0b01
#define DMA_WORDSIZE_32 0b10

#define DMA_OPTION_RELOAD 0x1
#define DMA_OPTION_NULLW  0x2

#if defined(DEVICE_32AK1216GC41036) || defined(DEVICE_32AK1216GC41048) || defined(DEVICE_32AK1216GC41064) || defined(DEVICE_32AK3208GC41036)                   \
    || defined(DEVICE_32AK3208GC41048) || defined(DEVICE_32AK3208GC41064) || defined(DEVICE_32AK6416GC41036) || defined(DEVICE_32AK6416GC41048)                \
    || defined(DEVICE_32AK6416GC41064) || defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105)                            \
    || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102) || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) \
    || defined(DEVICE_33AK128MC102) || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)
#    define DMA_COUNT 6
#elif defined(DEVICE_33AK128MPS103) || defined(DEVICE_33AK128MPS105) || defined(DEVICE_33AK128MPS106) || defined(DEVICE_33AK128MPS303)                         \
    || defined(DEVICE_33AK128MPS305) || defined(DEVICE_33AK128MPS306) || defined(DEVICE_33AK256MC205) || defined(DEVICE_33AK256MC206)                          \
    || defined(DEVICE_33AK256MC208) || defined(DEVICE_33AK256MC210) || defined(DEVICE_33AK256MC505) || defined(DEVICE_33AK256MC506)                            \
    || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510) || defined(DEVICE_33AK256MPS103) || defined(DEVICE_33AK256MPS105)                          \
    || defined(DEVICE_33AK256MPS106) || defined(DEVICE_33AK256MPS205) || defined(DEVICE_33AK256MPS206) || defined(DEVICE_33AK256MPS208)                        \
    || defined(DEVICE_33AK256MPS210) || defined(DEVICE_33AK256MPS212) || defined(DEVICE_33AK256MPS303) || defined(DEVICE_33AK256MPS305)                        \
    || defined(DEVICE_33AK256MPS306) || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506) || defined(DEVICE_33AK256MPS508)                        \
    || defined(DEVICE_33AK256MPS510) || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC205) || defined(DEVICE_33AK512MC206)                          \
    || defined(DEVICE_33AK512MC208) || defined(DEVICE_33AK512MC210) || defined(DEVICE_33AK512MC505) || defined(DEVICE_33AK512MC506)                            \
    || defined(DEVICE_33AK512MC508) || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS205) || defined(DEVICE_33AK512MPS206)                          \
    || defined(DEVICE_33AK512MPS208) || defined(DEVICE_33AK512MPS210) || defined(DEVICE_33AK512MPS212) || defined(DEVICE_33AK512MPS505)                        \
    || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508) || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)
#    define DMA_COUNT 8
#else
#    define DMA_COUNT 0
#endif

#if defined(DEVICE_32AK1216GC41036) || defined(DEVICE_32AK1216GC41048) || defined(DEVICE_32AK1216GC41064) || defined(DEVICE_32AK3208GC41036)                   \
    || defined(DEVICE_32AK3208GC41048) || defined(DEVICE_32AK3208GC41064) || defined(DEVICE_32AK6416GC41036) || defined(DEVICE_32AK6416GC41048)                \
    || defined(DEVICE_32AK6416GC41064) || defined(DEVICE_33AK32MC102) || defined(DEVICE_33AK32MC103) || defined(DEVICE_33AK32MC105)                            \
    || defined(DEVICE_33AK32MC106) || defined(DEVICE_33AK64MC102) || defined(DEVICE_33AK64MC103) || defined(DEVICE_33AK64MC105) || defined(DEVICE_33AK64MC106) \
    || defined(DEVICE_33AK128MC102) || defined(DEVICE_33AK128MC103) || defined(DEVICE_33AK128MC105) || defined(DEVICE_33AK128MC106)

#    define DMA_TRIGGER_INT0             0x00
#    define DMA_TRIGGER_INT1             0x01
#    define DMA_TRIGGER_INT2             0x02
#    define DMA_TRIGGER_NVMWriteComplete 0x03
#    define DMA_TRIGGER_CRC              0x04
#    define DMA_TRIGGER_TMR1             0x05
#    define DMA_TRIGGER_SPI1RX           0x06
#    define DMA_TRIGGER_SPI1TX           0x07
#    define DMA_TRIGGER_SPI2RX           0x08
#    define DMA_TRIGGER_SPI2TX           0x09
#    define DMA_TRIGGER_SPI3RX           0x0A
#    define DMA_TRIGGER_SPI3TX           0x0B
#    define DMA_TRIGGER_UART1RX          0x0F
#    define DMA_TRIGGER_UART1TX          0x10
#    define DMA_TRIGGER_UART2RX          0x11
#    define DMA_TRIGGER_UART2TX          0x12
#    define DMA_TRIGGER_UART3RX          0x13
#    define DMA_TRIGGER_UART3TX          0x14
#    define DMA_TRIGGER_SCCP1            0x18
#    define DMA_TRIGGER_SCCP2            0x19
#    define DMA_TRIGGER_SCCP3            0x1A
#    define DMA_TRIGGER_SCCP4            0x1B
#    define DMA_TRIGGER_PWMEventA        0x21
#    define DMA_TRIGGER_PWMEventB        0x22
#    define DMA_TRIGGER_PWMGenerator1    0x23
#    define DMA_TRIGGER_PWMGenerator2    0x24
#    define DMA_TRIGGER_PWMGenerator3    0x25
#    define DMA_TRIGGER_PWMGenerator4    0x26
#    define DMA_TRIGGER_SENT1TXRX        0x28
#    define DMA_TRIGGER_SENT2TXRX        0x29
#    define DMA_TRIGGER_BiSS             0x2A
#    define DMA_TRIGGER_ADC1DoneCH0      0x2B
#    define DMA_TRIGGER_ADC1DoneCH1      0x2C
#    define DMA_TRIGGER_ADC1DoneCH2      0x2D
#    define DMA_TRIGGER_ADC1DoneCH3      0x2E
#    define DMA_TRIGGER_ADC1DoneCH4      0x2F
#    define DMA_TRIGGER_ADC1DoneCH5      0x30
#    define DMA_TRIGGER_ADC1DoneCH6      0x31
#    define DMA_TRIGGER_ADC1DoneCH7      0x32
#    define DMA_TRIGGER_ADC1DoneCH8      0x33
#    define DMA_TRIGGER_ADC1DoneCH9      0x34
#    define DMA_TRIGGER_ADC1DoneCH10     0x35
#    define DMA_TRIGGER_ADC1DoneCH11     0x36
#    define DMA_TRIGGER_ADC1DoneCH12     0x37
#    define DMA_TRIGGER_ADC1DoneCH13     0x38
#    define DMA_TRIGGER_ADC1DoneCH14     0x39
#    define DMA_TRIGGER_ADC1DoneCH15     0x3A
#    define DMA_TRIGGER_ADC1DoneCH16     0x3B
#    define DMA_TRIGGER_ADC1DoneCH17     0x3C
#    define DMA_TRIGGER_ADC1DoneCH18     0x3D
#    define DMA_TRIGGER_ADC1DoneCH19     0x3E
#    define DMA_TRIGGER_ADC2DoneCH0      0x40
#    define DMA_TRIGGER_ADC2DoneCH1      0x41
#    define DMA_TRIGGER_ADC2DoneCH2      0x42
#    define DMA_TRIGGER_ADC2DoneCH3      0x43
#    define DMA_TRIGGER_ADC2DoneCH4      0x44
#    define DMA_TRIGGER_ADC2DoneCH5      0x45
#    define DMA_TRIGGER_ADC2DoneCH6      0x46
#    define DMA_TRIGGER_ADC2DoneCH7      0x47
#    define DMA_TRIGGER_ADC2DoneCH8      0x48
#    define DMA_TRIGGER_ADC2DoneCH9      0x49
#    define DMA_TRIGGER_ADC2DoneCH10     0x4A
#    define DMA_TRIGGER_ADC2DoneCH11     0x4B
#    define DMA_TRIGGER_ADC2DoneCH12     0x4C
#    define DMA_TRIGGER_ADC2DoneCH13     0x4D
#    define DMA_TRIGGER_ADC2DoneCH14     0x4E
#    define DMA_TRIGGER_ADC2DoneCH15     0x4F
#    define DMA_TRIGGER_ADC2DoneCH16     0x50
#    define DMA_TRIGGER_ADC2DoneCH17     0x51
#    define DMA_TRIGGER_ADC2DoneCH18     0x52
#    define DMA_TRIGGER_ADC2DoneCH19     0x53
#    define DMA_TRIGGER_DMA0             0x5B
#    define DMA_TRIGGER_DMA1             0x5C
#    define DMA_TRIGGER_DMA2             0x5D
#    define DMA_TRIGGER_DMA3             0x5E
#    define DMA_TRIGGER_DMA4             0x5F
#    define DMA_TRIGGER_DMA5             0x60
#    define DMA_TRIGGER_I2C1             0x6B
#    define DMA_TRIGGER_I2C1Client       0x6C
#    define DMA_TRIGGER_I2C1Host         0x6D
#    define DMA_TRIGGER_I2C2             0x6E
#    define DMA_TRIGGER_I2C2Client       0x6F
#    define DMA_TRIGGER_I2C2Host         0x70

#elif defined(DEVICE_33AK128MPS103) || defined(DEVICE_33AK128MPS105) || defined(DEVICE_33AK128MPS106) || defined(DEVICE_33AK256MPS103)                         \
    || defined(DEVICE_33AK256MPS105) || defined(DEVICE_33AK256MPS106) || defined(DEVICE_33AK128MPS303) || defined(DEVICE_33AK128MPS305)                        \
    || defined(DEVICE_33AK128MPS306) || defined(DEVICE_33AK256MPS303) || defined(DEVICE_33AK256MPS305) || defined(DEVICE_33AK256MPS306)

#    define DMA_TRIGGER_INT0                     0x00
#    define DMA_TRIGGER_INT1                     0x01
#    define DMA_TRIGGER_INT2                     0x02
#    define DMA_TRIGGER_NVMWriteComplete         0x03
#    define DMA_TRIGGER_CRC                      0x04
#    define DMA_TRIGGER_TMR1                     0x05
#    define DMA_TRIGGER_SPI1RX                   0x06
#    define DMA_TRIGGER_SPI1TX                   0x07
#    define DMA_TRIGGER_SPI2RX                   0x08
#    define DMA_TRIGGER_SPI2TX                   0x09
#    define DMA_TRIGGER_SPI3RX                   0x0A
#    define DMA_TRIGGER_SPI3TX                   0x0B
#    define DMA_TRIGGER_TMR2                     0x0C
#    define DMA_TRIGGER_UART1RX                  0x0D
#    define DMA_TRIGGER_UART1TX                  0x0E
#    define DMA_TRIGGER_UART2RX                  0x0F
#    define DMA_TRIGGER_UART2TX                  0x10
#    define DMA_TRIGGER_UART3RX                  0x11
#    define DMA_TRIGGER_UART3TX                  0x12
#    define DMA_TRIGGER_UART4RX                  0x13
#    define DMA_TRIGGER_UART4TX                  0x14
#    define DMA_TRIGGER_TMR3                     0x15
#    define DMA_TRIGGER_SCCP1                    0x16
#    define DMA_TRIGGER_SCCP2                    0x17
#    define DMA_TRIGGER_SCCP3                    0x18
#    define DMA_TRIGGER_SCCP4                    0x19
#    define DMA_TRIGGER_MCCP5                    0x1A
#    define DMA_TRIGGER_SCCP1TriggerOutput       0x1B
#    define DMA_TRIGGER_SCCP2TriggerOutput       0x1C
#    define DMA_TRIGGER_SCCP3TriggerOutput       0x1D
#    define DMA_TRIGGER_SCCP4TriggerOutput       0x1E
#    define DMA_TRIGGER_MCCP5TriggerOutput       0x1F
#    define DMA_TRIGGER_PWMEventA                0x20
#    define DMA_TRIGGER_PWMEventB                0x21
#    define DMA_TRIGGER_PWMGenerator1            0x22
#    define DMA_TRIGGER_PWMGenerator2            0x23
#    define DMA_TRIGGER_PWMGenerator3            0x24
#    define DMA_TRIGGER_CAMTRNGInterrupt         0x25
#    define DMA_TRIGGER_PWMGenerator4            0x25
#    define DMA_TRIGGER_CAMPubKeyInterrupt       0x27
#    define DMA_TRIGGER_PTGInterrupt0            0x28
#    define DMA_TRIGGER_PTGInterrupt1            0x29
#    define DMA_TRIGGER_PTGInterrupt2            0x2A
#    define DMA_TRIGGER_PTGInterrupt3            0x2B
#    define DMA_TRIGGER_SENT1TXRX                0x2C
#    define DMA_TRIGGER_SENT2TXRX                0x2D
#    define DMA_TRIGGER_BiSS                     0x2E
#    define DMA_TRIGGER_ADC1DoneCH0              0x2F
#    define DMA_TRIGGER_ADC1DoneCH1              0x30
#    define DMA_TRIGGER_ADC1DoneCH2              0x31
#    define DMA_TRIGGER_ADC1DoneCH3              0x32
#    define DMA_TRIGGER_ADC1DoneCH4              0x33
#    define DMA_TRIGGER_ADC1DoneCH5              0x34
#    define DMA_TRIGGER_ADC1DoneCH6              0x35
#    define DMA_TRIGGER_ADC2DoneCH0              0x36
#    define DMA_TRIGGER_ADC2DoneCH1              0x37
#    define DMA_TRIGGER_ADC2DoneCH2              0x38
#    define DMA_TRIGGER_ADC2DoneCH3              0x39
#    define DMA_TRIGGER_ADC2DoneCH4              0x3A
#    define DMA_TRIGGER_ADC2DoneCH5              0x3B
#    define DMA_TRIGGER_ADC2DoneCH6              0x3C
#    define DMA_TRIGGER_ADC2DoneCH7              0x3D
#    define DMA_TRIGGER_ADC3DoneCH0              0x3E
#    define DMA_TRIGGER_ADC3DoneCH1              0x3F
#    define DMA_TRIGGER_ADC3DoneCH2              0x40
#    define DMA_TRIGGER_ADC3DoneCH3              0x41
#    define DMA_TRIGGER_ADC3DoneCH4              0x42
#    define DMA_TRIGGER_ADC3DoneCH5              0x43
#    define DMA_TRIGGER_ADC3DoneCH6              0x44
#    define DMA_TRIGGER_ADC3DoneCH7              0x45
#    define DMA_TRIGGER_ADC3DoneCH8              0x46
#    define DMA_TRIGGER_ADC3DoneCH9              0x47
#    define DMA_TRIGGER_ADC3DoneCH10             0x48
#    define DMA_TRIGGER_ADC3DoneCH11             0x49
#    define DMA_TRIGGER_CANFDRX                  0x4A
#    define DMA_TRIGGER_CANFDTX                  0x4B
#    define DMA_TRIGGER_CLC1RisingEdge           0x4C
#    define DMA_TRIGGER_CLC1FallingEdge          0x4D
#    define DMA_TRIGGER_CLC2RisingEdge           0x4E
#    define DMA_TRIGGER_CLC2FallingEdge          0x4F
#    define DMA_TRIGGER_CLC3RisingEdge           0x50
#    define DMA_TRIGGER_CLC3FallingEdge          0x51
#    define DMA_TRIGGER_CLC4RisingEdge           0x52
#    define DMA_TRIGGER_CLC4FallingEdge          0x53
#    define DMA_TRIGGER_I2C1                     0x54
#    define DMA_TRIGGER_I2C1Client               0x55
#    define DMA_TRIGGER_I2C1Host                 0x56
#    define DMA_TRIGGER_I2C2                     0x57
#    define DMA_TRIGGER_I2C2Client               0x58
#    define DMA_TRIGGER_I2C2Host                 0x59
#    define DMA_TRIGGER_DMA0                     0x5B
#    define DMA_TRIGGER_DMA1                     0x5C
#    define DMA_TRIGGER_DMA2                     0x5D
#    define DMA_TRIGGER_DMA3                     0x5E
#    define DMA_TRIGGER_DMA4                     0x5F
#    define DMA_TRIGGER_DMA5                     0x60
#    define DMA_TRIGGER_DMA6                     0x61
#    define DMA_TRIGGER_DMA7                     0x62
#    define DMA_TRIGGER_ITCTXA                   0x63
#    define DMA_TRIGGER_ITCTXB                   0x64
#    define DMA_TRIGGER_ITCTXC                   0x65
#    define DMA_TRIGGER_ITCList0                 0x66
#    define DMA_TRIGGER_ITCList1                 0x67
#    define DMA_TRIGGER_ITCList2                 0x68
#    define DMA_TRIGGER_ITCAllLists              0x69
#    define DMA_TRIGGER_ITCLoadSequence          0x6A
#    define DMA_TRIGGER_I3CHost                  0x6B
#    define DMA_TRIGGER_I3CClient                0x6C
#    define DMA_TRIGGER_I3CHostBurstRequestCH0   0x6D
#    define DMA_TRIGGER_I3CClientBurstRequestCH1 0x6E

#elif defined(DEVICE_33AK256MC205) || defined(DEVICE_33AK256MC206) || defined(DEVICE_33AK256MC208) || defined(DEVICE_33AK256MC210)                             \
    || defined(DEVICE_33AK256MPS205) || defined(DEVICE_33AK256MPS206) || defined(DEVICE_33AK256MPS208) || defined(DEVICE_33AK256MPS210)                        \
    || defined(DEVICE_33AK256MPS212) || defined(DEVICE_33AK512MC205) || defined(DEVICE_33AK512MC206) || defined(DEVICE_33AK512MC208)                           \
    || defined(DEVICE_33AK512MC210) || defined(DEVICE_33AK512MPS205) || defined(DEVICE_33AK512MPS206) || defined(DEVICE_33AK512MPS208)                         \
    || defined(DEVICE_33AK512MPS210) || defined(DEVICE_33AK512MPS212) || defined(DEVICE_33AK256MC505) || defined(DEVICE_33AK256MC506)                          \
    || defined(DEVICE_33AK256MC508) || defined(DEVICE_33AK256MC510) || defined(DEVICE_33AK256MPS505) || defined(DEVICE_33AK256MPS506)                          \
    || defined(DEVICE_33AK256MPS508) || defined(DEVICE_33AK256MPS510) || defined(DEVICE_33AK256MPS512) || defined(DEVICE_33AK512MC505)                         \
    || defined(DEVICE_33AK512MC506) || defined(DEVICE_33AK512MC508) || defined(DEVICE_33AK512MC510) || defined(DEVICE_33AK512MPS505)                           \
    || defined(DEVICE_33AK512MPS506) || defined(DEVICE_33AK512MPS508) || defined(DEVICE_33AK512MPS510) || defined(DEVICE_33AK512MPS512)

#    define DMA_TRIGGER_INT0             0x00
#    define DMA_TRIGGER_INT1             0x01
#    define DMA_TRIGGER_INT2             0x02
#    define DMA_TRIGGER_NVMWriteComplete 0x03
#    define DMA_TRIGGER_CRC              0x04
#    define DMA_TRIGGER_TMR1             0x05
#    define DMA_TRIGGER_SPI1RX           0x06
#    define DMA_TRIGGER_SPI1TX           0x07
#    define DMA_TRIGGER_SPI2RX           0x08
#    define DMA_TRIGGER_SPI2TX           0x09
#    define DMA_TRIGGER_SPI3RX           0x0A
#    define DMA_TRIGGER_SPI3TX           0x0B
#    define DMA_TRIGGER_SPI4RX           0x0C
#    define DMA_TRIGGER_SPI4TX           0x0D
#    define DMA_TRIGGER_TMR2             0x0E
#    define DMA_TRIGGER_UART1RX          0x0F
#    define DMA_TRIGGER_UART1TX          0x10
#    define DMA_TRIGGER_UART2RX          0x11
#    define DMA_TRIGGER_UART2TX          0x12
#    define DMA_TRIGGER_UART3RX          0x13
#    define DMA_TRIGGER_UART3TX          0x14
#    define DMA_TRIGGER_TMR3             0x17
#    define DMA_TRIGGER_SCCP1            0x18
#    define DMA_TRIGGER_SCCP2            0x19
#    define DMA_TRIGGER_SCCP3            0x1A
#    define DMA_TRIGGER_SCCP4            0x1B
#    define DMA_TRIGGER_SCCP5            0x1C
#    define DMA_TRIGGER_SCCP6            0x1D
#    define DMA_TRIGGER_SCCP7            0x1E
#    define DMA_TRIGGER_SCCP8            0x1F
#    define DMA_TRIGGER_MCCP9            0x20
#    define DMA_TRIGGER_PWMEventA        0x21
#    define DMA_TRIGGER_PWMEventB        0x22
#    define DMA_TRIGGER_PWMGenerator1    0x23
#    define DMA_TRIGGER_PWMGenerator2    0x24
#    define DMA_TRIGGER_PWMGenerator3    0x25
#    define DMA_TRIGGER_PWMGenerator4    0x26
#    define DMA_TRIGGER_PWMGenerator5    0x27
#    define DMA_TRIGGER_PWMGenerator6    0x28
#    define DMA_TRIGGER_PWMGenerator7    0x29
#    define DMA_TRIGGER_PWMGenerator8    0x2A
#    define DMA_TRIGGER_SENT1TXRX        0x2C
#    define DMA_TRIGGER_SENT2TXRX        0x2D
#    define DMA_TRIGGER_BiSS             0x2E
#    define DMA_TRIGGER_ADC1DoneCH0      0x2F
#    define DMA_TRIGGER_ADC1DoneCH1      0x30
#    define DMA_TRIGGER_ADC1DoneCH2      0x31
#    define DMA_TRIGGER_ADC1DoneCH3      0x32
#    define DMA_TRIGGER_ADC1DoneCH4      0x33
#    define DMA_TRIGGER_ADC1DoneCH5      0x34
#    define DMA_TRIGGER_ADC2DoneCH0      0x35
#    define DMA_TRIGGER_ADC2DoneCH1      0x36
#    define DMA_TRIGGER_ADC2DoneCH2      0x37
#    define DMA_TRIGGER_ADC2DoneCH3      0x38
#    define DMA_TRIGGER_ADC2DoneCH4      0x39
#    define DMA_TRIGGER_ADC2DoneCH5      0x3A
#    define DMA_TRIGGER_ADC3DoneCH0      0x3B
#    define DMA_TRIGGER_ADC3DoneCH1      0x3C
#    define DMA_TRIGGER_ADC3DoneCH2      0x3D
#    define DMA_TRIGGER_ADC3DoneCH3      0x3E
#    define DMA_TRIGGER_ADC3DoneCH4      0x3F
#    define DMA_TRIGGER_ADC3DoneCH5      0x40
#    define DMA_TRIGGER_ADC4DoneCH0      0x41
#    define DMA_TRIGGER_ADC4DoneCH1      0x42
#    define DMA_TRIGGER_ADC4DoneCH2      0x43
#    define DMA_TRIGGER_ADC4DoneCH3      0x44
#    define DMA_TRIGGER_ADC4DoneCH4      0x45
#    define DMA_TRIGGER_ADC4DoneCH5      0x46
#    define DMA_TRIGGER_ADC4DoneCH6      0x47
#    define DMA_TRIGGER_ADC5DoneCH0      0x48
#    define DMA_TRIGGER_ADC5DoneCH1      0x49
#    define DMA_TRIGGER_ADC5DoneCH2      0x4A
#    define DMA_TRIGGER_ADC5DoneCH3      0x4B
#    define DMA_TRIGGER_ADC5DoneCH4      0x4C
#    define DMA_TRIGGER_ADC5DoneCH5      0x4D
#    define DMA_TRIGGER_ADC5DoneCH6      0x4E
#    define DMA_TRIGGER_I2C1             0x4F
#    define DMA_TRIGGER_I2C1Client       0x50
#    define DMA_TRIGGER_I2C1Host         0x51
#    define DMA_TRIGGER_I2C2             0x52
#    define DMA_TRIGGER_I2C2Client       0x53
#    define DMA_TRIGGER_I2C2Host         0x54
#    define DMA_TRIGGER_I2C3             0x55
#    define DMA_TRIGGER_I2C3Client       0x56
#    define DMA_TRIGGER_I2C3Host         0x57
#    define DMA_TRIGGER_TouchController1 0x58
#    define DMA_TRIGGER_DMA0             0x59
#    define DMA_TRIGGER_DMA1             0x5A
#    define DMA_TRIGGER_DMA2             0x5B
#    define DMA_TRIGGER_DMA3             0x5C
#    define DMA_TRIGGER_APWMGenerator1   0x63
#    define DMA_TRIGGER_APWMGenerator2   0x64
#    define DMA_TRIGGER_APWMGenerator3   0x65
#    define DMA_TRIGGER_APWMGenerator4   0x66
#    define DMA_TRIGGER_ITCList0         0x6A
#    define DMA_TRIGGER_ITCList1         0x6B
#    define DMA_TRIGGER_ITCList2         0x6C
#    define DMA_TRIGGER_ITCAllLists      0x6D
#    define DMA_TRIGGER_ITCLoadSequence  0x6E
#endif

#ifdef __cplusplus
}
#endif

#endif  // DMA_DSPIC33A_PIC32A_H
