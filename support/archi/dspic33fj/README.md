# dsPIC33FJ support

dsPIC33FJ family handle a lot of subfamilies with the same [16 bits](../pic16b/README.md) high performance core.
This range is oldest than [dsPIC33EP](../dspic33ep/README.md).

## Main features

|Feature       |MC10X / GP10X |GP             |MC            |GS            |
|--------------|:------------:|:-------------:|:------------:|:------------:|
|Performance   |16 DMIPS      |40 DMIPS       |40 DMIPS      |40 - 50 DMIPS |
|Program memory|16 kb - 33  kb|12 kb - 131 kb |12 kb - 131 kb|5 kb - 65 kb  |
|Data memory   |1 kb - 2 kb   |1 kb - 16 kb   |1 kb - 16 kb  |1 kb - 9 kb   |
|Pins          |18-44         |18-100         |20-100        |18-100        |

## Common devices

|Peripheral           |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:--------------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|GP10X                |        1|      3-5|        2|        3|        1|        1|        0|        0|        0|         0|         0|         0|         0|
|GP20X/GP30X          |      1-2|      3-9|      2-8|      4-8|      1-2|      1-2|        0|        0|        0|         0|         0|         0|         0|
|GP50X                |        2|        9|        8|        8|        2|        2|        1|        0|        0|         0|         0|         0|         0|
|GP70X                |        2|        9|        8|        8|        2|        2|        2|        0|        0|         0|         0|         0|         0|
|GP80X                |        2|        5|        4|        4|        1|        2|        1|        0|        0|         0|         0|         0|         0|
|**GS10X/GS20X/GS30X**|        1|        2|        1|      0-1|        1|        1|        0|        0|        0|         0|       2-3|         0|         0|
|**GS40X/GS50X**      |      1-2|      3-5|      2-4|      2-4|      1-2|      1-2|        0|        0|        0|       0-1|         6|         0|         0|
|**GS60X**            |        2|        5|        4|        4|        2|        2|      0-1|        0|        0|         2|         9|         0|         0|
|MC10X                |        1|      3-5|        2|        3|        1|        1|        0|        0|        0|         0|         2|         0|         0|
|MC20X/MC30X          |      1-2|      3-5|      2-4|        4|        1|      1-2|        0|        0|        0|       1-2|         4|         0|         0|
|MC5xx                |        2|        9|        8|        8|        2|        2|        1|        0|        0|         1|         2|         0|         0|
|MC7xx                |        2|        9|        8|        8|        2|        2|      1-2|        0|        0|         1|         2|         0|         0|
|MC8xx                |        2|        5|        4|        4|        1|        2|        1|        0|        0|         2|         4|         0|         0|

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

114 devices on January 2023.

### GP family

