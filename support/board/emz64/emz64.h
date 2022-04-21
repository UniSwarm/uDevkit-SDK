/**
 * @file emz64.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 * @copyright UniSwarm 2018-2022
 *
 * @date March 01, 2017, 06:09 PM
 *
 * @brief Definitions for pic32-emz64 from Olimex
 */

#ifndef EMZ64_H
#define EMZ64_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "PIC32-EMZ64"
#define SYSCLOCK_XTAL 24000000

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1      0
#define LED2      1
#define LED3      2
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1     0
#define BUTTON_2     1
#define BUTTON_3     2
int8_t board_getButton(uint8_t button);

// oled
#define OLED_RST      LATFbits.LATF1
#define OLED_I2C_BUS  5
#define OLED_I2C_ADDR 0b01111000

#define CAN_ID_CAN_BUS 1

#endif  // EMZ64_H
