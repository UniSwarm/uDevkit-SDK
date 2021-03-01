/**
 * @file udt1cr-i.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018
 *
 * @date November 26, 2018, 18:00 PM
 *
 * @brief Code for UDT1CR-I from UniSwarm
 */

#ifndef UDT1CRI_H
#define UDT1CRI_H

#include <archi.h>
#include <driver/device.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME "UDT1CRI_H"
#define SYSCLOCK_XTAL 24000000

// ==== pins define ====
// leds
#define LED_COUNT 5
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// coms
#define CAN_ID_CAN_BUS 2
#define UART_ID_RS485_BUS 2
#define UART_ID_DBG 1

// ios
rt_dev_t board_iso_en_gpio(void);
rt_dev_t board_iso_rs485_re_gpio(void);
rt_dev_t board_iso_rs485_de_gpio(void);

#endif // UDT1CRI_H
