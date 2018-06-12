# dsPIC33CK support

dsPIC33CK family is a new generation of 16 bits microcontroller with DSP accelerator. Architechture and periphericals
are similar to [dsPIC33CH](../dspic33ch/README.md).

A lot of periphericals (UART, Timer...) are not compatible with others dsPIC ranges. Full support of drivers may needs additionnal time.

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

|Peripheral      |UART|TMR |OC  |IC  |I2C |SPI |CAN |SENT|CLC |QEI |PWM |MCCP|SCCP|
|:---------------|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
|dsPIC33CK MP10X |   3|   1|   0|   0|   2|   3|   0|   2|   4|   2|   8|   1|   4|
|dsPIC33CK MP20X |   3|   1|   0|   0|   3|   3|   0|   2|   4|   2|   8|   1|   8|
|dsPIC33CK MP50X |   3|   1|   0|   0|   3|   3|   1|   2|   4|   2|   8|   1|   8|

## Devices list

44 devices on june 2018.

### MP10X subfamily

Base device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MP102](http://microchip.com/wwwproducts/en/dsPIC33CK32MP102)|  33 kb|   8 kb| 28|
|[dsPIC33CK64MP102](http://microchip.com/wwwproducts/en/dsPIC33CK64MP102)|  66 kb|   8 kb| 28|
|[dsPIC33CK32MP103](http://microchip.com/wwwproducts/en/dsPIC33CK32MP103)|  33 kb|   8 kb| 40|
|[dsPIC33CK64MP103](http://microchip.com/wwwproducts/en/dsPIC33CK64MP103)|  66 kb|   8 kb| 40|
|[dsPIC33CK32MP105](http://microchip.com/wwwproducts/en/dsPIC33CK32MP105)|  33 kb|   8 kb| 48|
|[dsPIC33CK64MP105](http://microchip.com/wwwproducts/en/dsPIC33CK64MP105)|  66 kb|   8 kb| 48|

### MP20X subfamily

Same functionalities of 50X with more peripherals (MCCP, I2C) and more analog inputs and functionalities.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MP202](http://microchip.com/wwwproducts/en/dsPIC33CK32MP202)  |  36 kb|   8 kb| 28|
|[dsPIC33CK64MP202](http://microchip.com/wwwproducts/en/dsPIC33CK64MP202)  |  66 kb|   8 kb| 28|
|[dsPIC33CK128MP202](http://microchip.com/wwwproducts/en/dsPIC33CK128MP202)| 134 kb|  16 kb| 28|
|[dsPIC33CK256MP202](http://microchip.com/wwwproducts/en/dsPIC33CK256MP202)| 269 kb|  25 kb| 28|
|[dsPIC33CK32MP203](http://microchip.com/wwwproducts/en/dsPIC33CK32MP203)  |  36 kb|   8 kb| 40|
|[dsPIC33CK64MP203](http://microchip.com/wwwproducts/en/dsPIC33CK64MP203)  |  66 kb|   8 kb| 40|
|[dsPIC33CK128MP203](http://microchip.com/wwwproducts/en/dsPIC33CK128MP203)| 134 kb|  16 kb| 40|
|[dsPIC33CK256MP203](http://microchip.com/wwwproducts/en/dsPIC33CK256MP203)| 269 kb|  25 kb| 40|
|[dsPIC33CK32MP205](http://microchip.com/wwwproducts/en/dsPIC33CK32MP205)  |  36 kb|   8 kb| 48|
|[dsPIC33CK64MP205](http://microchip.com/wwwproducts/en/dsPIC33CK64MP205)  |  66 kb|   8 kb| 48|
|[dsPIC33CK128MP205](http://microchip.com/wwwproducts/en/dsPIC33CK128MP205)| 134 kb|  16 kb| 48|
|[dsPIC33CK256MP205](http://microchip.com/wwwproducts/en/dsPIC33CK256MP205)| 269 kb|  25 kb| 48|
|[dsPIC33CK32MP206](http://microchip.com/wwwproducts/en/dsPIC33CK32MP206)  |  36 kb|   8 kb| 64|
|[dsPIC33CK64MP206](http://microchip.com/wwwproducts/en/dsPIC33CK64MP206)  |  66 kb|   8 kb| 64|
|[dsPIC33CK128MP206](http://microchip.com/wwwproducts/en/dsPIC33CK128MP206)| 134 kb|  16 kb| 64|
|[dsPIC33CK256MP206](http://microchip.com/wwwproducts/en/dsPIC33CK256MP206)| 269 kb|  25 kb| 64|
|[dsPIC33CK64MP208](http://microchip.com/wwwproducts/en/dsPIC33CK64MP208)  |  66 kb|   8 kb| 80|
|[dsPIC33CK128MP208](http://microchip.com/wwwproducts/en/dsPIC33CK128MP208)| 134 kb|  16 kb| 80|
|[dsPIC33CK256MP208](http://microchip.com/wwwproducts/en/dsPIC33CK256MP208)| 269 kb|  25 kb| 80|

### MP50X subfamily

Same functionalities of 20X plus CAN FD device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MP502](http://microchip.com/wwwproducts/en/dsPIC33CK32MP502)  |  36 kb|   8 kb| 28|
|[dsPIC33CK64MP502](http://microchip.com/wwwproducts/en/dsPIC33CK64MP502)  |  66 kb|   8 kb| 28|
|[dsPIC33CK128MP502](http://microchip.com/wwwproducts/en/dsPIC33CK128MP502)| 134 kb|  16 kb| 28|
|[dsPIC33CK256MP502](http://microchip.com/wwwproducts/en/dsPIC33CK256MP502)| 269 kb|  25 kb| 28|
|[dsPIC33CK32MP503](http://microchip.com/wwwproducts/en/dsPIC33CK32MP503)  |  36 kb|   8 kb| 40|
|[dsPIC33CK64MP503](http://microchip.com/wwwproducts/en/dsPIC33CK64MP503)  |  66 kb|   8 kb| 40|
|[dsPIC33CK128MP503](http://microchip.com/wwwproducts/en/dsPIC33CK128MP503)| 134 kb|  16 kb| 40|
|[dsPIC33CK256MP503](http://microchip.com/wwwproducts/en/dsPIC33CK256MP503)| 269 kb|  25 kb| 40|
|[dsPIC33CK32MP505](http://microchip.com/wwwproducts/en/dsPIC33CK32MP505)  |  36 kb|   8 kb| 48|
|[dsPIC33CK64MP505](http://microchip.com/wwwproducts/en/dsPIC33CK64MP505)  |  66 kb|   8 kb| 48|
|[dsPIC33CK128MP505](http://microchip.com/wwwproducts/en/dsPIC33CK128MP505)| 134 kb|  16 kb| 48|
|[dsPIC33CK256MP505](http://microchip.com/wwwproducts/en/dsPIC33CK256MP505)| 269 kb|  25 kb| 48|
|[dsPIC33CK32MP506](http://microchip.com/wwwproducts/en/dsPIC33CK32MP506)  |  36 kb|   8 kb| 64|
|[dsPIC33CK64MP506](http://microchip.com/wwwproducts/en/dsPIC33CK64MP506)  |  66 kb|   8 kb| 64|
|[dsPIC33CK128MP506](http://microchip.com/wwwproducts/en/dsPIC33CK128MP506)| 134 kb|  16 kb| 64|
|[dsPIC33CK256MP506](http://microchip.com/wwwproducts/en/dsPIC33CK256MP506)| 269 kb|  25 kb| 64|
|[dsPIC33CK64MP508](http://microchip.com/wwwproducts/en/dsPIC33CK64MP508)  |  66 kb|   8 kb| 80|
|[dsPIC33CK128MP508](http://microchip.com/wwwproducts/en/dsPIC33CK128MP508)| 134 kb|  16 kb| 80|
|[dsPIC33CK256MP508](http://microchip.com/wwwproducts/en/dsPIC33CK256MP508)| 269 kb|  25 kb| 80|
