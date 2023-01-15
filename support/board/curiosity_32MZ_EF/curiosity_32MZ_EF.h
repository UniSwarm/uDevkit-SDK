/**
 * @file curiosity_32MZ_EF.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2023
 *
 * @date July 25, 2017, 11:20 AM
 *
 * @brief Code for Curiosity 32MZ EF board (DM320103)
 *
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320103
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005283B.pdf
 */

#ifndef CURIOSITY_32MZ_EF_H
#define CURIOSITY_32MZ_EF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "Curiosity_MZ_EF"
#define SYSCLOCK_XTAL 24000000
// #define SYSCLOCK_SOSC    32768

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1      LATEbits.LATE3
#define LED2      LATEbits.LATE4
#define LED3      LATEbits.LATE6
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 1
#define BUTTON_1     PORTGbits.RG12
int8_t board_getButton(uint8_t button);

#ifdef __cplusplus
}
#endif

#endif  // CURIOSITY_32MZ_EF_H
