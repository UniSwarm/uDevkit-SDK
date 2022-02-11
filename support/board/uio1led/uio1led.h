/**
 * @file uio1led.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2021
 *
 * @date August 11, 2021, 07:42 PM
 *
 * @brief Board support package for UIO1LEDF board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio1led
 */

#ifndef UIO1LED_H
#define UIO1LED_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UIO1LED"
#define SYSCLOCK_POSC 24000000  // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT 0
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS 1

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// outs
#define LED_CLK_LAT LATBbits.LATB12
#define LED_CLK_RP  44
#define LED_DAT_LAT LATBbits.LATB13
#define LED_DAT_RP  45

// Analog input
#define VOLTAGEIN_ADC_CHAN 3

// Memory page adress
#define ADRESS_BYTE_PAGE_1_COM 0x52000
#define ADRESS_BYTE_PAGE_2_MAN 0x53000
#define ADRESS_BYTE_PAGE_3_STD 0x54000
#define ADRESS_BYTE_PAGE_4_STD 0x55000
#define ADRESS_BYTE_PAGE_5_CAL 0x56000

#define OTP_SECTOR_BEGINADDR      (0x801700 * 2)
#define OTP_SECTOR_SECTOR_ENDADDR (0x801800 * 2)
#define OTP_SECTOR_BYTE_SIZE      (OTP_SECTOR_SECTOR_ENDADDR - OTP_SECTOR_BEGINADDR)

#endif  // UIO1LED_H
