# PIC32MZ EF support

PIC32MZ EF family is a high-performance 32 bits range for Embedded Connectivity with hardware Floating point unit (FPU).

This family is splitted into three variations :

* EFE/EFG : Base family
* EFF/EFH : EFE/EFG with 2 CAN devices
* EFK/EFM : EFE/EFG with 2 CAN devices and hardware crypto module

## Main features

|Feature|EFE/EFG - EFF/EFH - EFK/EFM|
|-------|------|
|Core|32 bits|
|Performance|330 DMIPS (up to 400DMIPS for some devices)|
|Program memory|1024kb - 2048kb|
|Data memory|512kb|
|Pins|64-144|

## Common devices

|Devices         |UART|TMR |OC  |IC  |I2C |SPI |CAN |SENT|CLC |QEI |PWM |MCCP|SCCP|
|:---------------|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|PIC32MZ EFE/EFG |   6|   9|   9|   9| 4-5| 4-6|   0|   0|   0|   0|   0|   0|   0|
|PIC32MZ EFF/EFH |   6|   9|   9|   9| 4-5| 4-6|   2|   0|   0|   0|   0|   0|   0|
|PIC32MZ EFK/EFM |   6|   9|   9|   9| 4-5| 4-6|   2|   0|   0|   0|   0|   0|   0|

## Devices list

48 devices on december 2017.

### EFE / EFG devices

Base family.

