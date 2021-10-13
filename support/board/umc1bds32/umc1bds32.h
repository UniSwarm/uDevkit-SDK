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
#define BUTTON_COUNT 1
#define BUTTON_RESET PORTDbits.RD13
int8_t board_getButton(uint8_t button);

// bridges
void board_setBridgesEnabled(int enable);
int board_bridgesEnabled(void);
#define BRIDGE_DISABLED_OUT  LATDbits.LATD14
#define BRIDGE_DISABLED_IN   PORTDbits.RD14
#define BRIDGE_POWER_ENABLED LATCbits.LATC12
#if BOARD_VERSION < 110
#    define BRIDGE_A_PWM 4
#    define BRIDGE_B_PWM 1
#    define BRIDGE_C_PWM 2
//#    define BRIDGE_D_PWM 3
#else
//#    define BRIDGE_POWEREN_PWM 4
#    define BRIDGE_A_PWM 2
#    define BRIDGE_B_PWM 1
#    define BRIDGE_C_PWM 3
//#    define BRIDGE_D_PWM       4
#endif

#define BRIDGES_OVER_TEMP_TRIG_HIGH_MAX 800
#define BRIDGES_OVER_TEMP_TRIG_LOW_MAX  750

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

// IOs
#if BOARD_VERSION < 111
#    define IO_COUNT 0
#else
#    define IO_COUNT 8
#    define IO_1_IN  PORTEbits.RE4
#    define IO_2_IN  PORTEbits.RE5
#    define IO_3_IN  PORTDbits.RD15
#    define IO_4_IN  PORTEbits.RE3
#    define IO_5_IN  PORTCbits.RC12
#    define IO_6_IN  PORTDbits.RD0
#    define IO_7_IN  PORTDbits.RD2
#    define IO_8_IN  PORTEbits.RE14
#endif
int8_t board_getIo(uint8_t io);

// limit switches inputs
#define LIMIT_SWITCH_NO_PORT   0
#define LIMIT_SWITCH_NO_OFFSET 0
#define LIMIT_SWITCH_1_PORT    PORTC
#define LIMIT_SWITCH_1_OFFSET  1
#define LIMIT_SWITCH_2_PORT    PORTC
#define LIMIT_SWITCH_2_OFFSET  2
#define LIMIT_SWITCH_3_PORT    PORTC
#define LIMIT_SWITCH_3_OFFSET  0
#define LIMIT_SWITCH_4_PORT    PORTD
#define LIMIT_SWITCH_4_OFFSET  10
#if BOARD_VERSION < 111
#    define LIMIT_SWITCH_COUNT 4
#else
#    define LIMIT_SWITCH_COUNT     12
#    define LIMIT_SWITCH_5_PORT    PORTE
#    define LIMIT_SWITCH_5_OFFSET  4
#    define LIMIT_SWITCH_6_PORT    PORTE
#    define LIMIT_SWITCH_6_OFFSET  5
#    define LIMIT_SWITCH_7_PORT    PORTD
#    define LIMIT_SWITCH_7_OFFSET  15
#    define LIMIT_SWITCH_8_PORT    PORTE
#    define LIMIT_SWITCH_8_OFFSET  3
#    define LIMIT_SWITCH_9_PORT    PORTC
#    define LIMIT_SWITCH_9_OFFSET  12
#    define LIMIT_SWITCH_10_PORT    PORTD
#    define LIMIT_SWITCH_10_OFFSET  0
#    define LIMIT_SWITCH_11_PORT   PORTD
#    define LIMIT_SWITCH_11_OFFSET 2
#    define LIMIT_SWITCH_12_PORT   PORTE
#    define LIMIT_SWITCH_12_OFFSET 14
#endif

//
#define STO_STATUS_OK_IN PORTEbits.RE0
#define STO_OUTPUT       PORTEbits.RE1
#define P12V_ENABLE      LATEbits.LATE2

// Page adress
#if BOARD_VERSION < 110
#    define ADRESS_BYTE_PAGE_1_COM 0x26000
#    define ADRESS_BYTE_PAGE_2_MAN 0x27000
#    define ADRESS_BYTE_PAGE_3_STD 0x28000
#    define ADRESS_BYTE_PAGE_4_STD 0x29000
#    define ADRESS_BYTE_PAGE_5_CAL 0x2A000
#else
#    define ADRESS_BYTE_PAGE_1_COM 0xAA000  // PAGE 170
#    define ADRESS_BYTE_PAGE_2_MAN 0xAB000  // PAGE 171
#    define ADRESS_BYTE_PAGE_3_STD 0xAC000  // PAGE 172
#    define ADRESS_BYTE_PAGE_4_STD 0xAD000  // PAGE 173
#    define ADRESS_BYTE_PAGE_5_CAL 0xAE000  // PAGE 174
#endif

#endif  // UMC1BDS32FR_H
