/**
 * @file rtboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 * @copyright UniSwarm 2018-2021
 *
 * @date April 25, 2016, 08:49 AM
 *
 * @brief Definitions for RTboard from Robotips
 */

#ifndef A6SCREENBOARD_H
#define A6SCREENBOARD_H

#include <archi.h>
#include <stdint.h>

int board_init(void);

#define BOARD_NAME "a6screenboard"

// ==== pins define ====
// no leds and no buttons
#define LED_COUNT 0
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// screen
#define SCREEN_PORT_OUT    LATB
#define SCREEN_PORT_OUTPUT (TRISB = 0x0000)

#define SCREEN_PORT_IN    PORTB
#define SCREEN_PORT_INPUT (TRISB = 0xFFFF)

#define SCREEN_RD    LATDbits.LATD3
#define SCREEN_RW    LATDbits.LATD2
#define SCREEN_RS    LATDbits.LATD1
#define SCREEN_CS    LATDbits.LATD0
#define SCREEN_RST   LATDbits.LATD4
#define SCREEN_LEDBL LATEbits.LATE4

// AR1021
#define AR1000_MODE AR1021_SPI
#define AR1000_M1   LATEbits.LATE6
#define AR1000_INT  PORTEbits.RE7

// A6
#define A6_RW      LATFbits.LATF1  // A6 trancever direction
#define A6_RW_PORT GPIO_PORTF
#define A6_RW_PIN  1
#define A6_UART    1

#endif  // A6SCREENBOARD_H
