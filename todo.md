# TODO

- [ ] Find a solution for interrupts (call back?)
- [ ] Find a solution for pins mapping and declaration

## Support:
### PPS
- [ ] Defines depending on device
- [ ] prototypes

### UART
- [x] prototypes
- [x] device assignation
- [x] config
- [x] send
- [x] receive

### I2C
- [ ] prototypes
- [ ] device assignation
- [ ] config
- [ ] send
- [ ] receive

### SPI
- [x] prototypes
- [ ] device assignation
- [ ] config
- [ ] send
- [ ] receive

### QEI
- [x] prototypes
- [x] device assignation
- [ ] config (default config done)
- [x] read data

### Timers
- [x] prototypes
- [ ] device assignation
- [ ] config
- [ ] read data

### PWM
- [ ] prototypes
- [ ] device assignation
- [ ] config
- [ ] set pwm

### ADC
- [x] prototypes
- [ ] config
- [x] read data
- [ ] interrupt

## Others drivers
### AX12
- [x] porting
- [x] send command
- [ ] receive data

### ESP8266 wifi
- [x] porting
- [ ] complete API
- [ ] debug emit
- [ ] interrupt parser

## Boards
### RTBoard
- [x] init io
- [x] adc static, motors...

### screenBoard
- [x] init io

### tactil
- [ ] Ask for number ar1000 or ar1021 ???
- [ ] add i2c and spi communication