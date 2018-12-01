# PIC32MK support

PIC32MK family is a high-performance [32 bits](../pic32/README.md) range with FPU. All version include at least 1 USB communication module (2 modules in 100 pins package).

All devices also contains 4 kb of EEPROM, operational amplifiers and Parallel Master Port.

This family is splitted into six subfamilies :

* GPD : Global Purpose
* GPK : GPD with ECC flash
* GPE : GPD with 4 CAN peripherals
* GPL : GPD with 4 CAN Fd peripherals and ECC flash
* MCF : GPD with 4 CAN peripherals and Motor Control special features (QEI and enhanced PWM)
* MCM : GPD with 4 CAN Fd peripheral, Motor Control special features (QEI and enhanced PWM) and ECC flash

Family documentation can be found here : http://ww1.microchip.com/downloads/en/DeviceDoc/PIC32MK-General-Purpose-and-Motor-Control-%20(GPMC)-Family-Datasheet-60001402E.pdf .

Devices with asterixis are future devices and not yet released.

## Main features

|Feature|GPD - GPE - MCF|GPK - GPL - MCM|
|-------|:------:|:------:|
|Core|32 bits|32 bits|
|Performance|198 DMIPS|198 DMIPS|
|Program memory|512kb - 1024kb|512kb - 1024kb **ECC Flash**|
|Data memory|128kb - 256kb|128kb - 256kb|
|Pins|64-100|64-100|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|PIC32MK GPD     |        6|        9|       16|       16|        4|        6|        0|        0|        0|         0|         0|         0|         0|
|PIC32MK GPK     |        6|        9|       16|       16|        4|        6|        0|        0|        0|         0|         0|         0|         0|
|PIC32MK GPE     |        6|        9|       16|       16|        4|        6|        4|        0|        0|         0|         0|         0|         0|
|PIC32MK GPL     |        6|        9|       16|       16|        4|        6|     4 Fd|        0|        0|         0|         0|         0|         0|
|PIC32MK MCF     |        6|        9|       16|       16|        4|        6|        4|        0|        0|         6|        12|         0|         0|
|PIC32MK MCM     |        6|        9|       16|       16|        4|        6|     4 Fd|        0|        0|         6|        12|         0|         0|

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

24 devices on June 2018.

### GPD devices

Global Purpose device

|GPD compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MK0512GPD064](http://microchip.com/wwwproducts/en/PIC32MK0512GPD064)| 524 kb|131 kb| 64|
|[PIC32MK1024GPD064](http://microchip.com/wwwproducts/en/PIC32MK1024GPD064)|1024 kb|262 kb| 64|
|[PIC32MK0512GPD100](http://microchip.com/wwwproducts/en/PIC32MK0512GPD100)| 524 kb|131 kb|100|
|[PIC32MK1024GPD100](http://microchip.com/wwwproducts/en/PIC32MK1024GPD100)|1024 kb|262 kb|100|

### GPK devices

Same as GPD with ECC flash.

|GPK compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*PIC32MK0512GPK064](http://microchip.com/wwwproducts/en/PIC32MK0512GPK064)| 524 kb| 131 kb| 64|
|[*PIC32MK1024GPK064](http://microchip.com/wwwproducts/en/PIC32MK1024GPK064)|1049 kb| 262 kb| 64|
|[*PIC32MK0512GPK100](http://microchip.com/wwwproducts/en/PIC32MK0512GPK100)| 524 kb| 131 kb|100|
|[*PIC32MK1024GPK100](http://microchip.com/wwwproducts/en/PIC32MK1024GPK100)|1049 kb| 262 kb|100|

### GPE devices

Same as GPD with 4 CAN peripherals.

|GPE compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MK0512GPE064](http://microchip.com/wwwproducts/en/PIC32MK0512GPE064)| 524 kb|131 kb| 64|
|[PIC32MK1024GPE064](http://microchip.com/wwwproducts/en/PIC32MK1024GPE064)|1024 kb|262 kb| 64|
|[PIC32MK0512GPE100](http://microchip.com/wwwproducts/en/PIC32MK0512GPE100)| 524 kb|131 kb|100|
|[PIC32MK1024GPE100](http://microchip.com/wwwproducts/en/PIC32MK1024GPE100)|1024 kb|262 kb|100|

### GPL devices

Same as GPD with 4 CAN Fd peripheral and ECC flash.

|GPL compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*PIC32MK0512GPL064](http://microchip.com/wwwproducts/en/PIC32MK0512GPL064)| 524 kb| 131 kb| 64|
|[*PIC32MK1024GPL064](http://microchip.com/wwwproducts/en/PIC32MK1024GPL064)|1049 kb| 262 kb| 64|
|[*PIC32MK0512GPL100](http://microchip.com/wwwproducts/en/PIC32MK0512GPL100)| 524 kb| 131 kb|100|
|[*PIC32MK1024GPL100](http://microchip.com/wwwproducts/en/PIC32MK1024GPL100)|1049 kb| 262 kb|100|


### MCF devices

Same as GPD with 4 CAN peripherals, 6 QEI modules and 12 enhanced PWM.

|MCF compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MK0512MCF064](http://microchip.com/wwwproducts/en/PIC32MK0512MCF064)| 524 kb|131 kb| 64|
|[PIC32MK1024MCF064](http://microchip.com/wwwproducts/en/PIC32MK1024MCF064)|1024 kb|262 kb| 64|
|[PIC32MK0512MCF100](http://microchip.com/wwwproducts/en/PIC32MK0512MCF100)| 524 kb|131 kb|100|
|[PIC32MK1024MCF100](http://microchip.com/wwwproducts/en/PIC32MK1024MCF100)|1024 kb|262 kb|100|

### MCM devices

Same as GPD with 4 CAN Fd peripheral, 6 QEI modules, 12 enhanced PWM and ECC flash.

|MCM compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[*PIC32MK0512MCM064](http://microchip.com/wwwproducts/en/PIC32MK0512MCM064)| 524 kb| 131 kb| 64|
|[*PIC32MK1024MCM064](http://microchip.com/wwwproducts/en/PIC32MK1024MCM064)|1049 kb| 262 kb| 64|
|[*PIC32MK0512MCM100](http://microchip.com/wwwproducts/en/PIC32MK0512MCM100)| 524 kb| 131 kb|100|
|[*PIC32MK1024MCM100](http://microchip.com/wwwproducts/en/PIC32MK1024MCM100)|1049 kb| 262 kb|100|
