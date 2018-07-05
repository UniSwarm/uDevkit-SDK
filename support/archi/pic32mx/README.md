# PIC32MX support

PIC32MX family is the first [32 bits](../pic32/README.md) Microchip range.

This family is splitted into multiple subfamilies :

* MX1 / MX2: lower CPU power, USB on MX2xx, low pin count available
* MX3 / MX4: two CPU speed available (105 or 150DMIP)
* MX5: USB and CAN com, large memory
* MX6: USB and Ethernet com, large memory
* MX7: USB, 2 CAN and Ethernet com, large memory

## Main features

|Feature|MX1 / MX2|MX3 / MX4|MX5|MX6|MX7|
|-------|:-------:|:-------:|:-:|:-:|:-:|
|Core|32 bits|32 bits|32 bits|32 bits|32 bits|
|Performance|83 DMIPS|105-150 DMIPS|105 DMIPS|105 DMIPS|105 DMIPS|
|Program memory|16kb - 512kb|32kb - 512kb|64kb - 512kb|64kb - 512kb|128kb - 512kb|
|Data memory|4kb - 64kb|8kb - 128kb|16kb - 64kb|32kb - 128kb|32kb - 128kb|
|Pins|28-100|64-100|64-100|64-100|64-100|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|PIC32 MX1 / MX2 |      2-5|        5|        5|        5|        2|      2-4|        0|        0|        0|         0|         0|         0|         0|
|PIC32 MX3 / MX4 |      2-5|        5|        5|        5|        2|      1-2|        0|        0|        0|         0|         0|         0|         0|
|PIC32 MX5       |      5-6|        5|        5|        5|        2|      3-4|        1|        0|        0|         0|         0|         0|         0|
|PIC32 MX6       |        6|        5|        5|        5|      4-5|      3-4|        0|        0|        0|         0|         0|         0|         0|
|PIC32 MX7       |        6|        5|        5|        5|      4-5|      3-4|      1-2|        0|        0|         0|         0|         0|         0|

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

128 devices on July 2018.

### MX1 / MX2 devices

