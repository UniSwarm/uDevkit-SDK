/**
 * @file umc1bd90.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2022
 *
 * @date April 25, 2022, 02:35 PM
 *
 * @brief Code for UMC1BD90FR / UMC1BD90FR-I board
 *
 * product page:
 *  https://uniswarm.eu/uboards/umc/umc1bd90
 */

#ifndef UMC1BD90FR_H
#define UMC1BD90FR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>
#include <driver/adc.h>

#include <stdint.h>

int board_init(void);

#define BOARD_NAME    "UMC1BD90"
#define SYSCLOCK_POSC 24000000  // 24MHz

// ==== pins define ====
// leds
#define LED_COUNT 6
#define LED1R     0
#define LED1G     1
#define LED1B     2
#define LED2R     3
#define LED2G     4
#define LED2B     5
int board_setLed(uint8_t led, uint8_t state);
int board_toggleLed(uint8_t led);
int8_t board_getLed(uint8_t led);

// coms
#define CAN_ID_CAN_BUS    1
#define UART_ID_RS485_BUS 1

// buttons
#define BUTTON_COUNT 1
#define BUTTON_RESET PORTDbits.RD13
int8_t board_getButton(uint8_t button);

// bridges
void board_setBridgesEnabled(int enable);

#define BRIDGE_DISABLED_OUT  LATDbits.LATD14
#define BRIDGE_DISABLED_IN   PORTDbits.RD14
#define BRIDGE_POWER_ENABLED LATCbits.LATC12
#define BRIDGE_COUNT         3
#define BRIDGE_A_PWM         2
#define BRIDGE_B_PWM         1
#define BRIDGE_C_PWM         3

// hall sensors
#define BLDC_1_HALL_HIGH_STATE 1
#define BLDC_1_HALL_A          PORTCbits.RC1
#define BLDC_1_HALL_B          PORTCbits.RC2
#define BLDC_1_HALL_C          PORTCbits.RC0

// analog iputs
#define TEMP_AB_ADC_CHAN  ADC_CHANNEL_CH0
#define TEMP_CD_ADC_CHAN  ADC_CHANNEL_CH1
#define V_BRIDGE_ADC_CHAN ADC_CHANNEL_CH2

#define V_BRIDGE_SADC_CHAN ADC_CHANNEL_CH16

#define I_A_CMP 3
#define I_B_CMP 2
#define I_C_CMP 1

// IOs
#define IO_COUNT 8
#define IO_1_IN  PORTEbits.RE4
#define IO_2_IN  PORTEbits.RE5
#define IO_3_IN  PORTDbits.RD15
#define IO_4_IN  PORTEbits.RE3
#define IO_5_IN  PORTCbits.RC12
#define IO_6_IN  PORTDbits.RD0
#define IO_7_IN  PORTDbits.RD2
#define IO_8_IN  PORTEbits.RE14
int8_t board_getIo(uint8_t io);

// limit switches inputs
#define LIMIT_SWITCH_NO_PORT   0
#define LIMIT_SWITCH_NO_OFFSET 0
#define LIMIT_SWITCH_COUNT     12
#define LIMIT_SWITCH_5_PORT    PORTE
#define LIMIT_SWITCH_5_OFFSET  4
#define LIMIT_SWITCH_6_PORT    PORTE
#define LIMIT_SWITCH_6_OFFSET  5
#define LIMIT_SWITCH_7_PORT    PORTD
#define LIMIT_SWITCH_7_OFFSET  15
#define LIMIT_SWITCH_8_PORT    PORTE
#define LIMIT_SWITCH_8_OFFSET  3
#define LIMIT_SWITCH_9_PORT    PORTC
#define LIMIT_SWITCH_9_OFFSET  12
#define LIMIT_SWITCH_10_PORT   PORTD
#define LIMIT_SWITCH_10_OFFSET 0
#define LIMIT_SWITCH_11_PORT   PORTD
#define LIMIT_SWITCH_11_OFFSET 2
#define LIMIT_SWITCH_12_PORT   PORTE
#define LIMIT_SWITCH_12_OFFSET 14

// STO
#define STO_STATUS_OK_IN PORTEbits.RE0
#define STO_OUTPUT       PORTEbits.RE1
#define P12V_ENABLE      LATEbits.LATE2

// Currents limits
#define CURRENT_PEAK_LIMIT      9000
#define CURRENT_PEAK_PERIOD     40
#define CURRENT_BURST_LIMIT     7500
#define CURRENT_BURST_TIME      1000  // in ms
#define CURRENT_SUSTAINED_LIMIT 6000
#define CURRENT_I2T_SCALE_SHIFT 3
// = current protection call frequency * burst time time unit. ex: 32kHz * 1ms = 32
#define CURRENT_LOOP_TIME_MULTIPLER 32

// Under/Over voltage protection
#define UNDER_VOLTAGE_MIN 1100  // 0.01 V
#define OVER_VOLTAGE_MAX  5500  // 0.01 V

// Temperatures limits
#define BRIDGES_OVER_TEMP_TRIG_HIGH_MAX 800  // 0.1 °C
#define BRIDGES_OVER_TEMP_TRIG_LOW_MAX  750  // 0.1 °C

// Memory page adress
#define ADRESS_BYTE_PAGE_1_COM 0xAA000  // PAGE 170
#define ADRESS_BYTE_PAGE_2_MAN 0xAB000  // PAGE 171
#define ADRESS_BYTE_PAGE_3_STD 0xAC000  // PAGE 172
#define ADRESS_BYTE_PAGE_4_STD 0xAD000  // PAGE 173
#define ADRESS_BYTE_PAGE_5_CAL 0xAE000  // PAGE 174

#define OTP_SECTOR_BEGINADDR      (0x801700 * 2)
#define OTP_SECTOR_SECTOR_ENDADDR (0x801800 * 2)
#define OTP_SECTOR_BYTE_SIZE      (OTP_SECTOR_SECTOR_ENDADDR - OTP_SECTOR_BEGINADDR)

inline int board_bridgesEnabled(void);
inline int board_bridgesEnabled(void)
{
#ifndef SIMULATOR
    return (BRIDGE_DISABLED_IN == 0 && STO_STATUS_OK_IN == 1) ? 1 : 0;
#else
    return 1;
#endif
}

#ifdef __cplusplus
}
#endif

#endif  // UMC1BD90FR_H
