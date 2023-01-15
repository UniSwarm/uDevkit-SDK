/**
 * @file curiosity_PIC24F.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date November 23, 2017, 03:12 PM
 *
 * @brief Code for Curiosity PIC24F board (DM240004)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/DM240004
 * datasheet:
 *  https://ww1.microchip.com/downloads/en/DeviceDoc/50002534a.pdf
 */

#ifndef CURIOSITY_PIC24F_H
#define CURIOSITY_PIC24F_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "Curiosity_PIC24F"
#define SYSCLOCK_SOSC 32768

// ==== pins define ====
// leds
#define LED_COUNT 2
#define LED1      LATAbits.LATA9
#define LED2      LATAbits.LATA10
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 2
#define BUTTON_1     PORTCbits.RC9
#define BUTTON_2     PORTCbits.RC8
int8_t board_getButton(uint8_t button);

#define ANPOT0 10

#ifdef __cplusplus
}
#endif

#endif  // CURIOSITY_PIC24F_H
