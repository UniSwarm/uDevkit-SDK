/**
 * @file umc1bds32.h
 * @author Sebastien CAUX (sebcaux)
 * @copyright UniSwarm 2019-2023
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

#ifdef __cplusplus
extern "C" {
#endif

#include <archi.h>

#include <stdint.h>

#include <driver/adc.h>

int board_init(void);

#define BOARD_NAME    "UMC1BDS32"
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
#define UART_ID_DBG       2

// buttons
#define BUTTON_COUNT 1
#define BUTTON_RESET PORTDbits.RD13
int8_t board_getButton(uint8_t button);

// bridges
void board_setBridgesEnabled(int enable);

#define BRIDGE_DISABLED_OUT  LATDbits.LATD14
#define BRIDGE_DISABLED_IN   PORTDbits.RD14
#define BRIDGE_POWER_ENABLED LATCbits.LATC12
#define BRIDGE_COUNT         4
#define BRIDGE_A_PWM         2
#define BRIDGE_B_PWM         1
#define BRIDGE_C_PWM         3
#define BRIDGE_D_PWM         4

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
#define I_D_CMP 1  // master

// Digital inputs
#define DI_1_IN0 PORTCbits.RC13
#define DI_1_IN1 PORTCbits.RC14
#define DI_1_IN2 PORTCbits.RC15

#define DI_1_IN3 PORTCbits.RC1
#define DI_1_IN4 PORTCbits.RC2
#define DI_1_IN5 PORTCbits.RC0

// STO
#define STO_STATUS_OK_IN PORTEbits.RE0
#define STO_OUTPUT       PORTEbits.RE1
#define P12V_ENABLE      LATEbits.LATE2

// IO dbg
#ifndef SECONDARY
#    define DBG1 LATBbits.LATB4
#    define DBG2 LATEbits.LATE13
#else
#    define DBG1 LATDbits.LATD2
#    define DBG2 LATEbits.LATE12
#endif

// Currents limits
#define CURRENT_PEAK_LIMIT      3200
#define CURRENT_PEAK_PERIOD     40
#define CURRENT_BURST_LIMIT     2400
#define CURRENT_BURST_TIME      1000  // in ms
#define CURRENT_SUSTAINED_LIMIT 1600
#define CURRENT_I2T_SCALE_SHIFT 3
// = current protection call frequency * burst time time unit. ex: 32kHz * 1ms = 32
#define CURRENT_LOOP_TIME_MULTIPLER 32

// Under/Over voltage protection
#define UNDER_VOLTAGE_MIN 1100  // 0.01 V
#define OVER_VOLTAGE_MAX  6000  // 0.01 V

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

#endif  // UMC1BDS32FR_H
