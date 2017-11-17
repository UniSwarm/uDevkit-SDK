# dsPIC33EP support

dsPIC33EP family handle a lot of subfamilies with the same 16 bits high performance core.
This range is very similar to [PIC24EP](../pic24ep/README.md) with an additional DSP core.

## Main features

|Feature|GS   |GM   |GP / MC / MU|
|-------|:---:|:---:|:---:|
|Performance|70 DMIPS|70 DMIPS|70 DMIPS|
|Program memory|16 kb - 131 kb|131 kb - 525 kb|33 kb - 525 kb|
|Data memory|2 kb - 4 kb|16 kb - 49 kb|4 kb - 49 kb|
|Pins|28-80|44-100|28-144|

## Common devices

|Peripheral|UART|TIMER|I2C|SPI|CLC|IC |OC |CAN|QEI|PWM|
|----------|:--:|:---:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|GS20X     |   1|    3|  1|  1|  0|  2|  2|  0|  0|  3|
|GS50X     |   2|    5|  2|  2|  0|  8|  8|  0|  0|  5|
|GS70X     |   2|    5|  2|  3|  4|  8|  8|  0|  0|  8|
|GS80X     |   2|    5|  2|  3|  4|  8|  8|  2|  0|  8|
|**GM30X** |   4|    9|  2|  3|  0|  8|  8|  2|  0|  6|
|**GM60X** |   4|    9|  2|  3|  0|  8|  8|  2|  0|  6|
|**GM70X** |   4|    9|  2|  3|  0|  8|  8|  2|  0|  6|
|GP50X     |   2|    5|  2|  2|  0|  4|  4|  1|  0|  0|
|GP80X     |   4|    9|  2|  3|  0| 16| 16|  2|  0|  0|
|**MC20X** |   2|    5|  2|  2|  0|  4|  4|  0|  1|  3|
|**MC50X** |   2|    5|  2|  2|  0|  4|  4|  1|  1|  3|
|**MC80X** |   4|    9|  2|  3|  0| 16| 16|  2|  2|  4|
|MU8XX     |   4|    9|  2|  3|  0|  8|  8|  2|  2|4-7|

(101 devices on november 2017)

## GS family

