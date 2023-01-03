# dsPIC33CK support

dsPIC33CK family is a new generation of [16 bits](../pic16b/README.md) MCU with DSP accelerator. Architecture and peripherals
are similar to [dsPIC33CH](../dspic33ch/README.md), the dual core version.

A lot of peripherals (UART, Timer...) are not compatible with others dsPIC ranges. Full support of drivers may needs additional time.

This family have variations of flash memory, pin count and CAN FD for 5XX, 6XX and 7XX subfamilies.

## Main features

|Feature|dsPIC33CK|
|-------|:------:|
|Core|16 bits|
|Performance|100 DMIPS|
|Program memory|32kb - 1024kb|
|Data memory|8 - 96kb|
|Pins|28-100|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|dsPIC33CK MC10X |        3|        1|        0|        0|        1|        2|        0|        1|        4|         1|         4|         1|         4|
|dsPIC33CK MC50X |        3|        1|        0|        0|        1|        2| __1 Fd__|        1|        4|         1|         4|         1|         4|
|dsPIC33CK MP10X |        3|        1|        0|        0|    __2__|    __3__|        0|    __2__|        4|     __2__|     __8__|         1|         4|
|dsPIC33CK MP20X |        3|        1|        0|        0|    __3__|        3|        0|        2|        4|         2|         8|         1|     __8__|
|dsPIC33CK MP30X |        3|        1|        0|        0|        3|        3|        0|        2|        4|     __3__|         8|         1|         8|
|dsPIC33CK MP40X |        3|        1|        0|        0|        3|        3|        0|        2|    __8__|         3|         8|         1|         8|
|dsPIC33CK MP50X |        3|        1|        0|        0|        3|        3|     1 Fd|        2|        4|         2|         8|         1|         8|
|dsPIC33CK MP60X |        3|        1|        0|        0|        3|        3| __2 Fd__|        2|        4|     __3__|         8|         1|         8|
|dsPIC33CK MP7XX |        3|        1|        0|        0|        3|        3|     2 Fd|        2|    __8__|     __3__|         8|         1|         8|

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
[12]: ../../driver/ccp

## Devices list

104 devices on January 2023.

### MC10X subfamily

Base device.

