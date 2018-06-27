# dsPIC33EV support

dsPIC33EV family is a robustified version of [dsPIC33EP](../dspic33ep/README.md) with
4.5V to 5.5V power and large range of temperature operation (up to 150°C).

## Main features

|Feature|dsPIC33EV|
|-------|:---:|
|Performance|70 DMIPS|
|Program memory|33 kb - 262 kb|
|Data memory|4 kb - 16 kb|
|Pins|28-64|

## Common devices

|Peripheral      |[UART][1]|[TMR][2] |[OC][3]  |[IC][4]  |[I2C][5] |[SPI][6] |[CAN][7] |[SENT][8]|[CLC][9] |[QEI][10] |[PWM][11] |[MCCP][12]|[SCCP][12]|
|:---------------|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|--------:|---------:|---------:|---------:|---------:|
|GM00X           |        2|        5|        4|        4|        1|        2|        0|        2|        0|         0|         3|         0|         0|
|GM10X           |        2|        5|        4|        4|        1|        2|        1|        2|        0|         0|         3|         0|         0|

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

32 devices on february 2018.

### GM00X subfamily

Base device.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EV32GM002](http://microchip.com/wwwproducts/en/dsPIC33EV32GM002)  |  33 kb|   4 kb| 28|
|[dsPIC33EV64GM002](http://microchip.com/wwwproducts/en/dsPIC33EV64GM002)  |  65 kb|   8 kb| 28|
|[dsPIC33EV128GM002](http://microchip.com/wwwproducts/en/dsPIC33EV128GM002)| 131 kb|   8 kb| 28|
|[dsPIC33EV256GM002](http://microchip.com/wwwproducts/en/dsPIC33EV256GM002)| 262 kb|  16 kb| 28|
|[dsPIC33EV32GM003](http://microchip.com/wwwproducts/en/dsPIC33EV32GM003)  |  33 kb|   4 kb| 40|
|[dsPIC33EV64GM003](http://microchip.com/wwwproducts/en/dsPIC33EV64GM003)  |  65 kb|   8 kb| 40|
|[dsPIC33EV128GM003](http://microchip.com/wwwproducts/en/dsPIC33EV128GM003)| 131 kb|   8 kb| 40|
|[dsPIC33EV256GM003](http://microchip.com/wwwproducts/en/dsPIC33EV256GM003)| 262 kb|  16 kb| 40|
|[dsPIC33EV32GM004](http://microchip.com/wwwproducts/en/dsPIC33EV32GM004)  |  33 kb|   4 kb| 44|
|[dsPIC33EV64GM004](http://microchip.com/wwwproducts/en/dsPIC33EV64GM004)  |  65 kb|   8 kb| 44|
|[dsPIC33EV128GM004](http://microchip.com/wwwproducts/en/dsPIC33EV128GM004)| 131 kb|   8 kb| 44|
|[dsPIC33EV256GM004](http://microchip.com/wwwproducts/en/dsPIC33EV256GM004)| 262 kb|  16 kb| 44|
|[dsPIC33EV32GM006](http://microchip.com/wwwproducts/en/dsPIC33EV32GM006)  |  33 kb|   4 kb| 64|
|[dsPIC33EV64GM006](http://microchip.com/wwwproducts/en/dsPIC33EV64GM006)  |  65 kb|   8 kb| 64|
|[dsPIC33EV128GM006](http://microchip.com/wwwproducts/en/dsPIC33EV128GM006)| 131 kb|   8 kb| 64|
|[dsPIC33EV256GM006](http://microchip.com/wwwproducts/en/dsPIC33EV256GM006)| 262 kb|  16 kb| 64|


### GM10X subfamily

Base device plus CAN peripheral.

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EV32GM102](http://microchip.com/wwwproducts/en/dsPIC33EV32GM102)  |  33 kb|   4 kb| 28|
|[dsPIC33EV64GM102](http://microchip.com/wwwproducts/en/dsPIC33EV64GM102)  |  65 kb|   8 kb| 28|
|[dsPIC33EV128GM102](http://microchip.com/wwwproducts/en/dsPIC33EV128GM102)| 131 kb|   8 kb| 28|
|[dsPIC33EV256GM102](http://microchip.com/wwwproducts/en/dsPIC33EV256GM102)| 262 kb|  16 kb| 28|
|[dsPIC33EV32GM103](http://microchip.com/wwwproducts/en/dsPIC33EV32GM103)  |  33 kb|   4 kb| 40|
|[dsPIC33EV64GM103](http://microchip.com/wwwproducts/en/dsPIC33EV64GM103)  |  65 kb|   8 kb| 40|
|[dsPIC33EV128GM103](http://microchip.com/wwwproducts/en/dsPIC33EV128GM103)| 131 kb|   8 kb| 40|
|[dsPIC33EV256GM103](http://microchip.com/wwwproducts/en/dsPIC33EV256GM103)| 262 kb|  16 kb| 40|
|[dsPIC33EV32GM104](http://microchip.com/wwwproducts/en/dsPIC33EV32GM104)  |  33 kb|   4 kb| 44|
|[dsPIC33EV64GM104](http://microchip.com/wwwproducts/en/dsPIC33EV64GM104)  |  65 kb|   8 kb| 44|
|[dsPIC33EV128GM104](http://microchip.com/wwwproducts/en/dsPIC33EV128GM104)| 131 kb|   8 kb| 44|
|[dsPIC33EV256GM104](http://microchip.com/wwwproducts/en/dsPIC33EV256GM104)| 262 kb|  16 kb| 44|
|[dsPIC33EV32GM106](http://microchip.com/wwwproducts/en/dsPIC33EV32GM106)  |  33 kb|   4 kb| 64|
|[dsPIC33EV64GM106](http://microchip.com/wwwproducts/en/dsPIC33EV64GM106)  |  65 kb|   8 kb| 64|
|[dsPIC33EV128GM106](http://microchip.com/wwwproducts/en/dsPIC33EV128GM106)| 131 kb|   8 kb| 64|
|[dsPIC33EV256GM106](http://microchip.com/wwwproducts/en/dsPIC33EV256GM106)| 262 kb|  16 kb| 64|
