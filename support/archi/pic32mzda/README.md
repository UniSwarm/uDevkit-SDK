# PIC32MZ DA support

PIC32MZ DA family is a high-performance [32 bits](../pic32/README.md) range with MMU, MPU and GPU designed for user graphic interface applications.
It can embed up to 32Mb of internal memory or offer an interface for an external 128Mb DDR2.
Compared to MZ EF/EC family, MZ DA add DDR memory, LCD controller, 2D graphic accelerator and SDIO interface.
An hardware crypto module is optionally available.

## Main features

|Feature|MZ DA|
|-------|---|
|Core|32 bits|
|Performance|330 DMIPS|
|Program memory|1024kb - 2048kb|
|Data memory|256kb - 640kb|
|Pins|169-288|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|PIC32MZ DA      |        6|        9|        9|        9|        5|        6|        2|        0|        0|         0|         0|         0|         0|

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

40 devices on december 2017.

### Devices without DDR

|Compatible devices|Program|Data|Pins|Crypto module|
|---------|--:|--:|--:|--:|
|[PIC32MZ1025DAA169](http://microchip.com/wwwproducts/en/PIC32MZ1025DAA169)|1049 kb| 262 kb|169| |
|[PIC32MZ1025DAB169](http://microchip.com/wwwproducts/en/PIC32MZ1025DAB169)|1049 kb| 262 kb|169|Y|
|[PIC32MZ1064DAA169](http://microchip.com/wwwproducts/en/PIC32MZ1064DAA169)|1049 kb| 655 kb|169| |
|[PIC32MZ1064DAB169](http://microchip.com/wwwproducts/en/PIC32MZ1064DAB169)|1049 kb| 655 kb|169|Y|
|[PIC32MZ2025DAA169](http://microchip.com/wwwproducts/en/PIC32MZ2025DAA169)|2097 kb| 262 kb|169| |
|[PIC32MZ2025DAB169](http://microchip.com/wwwproducts/en/PIC32MZ2025DAB169)|2097 kb| 262 kb|169|Y|
|[PIC32MZ2064DAA169](http://microchip.com/wwwproducts/en/PIC32MZ2064DAA169)|2097 kb| 655 kb|169| |
|[PIC32MZ2064DAB169](http://microchip.com/wwwproducts/en/PIC32MZ2064DAB169)|2097 kb| 655 kb|169|Y|
|[PIC32MZ1025DAA176](http://microchip.com/wwwproducts/en/PIC32MZ1025DAA176)|1049 kb| 262 kb|176| |
|[PIC32MZ1025DAB176](http://microchip.com/wwwproducts/en/PIC32MZ1025DAB176)|1049 kb| 262 kb|176|Y|
|[PIC32MZ1064DAA176](http://microchip.com/wwwproducts/en/PIC32MZ1064DAA176)|1049 kb| 655 kb|176| |
|[PIC32MZ1064DAB176](http://microchip.com/wwwproducts/en/PIC32MZ1064DAB176)|1049 kb| 655 kb|176|Y|
|[PIC32MZ2025DAA176](http://microchip.com/wwwproducts/en/PIC32MZ2025DAA176)|2097 kb| 262 kb|176| |
|[PIC32MZ2025DAB176](http://microchip.com/wwwproducts/en/PIC32MZ2025DAB176)|2097 kb| 262 kb|176|Y|
|[PIC32MZ2064DAA176](http://microchip.com/wwwproducts/en/PIC32MZ2064DAA176)|2097 kb| 655 kb|176| |
|[PIC32MZ2064DAB176](http://microchip.com/wwwproducts/en/PIC32MZ2064DAB176)|2097 kb| 655 kb|176|Y|

### Devices with external DDR interface

External DDR2 interface up to 128MB.

|Compatible devices|Program|Data|Pins|Crypto module|
|---------|--:|--:|--:|--:|
|[PIC32MZ1025DAA288](http://microchip.com/wwwproducts/en/PIC32MZ1025DAA288)|1049 kb| 262 kb|288| |
|[PIC32MZ1025DAB288](http://microchip.com/wwwproducts/en/PIC32MZ1025DAB288)|1049 kb| 262 kb|288|Y|
|[PIC32MZ1064DAA288](http://microchip.com/wwwproducts/en/PIC32MZ1064DAA288)|1049 kb| 655 kb|288| |
|[PIC32MZ1064DAB288](http://microchip.com/wwwproducts/en/PIC32MZ1064DAB288)|1049 kb| 655 kb|288|Y|
|[PIC32MZ2025DAA288](http://microchip.com/wwwproducts/en/PIC32MZ2025DAA288)|2097 kb| 262 kb|288| |
|[PIC32MZ2025DAB288](http://microchip.com/wwwproducts/en/PIC32MZ2025DAB288)|2097 kb| 262 kb|288|Y|
|[PIC32MZ2064DAA288](http://microchip.com/wwwproducts/en/PIC32MZ2064DAA288)|2097 kb| 655 kb|288| |
|[PIC32MZ2064DAB288](http://microchip.com/wwwproducts/en/PIC32MZ2064DAB288)|2097 kb| 655 kb|288|Y|

### Devices with internal DDR

Internal stacked 32MB DDR2.

|Compatible devices|Program|Data|Pins|Crypto module|
|---------|--:|--:|--:|--:|
|[PIC32MZ1025DAG169](http://microchip.com/wwwproducts/en/PIC32MZ1025DAG169)|1049 kb| 262 kb|169| |
|[PIC32MZ1025DAH169](http://microchip.com/wwwproducts/en/PIC32MZ1025DAH169)|1049 kb| 262 kb|169|Y|
|[PIC32MZ1064DAG169](http://microchip.com/wwwproducts/en/PIC32MZ1064DAG169)|1049 kb| 655 kb|169| |
|[PIC32MZ1064DAH169](http://microchip.com/wwwproducts/en/PIC32MZ1064DAH169)|1049 kb| 655 kb|169|Y|
|[PIC32MZ2025DAG169](http://microchip.com/wwwproducts/en/PIC32MZ2025DAG169)|2097 kb| 262 kb|169| |
|[PIC32MZ2025DAH169](http://microchip.com/wwwproducts/en/PIC32MZ2025DAH169)|2097 kb| 262 kb|169|Y|
|[PIC32MZ2064DAG169](http://microchip.com/wwwproducts/en/PIC32MZ2064DAG169)|2097 kb| 655 kb|169| |
|[PIC32MZ2064DAH169](http://microchip.com/wwwproducts/en/PIC32MZ2064DAH169)|2097 kb| 655 kb|169|Y|
|[PIC32MZ1025DAG176](http://microchip.com/wwwproducts/en/PIC32MZ1025DAG176)|1049 kb| 262 kb|176| |
|[PIC32MZ1025DAH176](http://microchip.com/wwwproducts/en/PIC32MZ1025DAH176)|1049 kb| 262 kb|176|Y|
|[PIC32MZ1064DAG176](http://microchip.com/wwwproducts/en/PIC32MZ1064DAG176)|1049 kb| 655 kb|176| |
|[PIC32MZ1064DAH176](http://microchip.com/wwwproducts/en/PIC32MZ1064DAH176)|1049 kb| 655 kb|176|Y|
|[PIC32MZ2025DAG176](http://microchip.com/wwwproducts/en/PIC32MZ2025DAG176)|2097 kb| 262 kb|176| |
|[PIC32MZ2025DAH176](http://microchip.com/wwwproducts/en/PIC32MZ2025DAH176)|2097 kb| 262 kb|176|Y|
|[PIC32MZ2064DAG176](http://microchip.com/wwwproducts/en/PIC32MZ2064DAG176)|2097 kb| 655 kb|176| |
|[PIC32MZ2064DAH176](http://microchip.com/wwwproducts/en/PIC32MZ2064DAH176)|2097 kb| 655 kb|176|Y|
