# PIC32AK support

The PIC32AK is very similar to the [dsPIC33AK](../dspic33ak/README.md) family but with XC32 compiler.

## 📌 Key features

| Feature        | PIC32AK      |
| -------------- | ------------ |
| Core           | 32-bits      |
| Performance    | 200 DMIPS    |
| Program memory | 43-190 KB    |
| Data memory    | 8-16 KB      |
| Pin count      | 36-64        |

## 🧩 Peripheral overview

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|AKxxGC          |        0|        1|        0|        0|        2|        3|        0|        2|        4|         1|         0|         4|         0|

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

9 devices on May 2025.

## 📚 Subfamily breakdown

### AKxxGC subfamily

Base device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32AK3208GC41036](http://microchip.com/wwwproducts/en/PIC32AK3208GC41036) |  43 kb|   8 kb| 36|
|[PIC32AK6416GC41036](http://microchip.com/wwwproducts/en/PIC32AK6416GC41036) |  92 kb|  16 kb| 36|
|[PIC32AK1216GC41036](http://microchip.com/wwwproducts/en/PIC32AK1216GC41036) | 190 kb|  16 kb| 36|
|[PIC32AK3208GC41048](http://microchip.com/wwwproducts/en/PIC32AK3208GC41048) |  43 kb|   8 kb| 48|
|[PIC32AK6416GC41048](http://microchip.com/wwwproducts/en/PIC32AK6416GC41048) |  92 kb|  16 kb| 48|
|[PIC32AK1216GC41048](http://microchip.com/wwwproducts/en/PIC32AK1216GC41048) | 190 kb|  16 kb| 48|
|[PIC32AK3208GC41064](http://microchip.com/wwwproducts/en/PIC32AK3208GC41064) |  43 kb|   8 kb| 64|
|[PIC32AK6416GC41064](http://microchip.com/wwwproducts/en/PIC32AK6416GC41064) |  92 kb|  16 kb| 64|
|[PIC32AK1216GC41064](http://microchip.com/wwwproducts/en/PIC32AK1216GC41064) | 190 kb|  16 kb| 64|
