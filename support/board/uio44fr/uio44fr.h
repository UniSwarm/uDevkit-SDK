/**
 * @file uio44fr.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2019
 *
 * @date November 28, 2018, 09:30 AM
 *
 * @brief Code for UIO44FR / UIO44FR-I board
 * 
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio44fr
 */

#ifndef UIO44FR_H
#define UIO44FR_H

#include <archi.h>

#include <stdint.h>

int board_init();

#define BOARD_NAME "UIO44FR"
#define SYSCLOCK_POSC    24000000 // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT 6
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4 // RS485 err
#define LED_RS485_ERR LED5
#define LED6 5 // CAN err
#define LED_CANFD_ERR LED6
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS 1
#define UART_ID_RS485_BUS 1
#define UART_ID_DBG 2

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// outs
#define OUT_COUNT 4
int board_setIO(uint8_t io, uint8_t state);

#endif // UIO44FR_H
