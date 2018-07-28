# dsPIC33CH support

dsPIC33CH family is the first Microchip *dual core* [16 bits](../pic16b/README.md) MCU. The main core have 16 kb of dedicated RAM and the slave core 4 kb
with a hardware MSI cache coherency protocol. Architecture and peripherals are similar to [dsPIC33CK](../dspic33ck/README.md), the simple core version.

A lot of peripherals (UART, Timer...) are not compatible with others dsPIC ranges. Full support of drivers may needs additional time.

This family have variations of flash memory, pin count and CAN FD for 5XX subfamily.

Slave core is marked with final S1. Slave core does not have same peripherals. They have 4 - 16 kb of ram and 24 - 73 kb of PRAM.

## Main features

|Feature|dsPIC33CH master core|dsPIC33CH slave core|
|-------|:------:|:------:|
|Core|16 bits|16 bits|
|Performance|90 DMIPS|100 DMIPS|
|Program memory|66 - 540 kb|24 - 73 kb (PRAM)|
|Data memory|16 - 49 kb|4 - 16 kb|
|Pins|28 - 80|28 - 80|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|MP20X           |        2|        1|        0|        0|        2|        2|        0|        2|        4|         1|         0|         0|         8|
|MP20XS1         |        1|        1|        0|        0|        1|        1|        0|        0|        4|         1|         0|         0|         4|
|MP50X           |        2|        1|        0|        0|        2|        2|        1|        2|        4|         1|         0|         0|         8|
|MP50XS1         |        1|        1|        0|        0|        1|        1|        0|        0|        4|         1|         0|         0|         4|

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

32 devices on August 2018, plus relative slave core with a final *S1* which are similar core.

### MP20X subfamily

Base device.

