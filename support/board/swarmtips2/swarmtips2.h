/**
 * @file swarmtips2.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 15, 2017, 01:16 AM
 *
 * @brief Definitions for swarmtips2 from Robotips
 */

#ifndef SWARMTIPS2_H
#define SWARMTIPS2_H

#include <archi.h>

#include <stdint.h>

#include <driver/device.h>

int board_init(void);

#define BOARD_NAME "swarmtips2"

// ====== oscillator ======
#define SYSCLOCK_XTAL 24000000
#define OSC_EN        LATCbits.LATC15

// ==== pins define ====
// leds
#define LED_COUNT 6
#define LED1_OC   8  // OC8
#define LED2_OC   9  // OC9
#define LED3_OC   7  // OC7
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

#define BUTTON_COUNT 3
int8_t board_getButton(uint8_t button);

rt_dev_t board_i2c_tof(void);
rt_dev_t board_i2c_ihm(void);

void board_buzz(uint16_t freq);

float board_getPowerVoltage(void);

// ====== charger ======
#define CHARGER_CE  LATBbits.LATB11
#define CHARGER_SYS LATBbits.LATB14
#ifndef SIMULATOR
#    define CHARGER_PWGOOD   PORTBbits.RB12
#    define CHARGER_CHARGING PORTBbits.RB13
#else
#    define CHARGER_PWGOOD   1
#    define CHARGER_CHARGING 1
#endif
#define BOARD_VOLT_IN 10  // RB15    // analog board voltage channel

// ====== motors pins ======
#define BOOST_SLEEP LATBbits.LATB8  // boost sleep

#define M1DIR LATCbits.LATC14  // M1 pin direction
#define M1PWM 3                // OC3             // M1 pwm speed

#define M2DIR LATCbits.LATC13  // M2 pin direction
#define M2PWM 4                // OC4             // M2 pwm speed

#ifndef SIMULATOR
#    define C1A PORTBbits.RB9   // Coder 1 pin A
#    define C1B PORTBbits.RB10  // Coder 1 pin B
#    define C2A PORTBbits.RB4   // Coder 2 pin A
#    define C2B PORTBbits.RB5   // Coder 2 pin B
#else
#    define C1A 1
#    define C1B 1
#    define C2A 1
#    define C2B 1
#endif

// ====== buzzer ======
#define BUZZER 1  // OC1             // PWM buzzer

// ====== wifi ======
#define ESP8266_UART  2
#define ESP8266_RST   LATEbits.LATE5
#define ESP8266_FLASH LATEbits.LATE7

// ====== ihm : screen and buttons ======
#define IHM_I2C_BUS    4               // I2C4       // I2C Bus for IHM oled and io expender
#define RBG_LED        LATEbits.LATE6  // RGB leds control pin
#define IHM_IOEXP_ADDR 0x82
#define IHM_LED_PIN    0
#define IHM_BTN1_PIN   1
#define IHM_BTN1_MASK  0x02
#define IHM_BTN2_PIN   2
#define IHM_BTN2_MASK  0x04
#define IHM_BTN3_PIN   3
#define IHM_BTN3_MASK  0x08
#define IHM_OLED_ADDR  0b01111000

// ====== gui module param ======
#define OLED_I2C_ADDR IHM_OLED_ADDR

// ====== acc gyro ======
#define ACC_I2C_BUS  3  // I2C3
#define ACC_I2C_ADDR 0xD6
#define ACC_SA0      LATDbits.LATD11
#define ACC_CS       LATDbits.LATD5
/*#define ACC_SD0   LATDbits.LATD2
#define ACC_SDI   PORTDbits.RD11
#define ACC_SCK   LATDbits.LATD3*/

// ====== sensor tof/als ======
#define TOF_I2C_BUS     1  // I2C1       // I2C Bus for tof sensors and als
#define TOF1_ADDR       0x30
#define TOF2_ADDR       0x32
#define TOF3_ADDR       0x34
#define TOF_IOEXP_ADDR  0x82
#define TOF2_ENABLE_PIN 0
#define TOF3_ENABLE_PIN 1
#define TOF_LED1_PIN    2
#define TOF_LED2_PIN    3

#define ALS1_ADDR     0x90
#define ALS2_ADDR     0x10
#define ALSCOLOR_ADDR 0x52

#endif  // SWARMTIPS2_H
