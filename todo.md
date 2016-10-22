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
- [x] prototypes
- [x] device assignation
- [x] config
- [x] send
- [x] receive

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
- [x] device assignation
- [x] config
- [x] read data
- [ ] 32 bits mode
- [ ] counter mode

### PWM
- [x] prototypes
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

### Screen
- [x] character draw
- [ ] multiline draw
- [x] pixel vector picture draw
- [ ] 2D picture header

## Module
###GUI
 - [] bouger les fonctions bas niveau dans driver/lcd

## Boards
### RTBoard
- [x] init io
- [x] adc static, motors...

### screenBoard
- [x] init io

### Touchscreen
- [ ] Ask for number ar1000 or ar1021 ???
- [ ] add i2c and spi communication

## Tools
### README
 - [ ] do a readme

### image
- [x] include meta information of the image (size, encodage or other...) in the MyImage.ext.c ->struct !
- [ ] FIX: warning: 30Fxxxx architecture of input file `build/pictureName.extentsion.o' is incompatible with 33EP512GP806 output
