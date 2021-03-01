/**
 * @file PIC32MK1024GPE_devboard.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2021
 *
 * @date October 25, 2017, 17:13 AM
 *
 * @brief Code for PIC32MK1024GPE dev board board (DM320106)
 * 
 * product page:
 *  http://www.microchip.com/Developmenttools/ProductDetails.aspx?PartNO=DM320106
 * datasheet:
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/70005316A.pdf
 *  http://ww1.microchip.com/downloads/en/DeviceDoc/50002568B.pdf
 */

#ifndef PIC32MK1024GPE_DEVBOARD_H
#define PIC32MK1024GPE_DEVBOARD_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME "PIC32MK1024GPE_DEVBOARD"
#define SYSCLOCK_XTAL 12000000
#define SYSCLOCK_SOSC    32768

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1 LATGbits.LATG12
#define LED2 LATGbits.LATG13
#define LED3 LATGbits.LATG14
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1 PORTGbits.RG11
#define BUTTON_2 PORTFbits.RF13
#define BUTTON_3 PORTFbits.RF12
int8_t board_getButton(uint8_t button);

#endif // PIC32MK1024GPE_DEVBOARD_H
