/**
 * @file umc1bds32fr.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board
 * 
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32fr
 */

#ifndef UMC1BDS32FR_H
#define UMC1BDS32FR_H

#include <archi.h>

#include <stdint.h>

int board_init();

#define BOARD_NAME "UMC1BDS32FR"
#define SYSCLOCK_POSC    24000000 // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT 4
#define LED1 0
#define LED2 1
#define LED3 2 // RS485 err
#define LED_RS485_ERR LED3
#define LED4 3 // CAN err
#define LED_CANFD_ERR LED4
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

// bridges
#define BRIDGE_A_PWM 4
#define BRIDGE_B_PWM 1
#define BRIDGE_C_PWM 2
#define BRIDGE_D_PWM 3

#endif // UMC1BDS32FR_H