14 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MC102](http://microchip.com/wwwproducts/en/dsPIC33CK32MC102)   |  36 kb|   8 kb| 28|
|[dsPIC33CK64MC102](http://microchip.com/wwwproducts/en/dsPIC33CK64MC102)   |  66 kb|   8 kb| 28|
|[dsPIC33CK128MC102](http://microchip.com/wwwproducts/en/dsPIC33CK128MC102) | 134 kb|  16 kb| 28|
|[dsPIC33CK256MC102](http://microchip.com/wwwproducts/en/dsPIC33CK256MC102) | 269 kb|  33 kb| 28|
|[dsPIC33CK32MC103](http://microchip.com/wwwproducts/en/dsPIC33CK32MC103)   |  36 kb|   8 kb| 40|
|[dsPIC33CK64MC103](http://microchip.com/wwwproducts/en/dsPIC33CK64MC103)   |  66 kb|   8 kb| 40|
|[dsPIC33CK128MC103](http://microchip.com/wwwproducts/en/dsPIC33CK128MC103) | 134 kb|  16 kb| 40|
|[dsPIC33CK256MC103](http://microchip.com/wwwproducts/en/dsPIC33CK256MC103) | 269 kb|  33 kb| 40|
|[dsPIC33CK32MC105](http://microchip.com/wwwproducts/en/dsPIC33CK32MC105)   |  36 kb|   8 kb| 48|
|[dsPIC33CK64MC105](http://microchip.com/wwwproducts/en/dsPIC33CK64MC105)   |  66 kb|   8 kb| 48|
|[dsPIC33CK128MC105](http://microchip.com/wwwproducts/en/dsPIC33CK128MC105) | 134 kb|  16 kb| 48|
|[dsPIC33CK256MC105](http://microchip.com/wwwproducts/en/dsPIC33CK256MC105) | 269 kb|  33 kb| 48|
|[dsPIC33CK128MC106](http://microchip.com/wwwproducts/en/dsPIC33CK128MC106) | 134 kb|  16 kb| 64|
|[dsPIC33CK256MC106](http://microchip.com/wwwproducts/en/dsPIC33CK256MC106) | 269 kb|  33 kb| 64|

### MC50X subfamily

Same functionalities of MC10X plus one CAN FD device.

8 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK128MC502](http://microchip.com/wwwproducts/en/dsPIC33CK128MC502)| 134 kb|  16 kb| 28|
|[dsPIC33CK128MC503](http://microchip.com/wwwproducts/en/dsPIC33CK128MC503)| 134 kb|  16 kb| 40|
|[dsPIC33CK128MC505](http://microchip.com/wwwproducts/en/dsPIC33CK128MC505)| 134 kb|  16 kb| 48|
|[dsPIC33CK128MC506](http://microchip.com/wwwproducts/en/dsPIC33CK128MC506)| 134 kb|  16 kb| 64|
|[dsPIC33CK256MC502](http://microchip.com/wwwproducts/en/dsPIC33CK256MC502)| 269 kb|  33 kb| 28|
|[dsPIC33CK256MC503](http://microchip.com/wwwproducts/en/dsPIC33CK256MC503)| 269 kb|  33 kb| 40|
|[dsPIC33CK256MC505](http://microchip.com/wwwproducts/en/dsPIC33CK256MC505)| 269 kb|  33 kb| 48|
|[dsPIC33CK256MC506](http://microchip.com/wwwproducts/en/dsPIC33CK256MC506)| 269 kb|  33 kb| 64|

### MP10X subfamily

Same functionalities of MP10X with more peripherals (SPI, I2C, SENT).

6 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK32MP102](http://microchip.com/wwwproducts/en/dsPIC33CK32MP102)|  33 kb|   8 kb| 28|
|[dsPIC33CK64MP102](http://microchip.com/wwwproducts/en/dsPIC33CK64MP102)|  66 kb|   8 kb| 28|
|[dsPIC33CK32MP103](http://microchip.com/wwwproducts/en/dsPIC33CK32MP103)|  33 kb|   8 kb| 40|
|[dsPIC33CK64MP103](http://microchip.com/wwwproducts/en/dsPIC33CK64MP103)|  66 kb|   8 kb| 40|
|[dsPIC33CK32MP105](http://microchip.com/wwwproducts/en/dsPIC33CK32MP105)|  33 kb|   8 kb| 48|
|[dsPIC33CK64MP105](http://microchip.com/wwwproducts/en/dsPIC33CK64MP105)|  66 kb|   8 kb| 48|

### MP20X subfamily

Same functionalities of MP10X with more peripherals (MCCP, I2C) and more analog inputs and functionalities.

19 devices

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

### MP30X subfamily

Same functionalities of MP20X with an additional QEI.

6 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK256MP305](http://microchip.com/wwwproducts/en/dsPIC33CK256MP305) | 269 kb|  61 kb| 48|
|[dsPIC33CK512MP305](http://microchip.com/wwwproducts/en/dsPIC33CK512MP305) | 540 kb|  61 kb| 48|
|[dsPIC33CK256MP306](http://microchip.com/wwwproducts/en/dsPIC33CK256MP306) | 269 kb|  61 kb| 64|
|[dsPIC33CK512MP306](http://microchip.com/wwwproducts/en/dsPIC33CK512MP306) | 540 kb|  61 kb| 64|
|[dsPIC33CK256MP308](http://microchip.com/wwwproducts/en/dsPIC33CK256MP308) | 269 kb|  61 kb| 80|
|[dsPIC33CK512MP308](http://microchip.com/wwwproducts/en/dsPIC33CK512MP308) | 540 kb|  61 kb| 80|

### MP40X subfamily

Same functionalities of MP30X with an additional CLC.

12 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK256MP405](http://microchip.com/wwwproducts/en/dsPIC33CK256MP405)  |  269 kb| 96 kb|  48|
|[dsPIC33CK256MP406](http://microchip.com/wwwproducts/en/dsPIC33CK256MP406)  |  269 kb| 96 kb|  64|
|[dsPIC33CK256MP408](http://microchip.com/wwwproducts/en/dsPIC33CK256MP408)  |  269 kb| 96 kb|  80|
|[dsPIC33CK256MP410](http://microchip.com/wwwproducts/en/dsPIC33CK256MP410)  |  269 kb| 96 kb| 100|
|[dsPIC33CK512MP405](http://microchip.com/wwwproducts/en/dsPIC33CK512MP405)  |  540 kb| 96 kb|  48|
|[dsPIC33CK512MP406](http://microchip.com/wwwproducts/en/dsPIC33CK512MP406)  |  540 kb| 96 kb|  64|
|[dsPIC33CK512MP408](http://microchip.com/wwwproducts/en/dsPIC33CK512MP408)  |  540 kb| 96 kb|  80|
|[dsPIC33CK512MP410](http://microchip.com/wwwproducts/en/dsPIC33CK512MP410)  |  540 kb| 96 kb| 100|
|[dsPIC33CK1024MP405](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP405)| 1080 kb| 96 kb|  48|
|[dsPIC33CK1024MP406](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP406)| 1080 kb| 96 kb|  64|
|[dsPIC33CK1024MP408](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP408)| 1080 kb| 96 kb|  80|
|[dsPIC33CK1024MP410](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP410)| 1080 kb| 96 kb| 100|

### MP50X subfamily

Same functionalities of MP20X plus one CAN FD device.

19 devices

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

### MP60X subfamily

Same functionalities of 30X plus two CAN FD devices.

8 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK256MP605](http://microchip.com/wwwproducts/en/dsPIC33CK256MP605)  | 269 kb|  61 kb| 48|
|[dsPIC33CK512MP605](http://microchip.com/wwwproducts/en/dsPIC33CK512MP605)  | 540 kb|  61 kb| 48|
|[dsPIC33CK256MP606](http://microchip.com/wwwproducts/en/dsPIC33CK256MP606)  | 269 kb|  61 kb| 64|
|[dsPIC33CK512MP606](http://microchip.com/wwwproducts/en/dsPIC33CK512MP606)  | 540 kb|  61 kb| 64|
|[dsPIC33CK256MPT608](http://microchip.com/wwwproducts/en/dsPIC33CK256MPT608)| 269 kb|  61 kb| 72|
|[dsPIC33CK512MPT608](http://microchip.com/wwwproducts/en/dsPIC33CK512MPT608)| 540 kb|  61 kb| 72|
|[dsPIC33CK256MP608](http://microchip.com/wwwproducts/en/dsPIC33CK256MP608)  | 269 kb|  61 kb| 80|
|[dsPIC33CK512MP608](http://microchip.com/wwwproducts/en/dsPIC33CK512MP608)  | 540 kb|  61 kb| 80|

### MP70X subfamily

Same functionalities of 30X plus two CAN FD devices.

12 devices

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33CK256MP705](http://microchip.com/wwwproducts/en/dsPIC33CK256MP705)  |  269 kb|  96 kb|  48|
|[dsPIC33CK256MP706](http://microchip.com/wwwproducts/en/dsPIC33CK256MP706)  |  269 kb|  96 kb|  64|
|[dsPIC33CK256MP708](http://microchip.com/wwwproducts/en/dsPIC33CK256MP708)  |  269 kb|  96 kb|  80|
|[dsPIC33CK512MP705](http://microchip.com/wwwproducts/en/dsPIC33CK512MP705)  |  540 kb|  96 kb|  48|
|[dsPIC33CK512MP706](http://microchip.com/wwwproducts/en/dsPIC33CK512MP706)  |  540 kb|  96 kb|  64|
|[dsPIC33CK512MP708](http://microchip.com/wwwproducts/en/dsPIC33CK512MP708)  |  540 kb|  96 kb|  80|
|[dsPIC33CK1024MP705](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP705)| 1080 kb|  96 kb|  48|
|[dsPIC33CK1024MP706](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP706)| 1080 kb|  96 kb|  64|
|[dsPIC33CK1024MP708](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP708)| 1080 kb|  96 kb|  80|
|[dsPIC33CK256MP710](http://microchip.com/wwwproducts/en/dsPIC33CK256MP710)  |  269 kb|  96 kb| 100|
|[dsPIC33CK512MP710](http://microchip.com/wwwproducts/en/dsPIC33CK512MP710)  |  540 kb|  96 kb| 100|
|[dsPIC33CK1024MP710](http://microchip.com/wwwproducts/en/dsPIC33CK1024MP710)| 1080 kb|  96 kb| 100|

## New set of peripherals

### sysclock

A new PLL block appears in this line.

### UART

Fully reviewed UART peripherals. Bits have quite similar name but not always in the same register. In addition to
UxMODE and UxSTAT, we can found UxMODEH and UxSTATH. This new version adds also integrated hardware protocols handler.

Clock generation can be done from 4 differents sources of clock with a MUX and BRG have now a fractional mode.

### Timer and SCCP

A surprising thing at the first view of global features of dsPIC33CH is the only one present timer. This one is quite
similar to old ones. SCCP replace it.

SCCP peripherals are multi-functions. They can be one 32bits timer, two 16bits timers, an input capture, PWM or output
capture.

### CAN Fd

CAN Fd module is completely different of ECAN from dsPIC33E. A complete driver write needs to be done.

### PWM

PWM modules are more precises and offers more functionalities. A complete driver write needs to be done.

### IOs

A new interupt on change system are available, but still compatible with old drivers.
