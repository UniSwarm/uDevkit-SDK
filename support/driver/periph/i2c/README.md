# i2c
I2C driver support for hardware abstraction layer

## Minimalist code

```C
uint16_t value, i2cPeriphAddr, i2cRegAddr;
rt_dev_t i2c_bus;

// init
i2c_bus = i2c_getFreeDevice();
i2c_setBaudSpeed(i2c_bus, I2C_BAUD_400K);
i2c_setAddressWidth(i2c_bus, 7);
i2c_enable(i2c_bus);

// send and receive data
i2cPeriphAddr = 0x2A;
i2cRegAddr = 0x12;
value = i2c_readreg(i2c_bus, i2cPeriphAddr, i2cRegAddr, I2C_REG8 | I2C_REGADDR8);

value = 10;
i2c_writereg(i2c_bus, i2cPeriphAddr, i2cRegAddr, value, I2C_REG8 | I2C_REGADDR8);
```

## API

### device assignation
`rt_dev_t i2c_getFreeDevice()` Gives a free i2c bus device number

`int i2c_open(rt_dev_t device)` Open an i2c bus

`int i2c_close(rt_dev_t device)` Close an i2c bus

### device enable/disable
`int i2c_enable(rt_dev_t device)` Enable the specified i2c bus device

`int i2c_disable(rt_dev_t device)` Disable the specified i2c bus device

### device settings
`int i2c_setBaudSpeed(rt_dev_t device, uint32_t baudSpeed)` Sets the speed of receive and transmit

`uint32_t i2c_baudSpeed(rt_dev_t device)` Gets the true baud speed

`uint32_t i2c_effectiveBaudSpeed(rt_dev_t device)` Gets the effective baud speed

`int i2c_setAddressWidth(rt_dev_t device, uint8_t addressWidth)` Sets the address width of slaves

`uint8_t i2c_addressWidth(rt_dev_t device)` Gets the address width of slaves

### device low level interface
`int i2c_start(rt_dev_t device)` Sends a start condition

`int i2c_restart(rt_dev_t device)` Sends a restart condition

`int i2c_stop(rt_dev_t device)` Sends a stop condition

`int i2c_idle(rt_dev_t device)` Sends a idle condition

`int i2c_ack(rt_dev_t device)` Sends a ack condition

`int i2c_nack(rt_dev_t device)` Sends a nack condition

`int i2c_putc(rt_dev_t device, const char data)` Puts a byte

`uint8_t i2c_getc(rt_dev_t device)` Gets a byte

### high level functions, registers level
`uint16_t i2c_readreg(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t flags)` Read a register at address 'reg' in i2c chip with address 'address'

`ssize_t i2c_readregs(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t regs[], size_t size, uint8_t flags)` Read 'size' registers begining at address 'reg' in i2c chip with address 'address'

`int i2c_writereg(rt_dev_t device, uint16_t address, uint16_t reg, uint16_t value, uint8_t flags)` Write 'value' in register at address 'reg' in i2c chip with address 'address'

`int i2c_writeregs(rt_dev_t device, uint16_t address, uint16_t reg, uint8_t regs[], size_t size, uint8_t flags)` Write 'regs' in registers that start at address 'reg' in i2c chip

`flags` parameter should be use with the following flag :

* `I2C_REG8` (default) or `I2C_REG16` to indicate if register of the distant device have 8 or 16 bits register size (could be change for each transaction)

* `I2C_REGADDR8` (default) or `I2C_REGADDR16` to indicate the size of register address

* `I2C_READ_RESTART` (default) or `I2C_READ_STOPSTART` to indicate if device need a restart or a stop followed by a start between read transaction (both exists)

This flag should be used with (|) pipes/logic or. It is not necessary to precice it if you use default value

## Development status
Device assignation, config, send and read data fully functionnal

### TODO :
+ review error return in high level function and i2c_getc

## Supported architectures

|Family|Implementation file|Implementation header|
|------|-------------------|---------------------|
|[pic24f](../../../archi/pic24f/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[pic24fj](../../../archi/pic24fj/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[pic24ep](../../../archi/pic24ep/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[pic24hj](../../../archi/pic24hj/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[dspic33fj](../../../archi/dspic33fj/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[dspic33ep](../../../archi/dspic33ep/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[dspic33ev](../../../archi/dspic33ev/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[dspic30f](../../../archi/dspic30f/README.md)|[i2c_pic24_dspic30f_dspic33.c](i2c_pic24_dspic30f_dspic33.c)|[i2c_pic24_dspic30f_dspic33.h](i2c_pic24_dspic30f_dspic33.h)|
|[pic32mm](../../../archi/pic32mm/README.md)|[i2c_pic32.c](i2c_pic32.c)|[i2c_pic32.h](i2c_pic32.h)|
|[pic32mx](../../../archi/pic32mx/README.md)|[i2c_pic32.c](i2c_pic32.c)|[i2c_pic32.h](i2c_pic32.h)|
|[pic32mzec](../../../archi/pic32mzec/README.md)|[i2c_pic32.c](i2c_pic32.c)|[i2c_pic32.h](i2c_pic32.h)|
|[pic32mzef](../../../archi/pic32mzef/README.md)|[i2c_pic32.c](i2c_pic32.c)|[i2c_pic32.h](i2c_pic32.h)|
