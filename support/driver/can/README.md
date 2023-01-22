# CAN

CAN driver support for hardware abstraction layer.

## Minimalist code

```C
// init
rt_dev_t can = can(1);
can_open(can);
can_setBitTiming(can, 1000000, 1, 4, 2);
can_enable(can);
can_setMode(can, CAN_MODE_NORMAL);

// send and receive data
CAN_MSG_HEADER can_header;
char data[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
can_header.size = 8;
can_header.id = 0x01AB45CD;
can_header.flags = CAN_VERS2BA;
can_send(can, 0, &can_header, data);

char rdata[8];
int r = can_rec(can, 0, &can_header, rdata);
if (r == 1)
{
    printf("%#08X\n", rdata);
}
```

## API

### Device assignation

#### can_getFreeDevice

```C
rt_dev_t can_getFreeDevice();
```
Gives a free can device number and opens it

#### can_open

```C
int can_open(rt_dev_t device);
```
Opens a can bus device

#### can_close

```C
int can_close(rt_dev_t device);
```
Closes a can bus device

#### can_isOpened

```C
bool can_isOpened(rt_dev_t device)
```
Gives the SDK device status

### Device enable/disable

#### can_enable

```C
int can_enable(rt_dev_t device);
```
Enables the specified can bus device

#### can_disable

```C
int can_disable(rt_dev_t device);
```
Disables the specified can bus device

#### can_isEnabled

```C
bool can_isEnabled(rt_dev_t device)
```
Gives the SDK enabled state

### Device settings

#### can_setBitTiming

```C
int can_setBitTiming(rt_dev_t device, uint32_t bitRate, uint8_t propagSeg, uint8_t s1Seg, uint8_t s2Seg);
```
Sets bit rate and segments timing. Sum of all segments (propagSeg + s1Seg +, s2Seg) + 1 must be contained in the range of 8 to 25 quantums.

CAN Bit Timing (8-25 Tq) segments computation :

| Sync | Propag seg | Phase seg 1 ||Phase seg 2 |
|-|-|-|-|-|
| 1 Tq |   1-8 Tq   |   1-8 Tq    |   sample point    |   1-8 Tq    |

#### can_bitRate

```C
uint32_t can_bitRate(rt_dev_t device);
```
Gets the true bit rate

#### can_effectiveBitRate

```C
uint32_t can_effectiveBitRate(rt_dev_t device);
```
Gets the effective bit rate

#### can_propagSeg

```C
uint8_t can_propagSeg(rt_dev_t device);
```
Gets the current propagation segment length

#### can_s1Seg

```C
uint8_t can_s1Seg(rt_dev_t device);
```
Gets the current S1 segment length

#### can_s2Seg

```C
uint8_t can_s2Seg(rt_dev_t device);
```
Gets the current S2 segment length

### Device read / write

#### can_send

```C
int can_send(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data);
```
Puts a message in fifo `fifo`

#### can_rec

```C
int can_rec(rt_dev_t device, uint8_t fifo, CAN_MSG_HEADER *header, char *data);
```
Gets a message from fifo `fifo`, return 1 if a message is read

## Development status

Device assignation, configuration, send and read data on fifo 0 only

### TODO

+ multi fifo send / rec
+ fifo status
+ implementation on dsPIC33E/F
+ interrupts

## Supported architectures

Header file : [can.h](can.h)

|Family|Implementation files|
|------|--------------------|
|[dspic30f](../../archi/dspic33ch/README.md)|[can_dspic30f.c](can_dspic30f.c) / [can_dspic30f.h](can_dspic30f.h)|
|[dspic33ch](../../archi/dspic33ch/README.md)|[can_dspic33c.c](can_dspic33c.c) / [can_dspic33c.h](can_dspic33c.h)|
|[dspic33ck](../../archi/dspic33ck/README.md)|[can_dspic33c.c](can_dspic33c.c) / [can_dspic33c.h](can_dspic33c.h)|
|[pic24f](../../archi/pic24f/README.md)  |[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[pic24fj](../../archi/pic24fj/README.md)|[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[pic24ep](../../archi/pic24ep/README.md)|[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[pic24hj](../../archi/pic24hj/README.md)|[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[dspic33fj](../../archi/dspic33fj/README.md)|[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[dspic33ep](../../archi/dspic33ep/README.md)|[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[dspic33ev](../../archi/dspic33ev/README.md)|[can_pic24_dspic33.c](can_pic24_dspic33.c) / [can_pic24_dspic33.h](can_pic24_dspic33.h)|
|[dspic30f](../../archi/dspic30f/README.md)|[can_dspic30f.c](can_dspic30f.c) / [can_dspic30f.h](can_dspic30f.h)|
|[pic32mm](../../archi/pic32mm/README.md)|[can_pic32.c](can_pic32.c) / [can_pic32.h](can_pic32.h)|
|[pic32mk](../../archi/pic32mk/README.md)|[can_pic32.c](can_pic32.c) / [can_pic32.h](can_pic32.h)|
|[pic32mzec](../../archi/pic32mzec/README.md)|[can_pic32.c](can_pic32.c) / [can_pic32.h](can_pic32.h)|
|[pic32mzef](../../archi/pic32mzef/README.md)|[can_pic32.c](can_pic32.c) / [can_pic32.h](can_pic32.h)|
|[pic32mzda](../../archi/pic32mzda/README.md)|[can_pic32.c](can_pic32.c) / [can_pic32.h](can_pic32.h)|
|[pic32mx](../../archi/pic32mx/README.md)|[can_pic32.c](can_pic32.c) / [can_pic32.h](can_pic32.h)|
