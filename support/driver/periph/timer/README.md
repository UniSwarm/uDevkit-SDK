# timer
Timer/counter driver support for hardware abstraction layer.

## Minimalist code

In timer mode, with callback handler :

```C
void tt()
{
    puts("tt");
}

// init timer
rt_dev_t timer;
timer = timer_getFreeDevice();
timer_setPeriodMs(asserv_timer, 100);
timer_setHandler(asserv_timer, tt);
timer_enable(timer); // tt function will be called every 100ms
```

In counter mode :

```C
// init timer
rt_dev_t timer;
timer = timer_getFreeDevice();
timer_setCounter(asserv_timer, 1); // no diviser
timer_enable(timer); // start to count

uint16_t value;
value = timer_getValue(timer); // get count
timer_clearValue(timer); // clear count
```

## API

### device assignation
`rt_dev_t timer_getFreeDevice()` Gives a free timer device number

`int timer_open(rt_dev_t device)` Open an timer

`int timer_close(rt_dev_t device)` Close an timer

### device enable/disable
`int timer_enable(rt_dev_t device)` Enable the specified timer device

`int timer_disable(rt_dev_t device)` Disable the specified timer device

### ========= timer mode ===========
`int timer_setPeriodMs(rt_dev_t device, uint32_t periodMs)` Sets the period in us of the timer module to work in timer mode

`uint32_t timer_periodMs(rt_dev_t device)` Returns the curent period in us

### ======== counter mode ==========
`int timer_setCounter(rt_dev_t device, uint16_t diviser)` Returns the curent value of timer

`int timer_clearValue(rt_dev_t device)` Reset the value of counter

`int timer_setValue(rt_dev_t device, uint16_t value)` Sets the curent value of timer

`uint16_t timer_getValue(rt_dev_t device)` Returns the curent value of timer

## Development status
+ Device assignation, open, basic config and hander call with interrupt works. No test done on counter mode, need more config.

### TODO :
+ Clarify API

## Supported architectures

|Family|Implementation file|Implementation header|
|------|-------------------|---------------------|
|[pic24f](../../../archi/pic24f/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[pic24fj](../../../archi/pic24fj/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[pic24ep](../../../archi/pic24ep/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[pic24hj](../../../archi/pic24hj/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[dspic33fj](../../../archi/dspic33fj/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[dspic33ep](../../../archi/dspic33ep/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[dspic33ev](../../../archi/dspic33ev/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[dspic30f](../../../archi/dspic30f/README.md)|[timer_pic24_dspic30_dspic33.c](timer_pic24_dspic30_dspic33.c)|[timer_pic24_dspic30_dspic33.h](timer_pic24_dspic30_dspic33.h)|
|[pic32mm](../../../archi/pic32mm/README.md)|[timer_pic32.c](timer_pic32.c)|[timer_pic32.h](timer_pic32.h)|
|[pic32mx](../../../archi/pic32mx/README.md)|[timer_pic32.c](timer_pic32.c)|[timer_pic32.h](timer_pic32.h)|
|[pic32mzec](../../../archi/pic32mzec/README.md)|[timer_pic32.c](timer_pic32.c)|[timer_pic32.h](timer_pic32.h)|
|[pic32mzef](../../../archi/pic32mzef/README.md)|[timer_pic32.c](timer_pic32.c)|[timer_pic32.h](timer_pic32.h)|
