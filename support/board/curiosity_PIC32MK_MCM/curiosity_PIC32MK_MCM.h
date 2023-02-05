/**
 * @file curiosity_PIC32MK_MCM.h
 * @author Sebastien CAUX (secaux)
 * @copyright UniSwarm 2022-2023
 *
 * @date December 5, 2022, 09:53 PM
 *
 * @brief Code for Curiosity PIC32MK MCM board (EV31E34A)
 *
 * product page:
 *  https://www.microchip.com/en-us/development-tool/EV31E34A
 * datasheet:
 *  https://www.microchip.com/content/dam/mchp/documents/MCU32/ProductDocuments/UserGuides/PICK32MK-MCM-Curiosity-Pro-User-Guide-DS70005419.pdf
 */

#ifndef CURIOSITY_PIC32MK_MCM_H
#define CURIOSITY_PIC32MK_MCM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "Curiosity_PIC32MK_MCM"
#define SYSCLOCK_XTAL 12000000
#define SYSCLOCK_SOSC 32768

// ==== pins define ====
// leds
#define LED_COUNT 3
#define LED1      LATGbits.LATG12
#define LED2      LATGbits.LATG13
#define LED3      LATGbits.LATG14
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// buttons
#define BUTTON_COUNT 3
#define BUTTON_1     PORTGbits.RG11
#define BUTTON_2     PORTFbits.RF13
#define BUTTON_3     PORTFbits.RF12
int8_t board_getButton(uint8_t button);

// Peripherals assignation
#define UART_MIKROBUS_A_ID 3
#define UART_MIKROBUS_B_ID 4
#define UART_DBG_ID        6

#ifdef __cplusplus
}
#endif

#endif  // CURIOSITY_PIC32MK_MCM_H
