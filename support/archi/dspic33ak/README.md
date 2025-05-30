# dsPIC33AK support

The dsPIC33AK series from Microchip Technology represents a significant advancement in Digital Signal Controllers (DSCs), combining high-performance processing with robust peripheral integration.

## 📌 Key features

| Feature        | dsPIC33AK    |
| -------------- | ------------ |
| Core           | 32-bits      |
| Performance    | 200 DMIPS    |
| Program memory | 32-512 KB    |
| Data memory    | 8-64 KB      |
| Pin count      | 28-100       |

## 🧩 Peripheral overview

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|MC1XX           |        3|        1|        0|        0|        2|        3|        0|        2|        4|         1|         0|         0|         4|
|MC2XX           |        3|        3|        0|        0|        3|        4|        0|        2|       10|         4|         0|         1|         8|
|MC5XX           |        3|        3|        0|        0|        3|        4|     2 Fd|        2|       10|         4|         0|         1|         8|
|MPS2XX          |        3|        3|        0|        0|        3|        4|        0|        2|       10|         4|         0|         1|         8|
|MPS5XX          |        3|        3|        0|        0|        3|        4|     2 Fd|        2|       10|         4|         0|         1|         8|

[1]: ../../driver/uart/README.md
[2]: ../../driver/timer/README.md
[3]: ../../driver/oc/README.md
[4]: ../../driver/ic/README.md
[5]: ../../driver/i2c/README.md
[6]: ../../driver/spi/README.md
[7]: ../../driver/can/README.md
[8]: ../../driver/sent/README.md
[9]: ../../driver/clc/README.md
[10]: ../../driver/qei/README.md
[11]: ../../driver/pwm/README.md
[12]: ../../driver/mccp/README.md

## Devices list

### 📦 Device Families Overview

48 devices on May 2025.

## 📚 Subfamily breakdown

### MC10X subfamily

