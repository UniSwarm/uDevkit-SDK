/**
 * @file rtboard1_1.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2022
 *
 * @date April 11, 2016, 06:07 PM
 *
 * @brief Definitions for RTboard v1.1 from Robotips
 */

#ifndef RTBOARD1_1_H
#define RTBOARD1_1_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "rtboard1_1"
#define SYSCLOCK_XTAL 8000000

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1      LATDbits.LATD11
#define LED2      LATAbits.LATA15
#define LED3      LATAbits.LATA4
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// voltage measurement
#define BOARD_VOLT_IN 9  // RB9		// analog board voltage channel

// motors pins
#define M1A     LATBbits.LATB10  // A pin direction
#define M1B     LATBbits.LATB11  // B pin direction
#define M1en    LATFbits.LATF3   // pwm/en pin
#define M1fault PORTBbits.RB12   // bridge default input pin
#define M1I     15               // RB15               // analog current channel

#define M2A     LATBbits.LATB13  // A pin direction
#define M2B     LATDbits.LATD14  // B pin direction
#define M2en    LATFbits.LATF2   // pwm/en pin
#define M2fault PORFBbits.RF8    // bridge default input pin
#define M2I     14               // RB14               // analog current channel

// AX12
#define AX12_TXEN      LATBbits.LATB0  // AX12 buffer direction
#define AX12_TXEN_PORT GPIO_PORTB
#define AX12_TXEN_PIN  0
#define AX12_UART      3

// A6
#define A6_RW      LAADbits.LATA6  // A6 trancever direction
#define A6_RW_PORT GPIO_PORTA
#define A6_RW_PIN  6
#define A6_RE      LATDbits.LATD0
#define A6_RE_PORT GPIO_PORTD
#define A6_RE_PIN  0
#define A6_UART    2

// ESP8266
#define ESP8266_UART 1

// Analog ports
#define ANS0 24
#define ANS1 25
#define ANS2 26
#define ANS3 27
#define ANS4 28
#define ANS5 29
#define ANS6 30
#define ANS7 31
#define ANS8 1

#define OLED_I2C_ADDR 0b01111000

#endif  // RTBOARD1_1_H
