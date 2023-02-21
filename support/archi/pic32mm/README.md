# PIC32MM support

PIC32MM family is a low power high-performance [32 bits](../pic32/README.md) range.

This family is splitted into two subfamilies :

* GPL : low pin count (20 to 36) with a small set of peripherals
* GPM : medium pin count (28 to 64) with more peripherals and USB communication

## Main features

|Feature|GPL|GPM|
|-------|:-----:|:-----:|
|Core|32 bits|32 bits|
|Performance|37 DMIPS|37 DMIPS|
|Program memory|16kb - 66kb|66kb - 262kb|
|Data memory|4kb - 8kb|16kb - 33kb|
|Pins|20-36|28-64|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|PIC32MM GPL     |        2|        1|        0|        0|        0|        2|        0|        0|        2|         0|         0|         1|         2|
|PIC32MM GPM     |        3|        3|        0|        0|        3|        3|        0|        0|        4|         0|         0|         3|         6|

[1]: ../../driver/uart/README.md
[2]: ../../driver/timer/README.md
[3]: ../../driver/oc/README.md
[4]: ../../driver/ic/README.md
[5]: ../../driver/i2c/README.md
[6]: ../../driver/spi/README.md
[7]: ../../driver/can/README.md
[8]: ../../driver/sent/README.md
[9]: ../../driver/clc/README.md
[10]: ../../driver/qei/README.md
[11]: ../../driver/pwm/README.md
[12]: ../../driver/ccp/README.md

## Devices list

21 devices on January 2023.

### GPD devices

Smaller devices

|GPL Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MM0016GPL020](http://microchip.com/wwwproducts/en/PIC32MM0016GPL020)|16 kb| 4 kb|20|
|[PIC32MM0032GPL020](http://microchip.com/wwwproducts/en/PIC32MM0032GPL020)|33 kb| 8 kb|20|
|[PIC32MM0064GPL020](http://microchip.com/wwwproducts/en/PIC32MM0064GPL020)|66 kb| 8 kb|20|
|[PIC32MM0016GPL028](http://microchip.com/wwwproducts/en/PIC32MM0016GPL028)|16 kb| 4 kb|28|
|[PIC32MM0032GPL028](http://microchip.com/wwwproducts/en/PIC32MM0032GPL028)|33 kb| 8 kb|28|
|[PIC32MM0064GPL028](http://microchip.com/wwwproducts/en/PIC32MM0064GPL028)|66 kb| 8 kb|28|
|[PIC32MM0016GPL036](http://microchip.com/wwwproducts/en/PIC32MM0016GPL036)|16 kb| 4 kb|36/40|
|[PIC32MM0032GPL036](http://microchip.com/wwwproducts/en/PIC32MM0032GPL036)|33 kb| 8 kb|36/40|
|[PIC32MM0064GPL036](http://microchip.com/wwwproducts/en/PIC32MM0064GPL036)|66 kb| 8 kb|36/40|

### GPM devices

Same as GPD with 3 I2C, more memory and more pins.

|GPM Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MM0064GPM028](http://microchip.com/wwwproducts/en/PIC32MM0064GPM028)| 66 kb| 16 kb|28|
|[PIC32MM0128GPM028](http://microchip.com/wwwproducts/en/PIC32MM0128GPM028)|131 kb| 16 kb|28|
|[PIC32MM0256GPM028](http://microchip.com/wwwproducts/en/PIC32MM0256GPM028)|262 kb| 33 kb|28|
|[PIC32MM0064GPM036](http://microchip.com/wwwproducts/en/PIC32MM0064GPM036)| 66 kb| 16 kb|36/40|
|[PIC32MM0128GPM036](http://microchip.com/wwwproducts/en/PIC32MM0128GPM036)|131 kb| 16 kb|36/40|
|[PIC32MM0256GPM036](http://microchip.com/wwwproducts/en/PIC32MM0256GPM036)|262 kb| 33 kb|36/40|
|[PIC32MM0064GPM048](http://microchip.com/wwwproducts/en/PIC32MM0064GPM048)| 66 kb| 16 kb|48|
|[PIC32MM0128GPM048](http://microchip.com/wwwproducts/en/PIC32MM0128GPM048)|131 kb| 16 kb|48|
|[PIC32MM0256GPM048](http://microchip.com/wwwproducts/en/PIC32MM0256GPM048)|262 kb| 33 kb|48|
|[PIC32MM0064GPM064](http://microchip.com/wwwproducts/en/PIC32MM0064GPM064)| 66 kb| 16 kb|64|
|[PIC32MM0128GPM064](http://microchip.com/wwwproducts/en/PIC32MM0128GPM064)|131 kb| 16 kb|64|
|[PIC32MM0256GPM064](http://microchip.com/wwwproducts/en/PIC32MM0256GPM064)|262 kb| 33 kb|64|
