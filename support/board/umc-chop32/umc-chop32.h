/**
 * @file umc-chop32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date August 22, 2022, 10:00 AM
 *
 * @brief Board support package for UMC-CHOP32 board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc-chop32
 */

#ifndef UMC_CHOP32_H
#define UMC_CHOP32_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME "UMC-CHOP32"

// ==== pins define ====
// leds
#define LED_COUNT 3
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// Analog input
#define VOLTAGE_IN_ADC_CHAN    0
#define RESISTOR_TEMP_ADC_CHAN 9
#define BOARD_TEMP_ADC_CHAN    3
#define CURRENT_ADC_CHAN       4

#ifdef __cplusplus
}
#endif

#endif  // UMC_CHOP32_H
