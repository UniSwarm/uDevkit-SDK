# QEI

Quadrature Encoder Interface support driver for hardware abstraction layer.

## Minimalist code

```C
rt_dev_t qei1;
int position;

// init
qei1 = qei(1);
qei_setConfig(qei1, QEI_X4MODE);
qei_enable(qei1);

// qei read
position = qei_getValue(qei1);
```

## API

### Device assignation

#### qei_getFreeDevice

```C
rt_dev_t qei_getFreeDevice();
```
Gives a free qei device number and opens it

#### qei_open

```C
int qei_open(rt_dev_t device);
```
Opens an qei

#### qei_close

```C
int qei_close(rt_dev_t device);
```
Closes an qei

### Device enable/disable

#### qei_enable

```C
int qei_enable(rt_dev_t device);
```
Enables the specified qei device

#### qei_disable

```C
int qei_disable(rt_dev_t device);
```
Disables the specified qei device

### Device settings

#### qei_setConfig

```C
int qei_setConfig(rt_dev_t device, uint16_t config);
```

Configures the specified QEI device with bits in config.

### Device read / write

#### qei_getValue

```C
qei_type qei_getValue(rt_dev_t device);
```

Returns the actual position of the specified QEI.

## Development status

Device assignation, configuration, write and read data are fully functional

### TODO

+ complete device options (only quadrature base mode works)

## Supported architectures

Header file : [qei.h](qei.h)

|Family|Implementation files|
|------|--------------------|
|[pic24f](../../archi/pic24f/README.md)  |[qei_pic24f_dspic33f.c](qei_pic24f_dspic33f.c) / [qei_pic24f_dspic33f.h](qei_pic24f_dspic33f.h)|
|[pic24fj](../../archi/pic24fj/README.md)|[qei_pic24f_dspic33f.c](qei_pic24f_dspic33f.c) / [qei_pic24f_dspic33f.h](qei_pic24f_dspic33f.h)|
|[pic24hj](../../archi/pic24hj/README.md)|[qei_pic24f_dspic33f.c](qei_pic24f_dspic33f.c) / [qei_pic24f_dspic33f.h](qei_pic24f_dspic33f.h)|
|[dspic33fj](../../archi/dspic33fj/README.md)|[qei_pic24f_dspic33f.c](qei_pic24f_dspic33f.c) / [qei_pic24f_dspic33f.h](qei_pic24f_dspic33f.h)|
|[dspic30f](../../archi/dspic30f/README.md)|[qei_dspic30f.c](qei_dspic30f.c) / [qei_dspic30f.h](qei_dspic30f.h)|
|[dspic33ch](../../archi/dspic33ch/README.md)|[qei_pic24e_dspic33e.c](qei_pic24e_dspic33e.c) / [qei_pic24e_dspic33e.h](qei_pic24e_dspic33e.h)|
|[dspic33ck](../../archi/dspic33ck/README.md)|[qei_pic24e_dspic33e.c](qei_pic24e_dspic33e.c) / [qei_pic24e_dspic33e.h](qei_pic24e_dspic33e.h)|
|[pic24ep](../../archi/pic24ep/README.md)|[qei_pic24e_dspic33e.c](qei_pic24e_dspic33e.c) / [qei_pic24e_dspic33e.h](qei_pic24e_dspic33e.h)|
|[dspic33ep](../../archi/dspic33ep/README.md)|[qei_pic24e_dspic33e.c](qei_pic24e_dspic33e.c) / [qei_pic24e_dspic33e.h](qei_pic24e_dspic33e.h)|
|[dspic33ev](../../archi/dspic33ev/README.md)|[qei_pic24e_dspic33e.c](qei_pic24e_dspic33e.c) / [qei_pic24e_dspic33e.h](qei_pic24e_dspic33e.h)|
|[pic32mk](../../archi/pic32mk/README.md)|[qei_pic32mk.c](qei_pic32mk.c) / [qei_pic32mk.h](qei_pic32mk.h)|
