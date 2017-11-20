/**
 * @file curiosity_32MX470.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 25, 2017, 11:20 AM
 *
 * @brief Code for Curiosity 32MX470 board (DM320103)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320103
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005283B.pdf
 */

#ifndef CURIOSITY_32MX470_H
#define CURIOSITY_32MX470_H

#include <archi.h>

#include <stdint.h>

int board_init();

#define BOARD_NAME "Curiosity_MX470"
#define SYSCLOCK_XTAL 20000000
//#define SYSCLOCK_SOSC    32768

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1 LATEbits.LATE4
#define LED2 LATEbits.LATE6
#define LED3 LATEbits.LATE7
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led, uint8_t state);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 1
#define BUTTON_1 PORTDbits.RD6
int8_t board_getButton(uint8_t button);

#endif // CURIOSITY_32MX470_H