#### GP10X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ16GP101](http://microchip.com/wwwproducts/en/dsPIC33FJ16GP101) |  16 kb|   1 kb| 18|
|[dsPIC33FJ32GP101](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP101) |  33 kb|   2 kb| 18|
|[dsPIC33FJ16GP102](http://microchip.com/wwwproducts/en/dsPIC33FJ16GP102) |  16 kb|   1 kb| 28|
|[dsPIC33FJ32GP102](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP102) |  33 kb|   2 kb| 28|
|[dsPIC33FJ32GP104](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP104) |  33 kb|   2 kb| 28|

#### GP20X / GP30X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ12GP201](http://microchip.com/wwwproducts/en/dsPIC33FJ12GP201)     |  12 kb|   1 kb| 18|
|[dsPIC33FJ12GP202](http://microchip.com/wwwproducts/en/dsPIC33FJ12GP202)     |  12 kb|   1 kb| 28|
|[dsPIC33FJ32GP202](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP202)     |  33 kb|   2 kb| 28|
|[dsPIC33FJ32GP302](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP302)     |  33 kb|   4 kb| 28|
|[dsPIC33FJ64GP202](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP202)     |  65 kb|   8 kb| 28|
|[dsPIC33FJ128GP202](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP202)   | 131 kb|   8 kb| 28|
|[dsPIC33FJ16GP304](http://microchip.com/wwwproducts/en/dsPIC33FJ16GP304)     |  16 kb|   2 kb| 44|
|[dsPIC33FJ32GP204](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP204)     |  33 kb|   2 kb| 44|
|[dsPIC33FJ32GP304](http://microchip.com/wwwproducts/en/dsPIC33FJ32GP304)     |  33 kb|   4 kb| 44|
|[dsPIC33FJ64GP204](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP204)     |  65 kb|   8 kb| 44|
|[dsPIC33FJ128GP204](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP204)   | 131 kb|   8 kb| 44|
|[dsPIC33FJ64GP206A](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP206A)   |  65 kb|   8 kb| 64|
|[dsPIC33FJ64GP206](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP206)     |  65 kb|   8 kb| 64|
|[dsPIC33FJ64GP306](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP306)     |  65 kb|  16 kb| 64|
|[dsPIC33FJ64GP306A](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP306A)   |  65 kb|  16 kb| 64|
|[dsPIC33FJ128GP206](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP206)   | 131 kb|   8 kb| 64|
|[dsPIC33FJ128GP206A](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP206A) | 131 kb|   8 kb| 64|
|[dsPIC33FJ128GP306](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP306)   | 131 kb|  16 kb| 64|
|[dsPIC33FJ128GP306A](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP306A) | 131 kb|  16 kb| 64|
|[dsPIC33FJ64GP310](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP310)     |  65 kb|  16 kb|100|
|[dsPIC33FJ64GP310A](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP310A)   |  65 kb|  16 kb|100|
|[dsPIC33FJ128GP310](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP310)   | 131 kb|  16 kb|100|
|[dsPIC33FJ128GP310A](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP310A) | 131 kb|  16 kb|100|


#### GP50X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ256GP506](http://microchip.com/wwwproducts/en/dsPIC33FJ256GP506)   | 262 kb|  16 kb| 64|
|[dsPIC33FJ256GP506A](http://microchip.com/wwwproducts/en/dsPIC33FJ256GP506A) | 262 kb|  16 kb| 64|
|[dsPIC33FJ256GP510](http://microchip.com/wwwproducts/en/dsPIC33FJ256GP510)   | 262 kb|  16 kb|100|
|[dsPIC33FJ256GP510A](http://microchip.com/wwwproducts/en/dsPIC33FJ256GP510A) | 262 kb|  16 kb|100|

#### GP70X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ64GP706](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP706)     |  65 kb|  16 kb| 64|
|[dsPIC33FJ64GP706A](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP706A)   |  65 kb|  16 kb| 64|
|[dsPIC33FJ128GP706](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP706)   | 131 kb|  16 kb| 64|
|[dsPIC33FJ128GP706A](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP706A) | 131 kb|  16 kb| 64|
|[dsPIC33FJ64GP708](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP708)     |  65 kb|  16 kb| 80|
|[dsPIC33FJ64GP708A](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP708A)   |  65 kb|  16 kb| 80|
|[dsPIC33FJ128GP708](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP708)   | 131 kb|  16 kb| 80|
|[dsPIC33FJ128GP708A](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP708A) | 131 kb|  16 kb| 80|
|[dsPIC33FJ64GP710](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP710)     |  65 kb|  16 kb|100|
|[dsPIC33FJ64GP710A](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP710A)   |  65 kb|  16 kb|100|
|[dsPIC33FJ128GP710](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP710)   | 131 kb|  16 kb|100|
|[dsPIC33FJ128GP710A](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP710A) | 131 kb|  16 kb|100|
|[dsPIC33FJ256GP710](http://microchip.com/wwwproducts/en/dsPIC33FJ256GP710)   | 262 kb|  31 kb|100|
|[dsPIC33FJ256GP710A](http://microchip.com/wwwproducts/en/dsPIC33FJ256GP710A) | 262 kb|  31 kb|100|

#### GP80X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ64GP802](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP802)   |  65 kb|  16 kb| 28|
|[dsPIC33FJ128GP802](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP802) | 131 kb|  16 kb| 28|
|[dsPIC33FJ64GP804](http://microchip.com/wwwproducts/en/dsPIC33FJ64GP804)   |  65 kb|  16 kb| 44|
|[dsPIC33FJ128GP804](http://microchip.com/wwwproducts/en/dsPIC33FJ128GP804) | 131 kb|  16 kb| 44|

### GS family

#### GS10X / GS20X / GS30X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ06GS101A](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS101A) |   5 kb| 0.3 kb| 18|
|[dsPIC33FJ06GS101](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS101)   |   5 kb| 0.3 kb| 18|
|[dsPIC33FJ06GS001](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS001)   |   5 kb| 0.3 kb| 20|
|[dsPIC33FJ06GS102A](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS102A) |   5 kb| 0.3 kb| 28|
|[dsPIC33FJ06GS102](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS102)   |   5 kb| 0.3 kb| 28|
|[dsPIC33FJ06GS202](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS202)   |   5 kb|   1 kb| 28|
|[dsPIC33FJ09GS302](http://microchip.com/wwwproducts/en/dsPIC33FJ09GS302)   |   8 kb|   1 kb| 28|
|[dsPIC33FJ06GS202A](http://microchip.com/wwwproducts/en/dsPIC33FJ06GS202A) |   5 kb|   1 kb| 32|

#### GS40X / GS50X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ16GS402](http://microchip.com/wwwproducts/en/dsPIC33FJ16GS402) |  16 kb|   2 kb| 28|
|[dsPIC33FJ16GS502](http://microchip.com/wwwproducts/en/dsPIC33FJ16GS502) |  16 kb|   2 kb| 28|
|[dsPIC33FJ16GS404](http://microchip.com/wwwproducts/en/dsPIC33FJ16GS404) |  16 kb|   2 kb| 44|
|[dsPIC33FJ16GS504](http://microchip.com/wwwproducts/en/dsPIC33FJ16GS504) |  16 kb|   2 kb| 44|
|[dsPIC33FJ32GS406](http://microchip.com/wwwproducts/en/dsPIC33FJ32GS406) |  33 kb|   4 kb| 64|
|[dsPIC33FJ64GS406](http://microchip.com/wwwproducts/en/dsPIC33FJ64GS406) |  65 kb|   8 kb| 64|

#### GS60X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ32GS606](http://microchip.com/wwwproducts/en/dsPIC33FJ32GS606) |  33 kb|   4 kb| 64|
|[dsPIC33FJ64GS606](http://microchip.com/wwwproducts/en/dsPIC33FJ64GS606) |  65 kb|   9 kb| 64|
|[dsPIC33FJ32GS608](http://microchip.com/wwwproducts/en/dsPIC33FJ32GS608) |  33 kb|   4 kb| 80|
|[dsPIC33FJ64GS608](http://microchip.com/wwwproducts/en/dsPIC33FJ64GS608) |  65 kb|   9 kb| 80|
|[dsPIC33FJ32GS610](http://microchip.com/wwwproducts/en/dsPIC33FJ32GS610) |  33 kb|   4 kb|100|
|[dsPIC33FJ64GS610](http://microchip.com/wwwproducts/en/dsPIC33FJ64GS610) |  65 kb|   9 kb|100|

### MC family

#### MC10X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ16MC101](http://microchip.com/wwwproducts/en/dsPIC33FJ16MC101) |  16 kb|   1 kb| 20|
|[dsPIC33FJ32MC101](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC101) |  33 kb|   2 kb| 20|
|[dsPIC33FJ16MC102](http://microchip.com/wwwproducts/en/dsPIC33FJ16MC102) |  16 kb|   1 kb| 28|
|[dsPIC33FJ32MC102](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC102) |  33 kb|   2 kb| 28|
|[dsPIC33FJ32MC104](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC104) |  33 kb|   2 kb| 44|

#### MC20X / MC30X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ12MC201](http://microchip.com/wwwproducts/en/dsPIC33FJ12MC201)   |  12 kb|   1 kb| 20|
|[dsPIC33FJ12MC202](http://microchip.com/wwwproducts/en/dsPIC33FJ12MC202)   |  12 kb|   1 kb| 28|
|[dsPIC33FJ32MC202](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC202)   |  33 kb|   2 kb| 28|
|[dsPIC33FJ32MC302](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC302)   |  33 kb|   4 kb| 28|
|[dsPIC33FJ64MC202](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC202)   |  65 kb|   8 kb| 28|
|[dsPIC33FJ128MC202](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC202) | 131 kb|   8 kb| 28|
|[dsPIC33FJ16MC304](http://microchip.com/wwwproducts/en/dsPIC33FJ16MC304)   |  16 kb|   2 kb| 44|
|[dsPIC33FJ32MC204](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC204)   |  33 kb|   2 kb| 44|
|[dsPIC33FJ32MC304](http://microchip.com/wwwproducts/en/dsPIC33FJ32MC304)   |  33 kb|   4 kb| 44|
|[dsPIC33FJ64MC204](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC204)   |  65 kb|   8 kb| 44|
|[dsPIC33FJ128MC204](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC204) | 131 kb|   8 kb| 44|

#### MC50X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ64MC506A](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC506A)   |  65 kb|   8 kb| 64|
|[dsPIC33FJ64MC506](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC506)     |  65 kb|   8 kb| 64|
|[dsPIC33FJ128MC506](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC506)   | 131 kb|   8 kb| 64|
|[dsPIC33FJ128MC506A](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC506A) | 131 kb|   8 kb| 64|
|[dsPIC33FJ64MC508](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC508)     |  65 kb|   8 kb| 80|
|[dsPIC33FJ64MC508A](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC508A)   |  65 kb|   8 kb| 80|
|[dsPIC33FJ64MC510](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC510)     |  65 kb|   8 kb|100|
|[dsPIC33FJ64MC510A](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC510A)   |  65 kb|   8 kb|100|
|[dsPIC33FJ128MC510](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC510)   | 131 kb|   8 kb|100|
|[dsPIC33FJ128MC510A](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC510A) | 131 kb|   8 kb|100|
|[dsPIC33FJ256MC510](http://microchip.com/wwwproducts/en/dsPIC33FJ256MC510)   | 262 kb|  16 kb|100|
|[dsPIC33FJ256MC510A](http://microchip.com/wwwproducts/en/dsPIC33FJ256MC510A) | 262 kb|  16 kb|100|

#### MC70X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ64MC706A](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC706A)   |  65 kb|  16 kb| 64|
|[dsPIC33FJ64MC706](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC706)     |  65 kb|  16 kb| 64|
|[dsPIC33FJ128MC706](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC706)   | 131 kb|  16 kb| 64|
|[dsPIC33FJ128MC706A](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC706A) | 131 kb|  16 kb| 64|
|[dsPIC33FJ128MC708](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC708)   | 131 kb|  16 kb| 80|
|[dsPIC33FJ128MC708A](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC708A) | 131 kb|  16 kb| 80|
|[dsPIC33FJ64MC710](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC710)     |  65 kb|  16 kb|100|
|[dsPIC33FJ64MC710A](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC710A)   |  65 kb|  16 kb|100|
|[dsPIC33FJ128MC710](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC710)   | 131 kb|  16 kb|100|
|[dsPIC33FJ128MC710A](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC710A) | 131 kb|  16 kb|100|
|[dsPIC33FJ256MC710](http://microchip.com/wwwproducts/en/dsPIC33FJ256MC710)   | 262 kb|  31 kb|100|
|[dsPIC33FJ256MC710A](http://microchip.com/wwwproducts/en/dsPIC33FJ256MC710A) | 262 kb|  31 kb|100|

#### MC80X

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33FJ64MC802](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC802)   |  65 kb|  16 kb| 28|
|[dsPIC33FJ128MC802](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC802) | 131 kb|  16 kb| 28|
|[dsPIC33FJ64MC804](http://microchip.com/wwwproducts/en/dsPIC33FJ64MC804)   |  65 kb|  16 kb| 44|
|[dsPIC33FJ128MC804](http://microchip.com/wwwproducts/en/dsPIC33FJ128MC804) | 131 kb|  16 kb| 44|