|EFE / EFG Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MZ0512EFE064](http://microchip.com/wwwproducts/en/PIC32MZ0512EFE064)| 524 kb| 131 kb| 64|
|[PIC32MZ1024EFE064](http://microchip.com/wwwproducts/en/PIC32MZ1024EFE064)|1049 kb| 262 kb| 64|
|[PIC32MZ1024EFG064](http://microchip.com/wwwproducts/en/PIC32MZ1024EFG064)|1049 kb| 524 kb| 64|
|[PIC32MZ2048EFG064](http://microchip.com/wwwproducts/en/PIC32MZ2048EFG064)|2097 kb| 524 kb| 64|
|[PIC32MZ0512EFE100](http://microchip.com/wwwproducts/en/PIC32MZ0512EFE100)| 524 kb| 131 kb|100|
|[PIC32MZ1024EFE100](http://microchip.com/wwwproducts/en/PIC32MZ1024EFE100)|1049 kb| 262 kb|100|
|[PIC32MZ1024EFG100](http://microchip.com/wwwproducts/en/PIC32MZ1024EFG100)|1049 kb| 524 kb|100|
|[PIC32MZ2048EFG100](http://microchip.com/wwwproducts/en/PIC32MZ2048EFG100)|2097 kb| 524 kb|100|
|[PIC32MZ0512EFE124](http://microchip.com/wwwproducts/en/PIC32MZ0512EFE124)| 524 kb| 131 kb|124|
|[PIC32MZ1024EFE124](http://microchip.com/wwwproducts/en/PIC32MZ1024EFE124)|1049 kb| 262 kb|124|
|[PIC32MZ1024EFG124](http://microchip.com/wwwproducts/en/PIC32MZ1024EFG124)|1049 kb| 524 kb|124|
|[PIC32MZ2048EFG124](http://microchip.com/wwwproducts/en/PIC32MZ2048EFG124)|2097 kb| 524 kb|124|
|[PIC32MZ0512EFE144](http://microchip.com/wwwproducts/en/PIC32MZ0512EFE144)| 524 kb| 131 kb|144|
|[PIC32MZ1024EFE144](http://microchip.com/wwwproducts/en/PIC32MZ1024EFE144)|1049 kb| 262 kb|144|
|[PIC32MZ1024EFG144](http://microchip.com/wwwproducts/en/PIC32MZ1024EFG144)|1049 kb| 524 kb|144|
|[PIC32MZ2048EFG144](http://microchip.com/wwwproducts/en/PIC32MZ2048EFG144)|2097 kb| 524 kb|144|

### EFF / EFH devices

Same as EFE / EFG with 2 CAN devices.

|EFF / EFH Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MZ0512EFF064](http://microchip.com/wwwproducts/en/PIC32MZ0512EFF064)| 524 kb| 131 kb| 64|
|[PIC32MZ1024EFF064](http://microchip.com/wwwproducts/en/PIC32MZ1024EFF064)|1049 kb| 262 kb| 64|
|[PIC32MZ1024EFH064](http://microchip.com/wwwproducts/en/PIC32MZ1024EFH064)|1049 kb| 524 kb| 64|
|[PIC32MZ2048EFH064](http://microchip.com/wwwproducts/en/PIC32MZ2048EFH064)|2097 kb| 524 kb| 64|
|[PIC32MZ0512EFF100](http://microchip.com/wwwproducts/en/PIC32MZ0512EFF100)| 524 kb| 131 kb|100|
|[PIC32MZ1024EFF100](http://microchip.com/wwwproducts/en/PIC32MZ1024EFF100)|1049 kb| 262 kb|100|
|[PIC32MZ1024EFH100](http://microchip.com/wwwproducts/en/PIC32MZ1024EFH100)|1049 kb| 524 kb|100|
|[PIC32MZ2048EFH100](http://microchip.com/wwwproducts/en/PIC32MZ2048EFH100)|2097 kb| 524 kb|100|
|[PIC32MZ0512EFF124](http://microchip.com/wwwproducts/en/PIC32MZ0512EFF124)| 524 kb| 131 kb|124|
|[PIC32MZ1024EFF124](http://microchip.com/wwwproducts/en/PIC32MZ1024EFF124)|1049 kb| 262 kb|124|
|[PIC32MZ1024EFH124](http://microchip.com/wwwproducts/en/PIC32MZ1024EFH124)|1049 kb| 524 kb|124|
|[PIC32MZ2048EFH124](http://microchip.com/wwwproducts/en/PIC32MZ2048EFH124)|2097 kb| 524 kb|124|
|[PIC32MZ0512EFF144](http://microchip.com/wwwproducts/en/PIC32MZ0512EFF144)| 524 kb| 131 kb|144|
|[PIC32MZ1024EFF144](http://microchip.com/wwwproducts/en/PIC32MZ1024EFF144)|1049 kb| 262 kb|144|
|[PIC32MZ1024EFH144](http://microchip.com/wwwproducts/en/PIC32MZ1024EFH144)|1049 kb| 524 kb|144|
|[PIC32MZ2048EFH144](http://microchip.com/wwwproducts/en/PIC32MZ2048EFH144)|2097 kb| 524 kb|144|

### EFK / EFM devices

Same as EFE / EFG with 2 CAN devices and hardware crypto module.

|EFK / EFM Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MZ0512EFK064](http://microchip.com/wwwproducts/en/PIC32MZ0512EFK064)| 524 kb| 131 kb| 64|
|[PIC32MZ1024EFK064](http://microchip.com/wwwproducts/en/PIC32MZ1024EFK064)|1049 kb| 262 kb| 64|
|[PIC32MZ1024EFM064](http://microchip.com/wwwproducts/en/PIC32MZ1024EFM064)|1049 kb| 524 kb| 64|
|[PIC32MZ2048EFM064](http://microchip.com/wwwproducts/en/PIC32MZ2048EFM064)|2097 kb| 524 kb| 64|
|[PIC32MZ0512EFK100](http://microchip.com/wwwproducts/en/PIC32MZ0512EFK100)| 524 kb| 131 kb|100|
|[PIC32MZ1024EFK100](http://microchip.com/wwwproducts/en/PIC32MZ1024EFK100)|1049 kb| 262 kb|100|
|[PIC32MZ1024EFM100](http://microchip.com/wwwproducts/en/PIC32MZ1024EFM100)|1049 kb| 524 kb|100|
|[PIC32MZ2048EFM100](http://microchip.com/wwwproducts/en/PIC32MZ2048EFM100)|2097 kb| 524 kb|100|
|[PIC32MZ0512EFK124](http://microchip.com/wwwproducts/en/PIC32MZ0512EFK124)| 524 kb| 131 kb|124|
|[PIC32MZ1024EFK124](http://microchip.com/wwwproducts/en/PIC32MZ1024EFK124)|1049 kb| 262 kb|124|
|[PIC32MZ1024EFM124](http://microchip.com/wwwproducts/en/PIC32MZ1024EFM124)|1049 kb| 524 kb|124|
|[PIC32MZ2048EFM124](http://microchip.com/wwwproducts/en/PIC32MZ2048EFM124)|2097 kb| 524 kb|124|
|[PIC32MZ0512EFK144](http://microchip.com/wwwproducts/en/PIC32MZ0512EFK144)| 524 kb| 131 kb|144|
|[PIC32MZ1024EFK144](http://microchip.com/wwwproducts/en/PIC32MZ1024EFK144)|1049 kb| 262 kb|144|
|[PIC32MZ1024EFM144](http://microchip.com/wwwproducts/en/PIC32MZ1024EFM144)|1049 kb| 524 kb|144|
|[PIC32MZ2048EFM144](http://microchip.com/wwwproducts/en/PIC32MZ2048EFM144)|2097 kb| 524 kb|144|
