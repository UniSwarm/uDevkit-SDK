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

#define UNUSED(x) (void)(x)

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

// analog iputs
#define TEMP_AB_ADC_CHAN 0
#define TEMP_CD_ADC_CHAN 1
#define V_BRIDGE_ADC_CHAN 2
#define I_BRIDGE_ADC_CHAN 7

#define BEMF_A_SADC_CHAN 1
#define BEMF_B_SADC_CHAN 4
#define BEMF_C_SADC_CHAN 0
#define BEMF_D_SADC_CHAN 12
#define V_BRIDGE_SADC_CHAN 16
#define I_BRIDGE_SADC_CHAN 3
#define I_A_SADC_CHAN 0
#define I_A_PGA 1
#define I_B_SADC_CHAN 1
#define I_B_PGA 3
#define I_CD_SADC_CHAN 14
#define I_CD_PGA 2

#endif // UMC1BDS32FR_H