|MX1 / MX2 Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MX210F016B](http://microchip.com/wwwproducts/en/PIC32MX210F016B) |  16 kb|   4 kb| 28|
|[PIC32MX110F016B](http://microchip.com/wwwproducts/en/PIC32MX110F016B) |  16 kb|   4 kb| 28|
|[PIC32MX120F032B](http://microchip.com/wwwproducts/en/PIC32MX120F032B) |  33 kb|   8 kb| 28|
|[PIC32MX220F032B](http://microchip.com/wwwproducts/en/PIC32MX220F032B) |  33 kb|   8 kb| 28|
|[PIC32MX230F064B](http://microchip.com/wwwproducts/en/PIC32MX230F064B) |  66 kb|  16 kb| 28|
|[PIC32MX130F064B](http://microchip.com/wwwproducts/en/PIC32MX130F064B) |  66 kb|  16 kb| 28|
|[PIC32MX150F128B](http://microchip.com/wwwproducts/en/PIC32MX150F128B) | 131 kb|  33 kb| 28|
|[PIC32MX250F128B](http://microchip.com/wwwproducts/en/PIC32MX250F128B) | 131 kb|  33 kb| 28|
|[PIC32MX130F256B](http://microchip.com/wwwproducts/en/PIC32MX130F256B) | 262 kb|  16 kb| 28|
|[PIC32MX230F256B](http://microchip.com/wwwproducts/en/PIC32MX230F256B) | 262 kb|  16 kb| 28|
|[PIC32MX170F256B](http://microchip.com/wwwproducts/en/PIC32MX170F256B) | 262 kb|  66 kb| 28|
|[PIC32MX270F256B](http://microchip.com/wwwproducts/en/PIC32MX270F256B) | 262 kb|  66 kb| 28|
|[PIC32MX155F128B](http://microchip.com/wwwproducts/en/PIC32MX155F128B) | 131 kb|  33 kb| 28|
|[PIC32MX154F128B](http://microchip.com/wwwproducts/en/PIC32MX154F128B) | 131 kb|  33 kb| 28|
|[PIC32MX254F128B](http://microchip.com/wwwproducts/en/PIC32MX254F128B) | 131 kb|  33 kb| 28|
|[PIC32MX255F128B](http://microchip.com/wwwproducts/en/PIC32MX255F128B) | 131 kb|  33 kb| 28|
|[PIC32MX275F256B](http://microchip.com/wwwproducts/en/PIC32MX275F256B) | 262 kb|  66 kb| 28|
|[PIC32MX175F256B](http://microchip.com/wwwproducts/en/PIC32MX175F256B) | 262 kb|  66 kb| 28|
|[PIC32MX274F256B](http://microchip.com/wwwproducts/en/PIC32MX274F256B) | 262 kb|  66 kb| 28|
|[PIC32MX174F256B](http://microchip.com/wwwproducts/en/PIC32MX174F256B) | 262 kb|  66 kb| 28|
|[PIC32MX210F016C](http://microchip.com/wwwproducts/en/PIC32MX210F016C) |  16 kb|   4 kb| 40|
|[PIC32MX110F016C](http://microchip.com/wwwproducts/en/PIC32MX110F016C) |  16 kb|   4 kb| 40|
|[PIC32MX120F032C](http://microchip.com/wwwproducts/en/PIC32MX120F032C) |  33 kb|   8 kb| 40|
|[PIC32MX220F032C](http://microchip.com/wwwproducts/en/PIC32MX220F032C) |  33 kb|   8 kb| 40|
|[PIC32MX230F064C](http://microchip.com/wwwproducts/en/PIC32MX230F064C) |  66 kb|  16 kb| 40|
|[PIC32MX130F064C](http://microchip.com/wwwproducts/en/PIC32MX130F064C) |  66 kb|  16 kb| 40|
|[PIC32MX250F128C](http://microchip.com/wwwproducts/en/PIC32MX250F128C) | 131 kb|  33 kb| 40|
|[PIC32MX150F128C](http://microchip.com/wwwproducts/en/PIC32MX150F128C) | 131 kb|  33 kb| 40|
|[PIC32MX210F016D](http://microchip.com/wwwproducts/en/PIC32MX210F016D) |  16 kb|   4 kb| 44|
|[PIC32MX110F016D](http://microchip.com/wwwproducts/en/PIC32MX110F016D) |  16 kb|   4 kb| 44|
|[PIC32MX220F032D](http://microchip.com/wwwproducts/en/PIC32MX220F032D) |  33 kb|   8 kb| 44|
|[PIC32MX120F032D](http://microchip.com/wwwproducts/en/PIC32MX120F032D) |  33 kb|   8 kb| 44|
|[PIC32MX130F064D](http://microchip.com/wwwproducts/en/PIC32MX130F064D) |  66 kb|  16 kb| 44|
|[PIC32MX230F064D](http://microchip.com/wwwproducts/en/PIC32MX230F064D) |  66 kb|  16 kb| 44|
|[PIC32MX155F128D](http://microchip.com/wwwproducts/en/PIC32MX155F128D) | 131 kb|  33 kb| 44|
|[PIC32MX250F128D](http://microchip.com/wwwproducts/en/PIC32MX250F128D) | 131 kb|  33 kb| 44|
|[PIC32MX150F128D](http://microchip.com/wwwproducts/en/PIC32MX150F128D) | 131 kb|  33 kb| 44|
|[PIC32MX255F128D](http://microchip.com/wwwproducts/en/PIC32MX255F128D) | 131 kb|  33 kb| 44|
|[PIC32MX154F128D](http://microchip.com/wwwproducts/en/PIC32MX154F128D) | 131 kb|  33 kb| 44|
|[PIC32MX254F128D](http://microchip.com/wwwproducts/en/PIC32MX254F128D) | 131 kb|  33 kb| 44|
|[PIC32MX130F256D](http://microchip.com/wwwproducts/en/PIC32MX130F256D) | 262 kb|  16 kb| 44|
|[PIC32MX230F256D](http://microchip.com/wwwproducts/en/PIC32MX230F256D) | 262 kb|  16 kb| 44|
|[PIC32MX175F256D](http://microchip.com/wwwproducts/en/PIC32MX175F256D) | 262 kb|  66 kb| 44|
|[PIC32MX274F256D](http://microchip.com/wwwproducts/en/PIC32MX274F256D) | 262 kb|  66 kb| 44|
|[PIC32MX174F256D](http://microchip.com/wwwproducts/en/PIC32MX174F256D) | 262 kb|  66 kb| 44|
|[PIC32MX170F256D](http://microchip.com/wwwproducts/en/PIC32MX170F256D) | 262 kb|  66 kb| 44|
|[PIC32MX275F256D](http://microchip.com/wwwproducts/en/PIC32MX275F256D) | 262 kb|  66 kb| 44|
|[PIC32MX270F256D](http://microchip.com/wwwproducts/en/PIC32MX270F256D) | 262 kb|  66 kb| 44|
|[PIC32MX120F064H](http://microchip.com/wwwproducts/en/PIC32MX120F064H) |  66 kb|   8 kb| 64|
|[PIC32MX130F128H](http://microchip.com/wwwproducts/en/PIC32MX130F128H) | 131 kb|  16 kb| 64|
|[PIC32MX230F128H](http://microchip.com/wwwproducts/en/PIC32MX230F128H) | 131 kb|  16 kb| 64|
|[PIC32MX250F256H](http://microchip.com/wwwproducts/en/PIC32MX250F256H) | 262 kb|  33 kb| 64|
|[PIC32MX150F256H](http://microchip.com/wwwproducts/en/PIC32MX150F256H) | 262 kb|  33 kb| 64|
|[PIC32MX270F512H](http://microchip.com/wwwproducts/en/PIC32MX270F512H) | 524 kb|  66 kb| 64|
|[PIC32MX170F512H](http://microchip.com/wwwproducts/en/PIC32MX170F512H) | 524 kb|  66 kb| 64|
|[PIC32MX130F128L](http://microchip.com/wwwproducts/en/PIC32MX130F128L) | 131 kb|  16 kb|100|
|[PIC32MX230F128L](http://microchip.com/wwwproducts/en/PIC32MX230F128L) | 131 kb|  16 kb|100|
|[PIC32MX250F256L](http://microchip.com/wwwproducts/en/PIC32MX250F256L) | 262 kb|  33 kb|100|
|[PIC32MX150F256L](http://microchip.com/wwwproducts/en/PIC32MX150F256L) | 262 kb|  33 kb|100|
|[PIC32MX170F512L](http://microchip.com/wwwproducts/en/PIC32MX170F512L) | 524 kb|  66 kb|100|
|[PIC32MX270F512L](http://microchip.com/wwwproducts/en/PIC32MX270F512L) | 524 kb|  66 kb|100|

### MX3 / MX4 devices

|MX3 / MX4 Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MX320F032H](http://microchip.com/wwwproducts/en/PIC32MX320F032H)|  33 kb|   8 kb| 64|
|[PIC32MX420F032H](http://microchip.com/wwwproducts/en/PIC32MX420F032H)|  33 kb|   8 kb| 64|
|[PIC32MX320F064H](http://microchip.com/wwwproducts/en/PIC32MX320F064H)|  66 kb|  16 kb| 64|
|[PIC32MX430F064H](http://microchip.com/wwwproducts/en/PIC32MX430F064H)|  66 kb|  16 kb| 64|
|[PIC32MX330F064H](http://microchip.com/wwwproducts/en/PIC32MX330F064H)|  66 kb|  16 kb| 64|
|[PIC32MX320F128H](http://microchip.com/wwwproducts/en/PIC32MX320F128H)| 131 kb|  16 kb| 64|
|[PIC32MX440F128H](http://microchip.com/wwwproducts/en/PIC32MX440F128H)| 131 kb|  33 kb| 64|
|[PIC32MX340F128H](http://microchip.com/wwwproducts/en/PIC32MX340F128H)| 131 kb|  33 kb| 64|
|[PIC32MX450F128H](http://microchip.com/wwwproducts/en/PIC32MX450F128H)| 131 kb|  33 kb| 64|
|[PIC32MX350F128H](http://microchip.com/wwwproducts/en/PIC32MX350F128H)| 131 kb|  33 kb| 64|
|[PIC32MX340F256H](http://microchip.com/wwwproducts/en/PIC32MX340F256H)| 262 kb|  33 kb| 64|
|[PIC32MX440F256H](http://microchip.com/wwwproducts/en/PIC32MX440F256H)| 262 kb|  33 kb| 64|
|[PIC32MX450F256H](http://microchip.com/wwwproducts/en/PIC32MX450F256H)| 262 kb|  66 kb| 64|
|[PIC32MX350F256H](http://microchip.com/wwwproducts/en/PIC32MX350F256H)| 262 kb|  66 kb| 64|
|[PIC32MX440F512H](http://microchip.com/wwwproducts/en/PIC32MX440F512H)| 524 kb|  33 kb| 64|
|[PIC32MX340F512H](http://microchip.com/wwwproducts/en/PIC32MX340F512H)| 524 kb|  33 kb| 64|
|[PIC32MX370F512H](http://microchip.com/wwwproducts/en/PIC32MX370F512H)| 524 kb| 131 kb| 64|
|[PIC32MX470F512H](http://microchip.com/wwwproducts/en/PIC32MX470F512H)| 524 kb| 131 kb| 64|
|[PIC32MX320F128L](http://microchip.com/wwwproducts/en/PIC32MX320F128L)| 131 kb|  16 kb|100|
|[PIC32MX440F128L](http://microchip.com/wwwproducts/en/PIC32MX440F128L)| 131 kb|  33 kb|100|
|[PIC32MX340F128L](http://microchip.com/wwwproducts/en/PIC32MX340F128L)| 131 kb|  33 kb|100|
|[PIC32MX360F256L](http://microchip.com/wwwproducts/en/PIC32MX360F256L)| 262 kb|  33 kb|100|
|[PIC32MX460F256L](http://microchip.com/wwwproducts/en/PIC32MX460F256L)| 262 kb|  33 kb|100|
|[PIC32MX360F512L](http://microchip.com/wwwproducts/en/PIC32MX360F512L)| 524 kb|  33 kb|100|
|[PIC32MX460F512L](http://microchip.com/wwwproducts/en/PIC32MX460F512L)| 524 kb|  33 kb|100|
|[PIC32MX330F064L](http://microchip.com/wwwproducts/en/PIC32MX330F064L)|  66 kb|  16 kb|100|
|[PIC32MX430F064L](http://microchip.com/wwwproducts/en/PIC32MX430F064L)|  66 kb|  16 kb|100|
|[PIC32MX450F128L](http://microchip.com/wwwproducts/en/PIC32MX450F128L)| 131 kb|  33 kb|100|
|[PIC32MX350F128L](http://microchip.com/wwwproducts/en/PIC32MX350F128L)| 131 kb|  33 kb|100|
|[PIC32MX450F256L](http://microchip.com/wwwproducts/en/PIC32MX450F256L)| 262 kb|  66 kb|100|
|[PIC32MX350F256L](http://microchip.com/wwwproducts/en/PIC32MX350F256L)| 262 kb|  66 kb|100|
|[PIC32MX370F512L](http://microchip.com/wwwproducts/en/PIC32MX370F512L)| 524 kb| 131 kb|100|
|[PIC32MX470F512L](http://microchip.com/wwwproducts/en/PIC32MX470F512L)| 524 kb| 131 kb|100|
### MX5 devices

|MX5 Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MX534F064H](http://microchip.com/wwwproducts/en/PIC32MX534F064H)|  66 kb|  16 kb| 64|
|[PIC32MX564F064H](http://microchip.com/wwwproducts/en/PIC32MX564F064H)|  66 kb|  33 kb| 64|
|[PIC32MX530F128H](http://microchip.com/wwwproducts/en/PIC32MX530F128H)| 131 kb|  16 kb| 64|
|[PIC32MX564F128H](http://microchip.com/wwwproducts/en/PIC32MX564F128H)| 131 kb|  33 kb| 64|
|[PIC32MX550F256H](http://microchip.com/wwwproducts/en/PIC32MX550F256H)| 262 kb|  33 kb| 64|
|[PIC32MX575F256H](http://microchip.com/wwwproducts/en/PIC32MX575F256H)| 262 kb|  66 kb| 64|
|[PIC32MX575F512H](http://microchip.com/wwwproducts/en/PIC32MX575F512H)| 524 kb|  66 kb| 64|
|[PIC32MX570F512H](http://microchip.com/wwwproducts/en/PIC32MX570F512H)| 524 kb|  66 kb| 64|
|[PIC32MX530F128L](http://microchip.com/wwwproducts/en/PIC32MX530F128L)| 131 kb|  16 kb|100|
|[PIC32MX550F256L](http://microchip.com/wwwproducts/en/PIC32MX550F256L)| 262 kb|  33 kb|100|
|[PIC32MX570F512L](http://microchip.com/wwwproducts/en/PIC32MX570F512L)| 524 kb|  66 kb|100|
|[PIC32MX534F064L](http://microchip.com/wwwproducts/en/PIC32MX534F064L)|  66 kb|  16 kb|100|
|[PIC32MX564F064L](http://microchip.com/wwwproducts/en/PIC32MX564F064L)|  66 kb|  33 kb|100|
|[PIC32MX564F128L](http://microchip.com/wwwproducts/en/PIC32MX564F128L)| 131 kb|  33 kb|100|
|[PIC32MX575F256L](http://microchip.com/wwwproducts/en/PIC32MX575F256L)| 262 kb|  66 kb|100|
|[PIC32MX575F512L](http://microchip.com/wwwproducts/en/PIC32MX575F512L)| 524 kb|  66 kb|100|

### MX6 devices

|MX6 Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MX664F064H](http://microchip.com/wwwproducts/en/PIC32MX664F064H)|  66 kb|  33 kb| 64|
|[PIC32MX664F128H](http://microchip.com/wwwproducts/en/PIC32MX664F128H)| 131 kb|  33 kb| 64|
|[PIC32MX675F256H](http://microchip.com/wwwproducts/en/PIC32MX675F256H)| 262 kb|  66 kb| 64|
|[PIC32MX675F512H](http://microchip.com/wwwproducts/en/PIC32MX675F512H)| 524 kb|  66 kb| 64|
|[PIC32MX695F512H](http://microchip.com/wwwproducts/en/PIC32MX695F512H)| 524 kb| 131 kb| 64|
|[PIC32MX664F064L](http://microchip.com/wwwproducts/en/PIC32MX664F064L)|  66 kb|  33 kb|100|
|[PIC32MX664F128L](http://microchip.com/wwwproducts/en/PIC32MX664F128L)| 131 kb|  33 kb|100|
|[PIC32MX675F256L](http://microchip.com/wwwproducts/en/PIC32MX675F256L)| 262 kb|  66 kb|100|
|[PIC32MX675F512L](http://microchip.com/wwwproducts/en/PIC32MX675F512L)| 524 kb|  66 kb|100|
|[PIC32MX695F512L](http://microchip.com/wwwproducts/en/PIC32MX695F512L)| 524 kb| 131 kb|100|


### MX7 devices

|MX7 Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[PIC32MX764F128H](http://microchip.com/wwwproducts/en/PIC32MX764F128H)| 131 kb|  33 kb| 64|
|[PIC32MX775F256H](http://microchip.com/wwwproducts/en/PIC32MX775F256H)| 262 kb|  66 kb| 64|
|[PIC32MX775F512H](http://microchip.com/wwwproducts/en/PIC32MX775F512H)| 524 kb|  66 kb| 64|
|[PIC32MX795F512H](http://microchip.com/wwwproducts/en/PIC32MX795F512H)| 524 kb| 131 kb| 64|
|[PIC32MX764F128L](http://microchip.com/wwwproducts/en/PIC32MX764F128L)| 131 kb|  33 kb|100|
|[PIC32MX775F256L](http://microchip.com/wwwproducts/en/PIC32MX775F256L)| 262 kb|  66 kb|100|
|[PIC32MX775F512L](http://microchip.com/wwwproducts/en/PIC32MX775F512L)| 524 kb|  66 kb|100|
|[PIC32MX795F512L](http://microchip.com/wwwproducts/en/PIC32MX795F512L)| 524 kb| 131 kb|100|
