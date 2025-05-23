# dsPIC33AK support

The dsPIC33AK series from Microchip Technology represents a significant advancement in Digital Signal Controllers (DSCs), combining high-performance processing with robust peripheral integration.

## 📌 Key features

| Feature        | dsPIC33AK    |
| -------------- | ------------ |
| Core           | 32-bits      |
| Performance    | 200 DMIPS    |
| Program memory | 43-780 KB    |
| Data memory    | 8-33 KB      |
| Pin count      | 28–100       |

## 🧩 Peripheral overview

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|MC1XX           |        0|        1|        0|        0|        2|        3|        0|        2|        4|         1|         0|         4|         0|
|MC2XX           |        0|        3|        0|        0|        3|        4|        0|        2|        9|         4|         0|         9|         0|
|MC5XX           |        0|        3|        0|        0|        3|        4|     2 Fd|        2|        9|         4|         0|         9|         0|
|MPS2XX          |        0|        3|        0|        0|        3|        4|        0|        2|        9|         4|         0|         9|         0|
|MPS5XX          |        0|        3|        0|        0|        3|        4|     2 Fd|        2|        9|         4|         0|         9|         0|

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
|[dsPIC33AK32MC102](http://microchip.com/wwwproducts/en/dsPIC33AK32MC102)   |  43 kb|   8 kb| 28|
|[dsPIC33AK64MC102](http://microchip.com/wwwproducts/en/dsPIC33AK64MC102)   |  92 kb|  16 kb| 28|
|[dsPIC33AK128MC102](http://microchip.com/wwwproducts/en/dsPIC33AK128MC102) | 190 kb|  16 kb| 28|
|[dsPIC33AK32MC103](http://microchip.com/wwwproducts/en/dsPIC33AK32MC103)   |  43 kb|   8 kb| 36|
|[dsPIC33AK64MC103](http://microchip.com/wwwproducts/en/dsPIC33AK64MC103)   |  92 kb|  16 kb| 36|
|[dsPIC33AK128MC103](http://microchip.com/wwwproducts/en/dsPIC33AK128MC103) | 190 kb|  16 kb| 36|
|[dsPIC33AK32MC105](http://microchip.com/wwwproducts/en/dsPIC33AK32MC105)   |  43 kb|   8 kb| 48|
|[dsPIC33AK64MC105](http://microchip.com/wwwproducts/en/dsPIC33AK64MC105)   |  92 kb|  16 kb| 48|
|[dsPIC33AK128MC105](http://microchip.com/wwwproducts/en/dsPIC33AK128MC105) | 190 kb|  16 kb| 48|
|[dsPIC33AK32MC106](http://microchip.com/wwwproducts/en/dsPIC33AK32MC106)   |  43 kb|   8 kb| 64|
|[dsPIC33AK64MC106](http://microchip.com/wwwproducts/en/dsPIC33AK64MC106)   |  92 kb|  16 kb| 64|
|[dsPIC33AK128MC106](http://microchip.com/wwwproducts/en/dsPIC33AK128MC106) | 190 kb|  16 kb| 64|

### MC2XX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*dsPIC33AK256MC205](http://microchip.com/wwwproducts/en/dsPIC33AK256MC205)| 387 kb|  33 kb| 48|
|[*dsPIC33AK512MC205](http://microchip.com/wwwproducts/en/dsPIC33AK512MC205)| 780 kb|  33 kb| 48|
|[*dsPIC33AK256MC206](http://microchip.com/wwwproducts/en/dsPIC33AK256MC206)| 387 kb|  33 kb| 64|
|[*dsPIC33AK512MC206](http://microchip.com/wwwproducts/en/dsPIC33AK512MC206)| 780 kb|  33 kb| 64|
|[*dsPIC33AK256MC208](http://microchip.com/wwwproducts/en/dsPIC33AK256MC208)| 387 kb|  33 kb| 80|
|[*dsPIC33AK512MC208](http://microchip.com/wwwproducts/en/dsPIC33AK512MC208)| 780 kb|  33 kb| 80|
|[*dsPIC33AK256MC210](http://microchip.com/wwwproducts/en/dsPIC33AK256MC210)| 387 kb|  33 kb|100|
|[*dsPIC33AK512MC210](http://microchip.com/wwwproducts/en/dsPIC33AK512MC210)| 780 kb|  33 kb|100|

### MC5XX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*dsPIC33AK256MC505](http://microchip.com/wwwproducts/en/dsPIC33AK256MC505)| 387 kb|  33 kb| 48|
|[*dsPIC33AK512MC505](http://microchip.com/wwwproducts/en/dsPIC33AK512MC505)| 780 kb|  33 kb| 48|
|[*dsPIC33AK256MC506](http://microchip.com/wwwproducts/en/dsPIC33AK256MC506)| 387 kb|  33 kb| 64|
|[*dsPIC33AK512MC506](http://microchip.com/wwwproducts/en/dsPIC33AK512MC506)| 780 kb|  33 kb| 64|
|[*dsPIC33AK256MC508](http://microchip.com/wwwproducts/en/dsPIC33AK256MC508)| 387 kb|  33 kb| 80|
|[*dsPIC33AK512MC508](http://microchip.com/wwwproducts/en/dsPIC33AK512MC508)| 780 kb|  33 kb| 80|
|[*dsPIC33AK256MC510](http://microchip.com/wwwproducts/en/dsPIC33AK256MC510)| 387 kb|  33 kb|100|
|[*dsPIC33AK512MC510](http://microchip.com/wwwproducts/en/dsPIC33AK512MC510)| 780 kb|  33 kb|100|

### MPS2XX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*dsPIC33AK256MPS205](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS205)| 387 kb|  33 kb| 48|
|[*dsPIC33AK512MPS205](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS205)| 780 kb|  33 kb| 48|
|[*dsPIC33AK256MPS206](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS206)| 387 kb|  33 kb| 64|
|[*dsPIC33AK512MPS206](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS206)| 780 kb|  33 kb| 64|
|[*dsPIC33AK256MPS208](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS208)| 387 kb|  33 kb| 80|
|[*dsPIC33AK512MPS208](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS208)| 780 kb|  33 kb| 80|
|[*dsPIC33AK256MPS210](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS210)| 387 kb|  33 kb|100|
|[*dsPIC33AK512MPS210](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS210)| 780 kb|  33 kb|100|
|[*dsPIC33AK256MPS212](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS212)| 387 kb|  33 kb|128|
|[*dsPIC33AK512MPS212](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS212)| 780 kb|  33 kb|128|

### MP5SXX subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*dsPIC33AK256MPS505](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS505)| 387 kb|  33 kb| 48|
|[*dsPIC33AK512MPS505](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS505)| 780 kb|  33 kb| 48|
|[*dsPIC33AK256MPS506](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS506)| 387 kb|  33 kb| 64|
|[*dsPIC33AK512MPS506](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS506)| 780 kb|  33 kb| 64|
|[*dsPIC33AK256MPS508](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS508)| 387 kb|  33 kb| 80|
|[*dsPIC33AK512MPS508](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS508)| 780 kb|  33 kb| 80|
|[*dsPIC33AK256MPS510](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS510)| 387 kb|  33 kb|100|
|[*dsPIC33AK512MPS510](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS510)| 780 kb|  33 kb|100|
|[*dsPIC33AK256MPS512](http://microchip.com/wwwproducts/en/dsPIC33AK256MPS512)| 387 kb|  33 kb|128|
|[*dsPIC33AK512MPS512](http://microchip.com/wwwproducts/en/dsPIC33AK512MPS512)| 780 kb|  33 kb|128|

## Comparison with dsPIC33CK Family

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
