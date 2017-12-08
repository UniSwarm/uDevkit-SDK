# PIC32MK support

PIC32MK family is a high-performance 32 bits range with FPU. All version include at least 1 USB communication module (2 modules in 100 pins package)

This family is splitted into three subfamilies :

* GPD : Global Purpose
* GPE : GPD with 4 CAN devices
* MCF : GPD with 4 CAN devices and Motor Control special features (QEI and enhanced PWM)

## Main features

|Feature|GPD - GPE - MCF|
|-------|:------:|
|Core|32 bits|
|Performance|198 DMIPS|
|Program memory|512kb - 1024kb|
|Data memory|128kb - 256kb|
|Pins|64-100|

## Common devices

|Devices    |UART|TMR |OC  |IC  |I2C |SPI |CAN |SENT|CLC |QEI |PWM |MCCP|SCCP|
|:----------|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|PIC32MK GPD|   6|   9|  16|  16|   4|   6|   0|   0|   0|   0|   0|   0|   0|
|PIC32MK GPE|   6|   9|  16|  16|   4|   6|   4|   0|   0|   0|   0|   0|   0|
|PIC32MK MCF|   6|   9|  16|  16|   4|   6|   4|   0|   0|   6|  12|   0|   0|

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
