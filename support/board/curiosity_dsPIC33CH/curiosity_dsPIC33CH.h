/**
 * @file curiosity_dsPIC33CH.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2021
 *
 * @date July 5, 2018, 09:30 AM
 *
 * @brief Code for Curiosity dsPIC33CH board (DM330028)
 * 
 * product page:
 *  http://www.microchip.com/developmenttools/ProductDetails/PartNO/DM330028
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/dsPIC33CH%20Curiosity%20Development%20Board.pdf
 */

#ifndef CURIOSITY_dsPIC33CH_H
#define CURIOSITY_dsPIC33CH_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME "Curiosity_dsPIC33CH"
#define SYSCLOCK_POSC    8000000 // 8MHz

// ==== pins define ====
// leds
#define LED_COUNT 2
#define LED1 0
#define LED2 1
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1 0
#define BUTTON_2 1
#define BUTTON_3 2
int8_t board_getButton(uint8_t button);

#define ANPOT0 0

#endif // CURIOSITY_dsPIC33CH_H
