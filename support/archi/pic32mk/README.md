# PIC32MK support

PIC32MK family is a high-performance [32 bits](../pic32/README.md) range with FPU. All version include at least 1 USB communication module (2 modules in 100 pins package)

This family is splitted into four subfamilies :

* GPD : Global Purpose
* GPE : GPD with 4 CAN devices
* MCF : GPD with 4 CAN devices and Motor Control special features (QEI and enhanced PWM)
* MCM : GPD with 1 CAN Fd device and Motor Control special features (QEI and enhanced PWM)

## Main features

|Feature|GPD - GPE - MCF - MCM|
|-------|:------:|
|Core|32 bits|
|Performance|198 DMIPS|
|Program memory|512kb - 1024kb|
|Data memory|128kb - 256kb|
|Pins|64-100|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|PIC32MK GPD     |        6|        9|       16|       16|        4|        6|        0|        0|        0|         0|         0|         0|         0|
|PIC32MK GPE     |        6|        9|       16|       16|        4|        6|        4|        0|        0|         0|         0|         0|         0|
|PIC32MK MCF     |        6|        9|       16|       16|        4|        6|        4|        0|        0|         6|        12|         0|         0|
|PIC32MK MCM     |        6|        9|       16|       16|        4|        6|      1FD|        0|        0|         6|        12|         0|         0|

[1]: ../../driver/uart
[2]: ../../driver/timer
[3]: ../../driver/oc
[4]: ../../driver/ic
[5]: ../../driver/i2c
[6]: ../../driver/spi
[7]: ../../driver/can
[8]: ../../driver/sent
[9]: ../../driver/clc
[10]: ../../driver/qei
[11]: ../../driver/pwm
[12]: ../../driver/mccp

## Devices list

12 devices on december 2017.

### GPD devices

Global Purpose device

|GPD compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MK0512GPD064](http://microchip.com/wwwproducts/en/PIC32MK0512GPD064)| 524 kb|131 kb| 64|
|[PIC32MK1024GPD064](http://microchip.com/wwwproducts/en/PIC32MK1024GPD064)|1024 kb|262 kb| 64|
|[PIC32MK0512GPD100](http://microchip.com/wwwproducts/en/PIC32MK0512GPD100)| 524 kb|131 kb|100|
|[PIC32MK1024GPD100](http://microchip.com/wwwproducts/en/PIC32MK1024GPD100)|1024 kb|262 kb|100|

### GPE devices

Same as GPD with 4 CAN devices.

|GPE compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MK0512GPE064](http://microchip.com/wwwproducts/en/PIC32MK0512GPE064)| 524 kb|131 kb| 64|
|[PIC32MK1024GPE064](http://microchip.com/wwwproducts/en/PIC32MK1024GPE064)|1024 kb|262 kb| 64|
|[PIC32MK0512GPE100](http://microchip.com/wwwproducts/en/PIC32MK0512GPE100)| 524 kb|131 kb|100|
|[PIC32MK1024GPE100](http://microchip.com/wwwproducts/en/PIC32MK1024GPE100)|1024 kb|262 kb|100|

### MCF devices

Same as GPD with 4 CAN devices, 6 QEI modules and 12 enhanced PWM.

|MCF compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MK0512MCF064](http://microchip.com/wwwproducts/en/PIC32MK0512MCF064)| 524 kb|131 kb| 64|
|[PIC32MK1024MCF064](http://microchip.com/wwwproducts/en/PIC32MK1024MCF064)|1024 kb|262 kb| 64|
|[PIC32MK0512MCF100](http://microchip.com/wwwproducts/en/PIC32MK0512MCF100)| 524 kb|131 kb|100|
|[PIC32MK1024MCF100](http://microchip.com/wwwproducts/en/PIC32MK1024MCF100)|1024 kb|262 kb|100|

### MCM devices

Same as GPD with 1 CAN FD device, 6 QEI modules and 12 enhanced PWM.

|MCM compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*PIC32MK0512MCM064](http://microchip.com/wwwproducts/en/PIC32MK0512MCM064)| 524 kb| 131 kb| 64|
|[*PIC32MK1024MCM064](http://microchip.com/wwwproducts/en/PIC32MK1024MCM064)|1049 kb| 262 kb| 64|
|[*PIC32MK0512MCM100](http://microchip.com/wwwproducts/en/PIC32MK0512MCM100)| 524 kb| 131 kb|100|
|[*PIC32MK1024MCM100](http://microchip.com/wwwproducts/en/PIC32MK1024MCM100)|1049 kb| 262 kb|100|
