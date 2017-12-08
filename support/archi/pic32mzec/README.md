# PIC32MZ EC support

PIC32MZ EC family is a high-performance 32 bits range for Embedded Connectivity.

This family is splitted into three variations :

* ECG : Base family
* ECH : ECG with 2 CAN devices
* ECM : ECG with 2 CAN devices and hardware crypto module

Microchip recommends [PIC32MZEF family](../pic32mzef/README.md) for new design with
same functionalities and a floating point unit

## Main features

|Feature|ECG - ECH - ECM|
|-------|------|
|Core|32 bits|
|Performance|330 DMIPS|
|Program memory|1024kb - 2048kb|
|Data memory|512kb|
|Pins|64-144|

## Common devices

|Devices     |UART|TMR |OC  |IC  |I2C |SPI |CAN |SENT|CLC |QEI |PWM |MCCP|SCCP|
|:-----------|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|PIC32MZ ECG |   6|   9|   9|   9| 4-5| 4-6|   0|   0|   0|   0|   0|   0|   0|
|PIC32MZ ECH |   6|   9|   9|   9| 4-5| 4-6|   2|   0|   0|   0|   0|   0|   0|
|PIC32MZ ECM |   6|   9|   9|   9| 4-5| 4-6|   2|   0|   0|   0|   0|   0|   0|

## Devices list

24 devices on december 2017.

### ECG devices

Base family.

|ECG compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MZ1024ECG064](http://microchip.com/wwwproducts/en/PIC32MZ1024ECG064)|1049 kb| 524 kb| 64|
|[PIC32MZ2048ECG064](http://microchip.com/wwwproducts/en/PIC32MZ2048ECG064)|2097 kb| 524 kb| 64|
|[PIC32MZ1024ECG100](http://microchip.com/wwwproducts/en/PIC32MZ1024ECG100)|1049 kb| 524 kb|100|
|[PIC32MZ2048ECG100](http://microchip.com/wwwproducts/en/PIC32MZ2048ECG100)|2097 kb| 524 kb|100|
|[PIC32MZ1024ECG124](http://microchip.com/wwwproducts/en/PIC32MZ1024ECG124)|1049 kb| 524 kb|124|
|[PIC32MZ2048ECG124](http://microchip.com/wwwproducts/en/PIC32MZ2048ECG124)|2097 kb| 524 kb|124|
|[PIC32MZ1024ECG144](http://microchip.com/wwwproducts/en/PIC32MZ1024ECG144)|1049 kb| 524 kb|144|
|[PIC32MZ2048ECG144](http://microchip.com/wwwproducts/en/PIC32MZ2048ECG144)|2097 kb| 524 kb|144|

### ECH devices

Same as ECG with 2 CAN devices.

|ECH compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MZ1024ECH064](http://microchip.com/wwwproducts/en/PIC32MZ1024ECH064)|1049 kb| 524 kb| 64|
|[PIC32MZ2048ECH064](http://microchip.com/wwwproducts/en/PIC32MZ2048ECH064)|2097 kb| 524 kb| 64|
|[PIC32MZ1024ECH100](http://microchip.com/wwwproducts/en/PIC32MZ1024ECH100)|1049 kb| 524 kb|100|
|[PIC32MZ2048ECH100](http://microchip.com/wwwproducts/en/PIC32MZ2048ECH100)|2097 kb| 524 kb|100|
|[PIC32MZ1024ECH124](http://microchip.com/wwwproducts/en/PIC32MZ1024ECH124)|1049 kb| 524 kb|124|
|[PIC32MZ2048ECH124](http://microchip.com/wwwproducts/en/PIC32MZ2048ECH124)|2097 kb| 524 kb|124|
|[PIC32MZ1024ECH144](http://microchip.com/wwwproducts/en/PIC32MZ1024ECH144)|1049 kb| 524 kb|144|
|[PIC32MZ2048ECH144](http://microchip.com/wwwproducts/en/PIC32MZ2048ECH144)|2097 kb| 524 kb|144|

### ECM devices

Same as ECG with 2 CAN devices and hardware crypto module.

|ECM compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MZ1024ECM064](http://microchip.com/wwwproducts/en/PIC32MZ1024ECM064)|1049 kb| 524 kb| 64|
|[PIC32MZ2048ECM064](http://microchip.com/wwwproducts/en/PIC32MZ2048ECM064)|2097 kb| 524 kb| 64|
|[PIC32MZ1024ECM100](http://microchip.com/wwwproducts/en/PIC32MZ1024ECM100)|1049 kb| 524 kb|100|
|[PIC32MZ2048ECM100](http://microchip.com/wwwproducts/en/PIC32MZ2048ECM100)|2097 kb| 524 kb|100|
|[PIC32MZ1024ECM124](http://microchip.com/wwwproducts/en/PIC32MZ1024ECM124)|1049 kb| 524 kb|124|
|[PIC32MZ2048ECM124](http://microchip.com/wwwproducts/en/PIC32MZ2048ECM124)|2097 kb| 524 kb|124|
|[PIC32MZ1024ECM144](http://microchip.com/wwwproducts/en/PIC32MZ1024ECM144)|1049 kb| 524 kb|144|
|[PIC32MZ2048ECM144](http://microchip.com/wwwproducts/en/PIC32MZ2048ECM144)|2097 kb| 524 kb|144|
