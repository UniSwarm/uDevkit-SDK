/**
 * @file curiosity_dsPIC33CK.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022
 *
 * @date December 15, 2022, 07:42 PM
 *
 * @brief Code for Curiosity dsPIC33CK board (DM330030)
 *
 * product page:
 *  http://www.microchip.com/developmenttools/ProductDetails/PartNO/DM330030
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/dsPIC33CK-Curiosity-Development-Board-User%27s-Guide-DS50002859A.pdf
 */

#ifndef CURIOSITY_DSPIC33CK_H
#define CURIOSITY_DSPIC33CK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "curiosity_dsPIC33CK"
#define SYSCLOCK_POSC 8000000  // 8MHz

// Peripherals assignation
#define UART_MIKRO_A_ID 1
#define UART_MIKRO_B_ID 2
#define UART_DBG_ID     3

// ==== pins define ====
// leds
#define LED_COUNT 5
#define LED1      0
#define LED2      1
#define LEDR      2
#define LEDG      3
#define LEDB      4
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1     0
#define BUTTON_2     1
#define BUTTON_3     2
int8_t board_getButton(uint8_t button);

// analog iputs
#define POTENTIOMETER_ADC_CHAN ADC_CHANNEL_CH0
#define TEMP_ADC_CHAN          ADC_CHANNEL_CH16
#define VBUS_ADC_CHAN          ADC_CHANNEL_CH21

#ifdef __cplusplus
}
#endif

#endif  // CURIOSITY_DSPIC33CK_H
