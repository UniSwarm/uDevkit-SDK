# dsPIC33CK support

> Warning support based on a very low piece of information, may vary in few weeks, only preliminary support.

dsPIC33CK family is a new generation of 16 bits microcontroller with DSP accelerator. Architechture and periphericals
are similar to [dsPIC33CH](../dspic33ch/README.md).

A lot of periphericals (UART, Timer...) are not compatible with others dsPIC ranges. Full support of drivers ay needs additionnal time.

This family have variation of flash memory, pin count and CAN FD for 5XX subfamily.

## Main features

|Feature|dsPIC33CH|
|-------|:------:|
|Core|16 bits|
|Performance|100 DMIPS|
|Program memory|32kb - 256kb|
|Data memory|8 - 32kb|
|Pins|28-80|

## Common devices

|Peripheral|UART|TIMER|I2C|SPI|SENT|CLC|QEI|
|----------|:--:|:---:|:-:|:-:|:--:|:-:|:-:|
|Count     |   3|    1|  3|  3|   2|  4|  2|

## Devices list

38 devices on november 2017.

### 20X subfamily

Base device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MP202](http://microchip.com/wwwproducts/en/dsPIC33CK32MP202)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP202](http://microchip.com/wwwproducts/en/dsPIC33CK64MP202)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP202](http://microchip.com/wwwproducts/en/dsPIC33CK128MP202)|128 kb|16 kb|28|
|[dsPIC33CK256MP202](http://microchip.com/wwwproducts/en/dsPIC33CK256MP202)|256 kb|32 kb|28|
|[dsPIC33CK32MP203](http://microchip.com/wwwproducts/en/dsPIC33CK32MP203)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP203](http://microchip.com/wwwproducts/en/dsPIC33CK64MP203)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP203](http://microchip.com/wwwproducts/en/dsPIC33CK128MP203)|128 kb|16 kb|28|
|[dsPIC33CK256MP203](http://microchip.com/wwwproducts/en/dsPIC33CK256MP203)|256 kb|32 kb|28|
|[dsPIC33CK32MP205](http://microchip.com/wwwproducts/en/dsPIC33CK32MP205)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP205](http://microchip.com/wwwproducts/en/dsPIC33CK64MP205)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP205](http://microchip.com/wwwproducts/en/dsPIC33CK128MP205)|128 kb|16 kb|28|
|[dsPIC33CK256MP205](http://microchip.com/wwwproducts/en/dsPIC33CK256MP205)|256 kb|32 kb|28|
|[dsPIC33CK32MP206](http://microchip.com/wwwproducts/en/dsPIC33CK32MP206)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP206](http://microchip.com/wwwproducts/en/dsPIC33CK64MP206)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP206](http://microchip.com/wwwproducts/en/dsPIC33CK128MP206)|128 kb|16 kb|28|
|[dsPIC33CK256MP206](http://microchip.com/wwwproducts/en/dsPIC33CK256MP206)|256 kb|32 kb|28|
|[dsPIC33CK64MP208](http://microchip.com/wwwproducts/en/dsPIC33CK64MP208)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP208](http://microchip.com/wwwproducts/en/dsPIC33CK128MP208)|128 kb|16 kb|28|
|[dsPIC33CK256MP208](http://microchip.com/wwwproducts/en/dsPIC33CK256MP208)|256 kb|32 kb|28|

### 50X subfamily

Same functionnalities of 20X plus CAN FD device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MP502](http://microchip.com/wwwproducts/en/dsPIC33CK32MP502)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP502](http://microchip.com/wwwproducts/en/dsPIC33CK64MP502)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP502](http://microchip.com/wwwproducts/en/dsPIC33CK128MP502)|128 kb|16 kb|28|
|[dsPIC33CK256MP502](http://microchip.com/wwwproducts/en/dsPIC33CK256MP502)|256 kb|32 kb|28|
|[dsPIC33CK32MP503](http://microchip.com/wwwproducts/en/dsPIC33CK32MP503)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP503](http://microchip.com/wwwproducts/en/dsPIC33CK64MP503)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP503](http://microchip.com/wwwproducts/en/dsPIC33CK128MP503)|128 kb|16 kb|28|
|[dsPIC33CK256MP503](http://microchip.com/wwwproducts/en/dsPIC33CK256MP503)|256 kb|32 kb|28|
|[dsPIC33CK32MP505](http://microchip.com/wwwproducts/en/dsPIC33CK32MP505)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP505](http://microchip.com/wwwproducts/en/dsPIC33CK64MP505)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP505](http://microchip.com/wwwproducts/en/dsPIC33CK128MP505)|128 kb|16 kb|28|
|[dsPIC33CK256MP505](http://microchip.com/wwwproducts/en/dsPIC33CK256MP505)|256 kb|32 kb|28|
|[dsPIC33CK32MP506](http://microchip.com/wwwproducts/en/dsPIC33CK32MP506)  | 32 kb| 8 kb|28|
|[dsPIC33CK64MP506](http://microchip.com/wwwproducts/en/dsPIC33CK64MP506)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP506](http://microchip.com/wwwproducts/en/dsPIC33CK128MP506)|128 kb|16 kb|28|
|[dsPIC33CK256MP506](http://microchip.com/wwwproducts/en/dsPIC33CK256MP506)|256 kb|32 kb|28|
|[dsPIC33CK64MP508](http://microchip.com/wwwproducts/en/dsPIC33CK64MP508)  | 64 kb| 8 kb|28|
|[dsPIC33CK128MP508](http://microchip.com/wwwproducts/en/dsPIC33CK128MP508)|128 kb|16 kb|28|
|[dsPIC33CK256MP508](http://microchip.com/wwwproducts/en/dsPIC33CK256MP508)|256 kb|32 kb|28|
