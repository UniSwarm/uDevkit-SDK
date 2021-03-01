/**
 * @file curiosity_32MM_USB.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date July 28, 2017, 15:34 PM
 *
 * @brief Code for Curiosity 32MM USB board (DM320107)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320107
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002576a%20PIC32MM%20USB%20Curiosity%20Development%20Board%20Quick%20Start%20Guide.pdf
 */

#ifndef CURIOSITY_32MM_USB_H
#define CURIOSITY_32MM_USB_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME "Curiosity_MM_USB"
#define SYSCLOCK_XTAL 20000000
//#define SYSCLOCK_SOSC    32768

// ==== pins define ====
// leds
#define LED_COUNT 2
#define LED1 LATDbits.LATD3
#define LED2 LATCbits.LATC13
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1 PORTBbits.RB9
#define BUTTON_2 PORTCbits.RC10
#define BUTTON_3 PORTCbits.RC4
int8_t board_getButton(uint8_t button);

#endif // CURIOSITY_32MM_USB_H
