/**
 * @file curiosity_dsPIC33AK128MC106.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2025
 *
 * @date June 22, 2025, 06:01 PM
 *
 * @brief Code for Curiosity dsPIC33AK128MC106 board (EV02G02A) plus Curiosity Platform Development Board (EV74H48A)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/ev02g02a
 *  https://www.microchip.com/en-us/development-tool/EV74H48A
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/InformationSheet/dsPIC33AK128MC106-General-Purpose-DIM-Info-Sheet-DS70005556.pdf
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/Curiosity-Platform-Development-Board-Users-Guide-DS70005562.pdf
 */

#ifndef CURIOSITY_DSPIC33AK128MC106_H
#define CURIOSITY_DSPIC33AK128MC106_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "Curiosity_dsPIC33AK128MC106"
#define SYSCLOCK_XTAL 8000000

// ==== pins define ====
// leds
#define LED_COUNT 5
#define LED1      LATCbits.LATC3
#define LED2      LATCbits.LATC4
#define LED3      LATCbits.LATC5
#define LED4      LATCbits.LATC6
#define LED5      LATCbits.LATC7
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1     PORTAbits.RA6
#define BUTTON_2     PORTBbits.RB4
#define BUTTON_3     PORTBbits.RB5
int8_t board_getButton(uint8_t button);

#ifdef __cplusplus
}
#endif

#endif  // CURIOSITY_DSPIC33AK128MC106_H
