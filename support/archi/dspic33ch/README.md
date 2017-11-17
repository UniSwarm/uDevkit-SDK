# dsPIC33CH support

> Warning support based on a very low piece of information, may vary in few weeks, only preliminary support.

dsPIC33CH family is the first dual core 16 bits range. The main core have 16 kb of dedicated RAM and the slave core 4 kb with a harware MSI cache coherency protocol.
A lot of periphericals are not compatibles with others dsPIC ranges. Full support of driver ay needs additionnal time.

This family have variation of flash memory, pin count and CAN FD for 5XX subfamily.

## Main features

|Feature|dsPIC33CH|
|-------|:------:|
|Core|32 bits|
|Performance|100 DMIPS|
|Program memory|64kb - 128kb|
|Data memory|16kb|
|Pins|28-80|

## Common devices

|Peripheral|UART|TIMER|I2C|SPI|SENT|CLC|QEI|CAN|
|----------|:--:|:---:|:-:|:-:|:--:|:-:|:-:|:-:|
|20X       |   2|    1|  2|  2|   2|  4|  1|  0|
|50X       |   2|    1|  2|  2|   2|  4|  1|  1|

## Devices list

20 devices on november 2017, plus relative slave core with a final *S1* which are similar core.

### 20X subfamily

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

### 50X subfamily

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
