/**
 * @file uio8ad.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2020
 *
 * @date August 31, 2020, 11:30 AM
 *
 * @brief Board support package for UIO8AD(FR) / UIO8AD(FR)-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/uio/uio8ad
 */

#ifndef UIO8AD_H
#define UIO8AD_H

#include <archi.h>

#include <stdint.h>

int board_init();

#define BOARD_NAME    "UIO8AD"
#define SYSCLOCK_POSC 24000000  // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT 11
#define LEDOUT1   0
#define LEDOUT2   1
#define LEDOUT3   2
#define LEDOUT4   3
#define LEDOUT5   4
#define LEDOUT6   5
#define LEDOUT7   6
#define LEDOUT8   7
#define LED1R     8
#define LED1G     9
#define LED1B     10
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS    1
#define UART_ID_RS485_BUS 1

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// outs
#define OUT_COUNT           8
#define BOARD_OUT1_PWM_CHAN 5
#define BOARD_OUT2_PWM_CHAN 7
#define BOARD_OUT3_PWM_CHAN 4
#define BOARD_OUT4_PWM_CHAN 3
#define BOARD_OUT5_PWM_CHAN 2
#define BOARD_OUT6_PWM_CHAN 1
#define BOARD_OUT7_PWM_CHAN 8
#define BOARD_OUT8_PWM_CHAN 6
int board_setIO(uint8_t io, uint16_t state);

// Analog input
#define ANALOGIN_COUNT     8
#define BOARD_IN0_ADC_CHAN 12
#define BOARD_IN1_ADC_CHAN 0
#define BOARD_IN2_ADC_CHAN 1  // ANA1
#define BOARD_IN3_ADC_CHAN 9
#define BOARD_IN4_ADC_CHAN 3
#define BOARD_IN5_ADC_CHAN 4
#define BOARD_IN6_ADC_CHAN 13
#define BOARD_IN7_ADC_CHAN 14
uint8_t board_analogin(uint8_t io);

#endif  // UIO8AD_H
