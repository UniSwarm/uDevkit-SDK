/**
 * @file curiosity_PIC24F.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date July 28, 2017, 15:34 PM
 *
 * @brief Code for Curiosity 32MM USB board (DM320107)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM24004
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002534a.pdf
 */

#ifndef CURIOSITY_PIC24F_H
#define CURIOSITY_PIC24F_H

#include <archi.h>

#include <stdint.h>

int board_init();

#define BOARD_NAME "Curiosity_PIC24F"
#define SYSCLOCK_SOSC    32768

// ==== pins define ====
// leds
#define LED_COUNT 2
#define LED1 LATAbits.LATA9
#define LED2 LATAbits.LATA10
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 2
#define BUTTON_1 PORTCbits.RC9
#define BUTTON_2 PORTCbits.RC8
int8_t board_getButton(uint8_t button);

#define ANPOT0 10

#endif // CURIOSITY_PIC24F_H