|Compatible devices|Program|Data|Slave program|Slave data|Pins|
|---------|--:|--:|--:|--:|--:|
|[dsPIC33CH64MP202](http://microchip.com/wwwproducts/en/dsPIC33CH64MP202)  |  66 kb| 16 kb| 24 kb|  4 kb| 28|
|[dsPIC33CH128MP202](http://microchip.com/wwwproducts/en/dsPIC33CH128MP202)| 134 kb| 16 kb| 24 kb|  4 kb| 28|
|[dsPIC33CH64MP203](http://microchip.com/wwwproducts/en/dsPIC33CH64MP203)  |  66 kb| 16 kb| 24 kb|  4 kb| 36|
|[dsPIC33CH128MP203](http://microchip.com/wwwproducts/en/dsPIC33CH128MP203)| 134 kb| 16 kb| 24 kb|  4 kb| 36|
|[dsPIC33CH64MP205](http://microchip.com/wwwproducts/en/dsPIC33CH64MP205)  |  66 kb| 16 kb| 24 kb|  4 kb| 48|
|[dsPIC33CH128MP205](http://microchip.com/wwwproducts/en/dsPIC33CH128MP205)| 134 kb| 16 kb| 24 kb|  4 kb| 48|
|[dsPIC33CH256MP205](http://microchip.com/wwwproducts/en/dsPIC33CH256MP205)| 269 kb| 33 kb| 73 kb| 16 kb| 48|
|[dsPIC33CH512MP205](http://microchip.com/wwwproducts/en/dsPIC33CH512MP205)| 540 kb| 49 kb| 73 kb| 16 kb| 48|
|[dsPIC33CH64MP206](http://microchip.com/wwwproducts/en/dsPIC33CH64MP206)  |  66 kb| 16 kb| 24 kb|  4 kb| 64|
|[dsPIC33CH128MP206](http://microchip.com/wwwproducts/en/dsPIC33CH128MP206)| 134 kb| 16 kb| 24 kb|  4 kb| 64|
|[dsPIC33CH256MP206](http://microchip.com/wwwproducts/en/dsPIC33CH256MP206)| 269 kb| 33 kb| 73 kb| 16 kb| 64|
|[dsPIC33CH512MP206](http://microchip.com/wwwproducts/en/dsPIC33CH512MP206)| 540 kb| 49 kb| 73 kb| 16 kb| 64|
|[dsPIC33CH64MP208](http://microchip.com/wwwproducts/en/dsPIC33CH64MP208)  |  66 kb| 16 kb| 24 kb|  4 kb| 80|
|[dsPIC33CH128MP208](http://microchip.com/wwwproducts/en/dsPIC33CH128MP208)| 134 kb| 16 kb| 24 kb|  4 kb| 80|
|[dsPIC33CH256MP208](http://microchip.com/wwwproducts/en/dsPIC33CH256MP208)| 269 kb| 33 kb| 73 kb| 16 kb| 80|
|[dsPIC33CH512MP208](http://microchip.com/wwwproducts/en/dsPIC33CH512MP208)| 540 kb| 49 kb| 73 kb| 16 kb| 80|

### MP50X subfamily

Contains all functionnalities of 20X plus CAN FD device.

|Compatible devices|Program|Data|Slave program|Slave data|Pins|
|---------|--:|--:|--:|--:|--:|
|[dsPIC33CH64MP502](http://microchip.com/wwwproducts/en/dsPIC33CH64MP502)  |  66 kb| 16 kb| 24 kb|  4 kb| 28|
|[dsPIC33CH128MP502](http://microchip.com/wwwproducts/en/dsPIC33CH128MP502)| 134 kb| 16 kb| 24 kb|  4 kb| 28|
|[dsPIC33CH64MP503](http://microchip.com/wwwproducts/en/dsPIC33CH64MP503)  |  66 kb| 16 kb| 24 kb|  4 kb| 40|
|[dsPIC33CH128MP503](http://microchip.com/wwwproducts/en/dsPIC33CH128MP503)| 134 kb| 16 kb| 24 kb|  4 kb| 40|
|[dsPIC33CH64MP505](http://microchip.com/wwwproducts/en/dsPIC33CH64MP505)  |  66 kb| 16 kb| 24 kb|  4 kb| 48|
|[dsPIC33CH128MP505](http://microchip.com/wwwproducts/en/dsPIC33CH128MP505)| 134 kb| 16 kb| 24 kb|  4 kb| 48|
|[dsPIC33CH256MP505](http://microchip.com/wwwproducts/en/dsPIC33CH256MP505)| 269 kb| 33 kb| 73 kb| 16 kb| 48|
|[dsPIC33CH512MP505](http://microchip.com/wwwproducts/en/dsPIC33CH512MP505)| 540 kb| 49 kb| 73 kb| 16 kb| 48|
|[dsPIC33CH64MP506](http://microchip.com/wwwproducts/en/dsPIC33CH64MP506)  |  66 kb| 16 kb| 24 kb|  4 kb| 64|
|[dsPIC33CH128MP506](http://microchip.com/wwwproducts/en/dsPIC33CH128MP506)| 134 kb| 16 kb| 24 kb|  4 kb| 64|
|[dsPIC33CH256MP506](http://microchip.com/wwwproducts/en/dsPIC33CH256MP506)| 269 kb| 33 kb| 73 kb| 16 kb| 64|
|[dsPIC33CH512MP506](http://microchip.com/wwwproducts/en/dsPIC33CH512MP506)| 540 kb| 49 kb| 73 kb| 16 kb| 64|
|[dsPIC33CH64MP508](http://microchip.com/wwwproducts/en/dsPIC33CH64MP508)  |  66 kb| 16 kb| 24 kb|  4 kb| 80|
|[dsPIC33CH128MP508](http://microchip.com/wwwproducts/en/dsPIC33CH128MP508)| 134 kb| 16 kb| 24 kb|  4 kb| 80|
|[dsPIC33CH256MP508](http://microchip.com/wwwproducts/en/dsPIC33CH256MP508)| 269 kb| 33 kb| 73 kb| 16 kb| 80|
|[dsPIC33CH512MP508](http://microchip.com/wwwproducts/en/dsPIC33CH512MP508)| 540 kb| 49 kb| 73 kb| 16 kb| 80|

## Dual core usage

dsPIC33CH is the first range of dsPIC with two cores in one package. Each core have their own periphericals set.
They share access to pins by using MUX. GPIO are shared, they can both read pins but only one can write to it.
The owner of each pin is defined by the configuration word.

Memory program are also independent but the slave program is stocked in the single flash at a special address.
This space is copied to slave's PRAM at startup. So, only one hex file is needed to program both cores.

Debug could be individual by defined debug pairs for each cores.

MCLR pin reset both cores, but a special reset could be defined for slave only.

Clock sources are the same but they have independent PLLs and divisers.

They can comunicate by a shared memory zone with hardware arbitration, by two unidirectionnal FIFO and also by
virtual pins between them. VPins are usefull for synchronisations signals.

## New set of peripherals

### sysclock

A new PLL block appears in this line. Each core have one, but share the same clock sources.

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