### GS20X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP16GS202](http://microchip.com/wwwproducts/en/dsPIC33EP16GS202)|16 kb|2 kb|28|
|[dsPIC33EP32GS202](http://microchip.com/wwwproducts/en/dsPIC33EP32GS202)|33 kb|2 kb|28|

### GS50X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP16GS502](http://microchip.com/wwwproducts/en/dsPIC33EP16GS502)|16 kb|2 kb|28|
|[dsPIC33EP32GS502](http://microchip.com/wwwproducts/en/dsPIC33EP32GS502)|33 kb|4 kb|28|
|[dsPIC33EP64GS502](http://microchip.com/wwwproducts/en/dsPIC33EP64GS502)|67 kb|8 kb|28|
|[dsPIC33EP16GS504](http://microchip.com/wwwproducts/en/dsPIC33EP16GS504)|16 kb|2 kb|44|
|[dsPIC33EP32GS504](http://microchip.com/wwwproducts/en/dsPIC33EP32GS504)|33 kb|4 kb|44|
|[dsPIC33EP64GS504](http://microchip.com/wwwproducts/en/dsPIC33EP64GS504)|67 kb|8 kb|44|
|[dsPIC33EP16GS505](http://microchip.com/wwwproducts/en/dsPIC33EP16GS505)|16 kb|2 kb|48|
|[dsPIC33EP32GS505](http://microchip.com/wwwproducts/en/dsPIC33EP32GS505)|33 kb|4 kb|48|
|[dsPIC33EP64GS505](http://microchip.com/wwwproducts/en/dsPIC33EP64GS505)|67 kb|8 kb|48|
|[dsPIC33EP16GS506](http://microchip.com/wwwproducts/en/dsPIC33EP16GS506)|16 kb|2 kb|64|
|[dsPIC33EP32GS506](http://microchip.com/wwwproducts/en/dsPIC33EP32GS506)|33 kb|4 kb|64|
|[dsPIC33EP64GS506](http://microchip.com/wwwproducts/en/dsPIC33EP64GS506)|67 kb|8 kb|64|

### GS70X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP128GS702](http://microchip.com/wwwproducts/en/dsPIC33EP128GS702)|131 kb|4 kb|28|
|[dsPIC33EP128GS704](http://microchip.com/wwwproducts/en/dsPIC33EP128GS704)|131 kb|4 kb|44|
|[dsPIC33EP128GS705](http://microchip.com/wwwproducts/en/dsPIC33EP128GS705)|131 kb|4 kb|48|
|[dsPIC33EP128GS706](http://microchip.com/wwwproducts/en/dsPIC33EP128GS706)|131 kb|4 kb|64|
|[dsPIC33EP64GS708](http://microchip.com/wwwproducts/en/dsPIC33EP64GS708)  | 67 kb|4 kb|80|
|[dsPIC33EP128GS708](http://microchip.com/wwwproducts/en/dsPIC33EP128GS708)|131 kb|4 kb|80|

### GS80X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP64GS804](http://microchip.com/wwwproducts/en/dsPIC33EP64GS804)  | 67 kb|4 kb|44|
|[dsPIC33EP128GS804](http://microchip.com/wwwproducts/en/dsPIC33EP128GS804)|131 kb|4 kb|44|
|[dsPIC33EP64GS805](http://microchip.com/wwwproducts/en/dsPIC33EP64GS805)  | 67 kb|4 kb|48|
|[dsPIC33EP128GS805](http://microchip.com/wwwproducts/en/dsPIC33EP128GS805)|131 kb|4 kb|48|
|[dsPIC33EP64GS806](http://microchip.com/wwwproducts/en/dsPIC33EP64GS806)  | 67 kb|4 kb|64|
|[dsPIC33EP128GS806](http://microchip.com/wwwproducts/en/dsPIC33EP128GS806)|131 kb|4 kb|64|
|[dsPIC33EP64GS808](http://microchip.com/wwwproducts/en/dsPIC33EP64GS808)  | 67 kb|4 kb|80|
|[dsPIC33EP128GS808](http://microchip.com/wwwproducts/en/dsPIC33EP128GS808)|131 kb|4 kb|80|

## GM family

### GM30X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP128GM304](http://microchip.com/wwwproducts/en/dsPIC33EP128GM304)|131 kb|16 kb| 44|
|[dsPIC33EP256GM304](http://microchip.com/wwwproducts/en/dsPIC33EP256GM304)|262 kb|33 kb| 44|
|[dsPIC33EP512GM304](http://microchip.com/wwwproducts/en/dsPIC33EP512GM304)|525 kb|49 kb| 44|
|[dsPIC33EP128GM306](http://microchip.com/wwwproducts/en/dsPIC33EP128GM306)|131 kb|16 kb| 64|
|[dsPIC33EP256GM306](http://microchip.com/wwwproducts/en/dsPIC33EP256GM306)|262 kb|33 kb| 64|
|[dsPIC33EP512GM306](http://microchip.com/wwwproducts/en/dsPIC33EP512GM306)|525 kb|49 kb| 64|
|[dsPIC33EP128GM310](http://microchip.com/wwwproducts/en/dsPIC33EP128GM310)|131 kb|16 kb|100|
|[dsPIC33EP256GM310](http://microchip.com/wwwproducts/en/dsPIC33EP256GM310)|262 kb|33 kb|100|
|[dsPIC33EP512GM310](http://microchip.com/wwwproducts/en/dsPIC33EP512GM310)|525 kb|49 kb|100|

### GM60X-70X subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP128GM604](http://microchip.com/wwwproducts/en/dsPIC33EP128GM604)|131 kb|16 kb| 44|
|[dsPIC33EP256GM604](http://microchip.com/wwwproducts/en/dsPIC33EP256GM604)|262 kb|33 kb| 44|
|[dsPIC33EP512GM604](http://microchip.com/wwwproducts/en/dsPIC33EP512GM604)|525 kb|49 kb| 44|
|[dsPIC33EP128GM706](http://microchip.com/wwwproducts/en/dsPIC33EP128GM706)|131 kb|16 kb| 64|
|[dsPIC33EP256GM706](http://microchip.com/wwwproducts/en/dsPIC33EP256GM706)|262 kb|33 kb| 64|
|[dsPIC33EP512GM706](http://microchip.com/wwwproducts/en/dsPIC33EP512GM706)|525 kb|49 kb| 64|
|[dsPIC33EP128GM710](http://microchip.com/wwwproducts/en/dsPIC33EP128GM710)|131 kb|16 kb|100|
|[dsPIC33EP256GM710](http://microchip.com/wwwproducts/en/dsPIC33EP256GM710)|262 kb|33 kb|100|
|[dsPIC33EP512GM710](http://microchip.com/wwwproducts/en/dsPIC33EP512GM710)|525 kb|49 kb|100|

## GP / MC / MU families

### GP subfamily

|Compatible devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP32GP502](http://microchip.com/wwwproducts/en/dsPIC33EP32GP502)  | 33 kb| 4 kb|28|
|[dsPIC33EP64GP502](http://microchip.com/wwwproducts/en/dsPIC33EP64GP502)  | 67 kb| 8 kb|28|
|[dsPIC33EP128GP502](http://microchip.com/wwwproducts/en/dsPIC33EP128GP502)|131 kb|16 kb|28|
|[dsPIC33EP256GP502](http://microchip.com/wwwproducts/en/dsPIC33EP256GP502)|263 kb|33 kb|28|
|[dsPIC33EP512GP502](http://microchip.com/wwwproducts/en/dsPIC33EP512GP502)|525 kb|49 kb|28|
|[dsPIC33EP32GP503](http://microchip.com/wwwproducts/en/dsPIC33EP32GP503)  | 33 kb| 4 kb|36|
|[dsPIC33EP64GP503](http://microchip.com/wwwproducts/en/dsPIC33EP64GP503)  | 67 kb| 8 kb|36|
|[dsPIC33EP32GP504](http://microchip.com/wwwproducts/en/dsPIC33EP32GP504)  | 33 kb| 4 kb|44|
|[dsPIC33EP64GP504](http://microchip.com/wwwproducts/en/dsPIC33EP64GP504)  | 67 kb| 8 kb|44|
|[dsPIC33EP128GP504](http://microchip.com/wwwproducts/en/dsPIC33EP128GP504)|131 kb|16 kb|44|
|[dsPIC33EP256GP504](http://microchip.com/wwwproducts/en/dsPIC33EP256GP504)|263 kb|33 kb|44|
|[dsPIC33EP512GP504](http://microchip.com/wwwproducts/en/dsPIC33EP512GP504)|525 kb|49 kb|44|
|[dsPIC33EP64GP506](http://microchip.com/wwwproducts/en/dsPIC33EP64GP506)  | 67 kb| 8 kb|64|
|[dsPIC33EP128GP506](http://microchip.com/wwwproducts/en/dsPIC33EP128GP506)|131 kb|16 kb|64|
|[dsPIC33EP256GP506](http://microchip.com/wwwproducts/en/dsPIC33EP256GP506)|263 kb|33 kb|64|
|[dsPIC33EP512GP506](http://microchip.com/wwwproducts/en/dsPIC33EP512GP506)|525 kb|49 kb|64|
|[dsPIC33EP512GP806](http://microchip.com/wwwproducts/en/dsPIC33EP512GP806)|525 kb|53 kb|64|

### MC20X / MC50X / MC80X subfamilies

|Compatible MC20X devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP32MC202](http://microchip.com/wwwproducts/en/dsPIC33EP32MC202)  |33 kb | 4 kb|28|
|[dsPIC33EP64MC202](http://microchip.com/wwwproducts/en/dsPIC33EP64MC202)  |67 kb | 8 kb|28|
|[dsPIC33EP128MC202](http://microchip.com/wwwproducts/en/dsPIC33EP128MC202)|131 kb|16 kb|28|
|[dsPIC33EP256MC202](http://microchip.com/wwwproducts/en/dsPIC33EP256MC202)|263 kb|33 kb|28|
|[dsPIC33EP512MC202](http://microchip.com/wwwproducts/en/dsPIC33EP512MC202)|525 kb|49 kb|28|
|[dsPIC33EP32MC203](http://microchip.com/wwwproducts/en/dsPIC33EP32MC203)  |33 kb | 4 kb|36|
|[dsPIC33EP64MC203](http://microchip.com/wwwproducts/en/dsPIC33EP64MC203)  |67 kb | 8 kb|36|
|[dsPIC33EP32MC204](http://microchip.com/wwwproducts/en/dsPIC33EP32MC204)  |33 kb | 4 kb|44|
|[dsPIC33EP64MC204](http://microchip.com/wwwproducts/en/dsPIC33EP64MC204)  |67 kb | 8 kb|44|
|[dsPIC33EP128MC204](http://microchip.com/wwwproducts/en/dsPIC33EP128MC204)|131 kb|16 kb|44|
|[dsPIC33EP256MC204](http://microchip.com/wwwproducts/en/dsPIC33EP256MC204)|263 kb|33 kb|44|
|[dsPIC33EP512MC204](http://microchip.com/wwwproducts/en/dsPIC33EP512MC204)|525 kb|49 kb|44|
|[dsPIC33EP64MC206](http://microchip.com/wwwproducts/en/dsPIC33EP64MC206)  |67 kb| 8 kb| 64|
|[dsPIC33EP128MC206](http://microchip.com/wwwproducts/en/dsPIC33EP128MC206)|131 kb|16 kb|64|
|[dsPIC33EP256MC206](http://microchip.com/wwwproducts/en/dsPIC33EP256MC206)|263 kb|33 kb|64|
|[dsPIC33EP512MC206](http://microchip.com/wwwproducts/en/dsPIC33EP512MC206)|525 kb|49 kb|64|


|Compatible MC50X devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP32MC502](http://microchip.com/wwwproducts/en/dsPIC33EP32MC502)  |33 kb | 4 kb|28|
|[dsPIC33EP64MC502](http://microchip.com/wwwproducts/en/dsPIC33EP64MC502)  |67 kb | 8 kb|28|
|[dsPIC33EP128MC502](http://microchip.com/wwwproducts/en/dsPIC33EP128MC502)|131 kb|16 kb|28|
|[dsPIC33EP256MC502](http://microchip.com/wwwproducts/en/dsPIC33EP256MC502)|263 kb|33 kb|28|
|[dsPIC33EP512MC502](http://microchip.com/wwwproducts/en/dsPIC33EP512MC502)|525 kb|49 kb|28|
|[dsPIC33EP32MC503](http://microchip.com/wwwproducts/en/dsPIC33EP32MC503)  |33 kb | 4 kb|36|
|[dsPIC33EP64MC503](http://microchip.com/wwwproducts/en/dsPIC33EP64MC503)  |67 kb | 8 kb|36|
|[dsPIC33EP32MC504](http://microchip.com/wwwproducts/en/dsPIC33EP32MC504)  |33 kb | 4 kb|44|
|[dsPIC33EP64MC504](http://microchip.com/wwwproducts/en/dsPIC33EP64MC504)  |67 kb | 8 kb|44|
|[dsPIC33EP128MC504](http://microchip.com/wwwproducts/en/dsPIC33EP128MC504)|131 kb|16 kb|44|
|[dsPIC33EP256MC504](http://microchip.com/wwwproducts/en/dsPIC33EP256MC504)|263 kb|33 kb|44|
|[dsPIC33EP512MC504](http://microchip.com/wwwproducts/en/dsPIC33EP512MC504)|525 kb|49 kb|44|
|[dsPIC33EP64MC506](http://microchip.com/wwwproducts/en/dsPIC33EP64MC506)  |67 kb | 8 kb|64|
|[dsPIC33EP128MC506](http://microchip.com/wwwproducts/en/dsPIC33EP128MC506)|131 kb|16 kb|64|
|[dsPIC33EP256MC506](http://microchip.com/wwwproducts/en/dsPIC33EP256MC506)|263 kb|33 kb|64|
|[dsPIC33EP512MC506](http://microchip.com/wwwproducts/en/dsPIC33EP512MC506)|525 kb|49 kb|64|


|Compatible MC80X devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP512MC806](http://microchip.com/wwwproducts/en/dsPIC33EP512MC806)|525 kb|53 kb|64|

### MU8XX subfamily

|Compatible MU8XX devices|Program|Data|Pins|
|---------|--:|--:|--:|
|[dsPIC33EP256MU806](http://microchip.com/wwwproducts/en/dsPIC33EP256MU806)|262 kb|29 kb| 64|
|[dsPIC33EP256MU810](http://microchip.com/wwwproducts/en/dsPIC33EP256MU810)|262 kb|29 kb|100|
|[dsPIC33EP512MU810](http://microchip.com/wwwproducts/en/dsPIC33EP512MU810)|525 kb|53 kb|100|
|[dsPIC33EP256MU814](http://microchip.com/wwwproducts/en/dsPIC33EP256MU814)|262 kb|29 kb|144|
|[dsPIC33EP512MU814](http://microchip.com/wwwproducts/en/dsPIC33EP512MU814)|525 kb|53 kb|144|
