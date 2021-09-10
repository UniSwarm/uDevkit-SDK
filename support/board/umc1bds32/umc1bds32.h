/**
 * @file umc1bds32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2021
 *
 * @date March 1, 2019, 09:35 AM
 *
 * @brief Code for UMC1BDS32FR / UMC1BDS32FR-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bds32
 */

#ifndef UMC1BDS32FR_H
#define UMC1BDS32FR_H

#include <archi.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UMC1BDS32FR"
#define SYSCLOCK_POSC 24000000  // 24MHz

// ==== pins define ====
// leds
#if BOARD_VERSION < 110
#    define LED_COUNT     4
#    define LED1          0
#    define LED2          1
#    define LED3          2  // RS485 err
#    define LED_RS485_ERR LED3
#    define LED4          3  // CAN err
#    define LED_CANFD_ERR LED4
#else
#    define LED_COUNT 6
#    define LED1R     0
#    define LED1G     1
#    define LED1B     2
#    define LED2R     3
#    define LED2G     4
#    define LED2B     5
#endif
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS    1
#define UART_ID_RS485_BUS 1
#define UART_ID_DBG       2

// buttons
#define BUTTON_COUNT 0
int8_t board_getButton(uint8_t button);

// bridges
#if BOARD_VERSION < 110
#    define BRIDGE_A_PWM 4
#    define BRIDGE_B_PWM 1
#    define BRIDGE_C_PWM 2
//#    define BRIDGE_D_PWM 3
#else
//#    define BRIDGE_POWEREN_PWM 4
#    define BRIDGE_A_PWM       2
#    define BRIDGE_B_PWM       1
#    define BRIDGE_C_PWM       3
//#    define BRIDGE_D_PWM       4
#endif

// hall sensors
#define BLDC_1_HALL_HIGH_STATE 1
#define BLDC_1_HALL_A          PORTCbits.RC1
#define BLDC_1_HALL_B          PORTCbits.RC2
#define BLDC_1_HALL_C          PORTCbits.RC0

// analog iputs
#define TEMP_AB_ADC_CHAN  0
#define TEMP_CD_ADC_CHAN  1
#define V_BRIDGE_ADC_CHAN 2
#define I_BRIDGE_ADC_CHAN 7

#define V_BRIDGE_SADC_CHAN 16
#define I_BRIDGE_SADC_CHAN 3

#if BOARD_VERSION < 110
#    define BEMF_A_SADC_CHAN 1
#    define BEMF_B_SADC_CHAN 4
#    define BEMF_C_SADC_CHAN 0
#    define BEMF_D_SADC_CHAN 12
#    define I_A_SADC_CHAN    0
#    define I_A_PGA          1
#    define I_B_SADC_CHAN    1
#    define I_B_PGA          3
#    define I_CD_SADC_CHAN   14
#    define I_CD_PGA         2
#else
#    define BEMF_A_SADC_CHAN 12
#    define BEMF_C_SADC_CHAN 11
#    define BEMF_D_SADC_CHAN 14
#    define I_A_SADC_CHAN    18
#    define I_A_CMP          3
#    define I_A_PGA          3
#    define I_B_SADC_CHAN    1
#    define I_B_CMP          2
#    define I_B_PGA          2
#    define I_CD_SADC_CHAN   0
#    define I_CD_CMP         1
#    define I_CD_PGA         1
#    define ANI1_SADC_CHAN   6
#    if BOARD_VERSION < 111
#        define BEMF_B_SADC_CHAN 4
#        define ANI2_SADC_CHAN   8
#    else
#        define BEMF_B_SADC_CHAN 17
#        define ANI2_SADC_CHAN   13
#    endif
#endif

//
#define STO_STATUS_OK PORTEbits.RE0
#define P12V_ENABLE LATEbits.LATE2
#define BRIDGE_DISABLED_OUT LATDbits.LATD14
#define BRIDGE_DISABLED_IN  PORTDbits.RD14
#define BRIDGE_POWER_ENABLED LATCbits.LATC12

// Page adress
#if BOARD_VERSION < 110
#    define ADRESS_BYTE_PAGE_1_COM 0x26000
#    define ADRESS_BYTE_PAGE_2_MAN 0x27000
#    define ADRESS_BYTE_PAGE_3_STD 0x28000
#    define ADRESS_BYTE_PAGE_4_STD 0x29000
#    define ADRESS_BYTE_PAGE_5_CAL 0x2A000
#else
#    define ADRESS_BYTE_PAGE_1_COM 0xAA000 // PAGE 170
#    define ADRESS_BYTE_PAGE_2_MAN 0xAB000 // PAGE 171
#    define ADRESS_BYTE_PAGE_3_STD 0xAC000 // PAGE 172
#    define ADRESS_BYTE_PAGE_4_STD 0xAD000 // PAGE 173
#    define ADRESS_BYTE_PAGE_5_CAL 0xAE000 // PAGE 174
#endif

#endif  // UMC1BDS32FR_H
