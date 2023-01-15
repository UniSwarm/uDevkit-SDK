/**
 * @file udt1cr-i.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2018-2023
 *
 * @date November 26, 2018, 18:00 PM
 *
 * @brief Code for UDT1FR from UniSwarm
 *
 * product page:
 *  https://uniswarm.fr/uboards/udt/udt1fr
 */

#ifndef UDT1CRI_H
#define UDT1CRI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>
#include <driver/device.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UDT1FR-I"
#define SYSCLOCK_XTAL 24000000

// ==== pins define ====
// leds
#define LED_COUNT 5
#define LED1      0
#define LED2      1
#define LED3      2
#define LED4      3
#define LED5      4
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// coms
#define CAN_ID_CAN_BUS    2
#define UART_ID_RS485_BUS 2
#define UART_ID_DBG       1

// ios
rt_dev_t board_iso_en_gpio(void);
rt_dev_t board_iso_rs485_re_gpio(void);
rt_dev_t board_iso_rs485_de_gpio(void);

#ifdef __cplusplus
}
#endif

#endif  // UDT1CRI_H