Base device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33AK32MC102](http://microchip.com/dsPIC33AK32MC102)   |  32 kb|   8 kb| 28|
|[dsPIC33AK64MC102](http://microchip.com/dsPIC33AK64MC102)   |  64 kb|  16 kb| 28|
|[dsPIC33AK128MC102](http://microchip.com/dsPIC33AK128MC102) | 128 kb|  16 kb| 28|
|[dsPIC33AK32MC103](http://microchip.com/dsPIC33AK32MC103)   |  32 kb|   8 kb| 36|
|[dsPIC33AK64MC103](http://microchip.com/dsPIC33AK64MC103)   |  64 kb|  16 kb| 36|
|[dsPIC33AK128MC103](http://microchip.com/dsPIC33AK128MC103) | 128 kb|  16 kb| 36|
|[dsPIC33AK32MC105](http://microchip.com/dsPIC33AK32MC105)   |  32 kb|   8 kb| 48|
|[dsPIC33AK64MC105](http://microchip.com/dsPIC33AK64MC105)   |  64 kb|  16 kb| 48|
|[dsPIC33AK128MC105](http://microchip.com/dsPIC33AK128MC105) | 128 kb|  16 kb| 48|
|[dsPIC33AK32MC106](http://microchip.com/dsPIC33AK32MC106)   |  32 kb|   8 kb| 64|
|[dsPIC33AK64MC106](http://microchip.com/dsPIC33AK64MC106)   |  64 kb|  16 kb| 64|
|[dsPIC33AK128MC106](http://microchip.com/dsPIC33AK128MC106) | 128 kb|  16 kb| 64|

### MC10X subfamily

MP20X with more peripherals and memory :
- 

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33AK256MC205](http://microchip.com/dsPIC33AK256MC205)| 256 kb|  64 kb| 48|
|[dsPIC33AK512MC205](http://microchip.com/dsPIC33AK512MC205)| 512 kb|  64 kb| 48|
|[dsPIC33AK256MC206](http://microchip.com/dsPIC33AK256MC206)| 256 kb|  64 kb| 64|
|[dsPIC33AK512MC206](http://microchip.com/dsPIC33AK512MC206)| 512 kb|  64 kb| 64|
|[dsPIC33AK256MC208](http://microchip.com/dsPIC33AK256MC208)| 256 kb|  64 kb| 80|
|[dsPIC33AK512MC208](http://microchip.com/dsPIC33AK512MC208)| 512 kb|  64 kb| 80|
|[dsPIC33AK256MC210](http://microchip.com/dsPIC33AK256MC210)| 256 kb|  64 kb|100|
|[dsPIC33AK512MC210](http://microchip.com/dsPIC33AK512MC210)| 512 kb|  64 kb|100|

### MC5XX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33AK256MC505](http://microchip.com/dsPIC33AK256MC505)| 256 kb|  64 kb| 48|
|[dsPIC33AK512MC505](http://microchip.com/dsPIC33AK512MC505)| 512 kb|  64 kb| 48|
|[dsPIC33AK256MC506](http://microchip.com/dsPIC33AK256MC506)| 256 kb|  64 kb| 64|
|[dsPIC33AK512MC506](http://microchip.com/dsPIC33AK512MC506)| 512 kb|  64 kb| 64|
|[dsPIC33AK256MC508](http://microchip.com/dsPIC33AK256MC508)| 256 kb|  64 kb| 80|
|[dsPIC33AK512MC508](http://microchip.com/dsPIC33AK512MC508)| 512 kb|  64 kb| 80|
|[dsPIC33AK256MC510](http://microchip.com/dsPIC33AK256MC510)| 256 kb|  64 kb|100|
|[dsPIC33AK512MC510](http://microchip.com/dsPIC33AK512MC510)| 512 kb|  64 kb|100|

### MPS2XX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33AK256MPS205](http://microchip.com/dsPIC33AK256MPS205)| 256 kb|  64 kb| 48|
|[dsPIC33AK512MPS205](http://microchip.com/dsPIC33AK512MPS205)| 512 kb|  64 kb| 48|
|[dsPIC33AK256MPS206](http://microchip.com/dsPIC33AK256MPS206)| 256 kb|  64 kb| 64|
|[dsPIC33AK512MPS206](http://microchip.com/dsPIC33AK512MPS206)| 512 kb|  64 kb| 64|
|[dsPIC33AK256MPS208](http://microchip.com/dsPIC33AK256MPS208)| 256 kb|  64 kb| 80|
|[dsPIC33AK512MPS208](http://microchip.com/dsPIC33AK512MPS208)| 512 kb|  64 kb| 80|
|[dsPIC33AK256MPS210](http://microchip.com/dsPIC33AK256MPS210)| 256 kb|  64 kb|100|
|[dsPIC33AK512MPS210](http://microchip.com/dsPIC33AK512MPS210)| 512 kb|  64 kb|100|
|[dsPIC33AK256MPS212](http://microchip.com/dsPIC33AK256MPS212)| 256 kb|  64 kb|128|
|[dsPIC33AK512MPS212](http://microchip.com/dsPIC33AK512MPS212)| 512 kb|  64 kb|128|

### MP5SXX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33AK256MPS505](http://microchip.com/dsPIC33AK256MPS505)| 256 kb|  64 kb| 48|
|[dsPIC33AK512MPS505](http://microchip.com/dsPIC33AK512MPS505)| 512 kb|  64 kb| 48|
|[dsPIC33AK256MPS506](http://microchip.com/dsPIC33AK256MPS506)| 256 kb|  64 kb| 64|
|[dsPIC33AK512MPS506](http://microchip.com/dsPIC33AK512MPS506)| 512 kb|  64 kb| 64|
|[dsPIC33AK256MPS508](http://microchip.com/dsPIC33AK256MPS508)| 256 kb|  64 kb| 80|
|[dsPIC33AK512MPS508](http://microchip.com/dsPIC33AK512MPS508)| 512 kb|  64 kb| 80|
|[dsPIC33AK256MPS510](http://microchip.com/dsPIC33AK256MPS510)| 256 kb|  64 kb|100|
|[dsPIC33AK512MPS510](http://microchip.com/dsPIC33AK512MPS510)| 512 kb|  64 kb|100|
|[dsPIC33AK256MPS512](http://microchip.com/dsPIC33AK256MPS512)| 256 kb|  64 kb|128|
|[dsPIC33AK512MPS512](http://microchip.com/dsPIC33AK512MPS512)| 512 kb|  64 kb|128|

## Comparison with dsPIC33CK/CH Family

| Feature                     | dsPIC33CK   | dsPIC33AK   |
| --------------------------- | ----------- | ----------- |
| Core speed                  | 100 MHz     | 200 MHz     |
| Pipeline stages             | 1-stage     | 5-stage     |
| Working registers           | 16 x 16-bit | 16 x 32-bit |
| Accumulators                | 2 x 40-bit  | 2 x 72-bit  |
| Alternate register contexts | 4           | 7           |
| FPU                         | None        | Yes         |

### sysclock

TODO

### ADC

TODO
