/**
 * @file curiosity_nano_dsPIC33CK.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2025
 *
 * @date February 11, 2025, 03:27 PM
 *
 * @brief Code for Curiosity dsPIC33CK nano board (EV88G73A)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/EV88G73A
 * datasheet:
 *  https://ww1.microchip.com/downloads/aemDocuments/documents/MCU16/ProductDocuments/UserGuides/dsPIC33CK64MC105-Curiosity-Nano-Users-Guide-DS70005517.pdf
 */

#ifndef CURIOSITY_NANO_DSPIC33CK_H
#define CURIOSITY_NANO_DSPIC33CK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME "curiosity_nano_dsPIC33CK"
// #define SYSCLOCK_POSC 8000000  // 8MHz

// Peripherals assignation
#define UART_CDC_ID 1

// ==== pins define ====
// leds
#define LED_COUNT 1
#define LED1      0
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 1
#define BUTTON_1     0
int8_t board_getButton(uint8_t button);

// analog inputs
#define POTENTIOMETER_ADC_CHAN ADC_CHANNEL_CH0
#define TEMP_ADC_CHAN          ADC_CHANNEL_CH16
#define VBUS_ADC_CHAN          ADC_CHANNEL_CH21

// Peripherals assignation
#define UART_MIKROBUS_A_ID 1
#define UART_MIKROBUS_B_ID 2
#define UART_DBG_ID        3

#ifdef __cplusplus
}
#endif

#endif  // CURIOSITY_NANO_DSPIC33CK_H
