# dsPIC33CH support

> Warning support based on a very low piece of information, may vary in few weeks, only preliminary support.

dsPIC33CH family is the first dual core 16 bits range. The main core have 16 kb of dedicated RAM and the slave core 4 kb
with a hardware MSI cache coherency protocol. Architechture and periphericals are similar to [dsPIC33CK](../dspic33ck/README.md).

A lot of periphericals (UART, Timer...) are not compatible with others dsPIC ranges. Full support of drivers may needs additionnal time.

This family have variation of flash memory, pin count and CAN FD for 5XX subfamily.

Slave core is marked with final S1. Slave core does not have same peripherals. They have 4kb of shared ram and 24kb of flash.

## Main features

|Feature|dsPIC33CH|
|-------|:------:|
|Core|16 bits x 2|
|Performance|100 DMIPS|
|Program memory|64kb - 128kb|
|Data memory|20kb|
|Pins|28-80|

## Common devices

|Peripheral |UART|TMR |OC  |IC  |I2C |SPI |CAN |SENT|CLC |QEI |PWM |MCCP|SCCP|
|:----------|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|MP20X      |   2|   1|   0|   0|   2|   2|   0|   2|   4|   1|   0|   8|   0|
|MP20XS1    |   1|   1|   0|   0|   1|   1|   0|   0|   4|   1|   0|   4|   0|
|MP50X      |   2|   1|   0|   0|   2|   2|   1|   2|   4|   1|   0|   8|   0|
|MP50XS1    |   1|   1|   0|   0|   1|   1|   0|   0|   4|   1|   0|   4|   0|

## Devices list

20 devices on february 2018, plus relative slave core with a final *S1* which are similar core.

### MP20X subfamily

Base device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CH64MP202](http://microchip.com/wwwproducts/en/dsPIC33CH64MP202)  | 64 kb|20 kb|28|
|[dsPIC33CH128MP202](http://microchip.com/wwwproducts/en/dsPIC33CH128MP202)|128 kb|20 kb|28|
|[dsPIC33CH64MP203](http://microchip.com/wwwproducts/en/dsPIC33CH64MP203)  | 64 kb|20 kb|36|
|[dsPIC33CH128MP203](http://microchip.com/wwwproducts/en/dsPIC33CH128MP203)|128 kb|20 kb|36|
|[dsPIC33CH64MP205](http://microchip.com/wwwproducts/en/dsPIC33CH64MP205)  | 64 kb|20 kb|48|
|[dsPIC33CH128MP205](http://microchip.com/wwwproducts/en/dsPIC33CH128MP205)|128 kb|20 kb|48|
|[dsPIC33CH64MP206](http://microchip.com/wwwproducts/en/dsPIC33CH64MP206)  | 64 kb|20 kb|64|
|[dsPIC33CH128MP206](http://microchip.com/wwwproducts/en/dsPIC33CH128MP206)|128 kb|20 kb|64|
|[dsPIC33CH64MP208](http://microchip.com/wwwproducts/en/dsPIC33CH64MP208)  | 64 kb|20 kb|80|
|[dsPIC33CH128MP208](http://microchip.com/wwwproducts/en/dsPIC33CH128MP208)|128 kb|20 kb|80|

### MP50X subfamily

Contains all functionnalities of 20X plus CAN FD device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CH64MP502](http://microchip.com/wwwproducts/en/dsPIC33CH64MP502)  | 64 kb|20 kb|28|
|[dsPIC33CH128MP502](http://microchip.com/wwwproducts/en/dsPIC33CH128MP502)|128 kb|20 kb|28|
|[dsPIC33CH64MP503](http://microchip.com/wwwproducts/en/dsPIC33CH64MP503)  | 64 kb|20 kb|36|
|[dsPIC33CH128MP503](http://microchip.com/wwwproducts/en/dsPIC33CH128MP503)|128 kb|20 kb|36|
|[dsPIC33CH64MP505](http://microchip.com/wwwproducts/en/dsPIC33CH64MP505)  | 64 kb|20 kb|48|
|[dsPIC33CH128MP505](http://microchip.com/wwwproducts/en/dsPIC33CH128MP505)|128 kb|20 kb|48|
|[dsPIC33CH64MP506](http://microchip.com/wwwproducts/en/dsPIC33CH64MP506)  | 64 kb|20 kb|64|
|[dsPIC33CH128MP506](http://microchip.com/wwwproducts/en/dsPIC33CH128MP506)|128 kb|20 kb|64|
|[dsPIC33CH64MP508](http://microchip.com/wwwproducts/en/dsPIC33CH64MP508)  | 64 kb|20 kb|80|
|[dsPIC33CH128MP508](http://microchip.com/wwwproducts/en/dsPIC33CH128MP508)|128 kb|20 kb|80|
