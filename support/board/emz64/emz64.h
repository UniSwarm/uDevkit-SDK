/**
 * @file emz64.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date March 01, 2017, 06:09 PM
 *
 * @brief Definitions for pic32-emz64 from Olimex
 */

#ifndef EMZ64_H
#define EMZ64_H

#ifndef SIMULATOR
 #include <xc.h>
#endif

#include <stdint.h>

int board_init();

#define BOARD_NAME "PIC32-EMZ64"
#define SYSCLOCK_XTAL 24000000

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1 LATBbits.LATB8
#define LED2 LATBbits.LATB9
#define LED3 LATBbits.LATB10
int board_setLed(uint8_t led, uint8_t state);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1 PORTBbits.RB12
#define BUTTON_2 PORTBbits.RB13
#define BUTTON_3 PORTBbits.RB14

#endif // EMZ64_H
