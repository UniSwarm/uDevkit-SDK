# Timer / counter

Timer / counter driver support for hardware abstraction layer.

## Minimalist code

In timer mode, with callback handler :

```C
void timer100ms_fn()
{
    puts("tt");
}

// init timer
rt_dev_t timer;
timer = timer_getFreeDevice();
timer_setPeriodMs(timer, 100);
timer_setHandler(timer, timer100ms_fn);
timer_enable(timer); // tt function will be called every 100ms
```

In counter mode :

```C
// init timer
rt_dev_t timer;
timer = timer_getFreeDevice();
timer_setCounter(timer, 1); // no divider
timer_enable(timer); // start to count

uint16_t value;
value = timer_getValue(timer); // get count
timer_clearValue(timer); // clear count
```

## API

### Device assignation

#### timer_getFreeDevice

```C
rt_dev_t timer_getFreeDevice();
```

Gives a free timer device number

#### timer_open

```C
int timer_open(rt_dev_t device);
```

Opens a timer

#### timer_close

```C
int timer_close(rt_dev_t device);
```

Closes a timer

### Device enable/disable

#### timer_enable

```C
int timer_enable(rt_dev_t device);
```

Enables the specified timer device

#### timer_disable

```C
int timer_disable(rt_dev_t device);
```

Disables the specified timer device

### Timer mode

#### timer_setPeriodMs

```C
int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs);
```

Sets the period in ms of the timer module to work in timer mode

#### timer_periodMs

```C
uint32_t timer_periodMs(rt_dev_t device);
```

Returns the current period in ms

#### timer_setPeriodUs

```C
int timer_setPeriodUs(rt_dev_t device, uint32_t periodUs);
```

Sets the period in us of the timer module to work in timer mode

#### timer_periodMs

```C
uint32_t timer_periodUs(rt_dev_t device);
```

Returns the current period in us

#### timer_setPeriod

```C
int timer_setPeriodUs(rt_dev_t device, uint32_t period);
```

Sets the period in low level units. If the period is greatter than the PR register size,
the pre divider is adapted

#### timer_period

```C
uint32_t timer_period(rt_dev_t device);
```

Returns the current period in low level units

### Counter mode

#### timer_setCounter

```C
int timer_setCounter(rt_dev_t device, uint16_t diviser);
```

Returns the current value of timer

#### timer_clearValue

```C
int timer_clearValue(rt_dev_t device);
```

Reset the value of counter

#### timer_setValue

```C
int timer_setValue(rt_dev_t device, uint16_t value);
```

Sets the current value of timer

#### timer_getValue

```C
uint16_t timer_getValue(rt_dev_t device);
```

Returns the current value of timer

## Development status

+ Device assignation, open, basic configuration and handler call with interrupt works. No test done on counter mode, need 
to be more configurable.

### TODO

+ Clarify API

## Supported architectures

Header file : [timer.h](timer.h)

|Family|Implementation file|
|------|-------------------|
|[pic24f](../../archi/pic24f/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[pic24fj](../../archi/pic24fj/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[pic24ep](../../archi/pic24ep/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[pic24hj](../../archi/pic24hj/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[dspic33fj](../../archi/dspic33fj/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[dspic33ep](../../archi/dspic33ep/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[dspic33ev](../../archi/dspic33ev/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[dspic30f](../../archi/dspic30f/README.md)|[timer_pic24_dspic30f_dspic33.c](timer_pic24_dspic30f_dspic33.c) / [timer_pic24_dspic30f_dspic33.h](timer_pic24_dspic30f_dspic33.h)|
|[dspic33ch](../../archi/dspic33ch/README.md)|[timer_dspic33c.c](timer_dspic33c.c) / [timer_dspic33c.h](timer_dspic33c.h)|
|[dspic33ck](../../archi/dspic33ck/README.md)|[timer_dspic33c.c](timer_dspic33c.c) / [timer_dspic33c.h](timer_dspic33c.h)|
|[pic32mm](../../archi/pic32mm/README.md)|[timer_pic32.c](timer_pic32.c) / [timer_pic32.h](timer_pic32.h)|
|[pic32mk](../../archi/pic32mk/README.md)|[timer_pic32.c](timer_pic32.c) / [timer_pic32.h](timer_pic32.h)|
|[pic32mx](../../archi/pic32mx/README.md)|[timer_pic32.c](timer_pic32.c) / [timer_pic32.h](timer_pic32.h)|
|[pic32mzec](../../archi/pic32mzec/README.md)|[timer_pic32.c](timer_pic32.c) / [timer_pic32.h](timer_pic32.h)|
|[pic32mzef](../../archi/pic32mzef/README.md)|[timer_pic32.c](timer_pic32.c) / [timer_pic32.h](timer_pic32.h)|
|[pic32mzda](../../archi/pic32mzda/README.md)|[timer_pic32.c](timer_pic32.c) / [timer_pic32.h](timer_pic32.h)|
