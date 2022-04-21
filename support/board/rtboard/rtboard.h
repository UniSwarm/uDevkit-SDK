/**
 * @file rtboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016-2017
 * @copyright UniSwarm 2018-2022
 *
 * @date April 11, 2016, 06:07 PM
 *
 * @brief Definitions for RTboard from Robotips
 */

#ifndef RTBOARD_H
#define RTBOARD_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "rtboard"
#define SYSCLOCK_XTAL 8000000

// ==== pins define ====
// leds
#define LED_COUNT 1
#define LED1      LATDbits.LATD11
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// voltage measurement
#define BOARD_VOLT_IN 2  // RB2     // analog board voltage channel

// motors pins
#define M1A  LATBbits.LATB14  // A pin direction
#define M1B  LATBbits.LATB15  // B pin direction
#define M1en LATDbits.LATD0   // pwm/en pin
#define M1I  7                // RB7            // analog current channel

#define M2A  LATBbits.LATB12  // A pin direction
#define M2B  LATBbits.LATB13  // B pin direction
#define M2en LATFbits.LATF3   // pwm/en pin
#define M2I  6                // RB6            // analog current channel

#define M3A  LATBbits.LATB8  // A pin direction
#define M3B  LATBbits.LATB9  // B pin direction
#define M3en LATFbits.LATF5  // pwm/en pin
#define M3I  0               // RB0            // analog current channel

#define M4A  LATBbits.LATB11  // A pin direction
#define M4B  LATBbits.LATB10  // B pin direction
#define M4en LATFbits.LATF4   // pwm/en pin
#define M4I  1                // RB1            // analog current channel

// AX12
#define AX12_TXEN      LATBbits.LATB3  // AX12 buffer direction
#define AX12_TXEN_PORT GPIO_PORTB
#define AX12_TXEN_PIN  3
#define AX12_UART      3

// A6
#define A6_RW      LATDbits.LATD1  // A6 trancever direction
#define A6_RW_PORT GPIO_PORTD
#define A6_RW_PIN  1
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
#define ANS8 4

#endif  // RTBOARD_H
